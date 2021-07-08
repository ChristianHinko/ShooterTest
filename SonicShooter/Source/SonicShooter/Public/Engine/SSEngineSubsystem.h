// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/ASSEngineSubsystem.h"

#include "SSEngineSubsystem.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSEngineSubsystem : public UASSEngineSubsystem
{
	GENERATED_BODY()

public:
	//BEGIN USubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//END USubsystem Interface
};
