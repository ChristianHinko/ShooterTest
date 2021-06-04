// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BFL_MathHelpers.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UBFL_MathHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "MathHelpers|VectorMath")
		static bool PointLinesOnSegment(const FVector& Start, const FVector& End, const FVector& Point);

};
