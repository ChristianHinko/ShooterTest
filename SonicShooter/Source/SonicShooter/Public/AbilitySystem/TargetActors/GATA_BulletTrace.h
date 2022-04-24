// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetActors/GATA_Trace.h"
#include "BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"
#include "PhysicalMaterial/PM_Shooter.h"

#include "GATA_BulletTrace.generated.h"



/**
 * 
 */
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


struct FTraceSegment;

/**
 * This struct stores infomration about bullet movement at a certain point.
 * Will make up a TArray of FBulletSteps which represent how the bullet moves through the world.
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
		for (const UPhysicalMaterial* PhysMat : InTraceSegment.PhysMaterials)
		{
			// If this is a PM_Shooter, it has Bullet Speed loss data
			const UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(PhysMat);
			if (IsValid(ShooterPhysMat))
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

		// If this is a PM_Shooter, it has Bullet Speed loss data
		const UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(InRicochetPoint.PhysMaterial);
		if (IsValid(ShooterPhysMat))
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


class UO_BulletTrace;

/**
 * Scan class for Bullets.
 * 
 * Key notes:
 * - Implements the idea of Bullet Speed which can stop the tracing at any point. 
 * - Is tightly coupled with PM_Shooter to determine behavior. 
 * - Gives CalculateAimDirection() some random bullet spread. 
 * - Ditches the RicochetableSurfaces array and ricochets based on what ShouldRicochetOffOf()'s UPM_Shooter says.
 */
UCLASS()
class SONICSHOOTER_API AGATA_BulletTrace : public AGATA_Trace
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		UO_BulletTrace* BulletTraceSubobject;

public:
	AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer);


	virtual void ConfirmTargetingAndContinue() override;

	/** Injected */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float InitialBulletSpeed;

	/** Injected */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float BulletSpeedFalloff;

	/** Injected */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float CurrentBulletSpread;

	/** This is injected in every fire */
	UPROPERTY(/*BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet"*/)
		int16 FireSpecificNetSafeRandomSeed;

protected:
	virtual void PerformScan(TArray<FHitResult>& OutHitResults) override;
	virtual void CalculateAimDirection(FVector& OutAimStart, FVector& OutAimDir) const override;
	virtual bool ShouldRicochetOffOf(const FHitResult& Hit) const override;


	virtual void OnPrePerformScans(TArray<TArray<FHitResult>>& OutScansResults) override;
	
	virtual bool ShouldContinueTracingAfterFirstTrace(TArray<FHitResult>& FirstTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams) override;
	virtual bool ShouldContinueTracingAfterPenetrationTrace(TArray<FHitResult>& ScanHitResults, TArray<FHitResult>& PenetrationTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams) override;
	virtual bool ShouldContinueTracingAfterRicochetHit(TArray<FHitResult>& ScanHitResults, TArray<FHitResult>& RicochetTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams) override;
	virtual void OnFinishedScanWithLineTraces(TArray<FHitResult>& ScanHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams) override;

	/**
	 * Applies each of the Penetration Infos' Phys Mats' BulletPenetrationSpeedReduction to CurrentBulletSpeed.
	 * Outputs the point which we ran out of Bullet Speed in OutStoppedAtPoint - IF we ran out (if returned true).
	 * 
	 * Returns true if we ran out of Bullet Speed.
	 * If returned true, we have a valid OutStoppedAtPoint.
	 * 
	 * TODO: get rid of outStoppedInSegment
	 */
	bool ApplyBulletStepsToBulletSpeed(const TArray<FBulletStep>& BulletStepsToApply, FVector& OutStoppedAtPoint, bool& outStoppedInSegment);


	float CurrentBulletSpeed; // this is only used for optimization to see if we can stop tracing due to loss of speed. it is NOT used for damage calculation. there is separate and nearly duplicate logic for that which is really bad.
	
	/**
	 * Used to calculate FActorHitInfo::BulletSpeedAtImpact for calculating damage.
	 */
	float GetBulletSpeedAtPoint(const FVector& Point, const int32 ScanIndex);


	void NerfCurrentBulletSpeedByDistanceTraveled(const TArray<FHitResult>& HitResults);
	/**
	 * @brief: This is a nerf that is multiplied against our bullet's damage value to simulate a bullet slowing down as it travels through the air.
	 * @param BulletSpeedFalloffValue: Multiplier applied against the bullet's speed every 1000cm (32ft) or 10 blocks of our Proto material.
	 * @param TotalDistanceBulletTraveled: Required for our calculation.
	 * @return: The multiplier to multiply against our bullet's damage value.
	*/
	float GetBulletSpeedFalloffNerf(const float BulletSpeedFalloffValue, const float TotalDistanceBulletTraveled);

private:
	TArray<FHitResult> CurrentTracingDirectionBlockingHits; // all of the blocking hits for this current tracing direction
	TArray<TArray<FBulletStep>> BulletSteps; // NOTE: the lifetime of valid data for BulletSteps starts within PerformScans() and then persists after the function. Then, next time PerformScans() is called, new BulletSteps are filled out and then, again, persist after the function.
	int32 CurrentTracingDirectionStartIndex; // the index of this current tracing direction's first Hit Result

};
