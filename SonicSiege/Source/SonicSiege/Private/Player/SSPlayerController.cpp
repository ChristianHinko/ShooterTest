// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/SSPlayerController.h"

#include "Net/UnrealNetwork.h"
#include "Player/SSPlayerState.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SSGamemode.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"



void ASSPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME_CONDITION(ASSPlayerController, SSPlayerState, COND_OwnerOnly);
}


void ASSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SSGamemode = Cast<ASSGameMode>(UGameplayStatics::GetGameMode(this));
}

void ASSPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	// Right after player state gets created.....
	
	SSPlayerState = Cast<ASSPlayerState>(PlayerState);
	// This is where you would get any information you need from your PlayerState on the server
}

void ASSPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Right after player state gets repped
	
	SSPlayerState = Cast<ASSPlayerState>(PlayerState);
	// This is where you would get any information you need from your PlayerState on the client


}

void ASSPlayerController::OnPossess(APawn* P)
{
	Super::OnPossess(P);


	ASSPlayerState* PS = GetPlayerState<ASSPlayerState>();
	if (PS)
	{
		// This will be called from the Pawn in APawn::PossessedBy() and OnRep_PlayerState(). Just doing it here too just to make sure it gets init
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, P);
	}
}

void ASSPlayerController::SetPendingPawnInfo(const FPawnInfo& NewPawnInfo)
{
	if (GetLocalRole() < ROLE_Authority)
	{
		return;
	}

	PendingPawnInfo = NewPawnInfo;
	OnPendingPawnInfoChange.Broadcast();
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
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Tried spawning Pawn but PawnInfo is invalid. Will try to spawn first index of PawnInfos array as a fallback."), *FString(__FUNCTION__));
			SetPendingPawnInfo(GetPawnInfos()[0]);
			SpawnPawnFromPendingInfo();
			return nullptr;
		}
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Tried spawning Pawn with invalid PawnInfo. Spawned no Pawn"), *FString(__FUNCTION__));
		return nullptr;
	}
	#pragma endregion


	FActorSpawnParameters ASP;
	ASP.Owner = this;
	ASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	return GetWorld()->SpawnActor<APawn>(GetPendingPawnInfo().PawnClass, ASP);	//Spawn new character as NewCharacter
}
