// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "GEEC_FAMASInitialization.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGEEC_FAMASInitialization : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEEC_FAMASInitialization();


protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
