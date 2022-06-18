// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/SSGameMode.h"

#include "SSGameMode_Shooter.generated.h"


class UAIEInventoryComponent_Active;
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

private:
	void OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC, UAIEInventoryComponent_Active* const AIEInventoryComponentActive);
};
