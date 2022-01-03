// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTags.h"
#include "Engine/NetSerialization.h"
#include "ArcTeamComponent_GameState.generated.h"

class UArcTeam;
class UArcTeamDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FArcTeamTeamAddedEvent, UArcTeamComponent_GameState*, GameStateComponent, UArcTeam*, Team);

USTRUCT()
struct FArcTeamsTeamEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
public:

	UPROPERTY()
	UArcTeam* Team;

	void PreReplicatedRemove(const struct FArcTeamsTeamArray& InArraySerializer);
	void PostReplicatedAdd(const struct FArcTeamsTeamArray& InArraySerializer);
};

USTRUCT()
struct FArcTeamsTeamArray : public FFastArraySerializer
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FArcTeamsTeamEntry> Items;

	UPROPERTY()
	UArcTeamComponent_GameState* ParentGameState;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FArcTeamsTeamEntry, FArcTeamsTeamArray>(Items, DeltaParms, *this);
	}
};



template<>
struct TStructOpsTypeTraits< FArcTeamsTeamArray > : public TStructOpsTypeTraitsBase2< FArcTeamsTeamArray >
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};

UCLASS( Within=GameStateBase )
class ARCTEAMS_API UArcTeamComponent_GameState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArcTeamComponent_GameState();

	friend class UArcTeamComponent_Gamemode;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	virtual UArcTeamComponent_Gamemode* GetGameModeComponent() const;

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	virtual void GetTeams(TArray<UArcTeam*>& OutTeams, bool bIncludeSubTeams = false) const;

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	int32 GetNumTeams(bool bIncludeSubteams = false) const;

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	void GetTeamsBySubclass(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams);

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	void GetTeamsByTagQuery(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams);

	UPROPERTY(BlueprintAssignable)
	FArcTeamTeamAddedEvent OnTeamAdded;
	UPROPERTY(BlueprintAssignable)
	FArcTeamTeamAddedEvent OnTeamRemoved;

private:

	void AddTeam(UArcTeam* NewTeam);

	void RemoveTeam(UArcTeam* TeamToRemove);

	UPROPERTY(Replicated)
	FArcTeamsTeamArray TeamArray;
	
};
