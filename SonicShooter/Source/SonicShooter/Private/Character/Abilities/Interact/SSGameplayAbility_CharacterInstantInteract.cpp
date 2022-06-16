// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/Interact/SSGameplayAbility_CharacterInstantInteract.h"

#include "Character/SSCharacter_Shooter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character\AbilityTasks\SSAbilityTask_DurationInteractCallbacks.h"
#include "Subobjects/ActorComponents/SSActorComponent_Interactor.h"

USSGameplayAbility_CharacterInstantInteract::USSGameplayAbility_CharacterInstantInteract(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityTags.AddTag(SSNativeGameplayTags::Ability_Interact_InstantInteract);
}

void USSGameplayAbility_CharacterInstantInteract::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);
}

bool USSGameplayAbility_CharacterInstantInteract::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
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

void USSGameplayAbility_CharacterInstantInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// Valid ShooterCharacter and Interactable at this point

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	///////////////////////////////////// we are safe to proceed /////////

	Interactable->OnInstantInteract(ShooterCharacter.Get());

	

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void USSGameplayAbility_CharacterInstantInteract::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{

	Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}