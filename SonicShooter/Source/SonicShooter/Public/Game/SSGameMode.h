// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "SSGameMode.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API ASSGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ASSGameMode();


protected:
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;

};
