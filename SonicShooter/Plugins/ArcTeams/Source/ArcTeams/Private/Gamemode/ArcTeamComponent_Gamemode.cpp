// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Gamemode/ArcTeamComponent_Gamemode.h"
#include "Gamemode/ArcTeamComponent_GameState.h"
#include "Gamemode/ArcTeamComponent_PlayerState.h"

#include "Data/ArcTeam.h"
#include "ArcTeamsBlueprintLibrary.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework//GameStateBase.h"

#include "Engine.h"

#include "Data/ArcTeamDefinition.h"
#include "Data/ArcTeamJoinRequirement.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerStart.h"

#include "ArcTeamPlayerStart.h"
#include "TeamState/ArcPrivateTeamState.h"
#include "TeamState/ArcPublicTeamState.h"

#include "ArcTeams.h"


// Sets default values for this component's properties
UArcTeamComponent_Gamemode::UArcTeamComponent_Gamemode()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultTeamClass = UArcTeam::StaticClass();
	SpectatorTeamDefinition.TeamDefinition = UArcTeamDefinition_Spectator::StaticClass();
	bAutoAssignNewPlayers = true;
	bBindToPostLoginEvent = true;

	bWantsInitializeComponent = true;

}

template <typename T>
T* UArcTeamComponent_Gamemode::GetOuterGameMode()
{
	return Cast<T>(GetOuter());
}


void UArcTeamComponent_Gamemode::PostInitProperties()
{
	Super::PostInitProperties();	
}

void UArcTeamComponent_Gamemode::InitializeComponent()
{
	Super::InitializeComponent();

	//We don't want to do any of these things for CDOs
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}
	//Get the GameState Component.  If it doesn't have one, create it
	AGameModeBase* GameMode = Cast<AGameModeBase>(GetOuter());

	if (!IsValid(GameMode))
	{
		UE_LOG(LogArcTeams, Fatal, TEXT("UArcTeamComponent_Gamemode::PostInitProperties Not part of a GameMode.  This cannot be recovered from!"));
		return;
	}

	//If we are an instance on the GameMode CDO, don't do anything
	if (GameMode->HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}

	AGameStateBase* GameState = GameMode->GetGameState<AGameStateBase>();
	if (!IsValid(GameState))
	{
		//UE_LOG(LogArcTeams, Fatal, TEXT("UArcTeamComponent_Gamemode::PostInitProperties Can't Find a GameState.  This cannot be recovered from!"));
		return;
	}

	UArcTeamComponent_GameState* GameStateComp = Cast<UArcTeamComponent_GameState>(GameState->GetComponentByClass(UArcTeamComponent_GameState::StaticClass()));
	if (!IsValid(GameStateComp))
	{
		GameStateComp = NewObject<UArcTeamComponent_GameState>(GameState);
		GameStateComp->RegisterComponent();
	}

	GameStateComponent = GameStateComp;

	

	//Add the spectator team to the GameState
	if (!IsValid(SpectatorTeamDefinition.TeamDefinition))
	{
		//TODO: Get a DeveloperSettings default state here
		SpectatorTeamDefinition.TeamDefinition = UArcTeamDefinition_Spectator::StaticClass();
	}
	if (!IsValid(SpectatorTeamDefinition.TeamClass))
	{
		SpectatorTeamDefinition.TeamClass = DefaultTeamClass;
	}

	SpectatorTeam = CreateTeam(SpectatorTeamDefinition);

	//Add the default teams
	for (FArcTeamConstructionInfo TeamDefinition : DefaultTeams)
	{
		CreateTeam(TeamDefinition);
	}

	//Bind to the Gamemode events that we need
	if (bBindToPostLoginEvent)
	{
		FGameModeEvents::GameModePostLoginEvent.AddUObject(this, &UArcTeamComponent_Gamemode::OnPlayerLoggedIn);
	}
	FGameModeEvents::GameModeLogoutEvent.AddUObject(this, &UArcTeamComponent_Gamemode::OnPlayerLoggedOut);
}

