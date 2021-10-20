// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayCue/ASSGameplayCueManager.h"

#include "SSGameplayCueManager.generated.h"



/**
 * Our custom GameplayCueManager
 */
UCLASS()
class SONICSHOOTER_API USSGameplayCueManager : public UASSGameplayCueManager
{
	GENERATED_BODY()

public:
	virtual void FlushPendingCues() override;

};
