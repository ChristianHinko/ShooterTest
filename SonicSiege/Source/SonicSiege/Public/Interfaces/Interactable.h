// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class APawn;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SONICSIEGE_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IInteractable();

	bool bShouldFireSweepEvents;

	virtual void OnInteractInstant(APawn* InteractingPawn) = 0;

	// Called only on server by a server only ability
	virtual void BeginInteractDuration(APawn* InteractingPawn) = 0;
	// Called only on server by a server only ability
	virtual void EndInteractDuration(APawn* InteractingPawn) = 0;
	
	// Called on both client and server from a tick (chance that only client calls but server doesn't or vice versa)
	virtual void OnInteractSweepInitialHit(APawn* InteractingPawn) = 0;
	// Called on both client and server from a tick (chance that only client calls but server doesn't or vice versa)
	virtual void OnInteractSweepConsecutiveHit(APawn* InteractingPawn) = 0;
	// Called on both client and server from a tick (chance that only client calls but server doesn't or vice versa)
	virtual void OnInteractSweepEndHitting(APawn* InteractingPawn) = 0;
};
