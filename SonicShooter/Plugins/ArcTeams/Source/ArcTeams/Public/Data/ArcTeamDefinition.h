// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArcTeam_UIObject.h"

#include "TeamState/ArcPublicTeamState.h"
#include "TeamState/ArcPrivateTeamState.h"

#include "GameplayTags.h"
#include "ArcTeamDefinition.generated.h"

class UArcTeamJoinRequirement;

UCLASS()
class ARCTEAMS_API UArcTeamUIObject_TeamDefinition : public UArcTeam_UIObject
{
	GENERATED_BODY()
public:
	UArcTeamUIObject_TeamDefinition(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
		FText TeamName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
		FColor TeamColor;
};


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class ARCTEAMS_API UArcTeamDefinition : public UObject, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
public:
	UArcTeamDefinition(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Team)
	bool bAutoJoinable;

	//Tags that describe this team
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Tags)
	FGameplayTagContainer OwnedTags;

	//Tags that are granted to members of this team
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tags)
	FGameplayTagContainer TagsGrantedToMembers;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category=UI)
	UArcTeamUIObject_TeamDefinition* UIData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tags)
	TSubclassOf<AArcPublicTeamState> PublicTeamState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tags)
	TSubclassOf<AArcPrivateTeamState> PrivateTeamState;


	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = Team)
	TArray<UArcTeamJoinRequirement*> JoinRequirements;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override
	{
		TagContainer.AppendTags(OwnedTags);
	}

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

};


UCLASS()
class ARCTEAMS_API UArcTeamDefinition_Spectator : public UArcTeamDefinition
{
	GENERATED_BODY()
public:
	UArcTeamDefinition_Spectator(const FObjectInitializer& ObjectInitializer);

};

