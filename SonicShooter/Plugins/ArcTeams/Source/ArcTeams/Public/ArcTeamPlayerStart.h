// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "GameplayTags.h"
#include "ArcTeamPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class ARCTEAMS_API AArcTeamPlayerStart : public APlayerStart
{
	GENERATED_BODY()
public:
	AArcTeamPlayerStart(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Team")
	FGameplayTagQuery TeamAllowedToSpawnQuery;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Team")
	bool bAllowNoTeamToSpawn;

	UFUNCTION(BlueprintNativeEvent)
	bool AllowPlayerToSpawn(AController* Player);
	virtual bool AllowPlayerToSpawn_Implementation(AController* Player);
};
