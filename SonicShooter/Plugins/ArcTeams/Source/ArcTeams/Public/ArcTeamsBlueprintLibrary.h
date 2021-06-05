// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ArcTeamsBlueprintLibrary.generated.h"

class UArcTeam;
class APlayerState;
class AController;
class UArcTeamDefinition;
class UArcTeamComponent_Gamemode;

/**
 * 
 */
UCLASS()
class ARCTEAMS_API UArcTeamsBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category="Teams")
	static UArcTeam* GetPrimaryTeamFromPlayer(AController* PlayerController);

	UFUNCTION(BlueprintPure, Category = "Teams")
	static UArcTeam* GetPrimaryTeamForPlayerState(APlayerState* PlayerState);

	UFUNCTION(BlueprintPure, Category = "Teams")
	static UArcTeamComponent_Gamemode* GetAuthorityTeamComponent(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Teams")
	static UArcTeamComponent_GameState* GetGameStateTeamComponent(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Teams")
	static UArcTeamComponent_PlayerState* GetPlayerStateComponentFromPlayer(AController* PC);

	UFUNCTION(BlueprintPure, Category = "Teams")
	static class UArcTeamUIObject_TeamDefinition* GetUIDataFromTeamDefinition(TSubclassOf<UArcTeamDefinition> TeamDefinition);
};
