// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ArcPrivateTeamState.generated.h"

class UArcTeam;

/**
 * 
 */
UCLASS(Blueprintable)
class ARCTEAMS_API AArcPrivateTeamState : public AInfo
{
	GENERATED_BODY()
public:
	AArcPrivateTeamState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
	

	UPROPERTY(BlueprintReadOnly, Category = "ArcTeams", Replicated)
	UArcTeam* ParentTeam;
};
