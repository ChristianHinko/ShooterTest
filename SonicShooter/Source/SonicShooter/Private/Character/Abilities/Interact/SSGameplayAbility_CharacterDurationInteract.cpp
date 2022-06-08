// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/Interact/SSGameplayAbility_CharacterDurationInteract.h"

#include "Character/SSCharacter_Shooter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character\AbilityTasks\SSAbilityTask_DurationInteractCallbacks.h"
#include "Subobjects/ActorComponents/SSActorComponent_Interactor.h"


USSGameplayAbility_CharacterDurationInteract::USSGameplayAbility_CharacterDurationInteract()
{
	AbilityTags.AddTag(SSNativeGameplayTags::Ability_Interact_DurationInteract);
}

void USSGameplayAbility_CharacterDurationInteract::OnAvatarSetThatWorks(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSetThatWorks(ActorInfo, Spec);
}

bool USSGameplayAbility_CharacterDurationInteract::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{	
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	////////////// Allow the implementer to create custom conditions before we activate (may make this specific to the type of interact) ////////////
	if (ShooterCharacter->GetInteractorComponent()->CurrentPrioritizedInteractable->CanActivateInteractAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() A custom condition returned false from ISSInteractableInterface's implementor"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	return true;
}

void USSGameplayAbility_CharacterDurationInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// Valid ShooterCharacter and Interactable at this point

	Interactable->InjectDurationInteractOccurring(true);
	
	USSAbilityTask_DurationInteractCallbacks* DurationInteractCallbacks = USSAbilityTask_DurationInteractCallbacks::DurationInteractCallbacks(this, ShooterCharacter.Get(), Interactable);
	if (!DurationInteractCallbacks)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() DurationInteractCallbacks was NULL when trying to activate InteractDuration ability. May have been because a NULL Character or Interactable reference was passed in. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		InteractEndReason = ESSDurationInteractEndReason::REASON_Unknown;
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!InputReleasedTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate InteractDuration ability. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		InteractEndReason = ESSDurationInteractEndReason::REASON_Unknown;
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	InputReleasedTask->OnRelease.AddDynamic(this, &USSGameplayAbility_CharacterDurationInteract::OnRelease);
	InputReleasedTask->ReadyForActivation();
	
	DurationInteractCallbacks->OnInteractTickDelegate.AddUObject(this, &USSGameplayAbility_CharacterDurationInteract::OnInteractTick);
	DurationInteractCallbacks->OnInteractionSweepMissDelegate.AddUObject(this, &USSGameplayAbility_CharacterDurationInteract::OnInteractionSweepMiss);
	DurationInteractCallbacks->OnSuccessfulInteractDelegate.AddUObject(this, &USSGameplayAbility_CharacterDurationInteract::OnSuccessfullInteract);
	DurationInteractCallbacks->OnCharacterLeftInteractionOverlapDelegate.AddUObject(this, &USSGameplayAbility_CharacterDurationInteract::OnCharacterLeftInteractionOverlap);
	DurationInteractCallbacks->OnNewInteractionPriorityDelegate.AddUObject(this, &USSGameplayAbility_CharacterDurationInteract::OnNewInteractionPriority);
	DurationInteractCallbacks->ReadyForActivation();

	InteractEffectTSub = Interactable->GetInteractableEffectTSub();
	if (InteractEffectTSub)		// If implementor supplied us an effect for this interaction
	{
		InteractEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, InteractEffectTSub.GetDefaultObject(), GetAbilityLevel());
	}

	Interactable->OnDurationInteractBegin(ShooterCharacter.Get());
}









void USSGameplayAbility_CharacterDurationInteract::OnInteractTick(float DeltaTime, float TimeHeld)
{
	timeHeld = TimeHeld;
	Interactable->InteractingTick(ShooterCharacter.Get(), DeltaTime, TimeHeld);
}

void USSGameplayAbility_CharacterDurationInteract::OnRelease(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = ESSDurationInteractEndReason::REASON_InputRelease;

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);		// We don't replicate this end ability because both server and client should have this triggered
}

void USSGameplayAbility_CharacterDurationInteract::OnInteractionSweepMiss(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = ESSDurationInteractEndReason::REASON_SweepMiss;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}




void USSGameplayAbility_CharacterDurationInteract::OnCharacterLeftInteractionOverlap(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = ESSDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void USSGameplayAbility_CharacterDurationInteract::OnNewInteractionPriority(float TimeHeld)
{
	
	
	
}




void USSGameplayAbility_CharacterDurationInteract::OnSuccessfullInteract(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = ESSDurationInteractEndReason::REASON_SuccessfulInteract;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}



















void USSGameplayAbility_CharacterDurationInteract::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &USSGameplayAbility_CharacterDurationInteract::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}




	if (ActorInfo->AbilitySystemComponent.Get())
	{
		if (InteractEffectActiveHandle.IsValid())
		{
			ActorInfo->AbilitySystemComponent.Get()->RemoveActiveGameplayEffect(InteractEffectActiveHandle);
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() RemoveActiveGameplayEffect(InteractEffectActiveHandle) failed. AbilitySystemComponent was NULL"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	
	if (Interactable)
	{
		// Commented out because right now we don't have a way of knowing if the server rejected the activation
		/*if (InteractEndReason == ESSDurationInteractEndReason::REASON_PredictionCorrected)
		{
			Interactable->OnDurationInteractEnd(ShooterCharacter, ESSDurationInteractEndReason::REASON_PredictionCorrected, timeHeld);
		}
		else*/ if (InteractEndReason == ESSDurationInteractEndReason::REASON_InputRelease)
		{
			Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESSDurationInteractEndReason::REASON_InputRelease, timeHeld);
		}
		else if (InteractEndReason == ESSDurationInteractEndReason::REASON_SweepMiss)
		{
			Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESSDurationInteractEndReason::REASON_SweepMiss, timeHeld);
		}
		else if (InteractEndReason == ESSDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap)
		{
			Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESSDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap, timeHeld);
		}
		else if (InteractEndReason == ESSDurationInteractEndReason::REASON_NewInteractionOverlapPriority)
		{
			Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESSDurationInteractEndReason::REASON_NewInteractionOverlapPriority, timeHeld);
		}
		else if (InteractEndReason == ESSDurationInteractEndReason::REASON_SuccessfulInteract)
		{
			Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESSDurationInteractEndReason::REASON_SuccessfulInteract, timeHeld);
		}
		else
		{
			Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESSDurationInteractEndReason::REASON_Unknown, timeHeld);
		}
	}
		



	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);



	if (Interactable)
	{
		Interactable->InjectDurationInteractOccurring(false);
	}
}

