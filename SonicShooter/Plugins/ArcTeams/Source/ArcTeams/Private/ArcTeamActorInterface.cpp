// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "ArcTeamActorInterface.h"
#include "Data/ArcTeam.h"
#include "Data/ArcTeamDefinition.h"

UArcTeam* IArcTeamActorInterface::GetPrimaryTeam_Implementation() const
{
	return nullptr;
}

void IArcTeamActorInterface::SetPrimaryTeam_Implementation(UArcTeam* InTeam)
{

}

void IArcTeamActorInterface::GetSubTeams_Implementation(TArray<UArcTeam*>& OutSubteams) const
{

}

void IArcTeamActorInterface::AddSubTeam_Implementation(UArcTeam* InTeam)
{

}

void IArcTeamActorInterface::RemoveSubTeam_Implementation(UArcTeam* TeamToRemove)
{

}

// Add default functionality here for any IArcTeamActorInterface functions that are not pure virtual.

void IArcTeamActorInterface::GetSubTeamsBySubclass_Implementation(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams)
{
	TArray<UArcTeam*> SubTeams;
	GetSubTeams(SubTeams);

	for (UArcTeam* Team : SubTeams)
	{
		if (Team->GetTeamDefinition()->IsChildOf(SubteamDef))
		{
			OutSubteams.Add(Team);
		}
	}
}


void IArcTeamActorInterface::GetSubTeamsByTagQuery_Implementation(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams)
{
	TArray<UArcTeam*> SubTeams;
	GetSubTeams(SubTeams);

	for (UArcTeam* Team : SubTeams)
	{
		FGameplayTagContainer Tags;
		Team->GetOwnedGameplayTags(Tags);

		if (TagQuery.Matches(Tags))
		{
			OutSubteams.Add(Team);
		}
	}
}
