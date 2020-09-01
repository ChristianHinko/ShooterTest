// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterInteractInstant.h"

#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character\AbilityTasks\AT_InteractableInterfaceCaller.h"

UGA_CharacterInteractInstant::UGA_CharacterInteractInstant()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.InteractInstant")));
}

void UGA_CharacterInteractInstant::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
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
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL when trying to setup instant interact ability"), *FString(__FUNCTION__));
		return;
	}
}

bool UGA_CharacterInteractInstant::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	if (!GASCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL when trying to activate instant interact ability"), *FString(__FUNCTION__));
		return false;
	}
	if (!GASCharacter->CurrentInteract)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Detected nothing to interact with when activating interact instant ability. Cancelling"), *FString(__FUNCTION__));
		return false;
	}
	if ((GASCharacter->CurrentInteract->InteractionMode != EInteractionMode::Instant) && (GASCharacter->CurrentInteract->InteractionMode != EInteractionMode::InstantAndDuration))
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() EInteractionMode was not \"Instant\" or \"InstantAndDuration\" when trying to activate instant interact ability. Returning false"), *FString(__FUNCTION__));
		return false;
	}


	// Allow the implementer to create custom conditions before we activate
	if (GASCharacter->CurrentInteract->CanInteract(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() A custom condition returned false from IInteractable's implementor"), *FString(__FUNCTION__));
		return false;
	}



	return true;
}

void UGA_CharacterInteractInstant::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		return;
	}
	Interactable = GASCharacter->CurrentInteract;	// Wish I could put this in CanActivateAbiliy() but since it's called on CDO we can't set this reference on this instance
	if (!Interactable)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Server detected nothing to interact with when activating interact instant ability. This should be an invalid state. Cancelling"), *FString(__FUNCTION__));
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		return;
	}

	Interactable->OnInstantInteract(GASCharacter);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UGA_CharacterInteractInstant::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterInteractInstant::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}











	


	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}