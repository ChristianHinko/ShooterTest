// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Interfaces/ArcTeamInterface_Gamemode.h"
#include "EngineMinimal.h"
#include "Gamemode/ArcTeamComponent_Gamemode.h"

// Add default functionality here for any IArcTeamInterface_Gamemode functions that are not pure virtual.

AActor* IArcTeamInterface_Gamemode::ChooseTeamPlayerStart(AController* Player)
{
	if (UArcTeamComponent_Gamemode* GSComp = GetTeamComponent())
	{
		return GSComp->ChoosePlayerStart(Player);
	}

	return nullptr;
}
