// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTags.h"
#include "ArcTeamComponent_Gamemode.generated.h"

class UArcTeamDefinition;
class UArcTeamComponent_GameState;
class UArcTeam;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FArcTeamsTeamEvent, UArcTeam*, Team, UArcTeamComponent_PlayerState*, Player);

USTRUCT(BlueprintType)
struct ARCTEAMS_API FArcTeamConstructionInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FArcTeamConstructionInfo()
	{
		FMemory::Memzero(this, sizeof(FArcTeamConstructionInfo));
	}

	//Required.  Class of the team definition.  This is stored as a subclass and the default values are used
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	TSubclassOf<UArcTeamDefinition> TeamDefinition;

	//Set of tags that are added to the TeamInstance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	FGameplayTagContainer InstanceTags;

	//Optional.  Class of the Team Handle.  This can be your own user class.  If you leave blank, Default Team Class will be used
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building", AdvancedDisplay)
	TSubclassOf<UArcTeam> TeamClass;

	//Default Creation for a group of subteams.  Dynamic subteams can be created with CreateSubTeam
	//NOTE: Commented out because UE4 doesn't support struct recurison here.  TODO: Figure out a way around that
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//	TArray< FArcTeamConstructionInfo> SubTeams;
};

UCLASS( Within=GameModeBase )
class ARCTEAMS_API UArcTeamComponent_Gamemode : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArcTeamComponent_Gamemode();

	virtual void PostInitProperties() override;
	virtual void InitializeComponent() override;

	template <typename T>
	T* GetOuterGameMode();

	UFUNCTION(BlueprintCallable, Category = "Building")
	virtual UArcTeam* CreateTeam(const FArcTeamConstructionInfo& ConstructionInfo);

	UFUNCTION(BlueprintCallable, Category = "Building")
	virtual UArcTeam* CreateSubTeam(const FArcTeamConstructionInfo& ConstructionInfo, UArcTeam* ParentTeam);

	//Destroys a team and all of it's subteams.
	//Any members of this team will be removed from the team.
	//If the Team is a primary team, then the players in the team will be moved to Unassigned (PrimaryTeam == nullptr).  
	UFUNCTION(BlueprintCallable, Category = "Building")
	virtual void DestroyTeam(UArcTeam* Team, bool bCleanupTeam = true);
		
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Team)
	bool PlayerRequestJoinTeam(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToJoin);
	virtual bool PlayerRequestJoinTeam_Implementation(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToJoin);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Team)
	bool PlayerLeaveTeam(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToLeave);
	virtual bool PlayerLeaveTeam_Implementation(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToLeave);

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	bool CanPlayerJoinTeam(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToJoin) const;

	UFUNCTION(BlueprintCallable, Category = "ArcTeams|Teams")
	bool RemovePlayerFromOwnTeam(UArcTeamComponent_PlayerState* Player);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Team)
	UArcTeam* FindBestTeamForPlayer(UArcTeamComponent_PlayerState* Player);
	virtual UArcTeam* FindBestTeamForPlayer_Implementation(UArcTeamComponent_PlayerState* Player);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Team)
	void AutoAssignPlayer(UArcTeamComponent_PlayerState* Player);
	virtual void AutoAssignPlayer_Implementation(UArcTeamComponent_PlayerState* Player);


	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	virtual void GetAutoJoinableTeams(TArray<UArcTeam*>& OutTeams);

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	virtual void GetJoinableTeamsForPlayer(UArcTeamComponent_PlayerState* Player, TArray<UArcTeam*>& OutTeams, bool bIncludeSpectator = false);


	virtual void OnPlayerLoggedIn(AGameModeBase* GameMode, APlayerController* NewPlayer);
	virtual void OnPlayerLoggedOut(AGameModeBase* GameMode, AController* Exiting);

	virtual AActor* ChoosePlayerStart(AController* Player);

	UFUNCTION(BlueprintNativeEvent)
	bool CanUsePlayerStartForPlayer(AController* Player, AActor* PlayerStart);
	virtual bool CanUsePlayerStartForPlayer_Implementation(AController* Player, AActor* PlayerStart);


	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	virtual void GetPrimaryTeams(TArray<UArcTeam*>& OutTeams) const;

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	void GetTeamsBySubclass(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams);

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	void GetTeamsByTagQuery(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams);

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	int32 GetNumPrimaryTeams() const;

	UPROPERTY(BlueprintAssignable)
	FArcTeamsTeamEvent OnPlayerJoinedTeamEvent;
	UPROPERTY(BlueprintAssignable)
	FArcTeamsTeamEvent OnPlayerLeaveTeamEvent;

protected:
	//Internal Join/Leave functions.  These assume that a player can be join or leave the team, and thus ignore join requirements.
	//Use RequestJoinTeam if you neet to confirm that it's possible to do this
	virtual void PlayerJoinTeam_Internal(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToJoin);
	virtual void PlayerLeaveTeam_Internal(UArcTeamComponent_PlayerState* Player, UArcTeam* TeamToLeave = nullptr);

	
	
public:	

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	bool bAutoAssignNewPlayers;

	//True if you want to automatically call OnPlayerLoggedIn, false if you manually handle it in your gamemode
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	bool bBindToPostLoginEvent;

	UPROPERTY()
	UArcTeam* SpectatorTeam;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	TSubclassOf<UArcTeam> DefaultTeamClass;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	FArcTeamConstructionInfo SpectatorTeamDefinition;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	TArray<FArcTeamConstructionInfo> DefaultTeams;

	//Query to check if a given player on a given team is allowed to spawn on default Player Starts.  If this query is empty, teamed players will not be able to spawn 
	//on default spawns.  
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	FGameplayTagQuery DefaultSpawnAllowQuery;
	
private:

	UPROPERTY()
	UArcTeamComponent_GameState* GameStateComponent;
		
};

