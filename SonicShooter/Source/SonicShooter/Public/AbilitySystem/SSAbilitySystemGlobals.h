// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAbilitySystemGlobals.h"

#include "SSAbilitySystemGlobals.generated.h"



/**
 * Our custom AbilitySystemGlobals
 */
UCLASS()
class SONICSHOOTER_API USSAbilitySystemGlobals : public UASSAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	USSAbilitySystemGlobals(const FObjectInitializer& ObjectInitializer);


	virtual FGameplayAbilityActorInfo* AllocAbilityActorInfo() const override;
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;

};