UArcTeam* UArcTeamComponent_Gamemode::CreateTeam(const FArcTeamConstructionInfo& ConstructionInfo)
{
	check(IsValid(ConstructionInfo.TeamDefinition)); //Make sure we have a valid TeamDefinition	

	TSubclassOf<UArcTeam> TeamClass = ConstructionInfo.TeamClass;
	if (!IsValid(TeamClass))
	{
		TeamClass = DefaultTeamClass;
		if (!IsValid(TeamClass))
		{
			TeamClass = UArcTeam::StaticClass();
		}
	}

	check(IsValid(TeamClass)); //Make sure we have some TeamClass

	UArcTeam* NewTeam = NewObject<UArcTeam>(GameStateComponent, TeamClass);
	NewTeam->TeamDefinition = ConstructionInfo.TeamDefinition;
	NewTeam->LooseTeamTags.AppendTags(ConstructionInfo.InstanceTags);

	if (IsValid(NewTeam->GetTeamDefinition().GetDefaultObject()->PublicTeamState))
	{
		TSubclassOf<AArcPublicTeamState> TeamStateClass = NewTeam->GetTeamDefinition().GetDefaultObject()->PublicTeamState;
		NewTeam->PublicTeamState = GetWorld()->SpawnActor<AArcPublicTeamState>(TeamStateClass, FTransform::Identity);
		NewTeam->PublicTeamState->ParentTeam = NewTeam;
	}

	if (IsValid(NewTeam->GetTeamDefinition().GetDefaultObject()->PrivateTeamState))
	{
		TSubclassOf<AArcPrivateTeamState> TeamStateClass = NewTeam->GetTeamDefinition().GetDefaultObject()->PrivateTeamState;
		NewTeam->PrivateTeamState = GetWorld()->SpawnActor<AArcPrivateTeamState>(TeamStateClass, FTransform::Identity);
		NewTeam->PrivateTeamState->ParentTeam = NewTeam;
	}

	/* Commented out because UE4 doesn't support struct recurison.  
	for (auto SubTeamInfo : ConstructionInfo.SubTeams)
	{
		CreateSubTeam(SubTeamInfo, NewTeam);
	}
	*/
	GameStateComponent->AddTeam(NewTeam);


	return NewTeam;
}

UArcTeam* UArcTeamComponent_Gamemode::CreateSubTeam(const FArcTeamConstructionInfo& ConstructionInfo, UArcTeam* ParentTeam)
{
	UArcTeam* NewTeam = CreateTeam(ConstructionInfo);
	NewTeam->ParentTeam = ParentTeam;
	ParentTeam->AddSubteamToTeam(NewTeam);

	return NewTeam;
}

void UArcTeamComponent_Gamemode::DestroyTeam(UArcTeam* Team, bool bCleanupTeam /*= true*/)
{
	if (!IsValid(Team))
	{
		return;
	}

	//First, destroy all subteams.
	TArray<UArcTeam*> CurSubteams;
	Team->GetSubTeams(CurSubteams);

	for (UArcTeam* SubTeam : CurSubteams)
	{
		DestroyTeam(SubTeam);
	}
	Team->SubTeams.Items.Empty();

	if (!Team->IsPrimaryTeam())
	{
		TArray< UArcTeamComponent_PlayerState*> Players;
		Team->GetPlayers(Players);
		for (UArcTeamComponent_PlayerState* Member : Players)
		{
			Member->RemoveSubTeam(Team);
		}

		Team->ParentTeam->RemoveSubteamFromTeam(Team);
	}
	else
	{
		TArray< UArcTeamComponent_PlayerState*> Players;
		Team->GetPlayers(Players);
		for (UArcTeamComponent_PlayerState* Member : Players)
		{
			Member->PrimaryTeam = nullptr;
		}		
	}
	Team->PrepareForDestroy();

	GameStateComponent->RemoveTeam(Team);

	if (bCleanupTeam)
	{
		Team->CleanupTeam();
	}
}

bool UArcTeamComponent_Gamemode::PlayerRequestJoinTeam_Implementation(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToJoin)
{
	if (!IsValid(TeamToJoin))
	{
		return false;
	}

	if (!IsValid(Player))
	{
		return false;
	}

	//We cannot join a Primary Team if the player is in one.  Leave that primary team first.  
	//We can be part of as many SubTeams as we want, however.  
	if (TeamToJoin->IsPrimaryTeam() && IsValid(Player->GetPrimaryTeam()))
	{
		return false;
	}

	if (!CanPlayerJoinTeam(Player, TeamToJoin))
	{
		//TODO: Report back to the player why not
		return false;
	}

	PlayerJoinTeam_Internal(Player, TeamToJoin);

	return true;
}

