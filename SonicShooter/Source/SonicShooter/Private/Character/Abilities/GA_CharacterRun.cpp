// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\Abilities\GA_CharacterRun.h"

#include "Character/AbilitySystemCharacter.h"
#include "Character/SSCharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Character\AbilitySystemCharacter.h"
#include "Character\AS_Character.h"
#include "Abilities\Tasks\AbilityTask_NetworkSyncPoint.h"
#include "AbilitySystem\AbilityTasks\AT_Ticker.h"



UGA_CharacterRun::UGA_CharacterRun()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Run")));

	RunDisabledTag = FGameplayTag::RequestGameplayTag("Character.Movement.RunDisabled");

	ActivationBlockedTags.AddTag(RunDisabledTag);
}

void UGA_CharacterRun::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
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

bool UGA_CharacterRun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	//	Returning false in here for checks is better than doing checks in ActivateAbility() since returning false triggers a rollback on the client if Server returns false. In our previous method we called CancelAbility() inside ActivateAbility() if a check didn't pass, which doesn't even cancel it on the remote machine if client since bRespectsRemoteAbilityToCancel most of the time will be false.
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
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
	if (!ActorInfo->AbilitySystemComponent.Get())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo->AbilitySystemComponent was NULL when trying to activate. Returned false"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_CharacterRun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}


	// Lets do the logic we want to happen when the ability starts.
	UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!InputReleasedTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}
	InputReleasedTask->OnRelease.AddDynamic(this, &UGA_CharacterRun::OnRelease);
	InputReleasedTask->ReadyForActivation();

	//	Create the interval task so we can decrement our stamina every second
	UAT_Ticker* Ticker = UAT_Ticker::Ticker(this, -1, 0, false);
	if (!Ticker)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Ticker was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}
	Ticker->OnTick.AddDynamic(this, &UGA_CharacterRun::DecrementStamina);
	Ticker->ReadyForActivation();

	// Both tasks were created successfully. Set to running speed
	CMC->SetWantsToRun(true);	//	In the case of an activation rollback, EndAbility() will be called which will call CMC->SetWantsToRun(false);
}

void UGA_CharacterRun::DecrementStamina(float DeltaTime, float currentTime, float timeRemaining)
{

	float stamina = CharacterAttributeSet->GetStamina();
	float staminaDrain = CharacterAttributeSet->GetStaminaDrain();
	if (stamina > 0)
	{
		CharacterAttributeSet->SetStamina(stamina - (staminaDrain * DeltaTime));
	}
	else
	{
		// Make a valid prediction window
		UAbilityTask_NetworkSyncPoint* WaitNetSyncTask = UAbilityTask_NetworkSyncPoint::WaitNetSync(this, EAbilityTaskNetSyncType::OnlyServerWait);
		WaitNetSyncTask->OnSync.AddDynamic(this, &UGA_CharacterRun::OnStaminaFullyDrained);
		WaitNetSyncTask->ReadyForActivation();
	}
}

void UGA_CharacterRun::OnStaminaFullyDrained() 
{
	ApplyGameplayEffectToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), DisableRunEffectTSub.GetDefaultObject(), GetAbilityLevel());
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}



void UGA_CharacterRun::OnRelease(float TimeHeld)
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_CharacterRun::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Super wraps the whole EndAbility() in IsEndAbilityValid()
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	// Make sure we bind our child class' version of EndAbility() instead of using the Super's version of this part
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterRun::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}



	// Lets do the logic we want to happen when the ability ends. If you want you can do an async task,
	// but just make sure you don't call Super::EndAbility until after the task ends (call Super::EndAbility in the task's callback)
	CMC->SetWantsToRun(false);	// Should we use this? Or should we just let the CMC handle making player stop running by its GetMaxSpeed() function seeing the bRunDisabled bool?







	//Now call the Super to finish ending the ability.
	/*
		IMPORTANT: If part of your gameplay logic in EndAbility() uses an async task, make sure you wait until the task is completed before you call Super::EndAbility.
		Otherwise the task may not complete. Call Super::EndAbility inside the task's OnComplete delegate.
	*/
	// super end ability loops through all tasks and calls OnDestroy; however, this is a virtual function, some tasks may not be destroyed on end ability (this is probably a super rare case tho) (dan says WaitTargetData doesn't end)
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}
