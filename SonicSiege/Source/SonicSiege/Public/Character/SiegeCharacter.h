// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AbilitySystemCharacter.h"
#include "SiegeCharacter.generated.h"



/**
 *
 */
UCLASS()
class SONICSIEGE_API ASiegeCharacter : public AAbilitySystemCharacter
{
	GENERATED_BODY()

public:
	ASiegeCharacter(const FObjectInitializer& ObjectInitializer);

};
