// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\Abilities\Interact\STGameplayAbility_CharacterAutoInteract.h"

#include "Character/STCharacter_Shooter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character\AbilityTasks\STAbilityTask_DurationInteractCallbacks.h"

/**
 * To keep all my thoughts in one place.
 * 1) Keep system where there can only be one interactable "CurrentDetectedInteractable"
 *		- Good system but I feel adding more features is breaking it
 * 2) Give system functionality to be able to interact with multible overlap interactables at once (give implementor the option)
 *		- Maybe implement this by stepping down the stack and checking if the next interactable is allowed to be activated along with one above it in the stack
 * 3) Find a home for the automatic interactables (doesn't really belong in this system since there are priority stuff going on with only one interactable allowed
 *		- All I know is that these must be handled/activated in the OnCapsuleBeginOverlap() event. Otherwise results may be innacurrate.
 *				- Maybe do the duration interact with lots of overlaps at once by copying the way instant does it, but then this is instanced per execution which means we'd have some activation wastes. Maybe make this back to instanced per actor?
 *		- Maybe make it a separate ability? Actually kind of makes sense though since we only want to activate it when the server gets the overlap. LocalPredicted called from the server would just be a waste of RPC.
 *				- If separate ability, should it still belong to interactable system? Making new ability is a good opprotunity to break this off into its own system.
 *		- Breaking this off into its own system might be annoying because I still want the flexability to be able to automatic interact with physical objects.
 *
 *
 * 5) Bugs to squash
 *		- these problems assume our current goal is to interact with them one by one, not all at once. Assuming this because we should probably sort out those bugs before we change it for stability reasons
 *				- After overlap finishes successfully, a useless timer starts some reason (when activating ability was in Tick for automatics)
 *				- If trying to automatically interact with a sweep object while automatically interacting with an overlap, 2 timers are started with the , the sweep interact will be stopped by the overlap finishing successfully.
 *		- (Automatic activation called in overlap event) Walking into 2 overlap interactables activates 2 ablities and starts timers, not for both but only for the one in top of stack (technicly this is kinda cool since it's enforcing only interacting with the one with highest priority)
 *				- This can be solved with bDurationInteractOccurring somehow
 *						- Also figure out a way to make bCanCurrentlyBeInteractedWith and bDurationInteractOccurring cleaner and more understandable
 */

USTGameplayAbility_CharacterAutoInteract::USTGameplayAbility_CharacterAutoInteract(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityInputID = ESTAbilityInputID::NoInput; // don't use the interact input ID since there is no input needed to activate this ability
	AbilityTags.AddTag(STNativeGameplayTags::Ability_Interact_AutoInteract);
	// Probably make this an InstancedPerActor passive ability to handle all automatic interactions. Since it will be passive the ability will never end than thus we don't need to do Durration End callbacks inside EndAbility(). We can just do them where ever
}

void USTGameplayAbility_CharacterAutoInteract::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time
	if (!ActorInfo)
	{
		return;
	}

	ShooterCharacter = Cast<ASTCharacter_Shooter>(ActorInfo->AvatarActor);
}

// From DurationInteract
bool USTGameplayAbility_CharacterAutoInteract::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}



//if (!ShooterCharacter->CurrentPrioritizedInteractable->GetIsManualDurationInteract() && !ShooterCharacter->CurrentPrioritizedInteractable->GetIsAutomaticDurationInteract())
//{
//	UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() GetIsManualDurationInteract() returned false"), ANSI_TO_TCHAR(__FUNCTION__));
//	return false;
//}
//if (ShooterCharacter->CurrentPrioritizedInteractable->GetIsAutomaticInstantInteract() && ShooterCharacter->CurrentPrioritizedInteractable->GetIsManualInstantInteract())
//{
//	UE_LOG(LogSTGameplayAbility, Warning, TEXT("%s() Interactable was set to be both automatic and manual which doesn't make sense. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
//	return false;
//}

 //Activate ability from instant interact
