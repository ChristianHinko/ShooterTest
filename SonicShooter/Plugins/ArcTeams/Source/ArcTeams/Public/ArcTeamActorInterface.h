// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTags.h"
#include "Templates/SubclassOf.h"
#include "ArcTeamActorInterface.generated.h"

class UArcTeam;
class UArcTeamDefinition;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UArcTeamActorInterface : public UInterface
{
	GENERATED_BODY()
};

/** Interface for objects that need associations to a team (or subteams)
 * 
 * Example:

 UCLASS()
 class AExampleTeamActor : public AActor, public IArcTeamActorInterface
 {
   GENERATED_BODY()
public:
	
	//Replicate Team and SubTeams
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    
	UPROPERTY(Replicated)
	UArcTeam* Team;

	UPROPERTY(Replicated)
	TArray<UArcTeam*> SubTeams;

	virtual UArcTeam* GetPrimaryTeam() const override
	{
		return Team;
	}
	virtual void SetPrimaryTeam(UArcTeam* InTeam) override
	{
		Team = InTeam;
	}

	virtual void GetSubTeams(TArray<UArcTeam*>& OutSubteams) const override
	{
		OutSubteams.Append(SubTeams);
	}
	virtual void AddSubTeam(UArcTeam* InTeam) override
	{
		SubTeams.Add(InTeam);
	}
	virtual void RemoveSubTeam(UArcTeam* TeamToRemove) override
	{
		SubTeams.Remove(TeamToRemove);
	}

 };

 */
class ARCTEAMS_API IArcTeamActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ArcTeams")
	UArcTeam* GetPrimaryTeam() const;
	virtual UArcTeam* GetPrimaryTeam_Implementation() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ArcTeams")
	void SetPrimaryTeam(UArcTeam* InTeam);
	virtual void SetPrimaryTeam_Implementation(UArcTeam* InTeam);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ArcTeams")
	void GetSubTeams(TArray<UArcTeam*>& OutSubteams) const;
	virtual void GetSubTeams_Implementation(TArray<UArcTeam*>& OutSubteams) const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ArcTeams")
	void AddSubTeam(UArcTeam* InTeam);
	virtual void AddSubTeam_Implementation(UArcTeam* InTeam);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ArcTeams")
	void RemoveSubTeam(UArcTeam* TeamToRemove);
	virtual void RemoveSubTeam_Implementation(UArcTeam* TeamToRemove);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ArcTeams")
	void GetSubTeamsBySubclass(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams);
	virtual void GetSubTeamsBySubclass_Implementation(TSubclassOf<UArcTeamDefinition> SubteamDef, TArray<UArcTeam*>& OutSubteams);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ArcTeams")
	void GetSubTeamsByTagQuery(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams);
	virtual void GetSubTeamsByTagQuery_Implementation(FGameplayTagQuery TagQuery, TArray<UArcTeam*>& OutSubteams);
};
