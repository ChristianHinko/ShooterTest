// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Data/ArcTeam.h"
#include "Data/ArcTeamDefinition.h"

#include "Gamemode/ArcTeamComponent_PlayerState.h"

#include "TeamState/ArcPrivateTeamState.h"
#include "TeamState/ArcPublicTeamState.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

UArcTeam::UArcTeam(const FObjectInitializer& ObjectInitializer)
	: Super()
{
	Players.ParentTeam = this;
	SubTeams.ParentTeam = this;
}

void UArcTeam::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UArcTeam, LooseTeamTags);
	DOREPLIFETIME(UArcTeam, TeamDefinition);
	DOREPLIFETIME(UArcTeam, Players);
	DOREPLIFETIME(UArcTeam, ParentTeam);
	DOREPLIFETIME(UArcTeam, SubTeams);
	DOREPLIFETIME(UArcTeam, PublicTeamState);
	DOREPLIFETIME(UArcTeam, PrivateTeamState);
}
 
bool UArcTeam::IsSupportedForNetworking() const
{
	return true;
}

bool UArcTeam::ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = false;

	TArray<UArcTeam*> CurSubteams;
	GetSubTeams(CurSubteams);

	for (UArcTeam* SubTeam : CurSubteams)
	{
		if (IsValid(SubTeam))
		{
			WroteSomething |= Channel->ReplicateSubobject(SubTeam, *Bunch, *RepFlags);
			WroteSomething |= SubTeam->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	return WroteSomething;
}

void UArcTeam::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AppendTags(LooseTeamTags);
	TeamDefinition.GetDefaultObject()->GetOwnedGameplayTags(TagContainer);
}

TSubclassOf<UArcTeamDefinition> UArcTeam::GetTeamDefinition() const
{
	return TeamDefinition;
}

void UArcTeam::GetPlayers(TArray<UArcTeamComponent_PlayerState*>& OutPlayers) const
{
	for (int i = 0; i < Players.Items.Num(); i++)
	{
		const FArcTeamsPlayerEntry& Entry = Players.Items[i];
		OutPlayers.Add(Entry.Player);
	}
}

int32 UArcTeam::GetNumPlayers() const
{
	return Players.Items.Num();
}

void UArcTeam::GetSubTeams(TArray<UArcTeam*>& OutSubTeams) const
{
	for (int32 i = 0; i < GetNumSubTeams(); i++)
	{
		const FArcTeamsSubTeamEntry& Entry = SubTeams.Items[i];
		OutSubTeams.Add(Entry.Team);
	}
}

int32 UArcTeam::GetNumSubTeams() const
{
	return SubTeams.Items.Num();
}

bool UArcTeam::IsPrimaryTeam() const
{
	return !IsValid(ParentTeam);
}

UArcTeam* UArcTeam::GetParentTeam() const
{
	return ParentTeam;
}

void UArcTeam::GetSubTeamsBySubclass(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams)
{
	TArray<UArcTeam*> CurSubteams;
	GetSubTeams(CurSubteams);

	for (UArcTeam* Team : CurSubteams)
	{
		if (Team->GetTeamDefinition()->IsChildOf(SubteamDef))
		{
			OutSubteams.Add(Team);
		}
	}
}

void UArcTeam::GetSubTeamsByTagQuery(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams)
{
	TArray<UArcTeam*> CurSubteams;
	GetSubTeams(CurSubteams);

	for (UArcTeam* Team : CurSubteams)
	{
		FGameplayTagContainer Tags;
		Team->GetOwnedGameplayTags(Tags);

		if (TagQuery.Matches(Tags))
		{
			OutSubteams.Add(Team);
		}
	}
}

AArcPublicTeamState* UArcTeam::GetPublicTeamState() const
{
	return PublicTeamState;
}

AArcPrivateTeamState* UArcTeam::GetPrivateTeamState() const
{
	return PrivateTeamState;
}

