// Copyright 2017-2020 Puny Human, All Rights Reserved.

#include "Gamemode/ArcTeamComponent_GameState.h"
#include "Gamemode/ArcTeamComponent_Gamemode.h"
#include "Gamemode/ArcTeamComponent_PlayerState.h"
#include "Data/ArcTeam.h"
#include "Data/ArcTeamDefinition.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

#include "ArcTeams.h"


// Sets default values for this component's properties
UArcTeamComponent_GameState::UArcTeamComponent_GameState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	TeamArray.ParentGameState = this;
}


void UArcTeamComponent_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UArcTeamComponent_GameState, TeamArray);
}

bool UArcTeamComponent_GameState::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (const FArcTeamsTeamEntry& Entry : TeamArray.Items)
	{
		UArcTeam* Team = Entry.Team;
		if (!IsValid(Team))
		{
			continue;
		}

		WroteSomething |= Channel->ReplicateSubobject(Team, *Bunch, *RepFlags);
		WroteSomething |= Team->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return WroteSomething;
}

UArcTeamComponent_Gamemode* UArcTeamComponent_GameState::GetGameModeComponent() const
{
	AGameStateBase* GSBase = GetOuterAGameStateBase();
	const AGameModeBase* GMBase = GSBase->GetDefaultGameMode();

	return Cast<UArcTeamComponent_Gamemode>(GMBase->GetComponentByClass(UArcTeamComponent_Gamemode::StaticClass()));
}

void AppendTeams(const TArray<UArcTeam*>& InTeams, TArray<UArcTeam*>& OutTeams, bool bIncludeSubTeams = false)
{
	if (InTeams.Num() > 0)
	{
		OutTeams.Append(InTeams);

		if (bIncludeSubTeams)
		{
			for (UArcTeam* Team : InTeams)
			{
				TArray<UArcTeam*> SubTeams;
				Team->GetSubTeams(SubTeams);
				AppendTeams(SubTeams, OutTeams, bIncludeSubTeams);
			}
		}
	}
}


void UArcTeamComponent_GameState::GetTeams(TArray<UArcTeam*>& OutTeams, bool bIncludeSubTeams /*= false*/) const
{
	TArray<UArcTeam*> TempTeamArray;
	for (const FArcTeamsTeamEntry& Entry : TeamArray.Items)
	{
		if (Entry.Team->IsPrimaryTeam())
		{
			TempTeamArray.Add(Entry.Team);
		}
		
	}

	AppendTeams(TempTeamArray, OutTeams, bIncludeSubTeams);
}

int32 UArcTeamComponent_GameState::GetNumTeams(bool bIncludeSubteams /*= false*/) const
{
	TArray<UArcTeam*> PossibleTeams;
	GetTeams(PossibleTeams, bIncludeSubteams);
	return PossibleTeams.Num();
}

void UArcTeamComponent_GameState::GetTeamsBySubclass(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams)
{
	for (const FArcTeamsTeamEntry& Entry : TeamArray.Items)
	{
		UArcTeam* Team = Entry.Team;
		if (IsValid(Team) && Team->GetTeamDefinition()->IsChildOf(SubteamDef))
		{
			OutSubteams.Add(Team);
		}
	}
}



void UArcTeamComponent_GameState::GetTeamsByTagQuery(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams)
{
	for (const FArcTeamsTeamEntry& Entry : TeamArray.Items)
	{
		UArcTeam* Team = Entry.Team;

		if (!IsValid(Team))
		{
			continue;
		}

		FGameplayTagContainer Tags;
		Team->GetOwnedGameplayTags(Tags);

		if (TagQuery.Matches(Tags))
		{
			OutSubteams.Add(Team);
		}
	}
}

void UArcTeamComponent_GameState::AddTeam(UArcTeam* NewTeam)
{
	FArcTeamsTeamEntry Entry;
	Entry.Team = NewTeam;
	TeamArray.Items.Add(Entry);
	TeamArray.MarkArrayDirty();
	OnTeamAdded.Broadcast(this, NewTeam);
}

void UArcTeamComponent_GameState::RemoveTeam(UArcTeam* TeamToRemove)
{
	for (int i = 0; i < TeamArray.Items.Num(); i++)
	{
		FArcTeamsTeamEntry& Entry = TeamArray.Items[i];

		UArcTeam* Team = Entry.Team;

		if (Team == TeamToRemove)
		{
			TeamArray.Items.RemoveAt(i);
			i--;
		}
	}

	TeamArray.MarkArrayDirty();
	OnTeamRemoved.Broadcast(this, TeamToRemove);
}

#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "DisplayDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

namespace GameStateDebug
{
	struct FDebugInfoStruct
	{
		FDebugInfoStruct()
		{
			FMemory::Memzero(*this);
		}

		class UCanvas* Canvas;

		bool bPrintToLog;

		float XPos;
		float YPos;
		float OriginalX;
		float OriginalY;
		float MaxY;
		float NewColumnYPadding;
		float YL;

		bool Accumulate;
		TArray<FString>	Strings;

		int32 GameFlags; // arbitrary flags for games to set/read in Debug_Internal
	};

	void AccumulateScreenPos(FDebugInfoStruct& Info)
	{
		const float ColumnWidth = Info.Canvas ? Info.Canvas->ClipX * 0.4f : 0.f;

		float NewY = Info.YPos + Info.YL;
		if (NewY > Info.MaxY)
		{
			// Need new column, reset Y to original height
			NewY = Info.NewColumnYPadding;
			Info.XPos += ColumnWidth;
		}
		Info.YPos = NewY;
	}

