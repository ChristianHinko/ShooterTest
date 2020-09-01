// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterInteractDuration.h"

#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character\AbilityTasks\AT_InteractableInterfaceCaller.h"


//temp
#include "Kismet\KismetSystemLibrary.h"

UGA_CharacterInteractDuration::UGA_CharacterInteractDuration()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.InteractDuration")));
}

void UGA_CharacterInteractDuration::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
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

bool UGA_CharacterInteractDuration::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
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
	if (!GASCharacter->CurrentInteract)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Detected nothing to interact with when activating interact duration ability. Cancelling"), *FString(__FUNCTION__));
		return false;
	}
	if ((GASCharacter->CurrentInteract->InteractionMode != EInteractionMode::Duration) && (GASCharacter->CurrentInteract->InteractionMode != EInteractionMode::InstantAndDuration))
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() EInteractionMode was not \"Duration\" or \"InstantAndDuration\" when trying to activate duration interact ability. Returning false"), *FString(__FUNCTION__));
		return false;
	}
	if (!InteractEffectTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("Effect TSubclassOf empty in %s so this ability was canceled - please fill out Interact ability blueprint"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_CharacterInteractDuration::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	Interactable = GASCharacter->CurrentInteract;	// Wish I could put this in CanActivateAbiliy() but since it's called on CDO we can't set this reference on this instance
	if (!Interactable)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Server detected nothing to interact with when activating interact duration ability. This should be an invalid state. Cancelling"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	

	UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!InputReleasedTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate InteractDuration ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	InputReleasedTask->OnRelease.AddDynamic(this, &UGA_CharacterInteractDuration::OnRelease);
	InputReleasedTask->ReadyForActivation();

	UAT_InteractableInterfaceCaller* InteractableInterfaceCaller = UAT_InteractableInterfaceCaller::InteractableInterfaceCaller(this, GASCharacter, Interactable);
	if (!InteractableInterfaceCaller)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InteractableInterfaceCaller was NULL when trying to activate InteractDuration ability. May have been because a NULL Character or Interactable reference was passed in. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	InteractableInterfaceCaller->OnInteractionBeginDelegate.AddUObject(this, &UGA_CharacterInteractDuration::OnInteractionBegin);
	InteractableInterfaceCaller->OnInteractTickDelegate.AddUObject(this, &UGA_CharacterInteractDuration::OnInteractTick);
	InteractableInterfaceCaller->OnInteractionSweepMissDelegate.AddUObject(this, &UGA_CharacterInteractDuration::OnInteractionSweepMiss);
	InteractableInterfaceCaller->OnSuccessfulInteractDelegate.AddUObject(this, &UGA_CharacterInteractDuration::OnInteractCompleted);
	InteractableInterfaceCaller->ReadyForActivation();


	InteractEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, InteractEffectTSub.GetDefaultObject(), GetAbilityLevel());
}










void UGA_CharacterInteractDuration::OnInteractionBegin()
{
	Interactable->OnDurationInteractBegin(GASCharacter);
}

void UGA_CharacterInteractDuration::OnInteractTick(float DeltaTime, float TimeHeld)
{
	timeHeld = TimeHeld;
	Interactable->InteractingTick(GASCharacter, DeltaTime, TimeHeld);
}

void UGA_CharacterInteractDuration::OnRelease(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = EDurationInteractEndReason::REASON_InputRelease;

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_CharacterInteractDuration::OnInteractionSweepMiss(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = EDurationInteractEndReason::REASON_SweepMiss;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_CharacterInteractDuration::OnInteractCompleted(float TimeHeld)
{
	timeHeld = TimeHeld;
	InteractEndReason = EDurationInteractEndReason::REASON_SuccessfulInteract;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}



















void UGA_CharacterInteractDuration::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterInteractDuration::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}










	if (InteractEndReason == EDurationInteractEndReason::REASON_InputRelease)
	{
		Interactable->OnDurationInteractEnd(GASCharacter, EDurationInteractEndReason::REASON_InputRelease, timeHeld);
	}
	else if (InteractEndReason == EDurationInteractEndReason::REASON_SweepMiss)
	{
		Interactable->OnDurationInteractEnd(GASCharacter, EDurationInteractEndReason::REASON_SweepMiss, timeHeld);
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

	if (ActorInfo->AbilitySystemComponent.Get())
	{
		ActorInfo->AbilitySystemComponent.Get()->RemoveActiveGameplayEffect(InteractEffectActiveHandle);
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() RemoveActiveGameplayEffect(InteractEffectActiveHandle) failed. AbilitySystemComponent was NULL"), *FString(__FUNCTION__));
	}







	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

