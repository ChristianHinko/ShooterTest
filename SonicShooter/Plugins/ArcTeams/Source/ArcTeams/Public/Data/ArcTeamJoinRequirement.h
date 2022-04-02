// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArcTeamJoinRequirement.generated.h"

class UArcTeamComponent_PlayerState;
class UArcTeam;

USTRUCT(BlueprintType)
struct ARCTEAMS_API FArcTeamJoinRequirementParams
{
	GENERATED_USTRUCT_BODY()
public:
	FArcTeamJoinRequirementParams()
	{
		FMemory::Memzero(this, sizeof(FArcTeamJoinRequirementParams));
	}

	UPROPERTY(BlueprintReadOnly, Category = "ArcTeams|Teams")
	UObject* WorldContextObject;

	UPROPERTY(BlueprintReadOnly, Category = "ArcTeams|Teams")
	TArray<UArcTeamComponent_PlayerState*> PlayersJoining;

	UPROPERTY(BlueprintReadOnly, Category = "ArcTeams|Teams")
	UArcTeam* TeamToJoin;
};

/**
 * 
 */
UCLASS(EditInlineNew, Abstract, Blueprintable)
class ARCTEAMS_API UArcTeamJoinRequirement : public UObject
{
	GENERATED_BODY()
public:
	UArcTeamJoinRequirement(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintNativeEvent)
	bool CanJoinTeam(const FArcTeamJoinRequirementParams& Params);
	virtual bool CanJoinTeam_Implementation(const FArcTeamJoinRequirementParams& Params);
	
};
