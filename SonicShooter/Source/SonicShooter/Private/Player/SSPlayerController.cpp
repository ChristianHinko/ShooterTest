// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerController.h"

#include "GameFramework/Pawn.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"



void ASSPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	// Right after player state gets created.....

	OnPlayerStateValid.Broadcast();

	// This is where you would get any information you need from your PlayerState on the server
}

void ASSPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Right after player state gets repped

	OnPlayerStateValid.Broadcast();

	// This is where you would get any information you need from your PlayerState on the client
}

void ASSPlayerController::SetPendingPawnInfo(const FPawnInfo& NewPawnInfo)
{
	if (GetLocalRole() < ROLE_Authority)
	{
		return;
	}

	PendingPawnInfo = NewPawnInfo;
}

APawn* ASSPlayerController::SpawnPawnFromPendingInfo()
{
	if (GetLocalRole() < ROLE_Authority) // server only
	{
		return nullptr;
	}

	if (GetPendingPawnInfo().PawnClass == nullptr)
	{
		UE_LOG(LogPlayerControllerSetup, Error, TEXT("%s() Tried spawning Pawn with invalid PawnInfo. Spawned no Pawn"), *FString(__FUNCTION__));
		return nullptr;
	}


	FActorSpawnParameters ASP;
	ASP.Owner = this;
	ASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	return GetWorld()->SpawnActor<APawn>(GetPendingPawnInfo().PawnClass, ASP);	//Spawn new character as NewCharacter
}
