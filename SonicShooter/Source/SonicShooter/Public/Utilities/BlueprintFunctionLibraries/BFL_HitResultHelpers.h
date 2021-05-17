// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BFL_HitResultHelpers.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UBFL_HitResultHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Returns the MaterialIndex given the material's section index */
	UFUNCTION(BlueprintPure, Category = "HitResultHelpers")
		static UMaterialInterface* GetHitMaterial(const FHitResult& InHitResult);
};
