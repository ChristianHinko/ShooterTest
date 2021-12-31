// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SSPlayerController.generated.h"



DECLARE_MULTICAST_DELEGATE(FPlayerControllerStatus);


/**
 * Base PlayerController class.
 * 
 * Since this respawning system here. Has no dependancies so we should end up making this a plugin if we find it useful
 * Has the concept of a PendingPawnClass. This may be helpful for respawning a Pawn by using SpawnPawnFromPendingPawnClass() because
 * the classes calling the SpawnPawnFromPendingPawnClass() don't have to know what the pending pawn is, and SetPendingPawnClass lets
 * classes choose what is spawned next when the time comes.
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

	virtual void EndPlayingState() override;


private:
	TSubclassOf<APawn> PendingPawnClass;

};
