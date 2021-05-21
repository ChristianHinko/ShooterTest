// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PhysicalMaterials\PhysicalMaterial.h"

#include "BFL_CollisionQueryHelpers.generated.h"



/**
 *
 */
struct FPenetrationInfo
{
	FPenetrationInfo()
	{
		EntrancePoint = FVector::ZeroVector;
		ExitPoint = FVector::ZeroVector;
		PenetrationDistance = -1;
	}
	FPenetrationInfo(float InPenetrationDistance, const FVector& inEntrancePoint, const FVector& inExitPoint, TArray<UPhysicalMaterial*> inPenetratedPhysMaterials, const FString& inPenetratedActorName, const FString& inPenetratedComponentName, const FString& inPenetratedBoneName)
	{
		PenetratedPhysMaterials = inPenetratedPhysMaterials;

		EntrancePoint = inEntrancePoint;
		ExitPoint = inExitPoint;
		PenetrationDistance = InPenetrationDistance;

		PenetratedActorName = inPenetratedActorName;
		PenetratedComponentName = inPenetratedComponentName;
		PenetratedBoneName = inPenetratedBoneName;
	}

	const FString GetDebugString() const
	{
		FString PenetratedPhysMats;
		for (UPhysicalMaterial* physMat : PenetratedPhysMaterials)
		{
			PenetratedPhysMats += physMat->GetName() + ", ";
		}
		return "PenetratedActor = " + PenetratedActorName + "    PenetratedComponent = " + PenetratedComponentName + "    PenetratedBone = " + PenetratedBoneName + "    PenetratedPhysMaterials = " + PenetratedPhysMats + "    penetration distance: " + FString::SanitizeFloat(PenetrationDistance);
	}

	TArray<UPhysicalMaterial*> PenetratedPhysMaterials;

	FVector EntrancePoint;
	FVector ExitPoint;
	float PenetrationDistance;

	FString PenetratedActorName;
	FString PenetratedComponentName;
	FString PenetratedBoneName;
};

/**
 *
 */
struct FPenetrationHitResult
{
	FPenetrationHitResult()
	{
		bIsEntrance = true;
	}
	FPenetrationHitResult(const FHitResult& inHitResult, bool inIsEntrance)
	{
		HitResult = inHitResult;
		bIsEntrance = inIsEntrance;
	}

	FHitResult HitResult;
	uint8 bIsEntrance : 1;
};

/**
 * A collection of our custom collision queries
 */
UCLASS()
class SONICSHOOTER_API UBFL_CollisionQueryHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static void BuildPenetrationInfos(TArray<FPenetrationInfo>& OutPenetrationInfos, const TArray<FHitResult>& FwdBlockingHits, const FVector& FwdEndLocation, const UWorld* World, const FCollisionQueryParams& TraceParams, const TEnumAsByte<ECollisionChannel> TraceChannel);

};