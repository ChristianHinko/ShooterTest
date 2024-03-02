// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/Interact/STGameplayAbility_CharacterDurationInteract.h"

#include "Character/STCharacter_Shooter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character\AbilityTasks\STAbilityTask_DurationInteractCallbacks.h"
#include "Subobjects/ActorComponents/STActorComponent_Interactor.h"


USTGameplayAbility_CharacterDurationInteract::USTGameplayAbility_CharacterDurationInteract(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    AbilityTags.AddTag(STNativeGameplayTags::Ability_Interact_DurationInteract);
}

void USTGameplayAbility_CharacterDurationInteract::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::ASSOnAvatarSet(ActorInfo, Spec);
}

bool USTGameplayAbility_CharacterDurationInteract::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
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

void USTGameplayAbility_CharacterDurationInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    // Valid ShooterCharacter and Interactable at this point

    Interactable->InjectDurationInteractOccurring(true);
    
    USTAbilityTask_DurationInteractCallbacks* DurationInteractCallbacks = USTAbilityTask_DurationInteractCallbacks::DurationInteractCallbacks(this, ShooterCharacter.Get(), Interactable);
    if (!DurationInteractCallbacks)
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() DurationInteractCallbacks was NULL when trying to activate InteractDuration ability. May have been because a NULL Character or Interactable reference was passed in. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
        InteractEndReason = ESTDurationInteractEndReason::REASON_Unknown;
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
    if (!InputReleasedTask)
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate InteractDuration ability. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
        InteractEndReason = ESTDurationInteractEndReason::REASON_Unknown;
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }
    InputReleasedTask->OnRelease.AddDynamic(this, &USTGameplayAbility_CharacterDurationInteract::OnRelease);
    InputReleasedTask->ReadyForActivation();
    
    DurationInteractCallbacks->OnInteractTickDelegate.AddUObject(this, &USTGameplayAbility_CharacterDurationInteract::OnInteractTick);
    DurationInteractCallbacks->OnInteractionSweepMissDelegate.AddUObject(this, &USTGameplayAbility_CharacterDurationInteract::OnInteractionSweepMiss);
    DurationInteractCallbacks->OnSuccessfulInteractDelegate.AddUObject(this, &USTGameplayAbility_CharacterDurationInteract::OnSuccessfullInteract);
    DurationInteractCallbacks->OnCharacterLeftInteractionOverlapDelegate.AddUObject(this, &USTGameplayAbility_CharacterDurationInteract::OnCharacterLeftInteractionOverlap);
    DurationInteractCallbacks->OnNewInteractionPriorityDelegate.AddUObject(this, &USTGameplayAbility_CharacterDurationInteract::OnNewInteractionPriority);
    DurationInteractCallbacks->ReadyForActivation();

    InteractEffectTSub = Interactable->GetInteractableEffectTSub();
    if (InteractEffectTSub)        // If implementor supplied us an effect for this interaction
    {
        InteractEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, InteractEffectTSub.GetDefaultObject(), GetAbilityLevel());
    }

    Interactable->OnDurationInteractBegin(ShooterCharacter.Get());
}









void USTGameplayAbility_CharacterDurationInteract::OnInteractTick(float DeltaTime, float TimeHeld)
{
    timeHeld = TimeHeld;
    Interactable->InteractingTick(ShooterCharacter.Get(), DeltaTime, TimeHeld);
}

void USTGameplayAbility_CharacterDurationInteract::OnRelease(float TimeHeld)
{
    timeHeld = TimeHeld;
    InteractEndReason = ESTDurationInteractEndReason::REASON_InputRelease;

    EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);        // We don't replicate this end ability because both server and client should have this triggered
}

void USTGameplayAbility_CharacterDurationInteract::OnInteractionSweepMiss(float TimeHeld)
{
    timeHeld = TimeHeld;
    InteractEndReason = ESTDurationInteractEndReason::REASON_SweepMiss;
    EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}




void USTGameplayAbility_CharacterDurationInteract::OnCharacterLeftInteractionOverlap(float TimeHeld)
{
    timeHeld = TimeHeld;
    InteractEndReason = ESTDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap;
    EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void USTGameplayAbility_CharacterDurationInteract::OnNewInteractionPriority(float TimeHeld)
{
    
    
    
}




void USTGameplayAbility_CharacterDurationInteract::OnSuccessfullInteract(float TimeHeld)
{
    timeHeld = TimeHeld;
    InteractEndReason = ESTDurationInteractEndReason::REASON_SuccessfulInteract;
    EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}



















void USTGameplayAbility_CharacterDurationInteract::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (ActorInfo->AbilitySystemComponent.Get())
    {
        if (InteractEffectActiveHandle.IsValid())
        {
            ActorInfo->AbilitySystemComponent.Get()->RemoveActiveGameplayEffect(InteractEffectActiveHandle);
        }
    }
    else
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() RemoveActiveGameplayEffect(InteractEffectActiveHandle) failed. AbilitySystemComponent was NULL"), ANSI_TO_TCHAR(__FUNCTION__));
    }

    
    if (Interactable)
    {
        // Commented out because right now we don't have a way of knowing if the server rejected the activation
        /*if (InteractEndReason == ESTDurationInteractEndReason::REASON_PredictionCorrected)
        {
            Interactable->OnDurationInteractEnd(ShooterCharacter, ESTDurationInteractEndReason::REASON_PredictionCorrected, timeHeld);
        }
        else*/ if (InteractEndReason == ESTDurationInteractEndReason::REASON_InputRelease)
        {
            Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESTDurationInteractEndReason::REASON_InputRelease, timeHeld);
        }
        else if (InteractEndReason == ESTDurationInteractEndReason::REASON_SweepMiss)
        {
            Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESTDurationInteractEndReason::REASON_SweepMiss, timeHeld);
        }
        else if (InteractEndReason == ESTDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap)
        {
            Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESTDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap, timeHeld);
        }
        else if (InteractEndReason == ESTDurationInteractEndReason::REASON_NewInteractionOverlapPriority)
        {
            Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESTDurationInteractEndReason::REASON_NewInteractionOverlapPriority, timeHeld);
        }
        else if (InteractEndReason == ESTDurationInteractEndReason::REASON_SuccessfulInteract)
        {
            Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESTDurationInteractEndReason::REASON_SuccessfulInteract, timeHeld);
        }
        else
        {
            Interactable->OnDurationInteractEnd(ShooterCharacter.Get(), ESTDurationInteractEndReason::REASON_Unknown, timeHeld);
        }
    }
        



    Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);



    if (Interactable)
    {
        Interactable->InjectDurationInteractOccurring(false);
    }
}

