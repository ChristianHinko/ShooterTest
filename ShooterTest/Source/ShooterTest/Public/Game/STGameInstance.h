// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/GSGameInstance.h"

#include "STGameInstance.generated.h"



/**
 * Game's base GameInstance class
 */
UCLASS()
class SHOOTERTEST_API USTGameInstance : public UGSGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

};
