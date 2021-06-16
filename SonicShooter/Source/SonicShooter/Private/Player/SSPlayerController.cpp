// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/SSPlayerController.h"

#include "Net/UnrealNetwork.h"
#include "Player/SSPlayerState.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"



void ASSPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME_CONDITION(ASSPlayerController, SSPlayerState, COND_OwnerOnly);
}

void ASSPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	// Right after player state gets created.....

	SSPlayerState = Cast<ASSPlayerState>(PlayerState);
	// This is where you would get any information you need from your PlayerState on the server

	OnPlayerStateValid.Broadcast();
}

void ASSPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Right after player state gets repped

	SSPlayerState = Cast<ASSPlayerState>(PlayerState);
	// This is where you would get any information you need from your PlayerState on the client

	OnPlayerStateValid.Broadcast();
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

#pragma region safety checks
	if (GetPendingPawnInfo().PawnClass == nullptr)
	{
		if (GetPawnInfos().IsValidIndex(0))
		{
			UE_LOG(LogPlayerControllerSetup, Error, TEXT("%s() Tried spawning Pawn but PawnInfo is invalid. Will try to spawn first index of PawnInfos array as a fallback."), *FString(__FUNCTION__));
			SetPendingPawnInfo(GetPawnInfos()[0]);
			SpawnPawnFromPendingInfo();
			return nullptr;
		}
		UE_LOG(LogPlayerControllerSetup, Error, TEXT("%s() Tried spawning Pawn with invalid PawnInfo. Spawned no Pawn"), *FString(__FUNCTION__));
		return nullptr;
	}
#pragma endregion


	FActorSpawnParameters ASP;
	ASP.Owner = this;
	ASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	return GetWorld()->SpawnActor<APawn>(GetPendingPawnInfo().PawnClass, ASP);	//Spawn new character as NewCharacter
}
