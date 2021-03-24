// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSEffectExecutionCalculation.h"
#include "GEEC_GunDealDamage.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGEEC_GunDealDamage : public USSEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEEC_GunDealDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:

};