void UArcTeam::CleanupTeam()
{
	if (IsValid(PublicTeamState))
	{
		PublicTeamState->Destroy(true);
	}
	if (IsValid(PrivateTeamState))
	{
		PrivateTeamState->Destroy(true);
	}
}

void UArcTeam::AddPlayerToTeam(UArcTeamComponent_PlayerState* Player)
{
	FArcTeamsPlayerEntry PlayerEntry;
	PlayerEntry.Player = Player;
	Players.Items.Add(PlayerEntry);
	OnPlayerAddedToTeam.Broadcast(this, Player);

	Players.MarkArrayDirty();
}

void UArcTeam::RemovePlayerFromTeam(UArcTeamComponent_PlayerState* Player)
{
	for (int i = 0; i < Players.Items.Num(); i++)
	{
		FArcTeamsPlayerEntry& Entry = Players.Items[i];

		UArcTeamComponent_PlayerState* PlayerToCheck = Entry.Player;

		if (Player == PlayerToCheck)
		{
			Players.Items.RemoveAt(i);
			i--;
		}
	}

	Players.MarkArrayDirty();
	OnPlayerRemovedFromTeam.Broadcast(this, Player);
}

void UArcTeam::PrepareForDestroy()
{
	Players.Items.Empty();
	Players.MarkArrayDirty();
}

void UArcTeam::AddSubteamToTeam(UArcTeam* InSubTeam)
{
	if (!IsValid(InSubTeam))
	{
		return;
	}

	FArcTeamsSubTeamEntry STEntry;
	STEntry.Team = InSubTeam;
	SubTeams.Items.Add(STEntry);
	SubTeams.MarkArrayDirty();

	OnSubteamAdded.Broadcast(this, InSubTeam);
}

void UArcTeam::RemoveSubteamFromTeam(UArcTeam* InSubTeam)
{
	for (int i = 0; i < SubTeams.Items.Num(); i++)
	{
		FArcTeamsSubTeamEntry& Entry = SubTeams.Items[i];

		UArcTeam* TeamToCheck = Entry.Team;

		if (InSubTeam == TeamToCheck)
		{
			SubTeams.Items.RemoveAt(i);
			i--;
		}
	}

	SubTeams.MarkArrayDirty();
	OnSubteamRemoved.Broadcast(this, InSubTeam);
}

void UArcTeam::OnRep_PublicTeamState()
{
	
}

void UArcTeam::OnRep_PrivateTeamState()
{

}

void FArcTeamsPlayerEntry::PreReplicatedRemove(const struct FArcTeamsPlayersArray& InArraySerializer)
{
	if (IsValid(InArraySerializer.ParentTeam))
	{
		InArraySerializer.ParentTeam->OnPlayerRemovedFromTeam.Broadcast(InArraySerializer.ParentTeam, Player);
	}
}

void FArcTeamsPlayerEntry::PostReplicatedAdd(const struct FArcTeamsPlayersArray& InArraySerializer)
{
	if (IsValid(InArraySerializer.ParentTeam))
	{
		InArraySerializer.ParentTeam->OnPlayerAddedToTeam.Broadcast(InArraySerializer.ParentTeam, Player);
	}
}

void FArcTeamsSubTeamEntry::PreReplicatedRemove(const struct FArcTeamsSubTeamArray& InArraySerializer)
{
	if (IsValid(InArraySerializer.ParentTeam))
	{
		InArraySerializer.ParentTeam->OnSubteamRemoved.Broadcast(InArraySerializer.ParentTeam, Team);
	}
}

void FArcTeamsSubTeamEntry::PostReplicatedAdd(const struct FArcTeamsSubTeamArray& InArraySerializer)
{
	if (IsValid(InArraySerializer.ParentTeam))
	{
		
		InArraySerializer.ParentTeam->OnSubteamAdded.Broadcast(InArraySerializer.ParentTeam, Team);
	}
}
