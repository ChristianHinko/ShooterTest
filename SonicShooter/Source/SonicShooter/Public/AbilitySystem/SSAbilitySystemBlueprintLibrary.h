// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/TargetActor/GATDF_MultiFilter.h"
#include "SSAbilitySystemBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSAbilitySystemBlueprintLibrary : public UAbilitySystemBlueprintLibrary
{
	GENERATED_BODY()
	
public:
	/** Create a handle for filtering target data, filling out all fields */
	UFUNCTION(BlueprintPure, Category = "Filter")
		static FGATDF_MultiFilterHandle MakeMultiFilterHandle(FGATDF_MultiFilter MultiFilter/*, AActor* FilterActor*/);
};
