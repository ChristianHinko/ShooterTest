// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/TargetActors/GATA_Trace.h"
#include "Utilities/BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"

#include "GATA_BulletTrace.generated.h"


class UAS_Gun;
struct FTraceSegment;



struct FTracePoint
{
	FTracePoint()
	{
		Point = FVector::ZeroVector;
		PhysMaterial = nullptr;
	}
	FTracePoint(const FVector& InPoint, UPhysicalMaterial* InPhysMaterial)
	{
		Point = InPoint;
		PhysMaterial = InPhysMaterial;
	}


	FVector Point;
	UPhysicalMaterial* PhysMaterial;
};

/**
 *	This struct stores infomration about bullet movement at a certain point.
 *	Will make up a TArray of FBulletSteps which represent how the bullet moves through the world.
 */
struct FBulletStep
{
	// Copy ctor for BulletSteps.Append()
	FBulletStep(const FBulletStep& Other)
	{
		// Deep copy our pointers
		TraceSegment = Other.TraceSegment.IsValid() ? MakeUnique<FTraceSegment>(*(Other.TraceSegment.Get())) : nullptr;
		RicochetPoint = Other.RicochetPoint.IsValid() ? MakeUnique<FTracePoint>(*(Other.RicochetPoint.Get())) : nullptr;

		BulletSpeedToTakeAway = Other.BulletSpeedToTakeAway;
	}

	FBulletStep(const FTraceSegment& InTraceSegment)
	{
		TraceSegment = MakeUnique<FTraceSegment>(InTraceSegment);
		RicochetPoint = nullptr;

		BulletSpeedToTakeAway = 0;


		// Evaluate BulletSpeedToTakeAway:

		// For each Phys Mat in this Segment
		for (const UPhysicalMaterial* PhysMat : InTraceSegment.GetPhysMaterials())
		{
			// If this is a ShooterPhysicalMaterial, it has Bullet Speed loss data
			if (const UShooterPhysicalMaterial* ShooterPhysMat = Cast<UShooterPhysicalMaterial>(PhysMat))
			{
				const float SpeedLossPerCentimeter = (ShooterPhysMat->BulletPenetrationSpeedReduction / 100);
				const float SpeedToTakeAway = (InTraceSegment.GetSegmentDistance() * SpeedLossPerCentimeter);

				BulletSpeedToTakeAway += SpeedToTakeAway;
			}
		}
	}
	FBulletStep(const FTracePoint& InRicochetPoint)
	{
		TraceSegment = nullptr;
		RicochetPoint = MakeUnique<FTracePoint>(InRicochetPoint);

		BulletSpeedToTakeAway = 0;


		// Evaluate BulletSpeedToTakeAway:

		// If this is a ShooterPhysicalMaterial, it has Bullet Speed loss data
		if (const UShooterPhysicalMaterial* ShooterPhysMat = Cast<UShooterPhysicalMaterial>(InRicochetPoint.PhysMaterial))
		{
			BulletSpeedToTakeAway = ShooterPhysMat->BulletRicochetSpeedReduction;
		}
	}


	FTraceSegment* GetTraceSegment() const
	{
		return TraceSegment.Get();
	}
	FTracePoint* GetRicochetPoint() const
	{
		return RicochetPoint.Get();
	}

	float GetBulletSpeedToTakeAway() const
	{
		return BulletSpeedToTakeAway;
	}


private:
	TUniquePtr<FTraceSegment> TraceSegment;
	TUniquePtr<FTracePoint> RicochetPoint;

	float BulletSpeedToTakeAway;

};


/**
 * 
 */
UCLASS()
class SONICSHOOTER_API AGATA_BulletTrace : public AGATA_Trace
{
	GENERATED_BODY()

public:
	AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer);


	virtual void ConfirmTargetingAndContinue() override;


	virtual float GetMaxRange() const override;
	virtual int32 GetNumberOfTraces() const override;
	virtual int32 GetRicochets() const override;
	virtual int32 GetPenetrations() const override;

	float GetInitialBulletSpeed() const;
	float GetBulletSpeedFalloff() const;


	UPROPERTY()
		UAS_Gun* GunAttributeSet;
	/** This is injected in every fire */
	int16 FireSpecificNetSafeRandomSeed;

protected:
	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor) override;
	virtual void CalculateAimDirection(FVector& ViewStart, FVector& ViewDir) const override;


	virtual bool OnInitialTrace(TArray<FHitResult>& OutInitialHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams& TraceParams) override;
	virtual bool OnPenetrate(TArray<FHitResult>& HitResults, TArray<FHitResult>& OutPenetrateHitResults, const UWorld* World, const FVector& PenetrateStart, const FVector& PenetrateEnd, const FCollisionQueryParams& TraceParams) override;
	virtual bool OnRicochet(TArray<FHitResult>& HitResults, TArray<FHitResult>& OutRicoHitResults, const UWorld* World, const FVector& RicoStart, const FVector& RicoEnd, const FCollisionQueryParams& TraceParams) override;
	virtual void OnPostTraces(TArray<FHitResult>& HitResults, const UWorld* World, const FCollisionQueryParams& TraceParams) override;

	/**
	 * Applies each of the Penetration Infos' Phys Mats' BulletPenetrationSpeedReduction to CurrentBulletSpeed.
	 * Outputs the point which we ran out of Bullet Speed in OutStoppedAtPoint - IF we ran out (if returned true).
	 * 
	 * Returns true if we ran out of Bullet Speed.
	 * If returned true, we have a valid OutStoppedAtPoint.
	 * 
	 * TODO: get rid of OutStoppedInSegment
	 */
	bool ApplyBulletStepsToBulletSpeed(const TArray<FBulletStep>& BulletStepsToApply, FVector& OutStoppedAtPoint, bool& OutStoppedInSegment);


	float CurrentBulletSpeed;
	float GetBulletSpeedAtPoint(const FVector& Point, int32 bulletNumber);
	/**
	 * @brief: This is a nerf that is multiplied against our bullet's damage value to simulate a bullet slowing down as it travels through the air.
	 * @param bulletSpeedFalloffValue: Multiplier applied against the bullet's speed every 1000cm (32ft) or 10 blocks of our Proto material.
	 * @param totalDistanceBulletTraveled: Required for our calculation.
	 * @return: The multiplier to multiply against our bullet's damage value.
	*/
	float GetBulletSpeedFalloffNerf(const float& bulletSpeedFalloffValue, const float& totalDistanceBulletTraveled);

private:
	TArray<FHitResult> ThisRicochetBlockingHits;
	TArray<TArray<FBulletStep>> BulletSteps;
	int32 ThisRicochetStartingIndex;
	FVector ThisRicochetTraceDir;

};
