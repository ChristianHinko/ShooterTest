// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterRunV2.h"

#include "Character/AbilitySystemCharacter.h"
#include "Character/SSCharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Character\AbilitySystemCharacter.h"
#include "Character\AS_Character.h"
#include "AbilitySystem/AbilityTasks/AT_RepeatAction.h"
#include "Abilities\Tasks\AbilityTask_NetworkSyncPoint.h"
#include "Kismet/KismetSystemLibrary.h"

UGA_CharacterRunV2::UGA_CharacterRunV2()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.RunV2")));

	ActivationBlockedTags.AddTagFast(TagOutOfStamina);
}

void UGA_CharacterRunV2::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	
	//	Good place to cache references so we don't have to cast every time. If this event gets called too early from a GiveAbiliy(), AvatarActor will be messed up and some reason and this gets called 3 times
	if (!ActorInfo)
	{
		return;
	}
	if (!ActorInfo->AvatarActor.Get())
	{
		return;
	}
	
	
	CMC = Cast<USSCharacterMovementComponent>(ActorInfo->MovementComponent.Get());
	if (!CMC)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL"), *FString(__FUNCTION__));
	}
	
	GASCharacter = Cast<AAbilitySystemCharacter>(ActorInfo->AvatarActor.Get());
	if (!GASCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GASCharacter was NULL, meaning CharacterAttributeSet will also be NULL"), *FString(__FUNCTION__));
		return;
	}
	CharacterAttributeSet = GASCharacter->GetCharacterAttributeSet();
	if (!CharacterAttributeSet)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterAttributeSet was NULL"), *FString(__FUNCTION__));
	}
}

bool UGA_CharacterRunV2::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	//	Returning false in here for checks is better than doing checks in ActivateAbility() since returning false triggers a rollback on the client if Server returns false. In our previous method we called CancelAbility() inside ActivateAbility() if a check didn't pass, which doesn't even cancel it on the remote machine if client since bRespectsRemoteAbilityToCancel most of the time will be false.
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!DrainStaminaFromRunEffectTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Effect TSubclassOf NULL so returned false - please fill out Character Run ability blueprint"), *FString(__FUNCTION__));
		return false;
	}
	if (!CMC)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL when trying to activate ability. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!GASCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GASCharacter was NULL. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!CharacterAttributeSet)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterAttributeSet was NULL. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (GASCharacter->GetCharacterAttributeSet()->GetStamina() <= 0)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Stamina was <= 0 so can't run. Returned false"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_CharacterRunV2::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}




	// Lets do the logic we want to happen when the ability starts.
	UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!InputReleasedTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	InputReleasedTask->OnRelease.AddDynamic(this, &UGA_CharacterRunV2::OnRelease);
	InputReleasedTask->ReadyForActivation();

	//	Create the interval task so we can decrement our stamina every second
	UAT_RepeatAction* RepeatActionTask = UAT_RepeatAction::RepeatAction(this, 1, true);
	if (!RepeatActionTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() RepeatActionTask was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	RepeatActionTask->OnPerformAction.AddDynamic(this, &UGA_CharacterRunV2::OnTimerTick);
	RepeatActionTask->ReadyForActivation();

	// Both tasks were created successfully. Set to running speed
	CMC->SetWantsToRun(true);	//	In the case of an activation rollback, EndAbility() will be called which will call CMC->SetWantsToRun(false);
}

void UGA_CharacterRunV2::OnTimerTick()
{
	// Make a valid prediction key
	UAbilityTask_NetworkSyncPoint* WaitNetSyncTask = UAbilityTask_NetworkSyncPoint::WaitNetSync(this, EAbilityTaskNetSyncType::OnlyServerWait);
	WaitNetSyncTask->OnSync.AddDynamic(this, &UGA_CharacterRunV2::DecrementStaminaWithValidPredictionKey);
	WaitNetSyncTask->ReadyForActivation();
}

void UGA_CharacterRunV2::DecrementStaminaWithValidPredictionKey()
{
	if (GetAbilitySystemComponentFromActorInfo()->CanPredict())
	{
		UKismetSystemLibrary::PrintString(this, "prediction valid");
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, "prediction INVALID");
	}

	float staminaCurrentValue = GASCharacter->GetCharacterAttributeSet()->GetStamina();
	if (staminaCurrentValue > 1)
	{
		ApplyGameplayEffectToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), DrainStaminaFromRunEffectTSub.GetDefaultObject(), GetAbilityLevel());
	}
	else if (staminaCurrentValue == 1)
	{
		ApplyGameplayEffectToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), DrainStaminaFromRunEffectTSub.GetDefaultObject(), GetAbilityLevel());
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	}
	else if (staminaCurrentValue <= 0)
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	}


}









void UGA_CharacterRunV2::OnRelease(float TimeHeld)
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_CharacterRunV2::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	//GetAbilitySystemComponentFromActorInfo()->FindAbilitySpecFromHandle(Handle)->ActivationInfo.SetActivationRejected();
	//ActivationInfo.ActivationMode = EGameplayAbilityActivationMode::Rejected;
	// Super wraps the whole EndAbility() in IsEndAbilityValid()
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	// Make sure we bind our child class' version of EndAbility() instead of using the Super's version of this part
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterRunV2::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}



	// Lets do the logic we want to happen when the ability ends. If you want you can do an async task,
	// but just make sure you don't call Super::EndAbility until after the task ends (call Super::EndAbility in the task's callback)
	EndTaskByInstanceName("RepeatAction");
	CMC->SetWantsToRun(false);	// In case of successful runthrough, stop running. But this will also be called if activation rollback occurrs so we good



	



	//Now call the Super to finish ending the ability.
	/*
		IMPORTANT: If part of your gameplay logic in EndAbility() uses an async task, make sure you wait until the task is completed before you call Super::EndAbility.
		Otherwise the task may not complete. Call Super::EndAbility inside the task's OnComplete delegate.
	*/
	// super end ability loops through all tasks and calls OnDestroy; however, this is a virtual function, some tasks may not be destroyed on end ability (this is probably a super rare case tho) (dan says WaitTargetData doesn't end)
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
}
















void UGA_CharacterRunV2::BeginDestroy()
{
	Super::BeginDestroy();



}
