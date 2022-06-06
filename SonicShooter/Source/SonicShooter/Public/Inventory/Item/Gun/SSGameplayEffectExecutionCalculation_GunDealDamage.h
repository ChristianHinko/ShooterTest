// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "SSGameplayEffectExecutionCalculation_GunDealDamage.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSGameplayEffectExecutionCalculation_GunDealDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	USSGameplayEffectExecutionCalculation_GunDealDamage();


protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
