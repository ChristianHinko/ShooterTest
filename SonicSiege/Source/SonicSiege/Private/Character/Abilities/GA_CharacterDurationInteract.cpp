// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterDurationInteract.h"

#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character\AbilityTasks\AT_DurationInteractCallbacks.h"

UGA_CharacterDurationInteract::UGA_CharacterDurationInteract()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.DurationInteract")));
}

void UGA_CharacterDurationInteract::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
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

	GASCharacter = Cast<AAbilitySystemCharacter>(ActorInfo->AvatarActor.Get());
	if (!GASCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL when trying to setup duration interact ability"), *FString(__FUNCTION__));
		return;
	}
}

bool UGA_CharacterDurationInteract::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{	
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	if (!GASCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL when trying to activate duration interact ability"), *FString(__FUNCTION__));
		return false;
	}
	if (!GASCharacter->CurrentDetectedInteract)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Detected nothing to interact with when activating interact duration ability. Cancelling"), *FString(__FUNCTION__));
		return false;
	}
	if (!GASCharacter->CurrentDetectedInteract->GetCanCurrentlyBeInteractedWith())
	{
		UE_LOG(LogGameplayAbility, Log, TEXT("%s() Couldn't interact because bCanCurrentlyBeInteractedWith was false"), *FString(__FUNCTION__));
		return false;
	}
	if (!GASCharacter->CurrentDetectedInteract->GetIsManualDurationInteract() && !GASCharacter->CurrentDetectedInteract->GetIsAutomaticDurationInteract())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GetIsManualDurationInteract() returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (GASCharacter->CurrentDetectedInteract->GetIsAutomaticDurationInteract() && GASCharacter->CurrentDetectedInteract->GetIsManualDurationInteract())
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s() Interactable was set to be both automatic and manual which doesn't make sense. returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!InteractEffectTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("Effect TSubclassOf empty in %s so this ability was canceled - please fill out Interact ability blueprint"), *FString(__FUNCTION__));
		return false;
	}


	// Allow the implementer to create custom conditions before we activate
	if (GASCharacter->CurrentDetectedInteract->CanActivateInteractAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() A custom condition returned false from IInteractable's implementor"), *FString(__FUNCTION__));
		return false;
	}



	return true;
}

void UGA_CharacterDurationInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		return;
	}

	Interactable = GASCharacter->CurrentDetectedInteract;	// Wish I could put this in CanActivateAbiliy() but since it's called on CDO we can't set this reference on this instance
	if (!Interactable)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Server detected nothing to interact with when activating interact duration ability. This should be an invalid state. Cancelling"), *FString(__FUNCTION__));
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		return;
	}
	
	if (!Interactable->GetIsAutomaticDurationInteract())
	{
		UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
		if (!InputReleasedTask)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate InteractDuration ability. Called CancelAbility()"), *FString(__FUNCTION__));
			CancelAbility(Handle, ActorInfo, ActivationInfo, false);
			return;
		}
		InputReleasedTask->OnRelease.AddDynamic(this, &UGA_CharacterDurationInteract::OnRelease);
		InputReleasedTask->ReadyForActivation();
	}
	
	ENetRole role = GetAvatarActorFromActorInfo()->GetLocalRole();
	UAT_DurationInteractCallbacks* DurationInteractCallbacks = UAT_DurationInteractCallbacks::DurationInteractCallbacks(this, GASCharacter, Interactable);
	if (!DurationInteractCallbacks)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() DurationInteractCallbacks was NULL when trying to activate InteractDuration ability. May have been because a NULL Character or Interactable reference was passed in. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		return;
	}

	UE_CLOG(GASCharacter->GetLocalRole() == ROLE_Authority, LogGameplayAbility, Error, TEXT("%s() SERVER activating"), *FString(__FUNCTION__));
	UE_CLOG(GASCharacter->GetLocalRole() == ROLE_AutonomousProxy, LogGameplayAbility, Error, TEXT("%s() client activating"), *FString(__FUNCTION__));
	DurationInteractCallbacks->OnInteractTickDelegate.AddUObject(this, &UGA_CharacterDurationInteract::OnInteractTick);
	DurationInteractCallbacks->OnInteractionSweepMissDelegate.AddUObject(this, &UGA_CharacterDurationInteract::OnInteractionSweepMiss);
	DurationInteractCallbacks->OnSuccessfulInteractDelegate.AddUObject(this, &UGA_CharacterDurationInteract::OnSuccessfullInteract);
	DurationInteractCallbacks->OnCharacterLeftInteractionOverlapDelegate.AddUObject(this, &UGA_CharacterDurationInteract::OnCharacterLeftInteractionOverlap);
	DurationInteractCallbacks->OnNewInteractionPriorityDelegate.AddUObject(this, &UGA_CharacterDurationInteract::OnNewInteractionPriority);
	DurationInteractCallbacks->ReadyForActivation();


	InteractEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, InteractEffectTSub.GetDefaultObject(), GetAbilityLevel());
	Interactable->OnDurationInteractBegin(GASCharacter);
}









