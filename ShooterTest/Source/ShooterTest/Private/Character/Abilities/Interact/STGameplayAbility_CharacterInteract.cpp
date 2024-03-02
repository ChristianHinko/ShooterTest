// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/Interact/STGameplayAbility_CharacterInteract.h"

#include "Character/STCharacter_Shooter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character/AbilityTasks/STAbilityTask_DurationInteractCallbacks.h"
#include "Subobjects/ActorComponents/STActorComponent_Interactor.h"
#include "Utilities/ASSNativeGameplayTags.h"

USTGameplayAbility_CharacterInteract::USTGameplayAbility_CharacterInteract(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    AbilityTags.AddTag(ASSNativeGameplayTags::Ability_Type_DisableAutoActivationFromInput);
    AbilityTags.AddTag(STNativeGameplayTags::InputAction_Interact);
}

void USTGameplayAbility_CharacterInteract::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::ASSOnAvatarSet(ActorInfo, Spec);

    // Good place to cache references so we don't have to cast every time
    if (!ActorInfo)
    {
        return;
    }

    ShooterCharacter = Cast<ASTCharacter_Shooter>(ActorInfo->AvatarActor);
}

bool USTGameplayAbility_CharacterInteract::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
    if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
    {
        return false;
    }
    if (!ShooterCharacter.IsValid())
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() Character was NULL when trying to activate interact ability"), ANSI_TO_TCHAR(__FUNCTION__));
        return false;
    }
    if (!ShooterCharacter->GetInteractorComponent())
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() Character's InteractorComponent was NULL when trying to activate interact ability"), ANSI_TO_TCHAR(__FUNCTION__));
        return false;
    }
    if (!ShooterCharacter->GetInteractorComponent()->CurrentPrioritizedInteractable)
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() Detected nothing to interact with when activating interact ability. Not activating"), ANSI_TO_TCHAR(__FUNCTION__));
        return false;
    }
    if (!ShooterCharacter->GetInteractorComponent()->CurrentPrioritizedInteractable->GetCanCurrentlyBeInteractedWith())
    {
        UE_LOG(LogSTGameplayAbility, Log, TEXT("%s() Couldn't interact because bCanCurrentlyBeInteractedWith was false"), ANSI_TO_TCHAR(__FUNCTION__));
        return false;
    }
    
    return true;
}

void USTGameplayAbility_CharacterInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


    ShooterCharacter = Cast<ASTCharacter_Shooter>(ActorInfo->AvatarActor.Get());
    if (!ShooterCharacter.IsValid())
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() Cast to ShooterCharacter was NULL when activating an interact ability"), ANSI_TO_TCHAR(__FUNCTION__));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    Interactable = ShooterCharacter->GetInteractorComponent()->CurrentPrioritizedInteractable;
    if (!Interactable)
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() Server detected nothing to interact with when activating interact duration ability. This should be an invalid state. Ending"), ANSI_TO_TCHAR(__FUNCTION__));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }
    ///////////////////////////////////// we are safe to proceed /////////

    /*Your logic here... ie.
    
        //InteractEffectTSub = Interactable->GetInteractableEffectTSub();
        //if (InteractEffectTSub)
        //{
        //    InteractEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, InteractEffectTSub.GetDefaultObject(), GetAbilityLevel());
        //}
    
        //Interactable->OnDurationInteractBegin(ShooterCharacter);
    */
}
