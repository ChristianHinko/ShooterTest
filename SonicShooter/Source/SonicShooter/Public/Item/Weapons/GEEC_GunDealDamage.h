// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSEffectExecutionCalculation.h"
#include "Runtime\GameplayTags\Classes\GameplayTagContainer.h"

#include "GEEC_GunDealDamage.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGEEC_GunDealDamage : public UASSEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEEC_GunDealDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:

};
