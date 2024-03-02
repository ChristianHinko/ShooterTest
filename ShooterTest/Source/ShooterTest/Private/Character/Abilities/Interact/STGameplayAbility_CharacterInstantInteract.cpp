// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/Interact/STGameplayAbility_CharacterInstantInteract.h"

#include "Character/STCharacter_Shooter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character\AbilityTasks\STAbilityTask_DurationInteractCallbacks.h"
#include "Subobjects/ActorComponents/STActorComponent_Interactor.h"

USTGameplayAbility_CharacterInstantInteract::USTGameplayAbility_CharacterInstantInteract(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    AbilityTags.AddTag(STNativeGameplayTags::Ability_Interact_InstantInteract);
}

void USTGameplayAbility_CharacterInstantInteract::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::ASSOnAvatarSet(ActorInfo, Spec);
}

bool USTGameplayAbility_CharacterInstantInteract::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
    if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
    {
        return false;
    }

    ////////////// Allow the implementer to create custom conditions before we activate (may make this specific to the type of interact) ////////////
    if (ShooterCharacter->GetInteractorComponent()->CurrentPrioritizedInteractable->CanActivateInteractAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() A custom condition returned false from ISTInteractableInterface's implementor"), ANSI_TO_TCHAR(__FUNCTION__));
        return false;
    }
    return true;
}

void USTGameplayAbility_CharacterInstantInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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

void USTGameplayAbility_CharacterInstantInteract::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{

    Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}