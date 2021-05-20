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
	/** Returns the material that was hit from the trace (requires passed in Hit Result to have a face index) */
	UFUNCTION(BlueprintPure, Category = "HitResultHelpers")
		static UMaterialInterface* GetHitMaterial(const FHitResult& InHitResult);

	/** Returns the section index of the Primitive Component that was hit from the trace */
	UFUNCTION(BlueprintPure, Category = "HitResultHelpers|HitInfo")
		static void GetSectionLevelHitInfo(const FHitResult& InHitResult, UPrimitiveComponent*& OutHitPrimitiveComponent, int32& outHitSectionIndex);

};
