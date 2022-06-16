// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "SSGameplayEffectExecutionCalculation_InitAmmo.generated.h"



/**
 * Attribute Set default values for USSAttributeSet_Ammo.
 * 
 * Children can subclass this (in BP or CPP) and fill out default values.
 * Initialization Gameplay Effects should use these for initializing Attributes values.
 * - Useful for initializing Attributes that require complex default value calculations.
 * - Useful for initializing non-Attribute properties that exist outside of the Attribute Set.
 */
UCLASS()
class SONICSHOOTER_API USSGameplayEffectExecutionCalculation_InitAmmo : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	USSGameplayEffectExecutionCalculation_InitAmmo(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;


	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float MaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float MaxClipAmmo;

};
