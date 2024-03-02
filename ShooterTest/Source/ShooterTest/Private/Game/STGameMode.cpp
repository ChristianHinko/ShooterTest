// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/STGameMode.h"

#include "Game/STGameState.h"
#include "Player/STPlayerController.h"
#include "Player/STPlayerState.h"
#include "UI/STHUD.h"
#include "Character/STCharacter.h"



ASTGameMode::ASTGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    GameStateClass = ASTGameState::StaticClass();
    PlayerControllerClass = ASTPlayerController::StaticClass();
    PlayerStateClass = ASTPlayerState::StaticClass();
    HUDClass = ASTHUD::StaticClass();
    DefaultPawnClass = ASTCharacter::StaticClass();
    ReplaySpectatorPlayerControllerClass = ASTPlayerController::StaticClass();
}