//void USTGameplayAbility_CharacterInstantInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
//{
//	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
//	// Valid ShooterCharacter at this point
//
//	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
//	{
//      EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
//		return;
//	}
//	///////////////////////////////////// we are safe to proceed /////////
//
//	// Handle what we will do if this interactable is an automatic interact on overlap. If there are other interactables like this that we are currently overlaping with,
//	// we will take care of all of them in one ability (this one) instead of a bunch of ability calls for each one.
//	if (Interactable->GetIsAutomaticInstantInteract() && Interactable->GetDetectType() == ESTDetectType::DETECTTYPE_Overlapped && ShooterCharacter->CurrentOverlapInteractablesStack.Num() > 0)
//	{
//		/*if (Interactable->bAllowedInstantInteractActivationCombining)	// Maybe give implementor functionality
//		{*/
//		for (int32 i = ShooterCharacter->CurrentOverlapInteractablesStack.Num() - 1; i >= 0; --i)
//		{
//			if (ShooterCharacter->CurrentOverlapInteractablesStack.IsValidIndex(i) && ShooterCharacter->CurrentOverlapInteractablesStack[i])
//			{
//				if (ShooterCharacter->CurrentOverlapInteractablesStack[i]->GetIsAutomaticInstantInteract() && Interactable->GetDetectType() == ESTDetectType::DETECTTYPE_Overlapped)
//				{
//					ShooterCharacter->CurrentOverlapInteractablesStack[i]->OnInstantInteract(ShooterCharacter);
//				}
//			}
//		}
//		//}
//	}
//	else
//	{
//		Interactable->OnInstantInteract(ShooterCharacter);
//	}
//
//
//}

// Activate ability from duration interact
//void USTGameplayAbility_CharacterAutoInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
//{
//	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
//	// Valid ShooterCharacter and Interactable at this point
//
//	Interactable->InjectDurationInteractOccurring(true);
//
//	USTAbilityTask_DurationInteractCallbacks* DurationInteractCallbacks = USTAbilityTask_DurationInteractCallbacks::DurationInteractCallbacks(this, ShooterCharacter, Interactable);
//	if (!DurationInteractCallbacks)
//	{
//		UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() DurationInteractCallbacks was NULL when trying to activate an automatic duration interact."), ANSI_TO_TCHAR(__FUNCTION__));
//      EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
//		return;
//	}
//
//	DurationInteractCallbacks->OnInteractTickDelegate.AddUObject(this, &USTGameplayAbility_CharacterAutoInteract::OnInteractTick);
//	DurationInteractCallbacks->OnInteractionSweepMissDelegate.AddUObject(this, &USTGameplayAbility_CharacterAutoInteract::OnInteractionSweepMiss);
//	DurationInteractCallbacks->OnSuccessfulInteractDelegate.AddUObject(this, &USTGameplayAbility_CharacterAutoInteract::OnSuccessfullInteract);
//	DurationInteractCallbacks->OnCharacterLeftInteractionOverlapDelegate.AddUObject(this, &USTGameplayAbility_CharacterAutoInteract::OnCharacterLeftInteractionOverlap);
//	DurationInteractCallbacks->OnNewInteractionPriorityDelegate.AddUObject(this, &USTGameplayAbility_CharacterAutoInteract::OnNewInteractionPriority);
//	DurationInteractCallbacks->ReadyForActivation();
//
//	InteractEffectTSub = Interactable->GetInteractableEffectTSub();
//	if (InteractEffectTSub)		// If implementor supplied us an effect for this interaction
//	{
//		InteractEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, InteractEffectTSub.GetDefaultObject(), GetAbilityLevel());
//	}
//
//	Interactable->OnDurationInteractBegin(ShooterCharacter);
//}









//void USTGameplayAbility_CharacterAutoInteract::OnInteractTick(float DeltaTime, float TimeHeld)
//{
//	timeHeld = TimeHeld;
//	Interactable->InteractingTick(ShooterCharacter, DeltaTime, TimeHeld);
//}
//
//void USTGameplayAbility_CharacterAutoInteract::OnRelease(float TimeHeld)
//{
//	timeHeld = TimeHeld;
//	InteractEndReason = ESTDurationInteractEndReason::REASON_InputRelease;
//
//	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
//}
//
//void USTGameplayAbility_CharacterAutoInteract::OnInteractionSweepMiss(float TimeHeld)
//{
//	timeHeld = TimeHeld;
//	InteractEndReason = ESTDurationInteractEndReason::REASON_SweepMiss;
//	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
//}
//
//
//
//
//void USTGameplayAbility_CharacterAutoInteract::OnCharacterLeftInteractionOverlap(float TimeHeld)
//{
//	timeHeld = TimeHeld;
//	InteractEndReason = ESTDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap;
//	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
//}
//
//void USTGameplayAbility_CharacterAutoInteract::OnNewInteractionPriority(float TimeHeld)
//{
//
//
//
//}
//
//
//
//
//void USTGameplayAbility_CharacterAutoInteract::OnSuccessfullInteract(float TimeHeld)
//{
//	timeHeld = TimeHeld;
//	InteractEndReason = ESTDurationInteractEndReason::REASON_SuccessfulInteract;
//	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
//}
















