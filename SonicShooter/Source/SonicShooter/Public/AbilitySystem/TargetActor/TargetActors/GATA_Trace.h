// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/SSGameplayAbilityTargetActor.h"

#include "GATA_Trace.generated.h"



/**
 * 
 */
struct FBodyPenetrationInfo
{
	FBodyPenetrationInfo()
	{
		PhysMaterial = nullptr;
		PenetrationDistance = -1;
	}
	FBodyPenetrationInfo(UPhysicalMaterial* InPhysMaterial, float InPenetrationDistance, FString InDebugName)
	{
		PhysMaterial = InPhysMaterial;
		PenetrationDistance = InPenetrationDistance;
	}

	UPhysicalMaterial* PhysMaterial;
	float PenetrationDistance;

	FString DebugName;
};

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

	virtual int32 GetNumberOfTraces() const;
	virtual int32 GetRicochets() const;
	virtual int32 GetPenetrations() const;

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

	void BuildPenetrationInfos(TArray<FBodyPenetrationInfo>& OutPenetrationInfos, const TArray<FHitResult>& FwdBlockingHits, const UWorld* World, const FCollisionQueryParams& TraceParams) const;

	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor) PURE_VIRTUAL(AGATA_Trace);
	void PerformTraces(TArray<TArray<FHitResult>>& OutTraceResults, AActor* InSourceActor);

	int32 CurrentTraceIndex;


//#if ENABLE_DRAW_DEBUG
	/**
	 * Debugs given hit results.
	 * TODO: get rid of timesRicocheted! and clean this up a lot
	 */
	virtual void DebugTrace(const TArray<FHitResult>& HitResults, const UWorld* World, const FVector& Start, const FVector& End, const int32 timesRicocheted) const;
//#endif // ENABLE_DRAW_DEBUG

	TWeakObjectPtr<AGameplayAbilityWorldReticle> ReticleActor;

};
