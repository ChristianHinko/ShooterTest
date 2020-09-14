// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/Interact/GA_CharacterInstantInteract.h"

#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character\AbilityTasks\AT_DurationInteractCallbacks.h"

UGA_CharacterInstantInteract::UGA_CharacterInstantInteract()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.InstantInteract")));
}

void UGA_CharacterInstantInteract::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
}

bool UGA_CharacterInstantInteract::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	if (!GASCharacter->CurrentDetectedInteract->GetIsManualInstantInteract() && !GASCharacter->CurrentDetectedInteract->GetIsAutomaticInstantInteract())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GetIsManualInstantInteract() returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (GASCharacter->CurrentDetectedInteract->GetIsAutomaticInstantInteract() && GASCharacter->CurrentDetectedInteract->GetIsManualInstantInteract())
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s() Interactable was set to be both automatic and manual which doesn't make sense. returned false"), *FString(__FUNCTION__));
		return false;
	}

	////////////// Allow the implementer to create custom conditions before we activate (may make this specific to the type of interact) ////////////
	if (GASCharacter->CurrentDetectedInteract->CanActivateInteractAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() A custom condition returned false from IInteractable's implementor"), *FString(__FUNCTION__));
		return false;
	}
	return true;
}

void UGA_CharacterInstantInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// Valid GASCharacter and Interactable at this point

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	// Handle what we will do if this interactable is an automatic interact on overlap. If there are other interactables like this that we are currently overlaping with,
	// we will take care of all of them in one ability (this one) instead of a bunch of ability calls for each one.
	if (Interactable->GetIsAutomaticInstantInteract() && Interactable->GetDetectType() == EDetectType::DETECTTYPE_Overlapped && GASCharacter->CurrentOverlapInteractablesStack.Num() > 0)
	{
		/*if (Interactable->bAllowedInstantInteractActivationCombining)	// Maybe give implementor functionality
		{*/
			for (int32 i = GASCharacter->CurrentOverlapInteractablesStack.Num() - 1; i >= 0; i--)
			{
				if (GASCharacter->CurrentOverlapInteractablesStack.IsValidIndex(i) && GASCharacter->CurrentOverlapInteractablesStack[i])
				{
					if (GASCharacter->CurrentOverlapInteractablesStack[i]->GetIsAutomaticInstantInteract() && Interactable->GetDetectType() == EDetectType::DETECTTYPE_Overlapped)
					{
						GASCharacter->CurrentOverlapInteractablesStack[i]->OnInstantInteract(GASCharacter);
					}
				}
			}
		//}
	}
	else
	{
		Interactable->OnInstantInteract(GASCharacter);
	}

	

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UGA_CharacterInstantInteract::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterInstantInteract::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}











	


	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}