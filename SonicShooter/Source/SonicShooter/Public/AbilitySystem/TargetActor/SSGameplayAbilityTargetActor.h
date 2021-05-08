// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "AbilitySystem/SSGameplayAbilityWorldReticle.h"
#include "AbilitySystem/TargetActor/GATDF_MultiFilter.h"

#include "SSGameplayAbilityTargetActor.generated.h"

class ASSGameplayAbilityWorldReticle;

/**
 * Base target actor class
 */
UCLASS(Abstract, notplaceable)
class SONICSHOOTER_API ASSGameplayAbilityTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	ASSGameplayAbilityTargetActor(const FObjectInitializer& ObjectInitializer);


	/** Our custom World Reticle Parameters */
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Targeting")
		FSSWorldReticleParameters SSReticleParams;

	/** Our custom Gameplay Ability Target Data Filter */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Target Data")
		FGATDF_MultiFilter MultiFilter;
	FGATDF_MultiFilterHandle MultiFilterHandle;

	/**
	 * If true, when a trace overlaps an actor's multiple collisions, those multiple collision hits will add
	 * that actor to the hitresults multiple times.
	 * 
	 * TODO: add option for picking the hit with highest damage
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Target Data")
		bool bAllowMultipleHitsPerActor;


	/** Filter out hit results that do not pass filter and removes multiple hits per actor if needed */
	void FilterHitResults(TArray<FHitResult>& OutHitResults, const FGATDF_MultiFilterHandle FilterHandle, const bool inAllowMultipleHitsPerActor) const;
	/**
	 * Filters out one hit result out of a given array. Is meant to be use in FHitResult loops.
	 * Returns true if hit was filtered.
	 */
	bool FilterHitResult(TArray<FHitResult>& OutHitResults, const int32 index, const FGATDF_MultiFilterHandle FilterHandle, const bool inAllowMultipleHitsPerActor) const;


	/**
	 * Called if this Target Actor is going to be reused at the end of Wait Target Data to disable this actor (good for reusing Target Actors across these task activations)
	 */
	virtual void StopTargeting();


	/** Max range of this target actor (not required for all target actors)		(We made this virual so we can just return GunAttributeSet->GetMaxRange() that way we don't have to bind to that attribute's delegate)*/
	virtual float GetMaxRange() const;

	/** Trace channel for this target actor (not required for all target actors) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		TEnumAsByte<ECollisionChannel> TraceChannel;


	/** If true, sets StartLocation to the AimPoint determined in CalculateAimDirection() */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		bool bUseAimPointAsStartLocation;

	/** Does the trace affect the aiming pitch */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		bool bTraceAffectsAimPitch;

	/** Outputs a point that the player controller is looking at (within the MaxRange) (also this uses TraceChannel) */
	void AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceEnd) const;
	/** Outputs a direction to use rather than a trace endpoint */
	void DirWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceDir) const;

	static bool ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition);


protected:
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

	/** This is when the Wait Target Data Task starts using us */
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	/**
	 * Calculates AimDir which is used in DirWithPlayerController().
	 * This can be overriden to add bullet spread for guns and stuff.
	 * 
	 * You can also determine AimStart if needed
	 */
	virtual void CalculateAimDirection(FVector& AimStart, FVector& AimDir) const;


	/** Returns true if the two given hits were from the same trace */
	static bool AreHitsFromSameTrace(const FHitResult& HitA, const FHitResult& HitB)
	{
		const bool bSameStart = (HitA.TraceStart == HitB.TraceStart);
		const bool bSameEnd = (HitA.TraceEnd == HitB.TraceEnd);
		//const bool bSamePenetration = (HitA.bStartPenetrating == HitB.bStartPenetrating);

		const bool bSameTrace = (bSameStart && bSameEnd/* && bSamePenetration*/);
		return bSameTrace;
	}
	

	TArray<TWeakObjectPtr<ASSGameplayAbilityWorldReticle>> ReticleActors;

	ASSGameplayAbilityWorldReticle* SpawnReticleActor(FVector Location, FRotator Rotation);
	virtual void DestroyReticleActors();


	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};

/*
* Todo:
*	1) Pooling system for reticles (assuming were using a reusable target actor)
*		Resetting the reticles array in StartTargeting shouldn't just destroy all reticles for resetting. Reticles should be recycled (deactivated and activated)
*	2) 
*/

