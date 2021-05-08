// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "SSGameplayAbilityTargetTypes.generated.h"



/**
 * Our base Target Data struct
 */
USTRUCT()
struct SONICSHOOTER_API FSSGameplayAbilityTargetData : public FGameplayAbilityTargetData
{
	GENERATED_BODY()

		
	FSSGameplayAbilityTargetData();

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FSSGameplayAbilityTargetData::StaticStruct();
	}
};
