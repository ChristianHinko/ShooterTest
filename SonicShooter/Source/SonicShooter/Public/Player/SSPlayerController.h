// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SSPlayerController.generated.h"



DECLARE_MULTICAST_DELEGATE(FPlayerControllerStatus);


/**
 * Base Player Controller.
 * Has the concept of a PendingPawnClass. This may be helpful for respawning a Pawn by using SpawnPawnFromPendingPawnClass() because
 * the Player Controller doesn't have to know what he is respawning. If a Player decides to change their next character to play as next
 * time they spawn, you can call SetPendingPawnClass() to do so.
 * (This is just really an idea and is not tested) (may actually be a bad system idk)
 */
UCLASS()
class SONICSHOOTER_API ASSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	FPlayerControllerStatus OnPlayerStateValid;


	void SetPendingPawnClass(const TSubclassOf<APawn>& NewPawnClass);
	TSubclassOf<APawn> GetPendingPawnClass() const { return PendingPawnClass; }

	APawn* SpawnPawnFromPendingPawnClass();

protected:
	//BEGIN AController Interface
	virtual void InitPlayerState() override;	// server only (rare case for client I think)
	virtual void OnRep_PlayerState() override;
	//END AController Interface

private:
	TSubclassOf<APawn> PendingPawnClass;

};
