// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class APawn;

/** Describes interact event */
UENUM()
enum class EInteractionMode
{
	Instant,
	Duration
};

/** Describes interact event */
UENUM()
enum class EDurationInteractEndReason
{
	REASON_Unknown,				// Used when the interaction ends for any unknown reason
	REASON_InputRelease,		// Player let go of interact input
	REASON_SweepMiss,			// Character's Interaction sweep missed. (Can't reach it)
	REASON_SuccessfulInteract	// After you've successfully interacted (Frame after the last frame of interaction)
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

	EInteractionMode InteractionMode;	// may implement same idea but with GameplayTags later if we find out it has benifits
	
	


#pragma region InstantInteraction
	// Interact instant events



	virtual void OnInteractInstant(APawn* InteractingPawn) = 0;
#pragma endregion









#pragma region DurationInteraction
	// How long the player needs to hold interact input to interact with this interactable
	float interactDuration;
	// Time to wait between ticks. Be careful with this... longer wait between ticks means less precision of duration end (might over/undershoot interactDuration).
	float tickInterval;
	// Lets you make use of InteractingTick event
	bool shouldInteractableTick;
	// Skips first call to InteractingTick()
	bool shouldSkipFirstTick;

	// Called every frame during a duration interaction (while interact input is down)
	virtual void InteractingTick(APawn* InteractingPawn, float DeltaTime, float CurrentInteractionTime) = 0;
	// Called anytime a duration interaction ends (whatever the reason may be)
	virtual void OnDurationInteractEnd(APawn* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime) = 0;
#pragma endregion






#pragma region SweepEvents
	// Sweep events are called on both client and server from character tick (chance that only client calls but server doesn't or vice versa)

	// Allows events to be fired by the character's InteractionSweep
	bool bShouldFireSweepEvents;

	// Interaction sweep hit this interactable (a one frame fire)
	virtual void OnInteractSweepInitialHit(APawn* InteractingPawn) = 0;
	// Interaction sweep hit this interactable again
	virtual void OnInteractSweepConsecutiveHit(APawn* InteractingPawn) = 0;
	// Interaction sweep stopped hitting (a one frame fire)
	virtual void OnInteractSweepEndHitting(APawn* InteractingPawn) = 0;
#pragma endregion
};
