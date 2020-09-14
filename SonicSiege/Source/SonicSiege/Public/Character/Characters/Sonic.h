// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SiegeCharacter.h"
#include "Sonic.generated.h"



/**
 * 
 */
UCLASS()
class SONICSIEGE_API ASonic : public ASiegeCharacter
{
	GENERATED_BODY()
	
public:
	ASonic(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Tick(float DeltaSeconds) override;

};
