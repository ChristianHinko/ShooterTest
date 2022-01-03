// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "TeamState/ArcPrivateTeamState.h"
#include "Data/ArcTeam.h"
#include "Gamemode/ArcTeamComponent_PlayerState.h"
#include "ArcTeamsBlueprintLibrary.h"

#include "Net/UnrealNetwork.h"

AArcPrivateTeamState::AArcPrivateTeamState()
	: Super()
{
	SetReplicates(true);
	bAlwaysRelevant = true;
}

void AArcPrivateTeamState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AArcPrivateTeamState, ParentTeam);
}

bool AArcPrivateTeamState::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (IsValid(ParentTeam))
	{
		if (APlayerController* APC = Cast<APlayerController>(const_cast<AActor*>(RealViewer)))
		{
			if (UArcTeamComponent_PlayerState* TeamPS = UArcTeamsBlueprintLibrary::GetPlayerStateComponentFromPlayer(APC))
			{
				if (ParentTeam->IsPrimaryTeam())
				{
					return TeamPS->GetPrimaryTeam() == ParentTeam;
				}
				else
				{
					return TeamPS->IsInSubTeam(ParentTeam);
				}
			}
		}
	}	

	return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}
