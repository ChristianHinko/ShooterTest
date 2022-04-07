// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerController.h"

#include "Utilities/LogCategories.h"



void ASSPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	// Right after Player State gets created

	OnPlayerStateValid.Broadcast();
}

void ASSPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Right after Player State gets repped

	OnPlayerStateValid.Broadcast();
}

void ASSPlayerController::EndPlayingState()
{
	Super::EndPlayingState();

	//if (ASSCharacter* SSCharacter = Cast<ASSCharacter>(GetPawn()))
	//{
	//	SSCharacter->SetRemoteViewYaw(0.f);
	//}
}

void ASSPlayerController::SetPendingPawnClass(const TSubclassOf<APawn>& NewPawnClass)
{
	if (GetLocalRole() < ROLE_Authority)
	{
		UE_LOG(LogPlayerControllerSetup, Warning, TEXT("%s() Not allowed to set the PendingPawnClass on client"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}

	PendingPawnClass = NewPawnClass;
}
APawn* ASSPlayerController::SpawnPawnFromPendingPawnClass()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		UE_LOG(LogPlayerControllerSetup, Warning, TEXT("%s() Client tried to SpawnPawnFromPendingPawnClass. Refused to do anything"), ANSI_TO_TCHAR(__FUNCTION__));
		return nullptr;
	}

	if (IsValid(PendingPawnClass) == false)
	{
		UE_LOG(LogPlayerControllerSetup, Warning, TEXT("%s() Tried spawning Pawn with invalid PendingPawnClass. Spawned no Pawn"), ANSI_TO_TCHAR(__FUNCTION__));
		return nullptr;
	}


	FActorSpawnParameters ASP;
	ASP.Owner = this;
	ASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	return GetWorld()->SpawnActor<APawn>(PendingPawnClass, ASP);
}
