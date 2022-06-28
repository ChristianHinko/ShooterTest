// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/GSGameInstance.h"

#include "SSGameInstance.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSGameInstance : public UGSGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

};
