// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/ASSEngineSubsystem.h"

#include "STEngineSubsystem.generated.h"



/**
 * 
 */
UCLASS()
class SHOOTERTEST_API USTEngineSubsystem : public UASSEngineSubsystem
{
	GENERATED_BODY()

public:
	//BEGIN USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//END USubsystem Interface
};
