// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTags.h"
#include "UObject/CoreNet.h"
#include "Engine/EngineTypes.h"
#include "Engine/NetSerialization.h"
#include "ArcTeam.generated.h"

class UArcTeamDefinition;
class UArcTeamComponent_PlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FArcTeamPlayerAddedEvent, UArcTeam*, Team, UArcTeamComponent_PlayerState*, Player);

USTRUCT()
struct FArcTeamsPlayerEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
public:

	UPROPERTY()
		UArcTeamComponent_PlayerState* Player;

	void PreReplicatedRemove(const struct FArcTeamsPlayersArray& InArraySerializer);
	void PostReplicatedAdd(const struct FArcTeamsPlayersArray& InArraySerializer);
};

USTRUCT()
struct FArcTeamsPlayersArray : public FFastArraySerializer
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FArcTeamsPlayerEntry> Items;

	UPROPERTY()
	UArcTeam* ParentTeam;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FArcTeamsPlayerEntry, FArcTeamsPlayersArray>(Items, DeltaParms, *this);
	}
};

template<>
struct TStructOpsTypeTraits< FArcTeamsPlayersArray > : public TStructOpsTypeTraitsBase2< FArcTeamsPlayersArray >
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FArcTeamSubTeamAddedEvent, UArcTeam*, ParentTeam, UArcTeam*, SubTeam);

USTRUCT()
struct FArcTeamsSubTeamEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
public:

	UPROPERTY()
		UArcTeam* Team;

	void PreReplicatedRemove(const struct FArcTeamsSubTeamArray& InArraySerializer);
	void PostReplicatedAdd(const struct FArcTeamsSubTeamArray& InArraySerializer);
};

USTRUCT()
struct FArcTeamsSubTeamArray : public FFastArraySerializer
{
	GENERATED_BODY()
public:
	UPROPERTY()
		TArray<FArcTeamsSubTeamEntry> Items;

	UPROPERTY()
		UArcTeam* ParentTeam;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FArcTeamsSubTeamEntry, FArcTeamsSubTeamArray>(Items, DeltaParms, *this);
	}
};

template<>
struct TStructOpsTypeTraits< FArcTeamsSubTeamArray > : public TStructOpsTypeTraitsBase2< FArcTeamsSubTeamArray >
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};


/**
 * 
 */
UCLASS(BlueprintType)
class ARCTEAMS_API UArcTeam : public UObject, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
public:
	UArcTeam(const FObjectInitializer& ObjectInitializer);
	
	friend class UArcTeamComponent_Gamemode;
	friend class UArcTeamComponent_GameState;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override; 
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags);


	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;


	UFUNCTION(BlueprintPure, Category="ArcTeam")
	virtual TSubclassOf<UArcTeamDefinition> GetTeamDefinition() const;

	UFUNCTION(BlueprintPure, Category = "ArcTeam")
	void GetPlayers(TArray<UArcTeamComponent_PlayerState*>& OutPlayers) const;
	int32 GetNumPlayers() const;

	UFUNCTION(BlueprintPure, Category = "ArcTeam")
	void GetSubTeams(TArray<UArcTeam*>& OutSubTeams) const;
	int32 GetNumSubTeams() const;

	UFUNCTION(BlueprintPure, Category = "ArcTeam")
	bool IsPrimaryTeam() const;

	UFUNCTION(BlueprintPure, Category = "ArcTeam")
	UArcTeam* GetParentTeam() const;

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	void GetSubTeamsBySubclass(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams);

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	void GetSubTeamsByTagQuery(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams);

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	AArcPublicTeamState* GetPublicTeamState() const;

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	AArcPrivateTeamState* GetPrivateTeamState() const;

	UPROPERTY(BlueprintAssignable)
	FArcTeamPlayerAddedEvent OnPlayerAddedToTeam;
	UPROPERTY(BlueprintAssignable)
	FArcTeamPlayerAddedEvent OnPlayerRemovedFromTeam;

	UPROPERTY(BlueprintAssignable)
	FArcTeamSubTeamAddedEvent OnSubteamAdded;

	UPROPERTY(BlueprintAssignable)
	FArcTeamSubTeamAddedEvent OnSubteamRemoved;


	virtual void CleanupTeam();

protected:


	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Team", Replicated)
	FGameplayTagContainer LooseTeamTags;


	UPROPERTY(VisibleInstanceOnly, Category = "Team", Replicated)
	TSubclassOf<UArcTeamDefinition> TeamDefinition;

	UPROPERTY(VisibleInstanceOnly, Category = "Team", Replicated)
	FArcTeamsPlayersArray Players;

	UPROPERTY(VisibleInstanceOnly, Category = "Team", Replicated)
	UArcTeam* ParentTeam;

	UPROPERTY(VisibleInstanceOnly, Category = "Team", Replicated)
	FArcTeamsSubTeamArray SubTeams;

	UPROPERTY(VisibleInstanceOnly, Category = "Team", ReplicatedUsing=OnRep_PublicTeamState)
	AArcPublicTeamState* PublicTeamState;

	UFUNCTION()
	virtual void OnRep_PublicTeamState();

	UPROPERTY(VisibleInstanceOnly, Category = "Team", ReplicatedUsing=OnRep_PrivateTeamState)
	AArcPrivateTeamState* PrivateTeamState;

	UFUNCTION()
	virtual void OnRep_PrivateTeamState();

private:
	//These functions are called by the Gamemode component because we are a friend class
	void AddPlayerToTeam(UArcTeamComponent_PlayerState* Player);
	void RemovePlayerFromTeam(UArcTeamComponent_PlayerState* Player);
	void PrepareForDestroy();

	void AddSubteamToTeam(UArcTeam* InSubTeam);
	void RemoveSubteamFromTeam(UArcTeam* InSubTeam);
};
