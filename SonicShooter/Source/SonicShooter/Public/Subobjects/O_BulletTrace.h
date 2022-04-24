// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "O_BulletTrace.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UO_BulletTrace : public UObject
{
	GENERATED_BODY()
	
public:
	UO_BulletTrace(const FObjectInitializer& ObjectInitializer);


	/** Max times to penetrate through blocking hits (assign a value of -1 for an unbound number of penetrations) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Scan")
		int32 MaxPenetrations;
	/** Max times to ricochet (assign a value of -1 for an unbound number of ricochets) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Scan")
		int32 MaxRicochets;

	/**
	 * Any Physical Surfaces added to this array will ricochet any trace that hits them.
	 * You don't have to use these, you can override ShouldRicochetOffOf() for advanced ricochet logic.
	 */
	TArray<EPhysicalSurface> RicochetableSurfaces;

	/** Used for doing line traces in PerformScan() */
	void ScanWithLineTraces(TArray<FHitResult>& OutHitResults, const FVector& ScanStart, const FVector& ScanDirection, const float MaxRange, const UWorld* World, FCollisionQueryParams CollisionQueryParams);

protected:
	/**
	 * Determines whether we should ricochet off of the given Hit or not.
	 * This can be overriden for custom ricochet determination.
	 */
	virtual bool ShouldRicochetOffOf(const FHitResult& Hit) const;
	/**
	 * Calculates the direction to ricochet from the given hit.
	 * This can be overriden for custom ricochet directions.
	 */
	virtual FVector CalculateRicochetDirection(const FHitResult& FromHit) const;


	// Events for ScanWithLineTraces() - return false in these to discontinue the rest of the traces
	virtual bool ShouldContinueTracingAfterFirstTrace(TArray<FHitResult>& FirstTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams);
	virtual bool ShouldContinueTracingAfterPenetrationTrace(TArray<FHitResult>& ScanHitResults, TArray<FHitResult>& PenetrationTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams);
	virtual bool ShouldContinueTracingAfterRicochetHit(TArray<FHitResult>& ScanHitResults, TArray<FHitResult>& RicochetTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams);
	virtual void OnFinishedScanWithLineTraces(TArray<FHitResult>& ScanHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams);


	/** Moves our traces' start points in the trace direction by a small amount to ensure we don't get stuck hitting the same object over and over again. This allows us to avoid ignoring the component so that we can hit the same component's geometry again */
	static const float TraceStartWallAvoidancePadding;

};
