// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Gamemode/ArcTeamComponent_PlayerState.h"
#include "Data/ArcTeam.h"
#include "Data/ArcTeamDefinition.h"

#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "DisplayDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

#include "Net/UnrealNetwork.h"
#include "ArcTeams.h"

// Sets default values for this component's properties
UArcTeamComponent_PlayerState::UArcTeamComponent_PlayerState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.o
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	SubTeams.ParentPlayerState = this;
}

void UArcTeamComponent_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UArcTeamComponent_PlayerState, PrimaryTeam);
	DOREPLIFETIME(UArcTeamComponent_PlayerState, SubTeams);
}

APlayerState* UArcTeamComponent_PlayerState::GetPlayerState() const
{
	return Cast<APlayerState>(GetOuter());
}

UArcTeam* UArcTeamComponent_PlayerState::GetPrimaryTeam() const
{
	return PrimaryTeam;
}

void UArcTeamComponent_PlayerState::GetAllTeams(TArray<UArcTeam*>& OutTeams) const
{
	OutTeams.Add(PrimaryTeam);
	GetSubTeams(OutTeams);
}

void UArcTeamComponent_PlayerState::GetSubTeams(TArray<UArcTeam*>& OutSubteams) const
{
	for (const FArcTeamsPlayerSubTeamEntry& Entry : SubTeams.Items)
	{
		OutSubteams.Add(Entry.Team);
	}
}

bool UArcTeamComponent_PlayerState::IsInSubTeam(UArcTeam* InSubTeam) const
{
	TArray<UArcTeam*> Teams;
	GetSubTeams(Teams);

	return Teams.Contains(InSubTeam);
}

void UArcTeamComponent_PlayerState::OnRep_PrimaryTeam(UArcTeam* PreviousTeam)
{
	if (IsValid(PreviousTeam))
	{
		OnTeamLeave.Broadcast(PreviousTeam, this);
	}
	if (IsValid(PrimaryTeam))
	{
		OnTeamJoined.Broadcast(PrimaryTeam, this);
	}
}

void UArcTeamComponent_PlayerState::GetSubTeamsBySubclass(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams)
{
	TArray<UArcTeam*> Teams;
	GetSubTeams(Teams);
	for (UArcTeam* Team : Teams)
	{
		if (Team->GetTeamDefinition()->IsChildOf(SubteamDef))
		{
			OutSubteams.Add(Team);
		}
	}
}

void UArcTeamComponent_PlayerState::GetSubTeamsByTagQuery(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams)
{
	TArray<UArcTeam*> Teams;
	GetSubTeams(Teams);
	for (UArcTeam* Team : Teams)
	{
		FGameplayTagContainer Tags;
		Team->GetOwnedGameplayTags(Tags);

		if (TagQuery.Matches(Tags))
		{
			OutSubteams.Add(Team);
		}
	}
}

void UArcTeamComponent_PlayerState::SetPrimaryTeam(UArcTeam* InPrimaryTeam)
{
	UArcTeam* PreviousTeam = PrimaryTeam;
	PrimaryTeam = InPrimaryTeam;

	if (IsValid(PreviousTeam))
	{
		OnTeamLeave.Broadcast(PreviousTeam, this);
	}
	if (IsValid(PrimaryTeam))
	{
		OnTeamJoined.Broadcast(PrimaryTeam, this);
	}
}


void UArcTeamComponent_PlayerState::AddSubTeam(UArcTeam* SubTeam)
{
	if (IsValid(SubTeam))
	{
		FArcTeamsPlayerSubTeamEntry Entry;
		Entry.Team = SubTeam;
		SubTeams.Items.Add(Entry);

		SubTeams.MarkArrayDirty();
		OnTeamJoined.Broadcast(SubTeam, this);
	}	
}

void UArcTeamComponent_PlayerState::RemoveSubTeam(UArcTeam* SubTeam)
{
	for (int i = 0; i < SubTeams.Items.Num(); i++)
	{
		FArcTeamsPlayerSubTeamEntry& Entry = SubTeams.Items[i];

		UArcTeam* Team = Entry.Team;

		if (Team == SubTeam)
		{
			SubTeams.Items.RemoveAt(i);
			i--;
		}
	}

	SubTeams.MarkArrayDirty();
	OnTeamLeave.Broadcast(SubTeam, this);
}

void FArcTeamsPlayerSubTeamEntry::PreReplicatedRemove(const struct FArcTeamsPlayerSubTeamArray& InArraySerializer)
{
	if (IsValid(InArraySerializer.ParentPlayerState))
	{
		InArraySerializer.ParentPlayerState->OnTeamLeave.Broadcast(Team, InArraySerializer.ParentPlayerState);
	}
}

void FArcTeamsPlayerSubTeamEntry::PostReplicatedAdd(const struct FArcTeamsPlayerSubTeamArray& InArraySerializer)
{
	if (IsValid(InArraySerializer.ParentPlayerState))
	{
		InArraySerializer.ParentPlayerState->OnTeamJoined.Broadcast(Team, InArraySerializer.ParentPlayerState);
	}
}


namespace PlayerStateDebug
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

	void ShowDebug(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float&  YL, float&  YPos)
	{
		if (!DisplayInfo.IsDisplayOn(TEXT("Team")))
		{
			return;
		}

		APlayerController* PC = HUD->GetOwningPlayerController();
		APlayerState* PS = PC->GetPlayerState<APlayerState>();

		if (UArcTeamComponent_PlayerState* PSComp = Cast<UArcTeamComponent_PlayerState>(PS->GetComponentByClass(UArcTeamComponent_PlayerState::StaticClass())))
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

			//Debug here
			UArcTeam* Team = PSComp->GetPrimaryTeam();
			FString TeamStr = IsValid(Team) ? Team->GetName() : "Null";
			FString TeamDef = IsValid(Team) ? Team->GetTeamDefinition()->GetName() : "NullDef";

			Canvas->SetDrawColor(FColor::Green);
			DebugLine(DebugInfo, FString::Printf(TEXT("Team: %s, Def %s"), *TeamStr, *TeamDef), 0, 0);

			Canvas->SetDrawColor(FColor::White);


			YPos = DebugInfo.YPos;
			YL = DebugInfo.YL;
		}

	}

	FDelegateHandle DebugHandle = AHUD::OnShowDebugInfo.AddStatic(&ShowDebug);
}
