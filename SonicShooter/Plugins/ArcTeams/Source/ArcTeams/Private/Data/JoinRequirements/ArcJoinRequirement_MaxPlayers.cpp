// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Data/JoinRequirements/ArcJoinRequirement_MaxPlayers.h"
#include "Data/ArcTeam.h"

UArcJoinRequirement_MaxPlayers::UArcJoinRequirement_MaxPlayers(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxPlayers = 16;
}

bool UArcJoinRequirement_MaxPlayers::CanJoinTeam_Implementation(const FArcTeamJoinRequirementParams& Params)
{
	if (Params.TeamToJoin->GetNumPlayers() + Params.PlayersJoining.Num() > MaxPlayers)
	{
		return false;
	}

	return true;
}
