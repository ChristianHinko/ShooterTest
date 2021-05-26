// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueManager.h"

#include "SSGameplayCueManager.generated.h"



/**
 * Our custom GameplayCueManager
 */
UCLASS()
class SONICSHOOTER_API USSGameplayCueManager : public UGameplayCueManager
{
	GENERATED_BODY()


	virtual bool ShouldAsyncLoadRuntimeObjectLibraries() const override;

	virtual void FlushPendingCues() override;
};
