// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "SSGameplayEffectExecutionCalculation_InitStamina.generated.h"



/**
 * Attribute Set default values for USSAttributeSet_Stamina.
 * 
 * Children can subclass this (in BP or CPP) and fill out default values.
 * Initialization Gameplay Effects should use these for initializing Attributes values.
 * - Useful for initializing Attributes that require complex default value calculations.
 * - Useful for initializing non-Attribute properties that exist outside of the Attribute Set.
 */
UCLASS()
class SONICSHOOTER_API USSGameplayEffectExecutionCalculation_InitStamina : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	USSGameplayEffectExecutionCalculation_InitStamina(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;


	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float MaxStamina;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float StaminaDrain;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float StaminaGain;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float StaminaRegenPause;

};