bool UArcTeamComponent_Gamemode::PlayerLeaveTeam_Implementation(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToLeave)
{
	if (!IsValid(TeamToLeave))
	{
		return false;
	}

	if (!IsValid(Player))
	{
		return false;
	}

	PlayerLeaveTeam_Internal(Player, TeamToLeave);

	return true;
}

bool UArcTeamComponent_Gamemode::CanPlayerJoinTeam(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToJoin) const
{
	FArcTeamJoinRequirementParams RequestParams;
	RequestParams.WorldContextObject = const_cast<UArcTeamComponent_Gamemode*>(this);
	RequestParams.PlayersJoining.Add(Player);
	RequestParams.TeamToJoin = TeamToJoin;

	TArray<UArcTeamJoinRequirement*>& JoinRequirements = TeamToJoin->GetTeamDefinition().GetDefaultObject()->JoinRequirements;

	for (UArcTeamJoinRequirement*& Req : JoinRequirements)
	{
		if (!Req->CanJoinTeam(RequestParams))
		{
			return false;
		}
	}

	return true;
}

bool UArcTeamComponent_Gamemode::RemovePlayerFromOwnTeam(UArcTeamComponent_PlayerState* Player)
{	
	if (!IsValid(Player))
	{
		return false;
	}
	PlayerLeaveTeam_Internal(Player);
	return true;
}

UArcTeam* UArcTeamComponent_Gamemode::FindBestTeamForPlayer_Implementation(UArcTeamComponent_PlayerState* Player)
{
	TArray<UArcTeam*> JoinableTeams;
	GetAutoJoinableTeams(JoinableTeams);
	GetJoinableTeamsForPlayer(Player, JoinableTeams);

	//If we don't have any auto joinable teams, toss them into spectator
	if (JoinableTeams.Num() == 0)
	{
		return SpectatorTeam;
	}

	//Find the team with the smallest number of players
	UArcTeam* SmallestTeam = JoinableTeams[0];
	int32 SmallestCount = INT32_MAX;

	for (UArcTeam* Team : JoinableTeams)
	{
		if (Team->GetNumPlayers() < SmallestCount)
		{
			SmallestCount = Team->GetNumPlayers();
			SmallestTeam = Team;
		}
	}

	return SmallestTeam;

}

void UArcTeamComponent_Gamemode::AutoAssignPlayer_Implementation(UArcTeamComponent_PlayerState* Player)
{
	UArcTeam* TeamToJoin = FindBestTeamForPlayer(Player);

	PlayerRequestJoinTeam(Player, TeamToJoin);
}

void UArcTeamComponent_Gamemode::GetAutoJoinableTeams(TArray<UArcTeam*>& OutTeams)
{
	TArray<UArcTeam*> Teams;
	if (OutTeams.Num() > 0)
	{
		Teams.Append(OutTeams);
		OutTeams.Empty(OutTeams.Num());
	}
	else
	{
		GameStateComponent->GetTeams(Teams, false);
	}

	for (UArcTeam* Team : Teams)
	{
		if (Team == SpectatorTeam)
		{
			continue;
		}

		if (Team->GetTeamDefinition().GetDefaultObject()->bAutoJoinable)
		{
			OutTeams.Add(Team);
		}
	}
}

void UArcTeamComponent_Gamemode::GetJoinableTeamsForPlayer(UArcTeamComponent_PlayerState* Player, TArray<UArcTeam*>& OutTeams, bool bIncludeSpectator /*= false*/)
{
	TArray<UArcTeam*> Teams;
	if (OutTeams.Num() > 0)
	{
		Teams.Append(OutTeams);
		OutTeams.Empty(OutTeams.Num());
	}
	else
	{
		GameStateComponent->GetTeams(Teams, false);
	}

	for (UArcTeam* Team : Teams)
	{
		if (Team == SpectatorTeam && bIncludeSpectator)
		{
			continue;
		}

		FArcTeamJoinRequirementParams RequestParams;
		RequestParams.WorldContextObject = this;
		RequestParams.PlayersJoining.Add(Player);
		RequestParams.TeamToJoin = Team;

		TArray<UArcTeamJoinRequirement*>& JoinRequirements = Team->GetTeamDefinition().GetDefaultObject()->JoinRequirements;

		bool canJoin = true;
		for (UArcTeamJoinRequirement* Req : JoinRequirements)
		{
			if (!Req->CanJoinTeam(RequestParams))
			{
				canJoin = false;
				break;
			}
		}

		if (canJoin)
		{
			OutTeams.Add(Team);
		}
	}
}

