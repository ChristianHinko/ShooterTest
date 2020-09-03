// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.
IInteractable::IInteractable()
{
	bIsAutomaticInstantInteract = false;
	bIsAutomaticDurationInteract = false;
	bIsInstantInteract = false;
	bIsDurationInteract = false;
	bCanCurrentlyBeInteractedWith = true;
	bShouldFireSweepEvents = false;
	interactDuration = 5.f;
	tickInterval = 0;
	bShouldInteractableTick = true;
	bShouldSkipFirstTick = false;
}

bool IInteractable::GetIsInstantInteract()
{
	return bIsInstantInteract;
}
bool IInteractable::GetIsDurationInteract()
{
	return bIsDurationInteract;
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
EDetectType IInteractable::GetDetectType()
{
	return DetectType;
}

void IInteractable::SetInteractionType(EDetectType NewInteractionType)
{
	DetectType = NewInteractionType;
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
