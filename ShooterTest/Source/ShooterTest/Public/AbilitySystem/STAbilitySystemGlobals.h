// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAbilitySystemGlobals.h"

#include "STAbilitySystemGlobals.generated.h"



/**
 * Game's base AbilitySystemGlobals
 */
UCLASS()
class SHOOTERTEST_API USTAbilitySystemGlobals : public UASSAbilitySystemGlobals
{
    GENERATED_BODY()

public:
    USTAbilitySystemGlobals(const FObjectInitializer& ObjectInitializer);


    virtual FGameplayAbilityActorInfo* AllocAbilityActorInfo() const override;
    virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
