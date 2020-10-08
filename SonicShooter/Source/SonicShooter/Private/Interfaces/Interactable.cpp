// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.
IInteractable::IInteractable()
{
	bIsAutomaticInstantInteract = false;
	bIsAutomaticDurationInteract = false;
	bIsManualInstantInteract = false;
	bIsManualDurationInteract = false;
	bCanCurrentlyBeInteractedWith = true;
	bDurationInteractOccurring = false;
	bShouldFireDetectionEvents = true;
	interactDuration = 5.f;
	tickInterval = 0;
	bShouldDurationInteractableTick = true;
	bShouldSkipFirstTick = false;
}

void IInteractable::InjectDurationInteractOccurring(bool newDurationInteractOccurring)
{
	bDurationInteractOccurring = newDurationInteractOccurring;
}
void IInteractable::InjectDetectType(EDetectType newDetectType)
{
	DetectType = newDetectType;
}








bool IInteractable::GetIsManualInstantInteract()
{
	return bIsManualInstantInteract;
}
bool IInteractable::GetIsManualDurationInteract()
{
	return bIsManualDurationInteract;
}
bool IInteractable::GetCanCurrentlyBeInteractedWith()
{
	return bCanCurrentlyBeInteractedWith;
}
bool IInteractable::GetIsAutomaticInstantInteract()
{
	return bIsAutomaticInstantInteract;
}
bool IInteractable::GetIsAutomaticDurationInteract()
{
	return bIsAutomaticDurationInteract;
}
bool IInteractable::GetDurationInteractOccurring()
{
	return bDurationInteractOccurring;
}
EDetectType IInteractable::GetDetectType()
{
	return DetectType;
}









void IInteractable::OnInstantInteract(AShooterCharacter* InteractingCharacter)
{
}






void IInteractable::OnDurationInteractBegin(AShooterCharacter* InteractingCharacter)
{
}
void IInteractable::InteractingTick(AShooterCharacter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime)
{
}
void IInteractable::OnDurationInteractEnd(AShooterCharacter* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}






void IInteractable::OnInitialDetect(AShooterCharacter* InteractingCharacter)
{
}
void IInteractable::OnConsecutiveDetect(AShooterCharacter* InteractingCharacter)
{
}
void IInteractable::OnEndDetect(AShooterCharacter* InteractingCharacter)
{
}
