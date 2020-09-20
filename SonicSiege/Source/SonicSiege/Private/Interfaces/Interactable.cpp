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









void IInteractable::OnInstantInteract(ASiegeCharacter* InteractingCharacter)
{
}






void IInteractable::OnDurationInteractBegin(ASiegeCharacter* InteractingCharacter)
{
}
void IInteractable::InteractingTick(ASiegeCharacter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime)
{
}
void IInteractable::OnDurationInteractEnd(ASiegeCharacter* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}






void IInteractable::OnInitialDetect(ASiegeCharacter* InteractingCharacter)
{
}
void IInteractable::OnConsecutiveDetect(ASiegeCharacter* InteractingCharacter)
{
}
void IInteractable::OnEndDetect(ASiegeCharacter* InteractingCharacter)
{
}