	void DebugLine(struct FDebugInfoStruct& Info, FString Str, float XOffset, float YOffset)
	{
		if (Info.Canvas)
		{
			Info.YL = Info.Canvas->DrawText(GEngine->GetTinyFont(), Str, Info.XPos + XOffset, Info.YPos);
			AccumulateScreenPos(Info);
		}

		if (Info.bPrintToLog)
		{
			FString LogStr;
			for (int32 i = 0; i < (int32)XOffset; ++i)
			{
				LogStr += TEXT(" ");
			}
			LogStr += Str;
			UE_LOG(LogArcTeams, Warning, TEXT("%s"), *LogStr);
		}

		if (Info.Accumulate)
		{
			FString LogStr;
			for (int32 i = 0; i < (int32)XOffset; ++i)
			{
				LogStr += TEXT(" ");
			}
			LogStr += Str;
			Info.Strings.Add(Str);
		}
	}
	static TArray<FColor> ColorStack;

	void PushColor(struct FDebugInfoStruct& Info, FColor Color)
	{
		ColorStack.Push(Color);
		Info.Canvas->SetDrawColor(Color);
	}

	void PopColor(struct FDebugInfoStruct& Info)
	{
		ColorStack.Pop();

		if (ColorStack.Num() > 0)
		{
			Info.Canvas->SetDrawColor(ColorStack.Top());
		}		
	}

	void DebugTeam(struct FDebugInfoStruct& Info, UArcTeam* Team, FString Prepend, float XOffset, float YOffset)
	{
		
		UCanvas* Canvas = Info.Canvas;
		FString TeamStr = IsValid(Team) ? Team->GetName() : "Null";
		FString TeamDef = IsValid(Team) ? Team->GetTeamDefinition()->GetName() : "NullDef";

		DebugLine(Info, FString::Printf(TEXT("%s Team: %s, Def %s"), *Prepend, *TeamStr, *TeamDef), XOffset + 5, YOffset + 0);

		TArray<UArcTeamComponent_PlayerState*> Players;
		Team->GetPlayers(Players);

		PushColor(Info, FColor::Blue);
		for (int32 j = 0; j < Players.Num(); j++)
		{
			auto Player = Players[j];
			FString PlayerName = TEXT("Null");
			if (IsValid(Player))
			{
				PlayerName = Player->GetOuterAPlayerState()->GetPlayerName();
			}

			DebugLine(Info, FString::Printf(TEXT("[%d] %s"), j, *PlayerName), XOffset + 10, YOffset + 0);
		}
		PopColor(Info);

		TArray<UArcTeam*> Teams;
		Team->GetSubTeams(Teams);

		int32 Depth = 0;
		UArcTeam* TestTeam = Team;
		while (TestTeam->GetParentTeam())
		{
			Depth++;
			TestTeam = TestTeam->GetParentTeam();
		}
		FColor SubteamColor = FColor::Green;
		switch (Depth % 3)
		{
		case 0:
			SubteamColor = FColor::Emerald;
			break;
		case 1:
			SubteamColor = FColor::Yellow;
			break;
		case 2:
			SubteamColor = FColor::Magenta;
			break;
		default:
			break;
		}

		PushColor(Info, SubteamColor);
		for (int32 st = 0; st < Teams.Num(); st++)
		{
			UArcTeam* SubTeam = Teams[st];
			DebugTeam(Info, SubTeam, FString::Printf(TEXT("[%d]"), st), 10, 0);
		}
		PopColor(Info);
	}

	void ShowDebug(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float&  YL, float&  YPos)
	{
		if (!DisplayInfo.IsDisplayOn(TEXT("Team")))
		{
			return;
		}

		AGameStateBase* GS = HUD->GetWorld()->GetGameState();

		if (UArcTeamComponent_GameState* GSComp = Cast<UArcTeamComponent_GameState>(GS->GetComponentByClass(UArcTeamComponent_GameState::StaticClass())))
		{
			FDebugInfoStruct DebugInfo;
			DebugInfo.bPrintToLog = false;
			DebugInfo.Canvas = Canvas;
			DebugInfo.XPos = 0.f;
			DebugInfo.YPos = YPos;
			DebugInfo.OriginalX = 0.f;
			DebugInfo.OriginalY = YPos;
			DebugInfo.MaxY = Canvas->ClipY - 150.f; // Give some padding for any non-columnizing debug output following this output
			DebugInfo.NewColumnYPadding = 30.f;

			TArray<UArcTeam*> Teams;
			GSComp->GetTeams(Teams);

			PushColor(DebugInfo, FColor::Cyan);
			//Debug here
			for (int32 i = 0; i < Teams.Num(); i++)
			{
				UArcTeam* Team = Teams[i];
				DebugTeam(DebugInfo, Team, FString::Printf(TEXT("[%d]"), i), 0, 0);
			}
			PopColor(DebugInfo);

			Canvas->SetDrawColor(FColor::White);
			YPos = DebugInfo.YPos;
			YL = DebugInfo.YL;
		}

	}


	FDelegateHandle DebugHandle = AHUD::OnShowDebugInfo.AddStatic(&ShowDebug);
}

void FArcTeamsTeamEntry::PreReplicatedRemove(const struct FArcTeamsTeamArray& InArraySerializer)
{
	if (IsValid(InArraySerializer.ParentGameState))
	{
		InArraySerializer.ParentGameState->OnTeamRemoved.Broadcast(InArraySerializer.ParentGameState, Team);
	}
}

void FArcTeamsTeamEntry::PostReplicatedAdd(const struct FArcTeamsTeamArray& InArraySerializer)
{
	if (IsValid(InArraySerializer.ParentGameState))
	{
		InArraySerializer.ParentGameState->OnTeamAdded.Broadcast(InArraySerializer.ParentGameState, Team);
	}
}
