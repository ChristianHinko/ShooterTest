// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerController.h"



ASSPlayerController::ASSPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void ASSPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	// Right after Player State gets created
}
void ASSPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Right after Player State gets repped
}

void ASSPlayerController::EndPlayingState()
{
	Super::EndPlayingState();

	//if (ASSCharacter* SSCharacter = Cast<ASSCharacter>(GetPawn()))
	//{
	//	SSCharacter->SetRemoteViewYaw(0.f);
	//}
}
