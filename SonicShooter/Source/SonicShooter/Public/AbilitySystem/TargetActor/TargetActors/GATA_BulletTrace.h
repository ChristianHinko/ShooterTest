// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/TargetActors/GATA_Trace.h"

#include "GATA_BulletTrace.generated.h"


class UAS_Gun;
struct FTraceSegment;


/**
 *	This struct stores infomration about bullet movement at a certain point.
 *	Will make up a TArray of FBulletSteps which represent how the bullet moves through the world.
 */
struct FBulletStep
{
	FBulletStep()
	{
		RicochetPoint = nullptr;
		TraceSegment = nullptr;
	}
	FBulletStep(FVector* InRicochetPoint, FTraceSegment* InTraceSegment)
	{
		RicochetPoint = InRicochetPoint;
		TraceSegment = InTraceSegment;
	}
	FVector* RicochetPoint;
	FTraceSegment* TraceSegment;
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
	virtual float GetInitialTraceSpeed() const;

	UPROPERTY()
		UAS_Gun* GunAttributeSet;
	/** This is injected in every fire */
	int16 FireSpecificNetSafeRandomSeed;

protected:
	// This override signifies performing a trace for a ricochetable bullet (but it also might not richochet based on how this GATA is configed). The OutHitResults are the hit results from 1 bullet ricocheting off walls and hitting player(s)
	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor) override;

	virtual void CalculateAimDirection(FVector& ViewStart, FVector& ViewDir) const override;


	virtual bool OnInitialTrace(TArray<FHitResult>& OutInitialHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams& TraceParams) override;
	virtual bool OnPenetrate(TArray<FHitResult>& HitResults, TArray<FHitResult>& OutPenetrateHitResults, const UWorld* World, const FVector& PenetrateStart, const FVector& PenetrateEnd, const FCollisionQueryParams& TraceParams) override;
	virtual bool OnRicochet(TArray<FHitResult>& HitResults, TArray<FHitResult>& OutRicoHitResults, const UWorld* World, const FVector& RicoStart, const FVector& RicoEnd, const FCollisionQueryParams& TraceParams) override;
	virtual void OnPostTraces(TArray<FHitResult>& HitResults, const UWorld* World, const FCollisionQueryParams& TraceParams) override;

	float CurrentTraceSpeed;

	/**
	 * Applies each of the Penetration Infos' Phys Mats' BulletPenetrationSpeedReduction to CurrentTraceSpeed.
	 * Outputs the point which we ran out of Trace Speed in OutStoppedAtPoint - IF we ran out (if returned true).
	 * 
	 * Returns true if we ran out of Trace Speed.
	 * If returned true, we have a valid OutStoppedAtPoint.
	 */
	bool ApplyTraceSegmentsToTraceSpeed(const TArray<FTraceSegment>& TraceSegments, FVector& OutStoppedAtPoint);

private:
	TArray<FHitResult> ThisRicochetBlockingHits;
	TArray<FBulletStep> BulletSteps;
	int32 ThisRicochetStartingIndex;
	FVector ThisRicochetTraceDir;

};
