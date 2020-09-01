// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.
IInteractable::IInteractable()
{
	bShouldFireSweepEvents = false;
	interactDuration = 5.f;
	tickInterval = 0;
	shouldInteractableTick = false;
	shouldSkipFirstTick = false;
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
