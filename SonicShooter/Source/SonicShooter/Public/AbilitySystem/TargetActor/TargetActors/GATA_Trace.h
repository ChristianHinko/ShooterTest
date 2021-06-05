// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/SSGameplayAbilityTargetActor.h"

#include "GATA_Trace.generated.h"



/**
 * 
 */
UCLASS(Abstract, notplaceable)
class SONICSHOOTER_API AGATA_Trace : public ASSGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AGATA_Trace(const FObjectInitializer& ObjectInitializer);


	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;

	/** Traces as normal, but does ricochet and penetration traces aswell if needed */
	void LineTraceMulti(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams& Params, const bool inDebug);
	/** Sweeps as normal, but does ricochet traces aswell (unless ricochets is 0) */
	void SweepMultiWithRicochets(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FQuat& Rotation, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params, const bool inDebug);


	/** Number of traces to fire at once (a shotgun-like feature) */
	virtual int32 GetNumberOfTraces() const;
	/** Max times to penetrate through blocking hits (-1 for infinite) */
	virtual int32 GetPenetrations() const;
	/** Max times to ricochet (-1 for infinite) */
	virtual int32 GetRicochets() const;

	/** Any Physical Surfaces added to this array will ricochet any Trace that hits them */
	TArray<EPhysicalSurface> RicochetableSurfaces;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	/**
	 * Determines whether we should ricochet off of the given Hit or not.
	 * This can be overriden for custom ricochet determination.
	 */
	virtual bool ShouldRicochetOffOf(const FHitResult& Hit) const;
	/**
	 * Calculates the direction to ricochet from the given hit.
	 * This can be overriden for custom ricochet directions
	 */
	virtual void CalculateRicochetDirection(FVector& RicoDir, const FHitResult& FromHit) const;


	// LineTraceMulti() events - return false to discontinue traces
	virtual bool OnInitialTrace(TArray<FHitResult>& OutInitialHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams& TraceParams);
	virtual bool OnPenetrate(TArray<FHitResult>& HitResults, TArray<FHitResult>& OutPenetrateHitResults, const UWorld* World, const FVector& PenetrateStart, const FVector& PenetrateEnd, const FCollisionQueryParams& TraceParams);
	virtual bool OnRicochet(TArray<FHitResult>& HitResults, TArray<FHitResult>& OutRicoHitResults, const UWorld* World, const FVector& RicoStart, const FVector& RicoEnd, const FCollisionQueryParams& TraceParams);
	virtual void OnPostTraces(TArray<FHitResult>& HitResults, const UWorld* World, const FCollisionQueryParams& TraceParams);


	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor) PURE_VIRTUAL(AGATA_Trace);

	/**
	 * Calls PerformTrace() for GetNumberOfTraces() amount of times safely.
	 * Outputs a 2D array of Hits for clarity of which Hit Results were for which trace.
	 */
	void PerformTraces(TArray<TArray<FHitResult>>& OutTraceResults, AActor* InSourceActor);
	/** Indicates which PerformTrace() call we are. */
	int32 CurrentTraceIndex;


//#if ENABLE_DRAW_DEBUG
	/**
	 * Debugs given hit results.
	 */
	virtual void DebugHitResults(const TArray<FHitResult>& HitResults, const UWorld* World) const;
	virtual void DebugTrace(const TArray<FHitResult>& HitResults, const UWorld* World, const FVector& Start, const FVector& End) const;
	virtual void DebugTrace(const TArray<FHitResult>& HitResults, const UWorld* World, const FVector& Start, const FVector& End, const FVector& ExtraTraceEnd) const;
//#endif // ENABLE_DRAW_DEBUG

	TWeakObjectPtr<AGameplayAbilityWorldReticle> ReticleActor;

};
