// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Console\CVarChangeListenerManager.h"

#include "SSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

};
