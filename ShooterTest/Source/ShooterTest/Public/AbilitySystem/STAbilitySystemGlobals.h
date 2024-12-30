// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"

#include "STAbilitySystemGlobals.generated.h"

struct FGameplayAbilityActorInfo;
struct FGameplayEffectContext;

/**
 * @brief Game's ability system globals class.
 */
UCLASS()
class SHOOTERTEST_API USTAbilitySystemGlobals : public UAbilitySystemGlobals
{
    GENERATED_BODY()

public:

    USTAbilitySystemGlobals(const FObjectInitializer& objectInitializer);

public:

    // ~ UAbilitySystemGlobals overrides.
    virtual FGameplayAbilityActorInfo* AllocAbilityActorInfo() const override;
    virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
    // ~ UAbilitySystemGlobals overrides.
};
