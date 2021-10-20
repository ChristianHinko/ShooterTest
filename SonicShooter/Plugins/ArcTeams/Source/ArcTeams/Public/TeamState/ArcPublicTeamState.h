// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ArcPublicTeamState.generated.h"

class UArcTeam;

/**
 * 
 */
UCLASS(Blueprintable)
class ARCTEAMS_API AArcPublicTeamState : public AInfo
{
	GENERATED_BODY()
public:
	AArcPublicTeamState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly, Category="ArcTeams", Replicated)
	UArcTeam* ParentTeam;
};
