// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/ASSActorComponent_AbilitySystemComponentExample.h"

#include "STAbilitySystemComponent_Shooter.generated.h"

/**
 * Shooter-specific ASC.
 */
UCLASS()
class SHOOTERTEST_API USTAbilitySystemComponent_Shooter : public UASSActorComponent_AbilitySystemComponentExample
{
    GENERATED_BODY()

public:

    USTAbilitySystemComponent_Shooter(const FObjectInitializer& inObjectInitializer);
};
