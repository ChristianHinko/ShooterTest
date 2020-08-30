// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class APawn;

///** Describes interact event */
//UENUM()
//enum class EInteract
//{
//	StartInteract,
//	InteractTick,
//	EndInteract
//};

/** Describes interact event */
UENUM()
enum class EInteractionMode
{
	Instant,
	Duration
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 *	You can use Gameplay Tags to indicate if something is interacting
 */
class SONICSIEGE_API IInteractable
{
	GENERATED_BODY()

public:
	IInteractable();

	EInteractionMode InteractionMode;	// may implement same idea but with GameplayTags later if we find out it's better
	float InteractDuration;

	bool bShouldFireSweepEvents;

	// Interact instant events
	virtual void OnInteractInstant(APawn* InteractingPawn) = 0;

	// Interact duration events
	virtual void BeginInteractDuration(APawn* InteractingPawn) = 0;
	virtual void InteractingTick(APawn* InteractingPawn, float DeltaTime) = 0;
	virtual void FinishInteractDuration(APawn* InteractingPawn) = 0;
	virtual void CancelledInteractDuration(APawn* InteractingPawn, float interactionTime) = 0;








	
	// Sweep events are called on both client and server from character tick (chance that only client calls but server doesn't or vice versa)
	virtual void OnInteractSweepInitialHit(APawn* InteractingPawn) = 0;
	virtual void OnInteractSweepConsecutiveHit(APawn* InteractingPawn) = 0;
	virtual void OnInteractSweepEndHitting(APawn* InteractingPawn) = 0;
};
