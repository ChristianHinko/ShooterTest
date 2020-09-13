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
	bShouldFireSweepEvents = false;
	interactDuration = 5.f;
	tickInterval = 0;
	bShouldInteractableTick = true;
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







void IInteractable::OnAutomaticInteract(APawn* InteractingPawn)
{
}






void IInteractable::OnInstantInteract(APawn* InteractingPawn)
{
}






void IInteractable::OnDurationInteractBegin(APawn* InteractingPawn)
{
}
void IInteractable::InteractingTick(APawn* InteractingPawn, float DeltaTime, float CurrentInteractionTime)
{
}
void IInteractable::OnDurationInteractEnd(APawn* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}






void IInteractable::OnInteractSweepInitialHit(APawn* InteractingPawn)
{
}
void IInteractable::OnInteractSweepConsecutiveHit(APawn* InteractingPawn)
{
}
void IInteractable::OnInteractSweepEndHitting(APawn* InteractingPawn)
{
}
