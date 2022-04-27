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


	// Injected
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float InitialBulletSpeed;

	// Injected
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float BulletSpeedFalloff;


	/**
	 * Performs traces from a given ScanStart into a given ScanDirection with ricochets
	 * Penetrates through blocking hits.
	 * 
	 * @param  InMaxPenetrations        Max times to penetrate through blocking hits (-1 is unlimited)
	 * @param  InMaxRicochets           Max times to ricochet off of owner defined ricochetable hits (defined through TFunction parameter) (-1 is unlimited)
	 * @param  ShouldRicochetOffOf      TFunction where caller tells us if a hit result causes a ricochet
	 */
	void ScanWithLineTraces(TArray<FHitResult>& OutHitResults, FVector ScanStart, FVector ScanDirection, float DistanceToTravel, const int32 InMaxPenetrations, const int32 InMaxRicochets, const UWorld* InWorld, const ECollisionChannel InTraceChannel, const FCollisionQueryParams& InCollisionQueryParams = FCollisionQueryParams::DefaultQueryParam, const TFunctionRef<bool(const FHitResult&)>& ShouldRicochetOffOf = [](const FHitResult&) { return false; });

protected:
	/** Moves our traces' start points in the trace direction by a small amount to ensure we don't get stuck hitting the same object over and over again. This allows us to avoid ignoring the component so that we can hit the same component's geometry again */
	static const float TraceStartWallAvoidancePadding;

	static bool IsEntranceHitResult(const FVector& ForwardDir, const FHitResult& Hit)
	{
		FVector HitDir = (Hit.TraceEnd - Hit.TraceStart).GetSafeNormal();
		return HitDir.Equals(ForwardDir);
	}
};
