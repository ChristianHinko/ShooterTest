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
			PenetratedPhysMats += (IsValid(physMat) ? physMat->GetName() : "NULL") + ", ";
		}
		return "PenetratedActor = " + PenetratedActorName + "    PenetratedComponent = " + PenetratedComponentName + "    PenetratedBone = " + PenetratedBoneName + "    PenetratedPhysMaterials = " + PenetratedPhysMats + "    penetration distance: " + FString::SanitizeFloat(PenetrationDistance);
	}

	/**
	 * This is the stack of phys materials that this penetration is penetrating. Top of the stack is the most inner (most recent) phys material
	*/
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
	/**
	 * BuildPenetrationInfos Important note: This is mainly a system for used for when we are using complex collision. If any hit results that are passed in is a Hit Result from a component's collider that uses
	 * CTF_UseSimpleAsComplex, things can get inacurrate,	 * but only if that collider's mesh has multible material slots. This is because once we hit any simple collider,we ignore the rest of it so we don't get stuck
	 * inside it (distance being 0 every time).	 * Another note is that skeletal mesh bones are all a part of 1 component (skeletal mesh component), and each of the bones use simple collision.
	 * This means that if you hit a skeletal mesh bone, it won't just only ignore that specific bone. It will ignore all of the bones in that skeletal mesh component (since it just ignores the skeletal mesh component).
	 * So when using this against skeletal meshes, only one bone will be hit.
	*/
	static void BuildPenetrationInfos(TArray<FPenetrationInfo>& OutPenetrationInfos, const TArray<FHitResult>& FwdBlockingHits, const UWorld* World, const FCollisionQueryParams& TraceParams, const TEnumAsByte<ECollisionChannel> TraceChannel);
	static void BuildPenetrationInfos(TArray<FPenetrationInfo>& OutPenetrationInfos, const TArray<FHitResult>& FwdBlockingHits, const FVector& FwdEndLocation, const UWorld* World, const FCollisionQueryParams& TraceParams, const TEnumAsByte<ECollisionChannel> TraceChannel);

};
