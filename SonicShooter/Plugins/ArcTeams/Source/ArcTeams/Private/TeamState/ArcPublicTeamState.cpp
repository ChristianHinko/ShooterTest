// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "TeamState/ArcPublicTeamState.h"

#include "Net/UnrealNetwork.h"

AArcPublicTeamState::AArcPublicTeamState()
	: Super()
{
	SetReplicates(true);
	bAlwaysRelevant = true;
}

void AArcPublicTeamState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AArcPublicTeamState, ParentTeam);
}
