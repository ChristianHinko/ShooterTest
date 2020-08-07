// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Weapon/Abilities/GA_Fire.h"
#include "AbilitySystemComponent.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/GameplayAbilityTargetActor_SingleLineTrace.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_Fire::UGA_Fire()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Fire")));
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



	AGameplayAbilityTargetActor_SingleLineTrace* TargetTraceActor = GetWorld()->SpawnActor<AGameplayAbilityTargetActor_SingleLineTrace>(FActorSpawnParameters());
	TargetTraceActor->bDebug = true;

	FGameplayAbilityTargetingLocationInfo TargetingLocationInfo = FGameplayAbilityTargetingLocationInfo();
	TargetingLocationInfo.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	TargetingLocationInfo.LiteralTransform = GetAvatarActorFromActorInfo()->GetActorTransform();
	TargetTraceActor->StartLocation = TargetingLocationInfo;

	UAbilityTask_WaitTargetData* WaitTargetDataActorTask = UAbilityTask_WaitTargetData::WaitTargetDataUsingActor(this, TEXT("WaitTargetDataActorTask"), EGameplayTargetingConfirmation::UserConfirmed, TargetTraceActor);
	if (!WaitTargetDataActorTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitTargetDataActorTask was NULL when trying to activate fire ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}

	WaitTargetDataActorTask->ValidData.AddDynamic(this, &UGA_Fire::OnValidData);
	WaitTargetDataActorTask->ReadyForActivation();

	FireEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, FireEffectTSub.GetDefaultObject(), GetAbilityLevel());
	UKismetSystemLibrary::PrintString(this, "GA_Fire activated", true, false);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UGA_Fire::OnValidData(const FGameplayAbilityTargetDataHandle& Data)
{

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
