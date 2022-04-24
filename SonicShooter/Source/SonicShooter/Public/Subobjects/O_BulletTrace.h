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
	 * Performs traces from a given ScanStart into a given ScanDirection with ricochets
	 * Penetrates through blocking hits.
	 */
	void ScanWithLineTraces(TArray<FHitResult>& OutHitResults, const FVector& InScanStart, const FVector& InScanDirection, const float InMaxRange, const UWorld* InWorld, const ECollisionChannel InTraceChannel, const FCollisionQueryParams& InCollisionQueryParams);

protected:
	/** Moves our traces' start points in the trace direction by a small amount to ensure we don't get stuck hitting the same object over and over again. This allows us to avoid ignoring the component so that we can hit the same component's geometry again */
	static const float TraceStartWallAvoidancePadding;

};
