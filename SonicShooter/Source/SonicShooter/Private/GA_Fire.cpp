// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Fire.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AbilityTasks/AT_SSWaitTargetData.h"
#include "AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Utilities/CollisionChannels.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_Fire::UGA_Fire()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Fire")));


}


void UGA_Fire::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);


}

void UGA_Fire::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);


	if (!BulletTraceTargetActorTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("BulletTraceTargetActorTSub TSubclassOf empty in %s(). Please fill out BP"), *FString(__FUNCTION__));
		return;
	}


	// Ensure this target actor is always spawned
	FActorSpawnParameters TargetActorSpawnParameters;
	TargetActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn our target actor
	BulletTraceTargetActor = GetWorld()->SpawnActor<AGATA_BulletTrace>(BulletTraceTargetActorTSub, TargetActorSpawnParameters);
	BulletTraceTargetActor->bDestroyOnConfirmation = false;
}

void UGA_Fire::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	if (BulletTraceTargetActor && BulletTraceTargetActor->Destroy())
	{
		BulletTraceTargetActor = nullptr;
	}
}

bool UGA_Fire::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!BulletTraceTargetActor)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() BulletTraceTargetActor was NULL. returned false"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	// Update target actor's start location info
	BulletTraceTargetActor->StartLocation = MakeTargetLocationInfoFromOwnerSkeletalMeshComponent(TEXT("None"));		// this will take the actor info's skeletal mesh, maybe make our own in SSGameplayAbility which you can specify a skeletal mesh to use

	// Try to make wait target data task
	UAT_SSWaitTargetData* WaitTargetDataActorTask = UAT_SSWaitTargetData::SSWaitTargetDataUsingActor(this, TEXT("WaitTargetDataActorTask"), EGameplayTargetingConfirmation::Instant, BulletTraceTargetActor);
	if (!WaitTargetDataActorTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitTargetDataActorTask was NULL when trying to activate fire ability. Called EndAbility()"), *FString(__FUNCTION__));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}


	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	///////////////////////////////////// we are safe to proceed /////////

	// Take away ammo first
	if (FireEffectTSub)
	{
		FireEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, FireEffectTSub.GetDefaultObject(), GetAbilityLevel());
	}
	else
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("FireEffectTSub TSubclassOf empty in %s"), *FString(__FUNCTION__));
	}


	// Bind to wait target data delegates and activate the task
	WaitTargetDataActorTask->ValidData.AddDynamic(this, &UGA_Fire::OnValidData);
	WaitTargetDataActorTask->Cancelled.AddDynamic(this, &UGA_Fire::OnCancelled);
	WaitTargetDataActorTask->ReadyForActivation();


	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UGA_Fire::OnValidData(const FGameplayAbilityTargetDataHandle& Data)
{
	ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), Data, BulletHitEffectTSub, GetAbilityLevel());
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
