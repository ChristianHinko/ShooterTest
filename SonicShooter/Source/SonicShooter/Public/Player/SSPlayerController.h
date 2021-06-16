// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SSPlayerController.generated.h"



/**
 * The controller can use this to know when the current Pawn is changed,
 * and recreate or modify its pawn as needed (by calling UpdatePawn())
 */
DECLARE_MULTICAST_DELEGATE(FPlayerControllerState);




/**
 * Base Player Controller
 * This stores the info for a pending pawn. A player may switch Pawns by
 * calling SetPendingPawnClass(FPawnClass NewPawnClass), and then calling UpdatePawn().
 */
UCLASS()
class SONICSHOOTER_API ASSPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	/** Will be null if no Pawn has been selected yet */
	TSubclassOf<APawn> GetPendingPawnClass() const { return PendingPawnClass; }


	/** Set a new Pawn to be active. Can be called on client */
	void SetPendingPawnClass(const TSubclassOf<APawn>& NewPawnClass);

	APawn* SpawnPawnFromPendingPawnClass();


	FPlayerControllerState OnPlayerStateValid;

protected:
	//BEGIN AController Interface
	virtual void InitPlayerState() override;	// Server only (rare case for client I think)
	virtual void OnRep_PlayerState() override;
	//END AController Interface

private:
	TSubclassOf<APawn> PendingPawnClass;
};
