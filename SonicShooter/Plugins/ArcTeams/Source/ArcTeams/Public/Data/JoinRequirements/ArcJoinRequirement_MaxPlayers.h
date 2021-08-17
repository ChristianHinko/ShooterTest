// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/ArcTeamJoinRequirement.h"
#include "ArcJoinRequirement_MaxPlayers.generated.h"

/**
 * 
 */
UCLASS()
class ARCTEAMS_API UArcJoinRequirement_MaxPlayers : public UArcTeamJoinRequirement
{
	GENERATED_BODY()
public:
	UArcJoinRequirement_MaxPlayers(const FObjectInitializer& ObjectInitializer);

	virtual bool CanJoinTeam_Implementation(const FArcTeamJoinRequirementParams& Params) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team")
	int32 MaxPlayers;
};
