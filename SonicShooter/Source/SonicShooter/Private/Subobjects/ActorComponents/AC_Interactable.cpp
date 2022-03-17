// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/ActorComponents/AC_Interactable.h"
#include "Subobjects/ActorComponents/AC_Interactable.h"

UAC_Interactable::UAC_Interactable()
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

bool UAC_Interactable::CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return false;
}

TSubclassOf<UGameplayEffect> UAC_Interactable::GetInteractableEffectTSub()
{
	return TSubclassOf<UGameplayEffect>();
}

void UAC_Interactable::OnInstantInteract(AShooterCharacter* InteractingCharacter)
{
}

void UAC_Interactable::OnDurationInteractBegin(AShooterCharacter* InteractingCharacter)
{
}

void UAC_Interactable::InteractingTick(AShooterCharacter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime)
{
}

void UAC_Interactable::OnDurationInteractEnd(AShooterCharacter* InteractingCharacter, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}

void UAC_Interactable::OnInitialDetect(AShooterCharacter* InteractingCharacter)
{
}

void UAC_Interactable::OnConsecutiveDetect(AShooterCharacter* InteractingCharacter)
{
}

void UAC_Interactable::OnEndDetect(AShooterCharacter* InteractingCharacter)
{
}






bool UAC_Interactable::GetCanCurrentlyBeInteractedWith()
{
	return bCanCurrentlyBeInteractedWith;
}

bool UAC_Interactable::GetIsManualInstantInteract()
{
	return bIsManualInstantInteract;
}

bool UAC_Interactable::GetIsAutomaticInstantInteract()
{
	return bIsAutomaticInstantInteract;
}

bool UAC_Interactable::GetIsManualDurationInteract()
{
	return bIsManualDurationInteract;
}

bool UAC_Interactable::GetIsAutomaticDurationInteract()
{
	return bIsAutomaticDurationInteract;
}

float UAC_Interactable::GetInteractDuration()
{
	return interactDuration;
}

float UAC_Interactable::GetTickInterval()
{
	return tickInterval;
}

bool UAC_Interactable::GetShouldDurationInteractableTick()
{
	return bShouldDurationInteractableTick;
}

bool UAC_Interactable::GetShouldSkipFirstTick()
{
	return bShouldSkipFirstTick;
}

bool UAC_Interactable::GetShouldFireDetectionEvents()
{
	return bShouldFireDetectionEvents;
}
