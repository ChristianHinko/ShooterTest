// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerController.h"

#include "GameFramework/Pawn.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"



void ASSPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	// Right after player state gets created.....

	OnPlayerStateValid.Broadcast();
}

void ASSPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Right after player state gets repped

	OnPlayerStateValid.Broadcast();
}

void ASSPlayerController::SetPendingPawnClass(const TSubclassOf<APawn>& NewPawnClass)
{
	if (GetLocalRole() < ROLE_Authority)
	{
		UE_LOG(LogPlayerControllerSetup, Warning, TEXT("%s() Not allowed to set the pending pawn class on client"), *FString(__FUNCTION__));
		return;
	}

	PendingPawnClass = NewPawnClass;
}

APawn* ASSPlayerController::SpawnPawnFromPendingPawnClass()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		UE_LOG(LogPlayerControllerSetup, Warning, TEXT("%s() Client tried to SpawnPawnFromPendingPawnClass. Refused to do anything"), *FString(__FUNCTION__));
		return nullptr;
	}

	if (PendingPawnClass == nullptr)
	{
		UE_LOG(LogPlayerControllerSetup, Error, TEXT("%s() Tried spawning Pawn with invalid PawnClass. Spawned no Pawn"), *FString(__FUNCTION__));
		return nullptr;
	}


	FActorSpawnParameters ASP;
	ASP.Owner = this;
	ASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	return GetWorld()->SpawnActor<APawn>(PendingPawnClass, ASP);
}
