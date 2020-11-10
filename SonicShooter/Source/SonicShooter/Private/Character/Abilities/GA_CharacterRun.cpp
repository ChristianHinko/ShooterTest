// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\Abilities\GA_CharacterRun.h"

#include "Character/AbilitySystemCharacter.h"
#include "Character/SSCharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Character\AbilitySystemCharacter.h"
#include "Character\AS_Character.h"
#include "Abilities\Tasks\AbilityTask_NetworkSyncPoint.h"
#include "AbilitySystem\AbilityTasks\AT_Ticker.h"



UGA_CharacterRun::UGA_CharacterRun()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Run")));

	RunDisabledTag = FGameplayTag::RequestGameplayTag("Character.Movement.RunDisabled");

	ActivationBlockedTags.AddTag(RunDisabledTag);	// This isn't the singular thing stopping you from running. The CMC is what listens for the presence of the RunDisabledTag and blocks running. This check just saves an ability activation.
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

	if (!CMC)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL when trying to activate ability. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!CMC->IsMovingOnGround())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was not on ground. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!CMC->IsMovingForward())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was not moving forward. Returned false"), *FString(__FUNCTION__));
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
	InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!InputReleasedTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}
	InputReleasedTask->OnRelease.AddDynamic(this, &UGA_CharacterRun::OnRelease);
	InputReleasedTask->ReadyForActivation();


	//InputPressTask = UAbilityTask_WaitInputPress::WaitInputPress(this);
	//if (!InputPressTask)
	//{
	//	UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputPressTask was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
	//	CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	//	return;
	//}
	//InputPressTask->OnPress.AddDynamic(this, &UGA_CharacterRun::OnPress);








	//	Create the interval task so we can decrement our stamina every second
	TickerTask = UAT_Ticker::Ticker(this);
	if (!TickerTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() TickerTask was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}
	TickerTask->OnTick.AddDynamic(this, &UGA_CharacterRun::OnTick);
	TickerTask->ReadyForActivation();

	// Both tasks were created successfully. Set to running speed
	CMC->SetWantsToRun(true);
}

void UGA_CharacterRun::OnTick(float DeltaTime, float currentTime, float timeRemaining)
{
	float stamina = CharacterAttributeSet->GetStamina();
	float staminaDrain = CharacterAttributeSet->GetStaminaDrain();

	if (stamina <= 0)
	{
		// No more stamina so make a valid prediction window and stop the running
		UAbilityTask_NetworkSyncPoint* WaitNetSyncTask = UAbilityTask_NetworkSyncPoint::WaitNetSync(this, EAbilityTaskNetSyncType::OnlyServerWait);
		WaitNetSyncTask->OnSync.AddDynamic(this, &UGA_CharacterRun::OnStaminaFullyDrained);
		WaitNetSyncTask->ReadyForActivation();
		TickerTask->EndTask();

		OnStaminaFullyDrained();
	}
	else if (!ShouldBeAbleToRun())
	{
		// Wasn't able to run so make a valid prediction window and stop the running
		UAbilityTask_NetworkSyncPoint* WaitNetSyncTask = UAbilityTask_NetworkSyncPoint::WaitNetSync(this, EAbilityTaskNetSyncType::OnlyServerWait);
		WaitNetSyncTask->OnSync.AddDynamic(this, &UGA_CharacterRun::OnWasNotAbleToRun);
		WaitNetSyncTask->ReadyForActivation();
		TickerTask->EndTask();

		OnWasNotAbleToRun();
	}
	else
	{
		// We passed the checks, so decrement stamina and keep going
		CharacterAttributeSet->SetStamina(stamina - (staminaDrain * DeltaTime));
	}
}



// Break events
void UGA_CharacterRun::OnStaminaFullyDrained()		// Break out
{
	ApplyGameplayEffectToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), DisableRunEffectTSub.GetDefaultObject(), GetAbilityLevel());
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
void UGA_CharacterRun::OnWasNotAbleToRun()			// Break out
{
	ApplyGameplayEffectToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), DisableRunEffectTSub.GetDefaultObject(), GetAbilityLevel());
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
void UGA_CharacterRun::OnRelease(float TimeHeld)	// Break out
{
	InputReleasedTask->EndTask();
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);	// This should be uncommented if the player has the hold to run setting on

	//InputPressTask->ReadyForActivation();
}
void UGA_CharacterRun::OnPress(float TimeElapsed)	// Break out
{
	InputPressTask->EndTask();
	//EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
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



	/**
	 * Currently if the server's CanActivateAbility() returns false, it will end the client's predictive activation.
	 * So when this line gets hit, it will force the client to stop running if the server didn't run the ability.
	 * So in a sense the run is not 100% client authoritative since the server forces you to stop when its CanActivateAbility() returns false,
	 * however, SetWantsToRun(true) is client authoritative so for the time that the client is predicting (before its EndAbility gets called), the
	 * character will run (even on the server). This is a vulnerability we need to eventually fix since the client can do a large packet lag (such as 2000ms)
	 * and now he can run for 2 seconds on the server before being stopped D: Also the client could do a hack and find the SetWantsToRun() function in memory
	 * and run it by itself (outside the run ablity) and now the client won't get stopped D:
	 * Basicly we need to have SetWantsToRun() not be client authoritative and that would fix everything. Otherwise there are lots of vulnerabilities.
	 * 
	 * Also to possibly save some debugging time, we've already tried and we found we can't visualize this in a test because AbilitySystem.DenyClientActivations 1
	 * doesn't allow CanActivateAbility() to run on the server as it rejects it before it even gets there.
	 */
	CMC->SetWantsToRun(false);	// Should we use this? Or should we just let the CMC handle making player stop running by its GetMaxSpeed() function seeing the bRunDisabled bool?







	//Now call the Super to finish ending the ability.
	/*
		IMPORTANT: If part of your gameplay logic in EndAbility() uses an async task, make sure you wait until the task is completed before you call Super::EndAbility.
		Otherwise the task may not complete. Call Super::EndAbility inside the task's OnComplete delegate.
	*/
	// super end ability loops through all tasks and calls OnDestroy; however, this is a virtual function, some tasks may not be destroyed on end ability (this is probably a super rare case tho) (dan says WaitTargetData doesn't end)
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}





bool UGA_CharacterRun::ShouldBeAbleToRun() const	// This is really annoying rn because you have to be very careful with turning to make sure you don't stop running
{
	//if (GASCharacter->fowardInputAxis < .1f)	// This just is here so we might be able to return false earlier before we do expensive calculations.
	//{
	//	return false;
	//}

	// Maybe we shouldn't be only using this function. Maybe we should do some more checks first
	return CMC->IsMovingForward();
}

