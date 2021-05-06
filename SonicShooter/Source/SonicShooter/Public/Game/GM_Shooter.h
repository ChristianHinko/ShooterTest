// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/SSGameMode.h"

#include "GM_Shooter.generated.h"


class UArcInventoryComponent;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API AGM_Shooter : public ASSGameMode
{
	GENERATED_BODY()
	
public:
	AGM_Shooter();


protected:
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;

	/** Override this event if you want to customize how this Game Mode gives you your startup items */
	virtual void GiveInventoryStartupItems(UArcInventoryComponent* Inventory);
};