void UArcTeamComponent_Gamemode::OnPlayerLoggedIn(AGameModeBase* GameMode, APlayerController* NewPlayer)
{
	if (GameMode != GetOuter())
	{
		return;
	}

	//First thing we need to do is give this player a Team Component
	APlayerState* PS = NewPlayer->GetPlayerState<APlayerState>();

	UArcTeamComponent_PlayerState* PSComp = Cast<UArcTeamComponent_PlayerState>(PS->GetComponentByClass(UArcTeamComponent_PlayerState::StaticClass()));
	if (!IsValid(PSComp))
	{
		PSComp = NewObject<UArcTeamComponent_PlayerState>(PS);
		PSComp->RegisterComponent();
	}
		

	//If we need to push this player to spectator, do so.
	if (GameMode->MustSpectate(NewPlayer))
	{
		PlayerRequestJoinTeam(PSComp, SpectatorTeam);
	}

	//Else, find a team for them
	if (bAutoAssignNewPlayers)
	{
		AutoAssignPlayer(PSComp);
	}	
}

void UArcTeamComponent_Gamemode::OnPlayerLoggedOut(AGameModeBase* GameMode, AController* Exiting)
{
	if (GameMode != GetOuter())
	{
		return;
	}

	if (APlayerController* PC = Cast<APlayerController>(Exiting))
	{
		APlayerState* PS = PC->GetPlayerState<APlayerState>();
		if (!IsValid(PS))
		{
			return;
		}
		UArcTeamComponent_PlayerState* PSComp = Cast<UArcTeamComponent_PlayerState>(PS->GetComponentByClass(UArcTeamComponent_PlayerState::StaticClass()));
		if (!IsValid(PSComp))
		{
			return;
		}

		//TODO: Force this
		RemovePlayerFromOwnTeam(PSComp);		

	}

}

AActor* UArcTeamComponent_Gamemode::ChoosePlayerStart(AController* Player)
{
	// Choose a player start
	APlayerStart* FoundPlayerStart = nullptr;
	UClass* PawnClass =  GetOuterGameMode<AGameModeBase>()->GetDefaultPawnClassForController(Player);
	APawn* PawnToFit = PawnClass ? PawnClass->GetDefaultObject<APawn>() : nullptr;
	TArray<APlayerStart*> UnOccupiedStartPoints;
	TArray<APlayerStart*> OccupiedStartPoints;
	UWorld* World = GetWorld();
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* PlayerStart = *It;

		if (PlayerStart->IsA<APlayerStartPIE>())
		{
			// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
			FoundPlayerStart = PlayerStart;
			break;
		}

		if (!CanUsePlayerStartForPlayer(Player, PlayerStart))
		{
			continue;
		}
		
		FVector ActorLocation = PlayerStart->GetActorLocation();
		const FRotator ActorRotation = PlayerStart->GetActorRotation();
		if (!World->EncroachingBlockingGeometry(PawnToFit, ActorLocation, ActorRotation))
		{
			UnOccupiedStartPoints.Add(PlayerStart);
		}
		else if (World->FindTeleportSpot(PawnToFit, ActorLocation, ActorRotation))
		{
			OccupiedStartPoints.Add(PlayerStart);
		}
		
	}
	if (FoundPlayerStart == nullptr)
	{
		if (UnOccupiedStartPoints.Num() > 0)
		{
			FoundPlayerStart = UnOccupiedStartPoints[FMath::RandRange(0, UnOccupiedStartPoints.Num() - 1)];
		}
		else if (OccupiedStartPoints.Num() > 0)
		{
			FoundPlayerStart = OccupiedStartPoints[FMath::RandRange(0, OccupiedStartPoints.Num() - 1)];
		}
	}
	return FoundPlayerStart;
}

