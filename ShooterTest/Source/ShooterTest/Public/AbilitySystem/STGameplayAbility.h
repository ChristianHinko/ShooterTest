// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASSGameplayAbility_Example.h"

#include "STGameplayAbility.generated.h"

/**
 * Game's base gameplay ability class.
 */
UCLASS()
class SHOOTERTEST_API USTGameplayAbility : public UASSGameplayAbility_Example
{
    GENERATED_BODY()

public:

    USTGameplayAbility(const FObjectInitializer& inObjectInitializer);
};
