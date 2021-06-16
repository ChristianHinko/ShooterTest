// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SSPlayerController.generated.h"



DECLARE_MULTICAST_DELEGATE(FPlayerControllerStatus);


/**
 * Not enough functionality yet to be considered useful. If we are going to make this a plugin we should think of more features to put in it like maybe integrate it with ArcTeams plugin
 * Has the concept of a PendingPawnClass. This may be helpful for respawning a Pawn by using SpawnPawnFromPendingPawnClass() because
 * the classes calling the SpawnPawnFromPendingPawnClass() don't have to know what the pending pawn is, and SetPendingPawnClass lets
 * classes choose what is spawned next when the time comes.
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