bool UArcTeamComponent_Gamemode::CanUsePlayerStartForPlayer_Implementation(AController* Player, AActor* PlayerStart)
{
	if (!IsValid(PlayerStart))
	{
		return false;
	}

	//Sometimes, if we fail early to get a start spot, FindPlayerStart uses the world settings and just kinda holds onto it.
	if (PlayerStart->IsA(AWorldSettings::StaticClass()))
	{
		return false;
	}

	//If we don't have a team, might as well just let us spawn here
	UArcTeam* PlayerTeam = UArcTeamsBlueprintLibrary::GetPrimaryTeamFromPlayer(Player);
	if (!IsValid(PlayerTeam))
	{
		return true;
	}


	if (AArcTeamPlayerStart* TeamPlayerStart = Cast<AArcTeamPlayerStart>(PlayerStart))
	{
		return TeamPlayerStart->AllowPlayerToSpawn(Player);
	}

	//Otherwise handle how to allow this player to start here.
	if (!DefaultSpawnAllowQuery.IsEmpty())
	{		
		FGameplayTagContainer TeamTagContainer;
		PlayerTeam->GetOwnedGameplayTags(TeamTagContainer);

		if (DefaultSpawnAllowQuery.Matches(TeamTagContainer))
		{
			return true;
		}
	}

	return false;
}

void UArcTeamComponent_Gamemode::GetPrimaryTeams(TArray<UArcTeam*>& OutTeams) const
{
	GameStateComponent->GetTeams(OutTeams, false);
}

void UArcTeamComponent_Gamemode::GetTeamsBySubclass(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams)
{
	TArray <UArcTeam*> PossibleTeams;
	GameStateComponent->GetTeams(PossibleTeams, true);

	for (UArcTeam* Team : PossibleTeams)
	{
		if (Team->GetTeamDefinition()->IsChildOf(SubteamDef))
		{
			OutSubteams.Add(Team);
		}
	}
}

void UArcTeamComponent_Gamemode::GetTeamsByTagQuery(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams)
{
	TArray <UArcTeam*> PossibleTeams;
	GameStateComponent->GetTeams(PossibleTeams, true);

	for (UArcTeam* Team : PossibleTeams)
	{
		FGameplayTagContainer Tags;
		Team->GetOwnedGameplayTags(Tags);

		if (TagQuery.Matches(Tags))
		{
			OutSubteams.Add(Team);
		}
	}
}

int32 UArcTeamComponent_Gamemode::GetNumPrimaryTeams() const
{
	return GameStateComponent ? GameStateComponent->GetNumTeams(false) : 0;
}

void UArcTeamComponent_Gamemode::PlayerJoinTeam_Internal(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToJoin)
{
	check(IsValid(Player));
	check(IsValid(TeamToJoin));
	//check(TeamToJoin->IsPrimaryTeam() && IsValid(Player->GetPrimaryTeam())); // Can't join a Primary Team if the player is already in one. 
	
	//By this point, we assume that we can be put into this team
	TeamToJoin->AddPlayerToTeam(Player);

	if (TeamToJoin->IsPrimaryTeam())
	{
		Player->SetPrimaryTeam(TeamToJoin);
	}
	else
	{
		Player->AddSubTeam(TeamToJoin);
	}
	OnPlayerJoinedTeamEvent.Broadcast(TeamToJoin, Player);
	
}

void UArcTeamComponent_Gamemode::PlayerLeaveTeam_Internal(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToLeave)
{
	check(IsValid(Player));

	if (!IsValid(TeamToLeave))
	{
		//If nullptr is passed into this function, assume that we want to leave our primary team
		if (IsValid(Player->PrimaryTeam))
		{
			TeamToLeave = Player->PrimaryTeam;
		}
	}

	if (IsValid(TeamToLeave))
	{
		//Leave this team.
		TeamToLeave->RemovePlayerFromTeam(Player);

		if (TeamToLeave == Player->PrimaryTeam)
		{			
			Player->SetPrimaryTeam(nullptr);
		}
		else
		{
			Player->RemoveSubTeam(TeamToLeave);
		}

		//Leave all the subteams for this team
		TArray<UArcTeam*> SubTeams;
		TeamToLeave->GetSubTeams(SubTeams);

		for (UArcTeam* SubTeam : SubTeams)
		{
			PlayerLeaveTeam_Internal(Player, SubTeam);
			OnPlayerLeaveTeamEvent.Broadcast(SubTeam, Player);
		}
		OnPlayerLeaveTeamEvent.Broadcast(TeamToLeave, Player);
	}	
}

