// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PhysicalMaterials\PhysicalMaterial.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicalMaterial/ShooterPhysicalMaterial.h"

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
	FPenetrationInfo(const FVector& InEntrancePoint, const FVector& InExitPoint, const TArray<UPhysicalMaterial*>& InPenetratedPhysMaterials)
		: FPenetrationInfo()
	{
		SetEntranceAndExitPoints(InEntrancePoint, InExitPoint);
		PenetratedPhysMaterials = InPenetratedPhysMaterials;
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


	FString PenetratedActorName;
	FString PenetratedComponentName;
	FString PenetratedBoneName;



	const TArray<UPhysicalMaterial*>& GetPenetratedPhysMaterials() const { return PenetratedPhysMaterials; }
	void SetPenetratedPhysMaterials(const TArray<UPhysicalMaterial*>& InPenetratedPhysMaterials)
	{
		PenetratedPhysMaterials = InPenetratedPhysMaterials;


		// Reevaluate TraceSpeedToTakeAway:

		TraceSpeedToTakeAway = 0.f;

		// For each Phys Mat in this Penetration
		for (const UPhysicalMaterial* PhysMat : PenetratedPhysMaterials)
		{
			// If this is a ShooterPhysicalMaterial, it has Trace Speed loss data
			if (const UShooterPhysicalMaterial* ShooterPhysMat = Cast<UShooterPhysicalMaterial>(PhysMat))
			{
				const float SpeedLossPerCentimeter = (ShooterPhysMat->BulletPenetrationSpeedReduction / 100);
				const float SpeedToTakeAway = (PenetrationDistance * SpeedLossPerCentimeter);

				TraceSpeedToTakeAway += SpeedToTakeAway;
			}
		}
	}

	float GetTraceSpeedToTakeAway() const { return TraceSpeedToTakeAway; }

	FVector GetEntrancePoint() const { return EntrancePoint; }
	FVector GetExitPoint() const { return ExitPoint; }

	float GetPenetrationDistance() const { return PenetrationDistance; }
	FVector GetPenetrationDir() const { return PenetrationDir; }

	void SetEntranceAndExitPoints(const FVector& InEntrancePoint, const FVector& InExitPoint)
	{
		// Set points
		EntrancePoint = InEntrancePoint;
		ExitPoint = InExitPoint;

		// Reevaluate calculations
		PenetrationDistance = FVector::Distance(EntrancePoint, ExitPoint);
		PenetrationDir = UKismetMathLibrary::GetDirectionUnitVector(EntrancePoint, ExitPoint);
	}

private:
	/**
	 * This is the stack of phys materials that this penetration is penetrating. Top of the stack is the most inner (most recent) phys material
	 */
	TArray<UPhysicalMaterial*> PenetratedPhysMaterials;
	float TraceSpeedToTakeAway;

	FVector EntrancePoint;
	FVector ExitPoint;

	float PenetrationDistance;
	FVector PenetrationDir;

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
	 * BuildPenetrationInfos Important notes:
	 * This gathers data on the geometry level. If there are faces with normals pointing at an incomming trace, it will hit. This can get really (pointlessly) expensive if a model has lots of faces not visible and inside the mesh
	 * since it will penetrate those as well. I think in most cases it's pointless to do penetrations on those inner geometry parts, but we are just doing that for now. We could make an implementation that runs on the section level
	 * instead of the geometry level (using HitResult.GetComponent()->GetMaterialFromCollisionFaceIndex(HitResult.FaceIndex); ). We were just kinda too lazy to do this. We did this in a pervious commit but changed the system.
	 * This is mainly a system for used for when we are using complex collision. If any hit results that are passed in is a Hit Result from a component's collider that uses
	 * CTF_UseSimpleAsComplex, things can get inacurrate, but only if that collider's mesh has multible material slots. This is because once we hit any simple collider,we ignore the rest of it so we don't get stuck
	 * inside it (distance being 0 every time).	Another note is that skeletal mesh bones are all a part of 1 component (skeletal mesh component), and each of the bones use simple collision.
	 * This means that if you hit a skeletal mesh bone, it won't just only ignore that specific bone. It will ignore all of the bones in that skeletal mesh component (since it just ignores the skeletal mesh component).
	 * So when using this against skeletal meshes, only one bone will be hit.
	 * Another thing is if the first fwd hit result it already inside some geometry, then the function won't be aware of that and the stack of physical materials won't be fully accurate.
	*/
	static void BuildPenetrationInfos(TArray<FPenetrationInfo>& OutPenetrationInfos, const TArray<FHitResult>& FwdBlockingHits, const UWorld* World, const FCollisionQueryParams& TraceParams, const TEnumAsByte<ECollisionChannel> TraceChannel);
	static void BuildPenetrationInfos(TArray<FPenetrationInfo>& OutPenetrationInfos, const TArray<FHitResult>& FwdBlockingHits, const FVector& FwdEndLocation, const UWorld* World, const FCollisionQueryParams& TraceParams, const TEnumAsByte<ECollisionChannel> TraceChannel);
	
	
	/**
	 * 
	 */
	static void LineTracePenetrateBetweenPoints(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const ECollisionChannel TraceChannel, const FCollisionQueryParams& Params);

};
