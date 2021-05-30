// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Data/ArcTeamJoinRequirement.h"

UArcTeamJoinRequirement::UArcTeamJoinRequirement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool UArcTeamJoinRequirement::CanJoinTeam_Implementation(const FArcTeamJoinRequirementParams& Params)
{
	return true;
}
