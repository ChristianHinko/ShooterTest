// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "STGameplayEffectExecutionCalculation_GunDealDamage.generated.h"



/**
 *
 */
UCLASS()
class SHOOTERTEST_API USTGameplayEffectExecutionCalculation_GunDealDamage : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()

public:
    USTGameplayEffectExecutionCalculation_GunDealDamage();


protected:
    virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
