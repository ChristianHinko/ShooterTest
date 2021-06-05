// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "ArcTeamPlayerStart.h"

#include "EngineMinimal.h"
#include "Data/ArcTeam.h"
#include "ArcTeamsBlueprintLibrary.h"


AArcTeamPlayerStart::AArcTeamPlayerStart(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool AArcTeamPlayerStart::AllowPlayerToSpawn_Implementation(AController* Player)
{
	UArcTeam* PlayerTeam = UArcTeamsBlueprintLibrary::GetPrimaryTeamFromPlayer(Player);

	if (IsValid(PlayerTeam))
	{
		FGameplayTagContainer TeamTagContainer;
		PlayerTeam->GetOwnedGameplayTags(TeamTagContainer);

		if (TeamAllowedToSpawnQuery.Matches(TeamTagContainer))
		{
			return true;
		}
	}
	else
	{
		if (bAllowNoTeamToSpawn)
		{
			return true;
		}
	}

	return false;
}
