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
	/**
	 * @brief: Given a segment and a point, does that point lie on that segment?
	*/
	UFUNCTION(BlueprintPure, Category = "MathHelpers|VectorMath")
		static bool PointLiesOnSegment(const FVector& Start, const FVector& End, const FVector& Point);
};
