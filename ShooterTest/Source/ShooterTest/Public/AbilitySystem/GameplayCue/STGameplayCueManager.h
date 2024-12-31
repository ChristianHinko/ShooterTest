// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueManager.h"

#include "STGameplayCueManager.generated.h"

/**
 * Our custom gameplay cue manager.
 */
UCLASS()
class SHOOTERTEST_API USTGameplayCueManager : public UGameplayCueManager
{
    GENERATED_BODY()

public:

    // ~ UGameplayCueManager overrides.
    virtual void FlushPendingCues() override;
    // ~ UGameplayCueManager overrides.
};
