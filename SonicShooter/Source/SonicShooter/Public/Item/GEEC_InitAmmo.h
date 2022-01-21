// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "GEEC_InitAmmo.generated.h"



/**
 * Attribute Set default values for UAS_Ammo.
 * Children can subclass this (in BP or cpp) and fill out default values
 */
UCLASS()
class SONICSHOOTER_API UGEEC_AmmoInitialization : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEEC_AmmoInitialization();

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;


	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float MaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float MaxClipAmmo;

};