void UGA_CharacterDurationInteract::OnInteractTick(float DeltaTime, float TimeHeld)
{
	timeHeld = TimeHeld;
	Interactable->InteractingTick(GASCharacter, DeltaTime, TimeHeld);
}

void UGA_CharacterDurationInteract::OnRelease(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = EDurationInteractEndReason::REASON_InputRelease;

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_CharacterDurationInteract::OnInteractionSweepMiss(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = EDurationInteractEndReason::REASON_SweepMiss;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}




void UGA_CharacterDurationInteract::OnCharacterLeftInteractionOverlap(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = EDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_CharacterDurationInteract::OnNewInteractionPriority(float TimeHeld)
{
	
	
	
}




void UGA_CharacterDurationInteract::OnSuccessfullInteract(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = EDurationInteractEndReason::REASON_SuccessfulInteract;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}



















void UGA_CharacterDurationInteract::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterDurationInteract::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}




	// Endabbility is rn being called twice for server. Once for success and once for end overlap. 
	InteractEndReason;





	if (ActorInfo->AbilitySystemComponent.Get())
	{
		ActorInfo->AbilitySystemComponent.Get()->RemoveActiveGameplayEffect(InteractEffectActiveHandle);
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() RemoveActiveGameplayEffect(InteractEffectActiveHandle) failed. AbilitySystemComponent was NULL"), *FString(__FUNCTION__));
	}

	// We want to call the events AFTER we know the ability is completely finished
	if (InteractEndReason == EDurationInteractEndReason::REASON_InputRelease)
	{
		Interactable->OnDurationInteractEnd(GASCharacter, EDurationInteractEndReason::REASON_InputRelease, timeHeld);
	}
	else if (InteractEndReason == EDurationInteractEndReason::REASON_SweepMiss)
	{
		Interactable->OnDurationInteractEnd(GASCharacter, EDurationInteractEndReason::REASON_SweepMiss, timeHeld);
	}
	else if (InteractEndReason == EDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap)
	{
		Interactable->OnDurationInteractEnd(GASCharacter, EDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap, timeHeld);
	}
	else if (InteractEndReason == EDurationInteractEndReason::REASON_NewInteractionOverlapPriority)
	{
		Interactable->OnDurationInteractEnd(GASCharacter, EDurationInteractEndReason::REASON_NewInteractionOverlapPriority, timeHeld);
	}
	else if (InteractEndReason == EDurationInteractEndReason::REASON_SuccessfulInteract)
	{
		Interactable->OnDurationInteractEnd(GASCharacter, EDurationInteractEndReason::REASON_SuccessfulInteract, timeHeld);
	}
	else
	{
		Interactable->OnDurationInteractEnd(GASCharacter, EDurationInteractEndReason::REASON_Unknown, timeHeld);
	}

	InteractEndReason = EDurationInteractEndReason::REASON_Unknown;
	timeHeld = 0;


	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);











	
}

