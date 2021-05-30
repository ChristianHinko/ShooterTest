// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gamemode/ArcTeamComponent_Gamemode.h"
#include "GameplayTags.h"
#include "ArcTeamComponent_PlayerState.generated.h"

class UArcTeam;
class UArcTeamDefinition;


USTRUCT()
struct FArcTeamsPlayerSubTeamEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
public:

	UPROPERTY()
		UArcTeam* Team;

	void PreReplicatedRemove(const struct FArcTeamsPlayerSubTeamArray& InArraySerializer);
	void PostReplicatedAdd(const struct FArcTeamsPlayerSubTeamArray& InArraySerializer);
};

USTRUCT()
struct FArcTeamsPlayerSubTeamArray : public FFastArraySerializer
{
	GENERATED_BODY()
public:
	UPROPERTY()
		TArray<FArcTeamsPlayerSubTeamEntry> Items;

	UPROPERTY()
	UArcTeamComponent_PlayerState* ParentPlayerState;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FArcTeamsPlayerSubTeamEntry, FArcTeamsPlayerSubTeamArray>(Items, DeltaParms, *this);
	}
};

template<>
struct TStructOpsTypeTraits< FArcTeamsPlayerSubTeamArray > : public TStructOpsTypeTraitsBase2< FArcTeamsPlayerSubTeamArray >
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};

UCLASS( Within=PlayerState )
class ARCTEAMS_API UArcTeamComponent_PlayerState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArcTeamComponent_PlayerState();
	friend class UArcTeam;
	friend class UArcTeamComponent_Gamemode;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintPure, Category= "ArcTeams|Teams")
	APlayerState* GetPlayerState() const;

	UFUNCTION(BlueprintPure, Category=PrimaryTeam)
	UArcTeam* GetPrimaryTeam() const;

	

	UFUNCTION(BlueprintPure, Category = PrimaryTeam)
	void GetAllTeams(TArray<UArcTeam*>& OutTeams) const;
	
	UFUNCTION(BlueprintPure, Category = PrimaryTeam)
	void GetSubTeams(TArray<UArcTeam*>& OutSubteams) const;

	UFUNCTION(BlueprintPure, Category = PrimaryTeam)
	bool IsInSubTeam(UArcTeam* InSubTeam) const;

	UFUNCTION()
	virtual void OnRep_PrimaryTeam(UArcTeam* PreviousTeam);

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	void GetSubTeamsBySubclass(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams);

	UFUNCTION(BlueprintPure, Category = "ArcTeams|Teams")
	void GetSubTeamsByTagQuery(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams);

	UPROPERTY(BlueprintAssignable)
	FArcTeamsTeamEvent OnTeamJoined;
	UPROPERTY(BlueprintAssignable)
	FArcTeamsTeamEvent OnTeamLeave;

protected:

	void SetPrimaryTeam(UArcTeam* InPrimaryTeam);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team", ReplicatedUsing = OnRep_PrimaryTeam)
	UArcTeam* PrimaryTeam;

	UPROPERTY(Replicated)
	FArcTeamsPlayerSubTeamArray SubTeams;

private:
	//Private, as our friend class the gamemode will call these
	void AddSubTeam(UArcTeam* SubTeam);
	void RemoveSubTeam(UArcTeam* SubTeam);

};
