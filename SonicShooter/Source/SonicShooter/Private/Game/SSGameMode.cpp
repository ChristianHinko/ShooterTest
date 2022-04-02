// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SSGameMode.h"

#include "Game/SSGameState.h"
#include "Player/SSPlayerController.h"
#include "Player/SSPlayerState.h"
#include "UI/SSHUD.h"
#include "Character/SSCharacter.h"



ASSGameMode::ASSGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseSeamlessTravel = true; // multiplayer Seamless Travel

	GameStateClass = ASSGameState::StaticClass();
	PlayerControllerClass = ASSPlayerController::StaticClass();
	PlayerStateClass = ASSPlayerState::StaticClass();
	HUDClass = ASSHUD::StaticClass();
	DefaultPawnClass = ASSCharacter::StaticClass();
	ReplaySpectatorPlayerControllerClass = ASSPlayerController::StaticClass();
}