//void USTGameplayAbility_CharacterAutoInteract::HandleDurationInteractEnded()
//{
//	if (ActorInfo->AbilitySystemComponent.Get())
//	{
//		if (InteractEffectActiveHandle.IsValid())
//		{
//			ActorInfo->AbilitySystemComponent.Get()->RemoveActiveGameplayEffect(InteractEffectActiveHandle);
//		}
//	}
//	else
//	{
//		UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() RemoveActiveGameplayEffect(InteractEffectActiveHandle) failed. AbilitySystemComponent was NULL"), ANSI_TO_TCHAR(__FUNCTION__));
//	}
//
//	if (bWasCancelled)
//	{
//		InteractEndReason = ESTDurationInteractEndReason::REASON_PredictionCorrected;
//		if (Interactable)	// If there is a valid interactable for this machine (it's ok if not. That may be why it was canceled)
//		{
//			if (InteractEndReason == ESTDurationInteractEndReason::REASON_PredictionCorrected)
//			{
//				Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_PredictionCorrected, timeHeld);
//			}
//		}
//	}
//	else
//	{
//		if (InteractEndReason == ESTDurationInteractEndReason::REASON_InputRelease)
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_InputRelease, timeHeld);
//		}
//		else if (InteractEndReason == ESTDurationInteractEndReason::REASON_SweepMiss)
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_SweepMiss, timeHeld);
//		}
//		else if (InteractEndReason == ESTDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap)
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap, timeHeld);
//		}
//		else if (InteractEndReason == ESTDurationInteractEndReason::REASON_NewInteractionOverlapPriority)
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_NewInteractionOverlapPriority, timeHeld);
//		}
//		else if (InteractEndReason == ESTDurationInteractEndReason::REASON_SuccessfulInteract)
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_SuccessfulInteract, timeHeld);
//		}
//		else
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_Unknown, timeHeld);
//		}
//	}
//
//	if (Interactable)
//	{
//		Interactable->InjectDurationInteractOccurring(false);	// Maybe should do this at the vary start of EndAbility() but well try here for now.
//	}
//}

// From DurationInteract
//void USTGameplayAbility_CharacterAutoInteract::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
//{
//	if (!IsEndAbilityValid(Handle, ActorInfo))
//	{
//		return;
//	}
//	if (ScopeLockCount > 0)
//	{
//		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &USTGameplayAbility_CharacterAutoInteract::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
//		return;
//	}
//
//
//
//
//	if (ActorInfo->AbilitySystemComponent.Get())
//	{
//		if (InteractEffectActiveHandle.IsValid())
//		{
//			ActorInfo->AbilitySystemComponent.Get()->RemoveActiveGameplayEffect(InteractEffectActiveHandle);
//		}
//	}
//	else
//	{
//		UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() RemoveActiveGameplayEffect(InteractEffectActiveHandle) failed. AbilitySystemComponent was NULL"), ANSI_TO_TCHAR(__FUNCTION__));
//	}
//
//	if (bWasCancelled)
//	{
//		InteractEndReason = ESTDurationInteractEndReason::REASON_PredictionCorrected;
//		if (Interactable)	// If there is a valid interactable for this machine (it's ok if not. That may be why it was canceled)
//		{
//			if (InteractEndReason == ESTDurationInteractEndReason::REASON_PredictionCorrected)
//			{
//				Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_PredictionCorrected, timeHeld);
//			}
//		}
//	}
//	else
//	{
//		if (InteractEndReason == ESTDurationInteractEndReason::REASON_InputRelease)
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_InputRelease, timeHeld);
//		}
//		else if (InteractEndReason == ESTDurationInteractEndReason::REASON_SweepMiss)
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_SweepMiss, timeHeld);
//		}
//		else if (InteractEndReason == ESTDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap)
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap, timeHeld);
//		}
//		else if (InteractEndReason == ESTDurationInteractEndReason::REASON_NewInteractionOverlapPriority)
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_NewInteractionOverlapPriority, timeHeld);
//		}
//		else if (InteractEndReason == ESTDurationInteractEndReason::REASON_SuccessfulInteract)
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_SuccessfulInteract, timeHeld);
//		}
//		else
//		{
//			Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_Unknown, timeHeld);
//		}
//	}
//
//
//
//
//	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
//
//
//
//	if (Interactable)
//	{
//		Interactable->InjectDurationInteractOccurring(false);	// Maybe should do this at the vary start of EndAbility() but well try here for now.
//	}
//
//
//
//
//
//
//
//
//
//}