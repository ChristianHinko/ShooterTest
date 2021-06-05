// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "ArcTeamsBlueprintLibrary.h"
#include "Gamemode/ArcTeamComponent_PlayerState.h"
#include "Gamemode/ArcTeamComponent_Gamemode.h"
#include "Gamemode/ArcTeamComponent_GameState.h"

#include "EngineMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Data/ArcTeamDefinition.h"
#include "GameFramework/GameStateBase.h"

UArcTeam* UArcTeamsBlueprintLibrary::GetPrimaryTeamFromPlayer(AController* PlayerController)
{
	APlayerState* PS = PlayerController->GetPlayerState<APlayerState>();
	if (!IsValid(PS))
	{
		return nullptr;
	}
	return GetPrimaryTeamForPlayerState(PS);
}

UArcTeam* UArcTeamsBlueprintLibrary::GetPrimaryTeamForPlayerState(APlayerState* PlayerState)
{
	if (!IsValid(PlayerState))
	{
		return nullptr;
	}

	if (UArcTeamComponent_PlayerState* PSComp = Cast<UArcTeamComponent_PlayerState>(PlayerState->GetComponentByClass(UArcTeamComponent_PlayerState::StaticClass())))
	{
		return PSComp->GetPrimaryTeam();
	}

	return nullptr;
}

UArcTeamComponent_Gamemode* UArcTeamsBlueprintLibrary::GetAuthorityTeamComponent(UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject))
	{
		return nullptr;
	}
	UWorld* World = WorldContextObject->GetWorld();

	return Cast<UArcTeamComponent_Gamemode>(World->GetAuthGameMode<AGameModeBase>()->GetComponentByClass(UArcTeamComponent_Gamemode::StaticClass()));
}

UArcTeamComponent_GameState* UArcTeamsBlueprintLibrary::GetGameStateTeamComponent(UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject))
	{
		return nullptr;
	}
	UWorld* World = WorldContextObject->GetWorld();

	return Cast<UArcTeamComponent_GameState>(World->GetGameState()->GetComponentByClass(UArcTeamComponent_GameState::StaticClass()));
}

UArcTeamUIObject_TeamDefinition* UArcTeamsBlueprintLibrary::GetUIDataFromTeamDefinition(TSubclassOf<UArcTeamDefinition> TeamDefinition)
{
	return TeamDefinition.GetDefaultObject()->UIData;
}

UArcTeamComponent_PlayerState* UArcTeamsBlueprintLibrary::GetPlayerStateComponentFromPlayer(AController* PC)
{
	APlayerState* PS = PC->GetPlayerState<APlayerState>();
	if (!IsValid(PS))
	{
		return nullptr;
	}

	if (UArcTeamComponent_PlayerState* PSComp = Cast<UArcTeamComponent_PlayerState>(PS->GetComponentByClass(UArcTeamComponent_PlayerState::StaticClass())))
	{
		return PSComp;
	}

	return nullptr;
}
