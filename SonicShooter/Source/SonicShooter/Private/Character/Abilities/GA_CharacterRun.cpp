// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\Abilities\GA_CharacterRun.h"

#include "Character/SSCharacter.h"
#include "Character/SSCharacterMovementComponent.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Utilities/SSNativeGameplayTags.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_CharacterRun::UGA_CharacterRun()
{
	AbilityInputID = EAbilityInputID::Run;
	AbilityTags.AddTag(Tag_RunAbility);


	ActivationBlockedTags.AddTag(Tag_RunDisabled);	// This isn't the singular thing stopping you from running. The CMC is what listens for the presence of the RunDisabledTag and blocks running. This check just saves an ability activation.

	CancelAbilitiesWithTag.AddTag(Tag_CrouchAbility);
}


void UGA_CharacterRun::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	TryCallOnAvatarSetOnPrimaryInstance
		Super::OnAvatarSet(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time. If this event gets called too early from a GiveAbiliy(), AvatarActor will be messed up and some reason and this gets called 3 times
	if (!ActorInfo)
	{
		return;
	}
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor)
	{
		return;
	}


	SSCharacter = Cast<ASSCharacter>(AvatarActor);
	if (SSCharacter)
	{
		CMC = SSCharacter->GetSSCharacterMovementComponent();
		if (!CMC)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() GetSSCharacterMovementComponent was NULL"), *FString(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() SSCharacter was NULL"), *FString(__FUNCTION__));
	}
}

bool UGA_CharacterRun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	// Returning false in here for checks is better than doing checks in ActivateAbility() since returning false triggers a rollback on the client if Server returns false. In our previous method we called EndAbility() inside ActivateAbility() if a check didn't pass, which doesn't even cancel it on the remote machine if client since bRespectsRemoteAbilityToCancel most of the time will be false.
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!SSCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() SSCharacter was NULL. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!CMC)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL when trying to activate ability. Returned false"), *FString(__FUNCTION__));
		return false;
	}

	if (CMC->CanRunInCurrentState() == false)
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s() Was not able to run in current state when trying to activate ability. Returned false"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_CharacterRun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	/////////////////////////////////////////////    we've passed the checks //////


	RunningEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, RunningEffectTSub.GetDefaultObject(), GetAbilityLevel());

	CMC->Run();
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




	CMC->UnRun();

	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(RunningEffectActiveHandle);



	//Now call the Super to finish ending the ability.
	/*
		IMPORTANT: If part of your gameplay logic in EndAbility() uses an async task, make sure you wait until the task is completed before you call Super::EndAbility.
		Otherwise the task may not complete. Call Super::EndAbility inside the task's OnComplete delegate.
	*/
	// super end ability loops through all tasks and calls OnDestroy; however, this is a virtual function, some tasks may not be destroyed on end ability (this is probably a super rare case tho) (dan says WaitTargetData doesn't end)
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
