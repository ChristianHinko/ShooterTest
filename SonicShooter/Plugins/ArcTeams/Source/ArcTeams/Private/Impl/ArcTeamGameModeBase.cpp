// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Impl/ArcTeamGameModeBase.h"
#include "Gamemode/ArcTeamComponent_Gamemode.h"


AArcTeamGameModeBase::AArcTeamGameModeBase()
	: Super()
{
	TeamComponent = CreateDefaultSubobject<UArcTeamComponent_Gamemode>(TEXT("Team Component"));
}

AActor* AArcTeamGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	return ChooseTeamPlayerStart(Player);
}

bool AArcTeamGameModeBase::ShouldSpawnAtStartSpot(AController* Player)
{
	return Super::ShouldSpawnAtStartSpot(Player) && GetTeamComponent()->CanUsePlayerStartForPlayer(Player, Player->StartSpot.Get());
}
