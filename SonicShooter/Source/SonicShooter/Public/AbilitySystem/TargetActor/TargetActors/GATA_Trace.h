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

	/** Traces as normal, but does ricochet traces aswell (unless ricochets is 0) */
	void LineTraceMultiWithRicochets(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams Params, const bool inDebug) const;
	/** Sweeps as normal, but does ricochet traces aswell (unless ricochets is 0) */
	void SweepMultiWithRicochets(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FQuat& Rotation, const FCollisionShape CollisionShape, const FCollisionQueryParams Params, const bool inDebug) const;

	virtual int32 GetRicochets() const;

protected:
	virtual void PreInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	 * Called in a loop "GetRicochets()" amount of times (unless unsuccessful rico occurs).
	 * Expects the OutHitResults to already have hits.
	 * 
	 * Returns true if successful (we should continue ricocheting).
	 * Returns false if didn't trace successfully (we should stop ricocheting).
	 */
	virtual bool RicochetLineTrace(TArray<FHitResult>& OutHitResults, const UWorld* World, const FCollisionQueryParams Params) const;
	virtual bool RicochetSweep(TArray<FHitResult>& OutHitResults, const UWorld* World, const FQuat& Rotation, const FCollisionShape CollisionShape, const FCollisionQueryParams Params) const;


	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor) PURE_VIRTUAL(AGATA_Trace);


//#if ENABLE_DRAW_DEBUG
	/**
	 * Debugs given hit results.
	 * TODO: get rid of timesRicocheted! and clean this up a lot
	 */
	virtual void DebugTrace(const TArray<FHitResult>& HitResults, const UWorld* World, const FVector& Start, const FVector& End, const int32 timesRicocheted) const;
//#endif // ENABLE_DRAW_DEBUG

	TWeakObjectPtr<AGameplayAbilityWorldReticle> ReticleActor;

};
