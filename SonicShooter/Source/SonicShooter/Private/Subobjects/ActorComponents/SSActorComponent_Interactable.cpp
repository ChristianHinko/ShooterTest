// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/ActorComponents/SSActorComponent_Interactable.h"
#include "Subobjects/ActorComponents/SSActorComponent_Interactable.h"

USSActorComponent_Interactable::USSActorComponent_Interactable()
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

bool USSActorComponent_Interactable::CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return false;
}

TSubclassOf<UGameplayEffect> USSActorComponent_Interactable::GetInteractableEffectTSub()
{
	return TSubclassOf<UGameplayEffect>();
}

void USSActorComponent_Interactable::OnInstantInteract(ASSCharacter_Shooter* InteractingCharacter)
{
}

void USSActorComponent_Interactable::OnDurationInteractBegin(ASSCharacter_Shooter* InteractingCharacter)
{
}

void USSActorComponent_Interactable::InteractingTick(ASSCharacter_Shooter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime)
{
}

void USSActorComponent_Interactable::OnDurationInteractEnd(ASSCharacter_Shooter* InteractingCharacter, ESSDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}

void USSActorComponent_Interactable::OnInitialDetect(ASSCharacter_Shooter* InteractingCharacter)
{
}

void USSActorComponent_Interactable::OnConsecutiveDetect(ASSCharacter_Shooter* InteractingCharacter)
{
}

void USSActorComponent_Interactable::OnEndDetect(ASSCharacter_Shooter* InteractingCharacter)
{
}






bool USSActorComponent_Interactable::GetCanCurrentlyBeInteractedWith()
{
	return bCanCurrentlyBeInteractedWith;
}

bool USSActorComponent_Interactable::GetIsManualInstantInteract()
{
	return bIsManualInstantInteract;
}

bool USSActorComponent_Interactable::GetIsAutomaticInstantInteract()
{
	return bIsAutomaticInstantInteract;
}

bool USSActorComponent_Interactable::GetIsManualDurationInteract()
{
	return bIsManualDurationInteract;
}

bool USSActorComponent_Interactable::GetIsAutomaticDurationInteract()
{
	return bIsAutomaticDurationInteract;
}

float USSActorComponent_Interactable::GetInteractDuration()
{
	return interactDuration;
}

float USSActorComponent_Interactable::GetTickInterval()
{
	return tickInterval;
}

bool USSActorComponent_Interactable::GetShouldDurationInteractableTick()
{
	return bShouldDurationInteractableTick;
}

bool USSActorComponent_Interactable::GetShouldSkipFirstTick()
{
	return bShouldSkipFirstTick;
}

bool USSActorComponent_Interactable::GetShouldFireDetectionEvents()
{
	return bShouldFireDetectionEvents;
}
