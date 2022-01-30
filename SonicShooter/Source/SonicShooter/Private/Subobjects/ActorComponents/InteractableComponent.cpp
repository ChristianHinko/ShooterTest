// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/ActorComponents/InteractableComponent.h"
#include "Subobjects/ActorComponents/InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
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

bool UInteractableComponent::CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return false;
}

TSubclassOf<UGameplayEffect> UInteractableComponent::GetInteractableEffectTSub()
{
	return TSubclassOf<UGameplayEffect>();
}

void UInteractableComponent::OnInstantInteract(AShooterCharacter* InteractingCharacter)
{
}

void UInteractableComponent::OnDurationInteractBegin(AShooterCharacter* InteractingCharacter)
{
}

void UInteractableComponent::InteractingTick(AShooterCharacter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime)
{
}

void UInteractableComponent::OnDurationInteractEnd(AShooterCharacter* InteractingCharacter, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}

void UInteractableComponent::OnInitialDetect(AShooterCharacter* InteractingCharacter)
{
}

void UInteractableComponent::OnConsecutiveDetect(AShooterCharacter* InteractingCharacter)
{
}

void UInteractableComponent::OnEndDetect(AShooterCharacter* InteractingCharacter)
{
}






bool UInteractableComponent::GetCanCurrentlyBeInteractedWith()
{
	return bCanCurrentlyBeInteractedWith;
}

bool UInteractableComponent::GetIsManualInstantInteract()
{
	return bIsManualInstantInteract;
}

bool UInteractableComponent::GetIsAutomaticInstantInteract()
{
	return bIsAutomaticInstantInteract;
}

bool UInteractableComponent::GetIsManualDurationInteract()
{
	return bIsManualDurationInteract;
}

bool UInteractableComponent::GetIsAutomaticDurationInteract()
{
	return bIsAutomaticDurationInteract;
}

float UInteractableComponent::GetInteractDuration()
{
	return interactDuration;
}

float UInteractableComponent::GetTickInterval()
{
	return tickInterval;
}

bool UInteractableComponent::GetShouldDurationInteractableTick()
{
	return bShouldDurationInteractableTick;
}

bool UInteractableComponent::GetShouldSkipFirstTick()
{
	return bShouldSkipFirstTick;
}

bool UInteractableComponent::GetShouldFireDetectionEvents()
{
	return bShouldFireDetectionEvents;
}
