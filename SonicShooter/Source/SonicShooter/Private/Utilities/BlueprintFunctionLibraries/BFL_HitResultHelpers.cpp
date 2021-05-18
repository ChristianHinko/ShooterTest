// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/BlueprintFunctionLibraries/BFL_HitResultHelpers.h"

#include "Utilities/LogCategories.h"

UMaterialInterface* UBFL_HitResultHelpers::GetHitMaterial(const FHitResult& InHitResult)
{
	UMaterialInterface* RetVal = nullptr;
	if (InHitResult.FaceIndex == -1)
	{
		UE_LOG(LogBlueprintFunctionLibrary, Error, TEXT("%s() failed because InHitResult.FaceIndex was -1. Make sure FCollisionQueryParams::bTraceComplex and FCollisionQueryParams::bReturnFaceIndex are set to true"), *FString(__FUNCTION__));
		return RetVal;
	}


	const UPrimitiveComponent* HitComponent = InHitResult.GetComponent();
	if (IsValid(HitComponent))
	{
		int32 sectionIndex;
		RetVal = HitComponent->GetMaterialFromCollisionFaceIndex(InHitResult.FaceIndex, sectionIndex);
	}


	return RetVal;
}

void UBFL_HitResultHelpers::GetSectionLevelHitInfo(const FHitResult& InHitResult, UPrimitiveComponent*& OutHitPrimitiveComponent, int32& outHitSectionIndex)
{
	OutHitPrimitiveComponent = nullptr;
	outHitSectionIndex = -1;


	if (InHitResult.FaceIndex == -1)
	{
		UE_LOG(LogBlueprintFunctionLibrary, Error, TEXT("%s() failed because InHitResult.FaceIndex was -1. Make sure FCollisionQueryParams::bTraceComplex and FCollisionQueryParams::bReturnFaceIndex are set to true"), *FString(__FUNCTION__));
		return;
	}
	OutHitPrimitiveComponent = InHitResult.GetComponent();
	if (!IsValid(OutHitPrimitiveComponent))
	{
		UE_LOG(LogBlueprintFunctionLibrary, Error, TEXT("%s() failed because InHitResult.HitComponent was NULL. We expected something of type UPrimitiveComponent to be hit, but doesn't look like any primitive component was hit. Either that or we were provided with a bad pointer somehow (unlikely)."), *FString(__FUNCTION__));
		return;
	}



	OutHitPrimitiveComponent->GetMaterialFromCollisionFaceIndex(InHitResult.FaceIndex, outHitSectionIndex);
}
