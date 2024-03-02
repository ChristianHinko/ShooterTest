// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/ActorComponents/STActorComponent_Interactable.h"
#include "Subobjects/ActorComponents/STActorComponent_Interactable.h"

USTActorComponent_Interactable::USTActorComponent_Interactable()
{
    PrimaryComponentTick.bCanEverTick = false;

    bIsAutomaticInstantInteract = false;
    bIsAutomaticDurationInteract = false;
    bIsManualInstantInteract = false;
    bIsManualDurationInteract = false;
    bCanCurrentlyBeInteractedWith = true;
    bShouldFireDetectionEvents = true;
    interactDuration = 5.f;
    tickInterval = 0;
    bShouldDurationInteractableTick = true;
    bShouldSkipFirstTick = false;
}

bool USTActorComponent_Interactable::CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
    return false;
}

TSubclassOf<UGameplayEffect> USTActorComponent_Interactable::GetInteractableEffectTSub()
{
    return TSubclassOf<UGameplayEffect>();
}

void USTActorComponent_Interactable::OnInstantInteract(ASTCharacter_Shooter* InteractingCharacter)
{
}

void USTActorComponent_Interactable::OnDurationInteractBegin(ASTCharacter_Shooter* InteractingCharacter)
{
}

void USTActorComponent_Interactable::InteractingTick(ASTCharacter_Shooter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime)
{
}

void USTActorComponent_Interactable::OnDurationInteractEnd(ASTCharacter_Shooter* InteractingCharacter, ESTDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}

void USTActorComponent_Interactable::OnInitialDetect(ASTCharacter_Shooter* InteractingCharacter)
{
}

void USTActorComponent_Interactable::OnConsecutiveDetect(ASTCharacter_Shooter* InteractingCharacter)
{
}

void USTActorComponent_Interactable::OnEndDetect(ASTCharacter_Shooter* InteractingCharacter)
{
}






bool USTActorComponent_Interactable::GetCanCurrentlyBeInteractedWith()
{
    return bCanCurrentlyBeInteractedWith;
}

bool USTActorComponent_Interactable::GetIsManualInstantInteract()
{
    return bIsManualInstantInteract;
}

bool USTActorComponent_Interactable::GetIsAutomaticInstantInteract()
{
    return bIsAutomaticInstantInteract;
}

bool USTActorComponent_Interactable::GetIsManualDurationInteract()
{
    return bIsManualDurationInteract;
}

bool USTActorComponent_Interactable::GetIsAutomaticDurationInteract()
{
    return bIsAutomaticDurationInteract;
}

float USTActorComponent_Interactable::GetInteractDuration()
{
    return interactDuration;
}

float USTActorComponent_Interactable::GetTickInterval()
{
    return tickInterval;
}

bool USTActorComponent_Interactable::GetShouldDurationInteractableTick()
{
    return bShouldDurationInteractableTick;
}

bool USTActorComponent_Interactable::GetShouldSkipFirstTick()
{
    return bShouldSkipFirstTick;
}

bool USTActorComponent_Interactable::GetShouldFireDetectionEvents()
{
    return bShouldFireDetectionEvents;
}
