// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/SSGameMode.h"

#include "SSGameMode_Shooter.generated.h"


class UArcInventoryComponent;
class UAbilitySystemComponent;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API ASSGameMode_Shooter : public ASSGameMode
{
	GENERATED_BODY()

public:
	ASSGameMode_Shooter(const FObjectInitializer& ObjectInitializer);


	virtual void SetPlayerDefaults(APawn* PlayerPawn) override;

protected:
	/** Override this event if you want to customize how this Game Mode gives you your startup items */
	virtual void GiveInventoryStartupItems(UArcInventoryComponent* Inventory);

private:
	void OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC, UArcInventoryComponent* Inventory);
};
