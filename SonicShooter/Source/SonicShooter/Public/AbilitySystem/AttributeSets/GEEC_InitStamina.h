// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "GEEC_InitStamina.generated.h"



/**
 * Attribute Set default values for UAS_Stamina.
 * Children can subclass this (in BP or cpp) and fill out default values.
 * 
 * Useful for non-Attribute typed properties that exist on the Attribute Set or anywhere else.
 * Useful for any Attributes that require more complex default value calculations.
 */
UCLASS()
class SONICSHOOTER_API UGEEC_InitStamina : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEEC_InitStamina(const FObjectInitializer& ObjectInitializer);

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
