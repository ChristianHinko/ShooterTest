// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"

#include "SSAbilitySystemGlobals.generated.h"



/**
 * Our custom AbilitySystemGlobals
 */
UCLASS()
class SONICSHOOTER_API USSAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()


	USSAbilitySystemGlobals();

public:
	virtual FGameplayAbilityActorInfo* AllocAbilityActorInfo() const override;
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;

};
