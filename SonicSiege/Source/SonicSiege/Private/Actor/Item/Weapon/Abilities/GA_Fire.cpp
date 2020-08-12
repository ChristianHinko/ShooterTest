// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Weapon/Abilities/GA_Fire.h"
#include "AbilitySystemComponent.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "AbilitySystem/TargetActors/GATA_MultiLineTrace.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/AbilitySystemCharacter.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Character/AS_Character.h"



UGA_Fire::UGA_Fire()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Fire")));

	maxTraces = 10;
}


bool UGA_Fire::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void UGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	if (!FireEffectTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("Effect TSubclassOf empty in %s so this ability was canceled - please fill out Fire ability blueprint"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}

	// take away ammo first
	FireEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, FireEffectTSub.GetDefaultObject(), GetAbilityLevel());

	// set up target actor if not already
	if (!TargetTraceActor)
	{
		TargetTraceActor = GetWorld()->SpawnActor<AGATA_MultiLineTrace>();
		TargetTraceActor->bDestroyOnConfirmation = false;
		TargetTraceActor->MaxRange = 100000.f;
		TargetTraceActor->bDebug = true;

		TargetTraceActor->maxTraces = maxTraces;			// maybe make this value vary per gun later on
		TargetTraceActor->ActorClassToCollect = ActorClassToCollect;
	}

	// update target actor's start location info
	FGameplayAbilityTargetingLocationInfo StartLocationInfo;
	StartLocationInfo.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	StartLocationInfo.LiteralTransform = GetAvatarActorFromActorInfo()->GetActorTransform();
	TargetTraceActor->StartLocation = StartLocationInfo;

	// try to make wait target data task
	UAbilityTask_WaitTargetData* WaitTargetDataActorTask = UAbilityTask_WaitTargetData::WaitTargetDataUsingActor(this, TEXT("WaitTargetDataActorTask"), EGameplayTargetingConfirmation::Instant, TargetTraceActor);
	if (!WaitTargetDataActorTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitTargetDataActorTask was NULL when trying to activate fire ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}

	// bind to wait target data delegates and activate the task
	WaitTargetDataActorTask->ValidData.AddDynamic(this, &UGA_Fire::OnValidData);
	WaitTargetDataActorTask->Cancelled.AddDynamic(this, &UGA_Fire::OnCancelled);
	WaitTargetDataActorTask->ReadyForActivation();


	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UGA_Fire::OnValidData(const FGameplayAbilityTargetDataHandle& Data)
{
	TArray<AActor*> Actors = UAbilitySystemBlueprintLibrary::GetAllActorsFromTargetData(Data);
	for (int32 i = 0; i < Actors.Num(); i++)
	{
		AActor* HitActor = Actors[i];
		if (AAbilitySystemCharacter* ASChar = Cast<AAbilitySystemCharacter>(HitActor))		// maybe check if implements IAbilitySystemInterface instead of this later (so you can apply damage to AbilitySystemActors and pawns and such)
		{
			ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(),
				UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(ASChar), BulletHitEffectTSub, GetAbilityLevel());

			if (ASChar->GetCharacterAttributeSet() && ASChar->GetCharacterAttributeSet()->GetHealth())
			{
				UKismetSystemLibrary::PrintString(this, ASChar->GetName() + "'s health is now: " + FString::SanitizeFloat(ASChar->GetCharacterAttributeSet()->GetHealth()), true, false);
			}
		}
	}
}
void UGA_Fire::OnCancelled(const FGameplayAbilityTargetDataHandle& Data)
{
	UKismetSystemLibrary::PrintString(this, "Cancelled...", true, false);
}

void UGA_Fire::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Super wraps the whole EndAbility() in IsEndAbilityValid()
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	// Make sure we bind our child class' version of EndAbility() instead of using the Super's version of this part
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_Fire::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}



	if (ActorInfo)
	{
		if (ActorInfo->AbilitySystemComponent.Get())
		{
			ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(FireEffectActiveHandle);
		}
		else
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo->AbilitySystemComponent.Get() was NULL when trying to remove RunEffectActiveHande"), *FString(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo was NULL when trying to remove RunEffectActiveHande"), *FString(__FUNCTION__));
	}


	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
