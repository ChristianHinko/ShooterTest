// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/ArcTeamInterface_Gamemode.h"
#include "ArcTeamGameModeBase.generated.h"

class UArcTeamComponent_Gamemode;

/**
 * 
 */
UCLASS()
class ARCTEAMS_API AArcTeamGameModeBase : public AGameModeBase, public IArcTeamInterface_Gamemode
{
	GENERATED_BODY()
public:
	AArcTeamGameModeBase();


	//Defaut Implementation of things.  It's safe to copy+ paste this into your gamemode class if you can't derive from this base class
public:
	virtual UArcTeamComponent_Gamemode* GetTeamComponent() const override
	{
		return TeamComponent;
	}

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual bool ShouldSpawnAtStartSpot(AController* Player) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UArcTeamComponent_Gamemode* TeamComponent;

	
};
