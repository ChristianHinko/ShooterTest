// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "AbilitySystem/TargetActor/GATDF_MultiFilter.h"

#include "SSGameplayAbilityTargetActor.generated.h"



/**
 * Base target actor class
 */
UCLASS(Abstract, notplaceable)
class SONICSHOOTER_API ASSGameplayAbilityTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	ASSGameplayAbilityTargetActor(const FObjectInitializer& ObjectInitializer);


	/** Our custom gameplay ability target data filter */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Target Data")
		FGATDF_MultiFilter MultiFilter;
	FGATDF_MultiFilterHandle MultiFilterHandle;

	/**
	 * If true, when a trace overlaps an actor's multiple collisions, those multiple collision hits will add
	 * that actor to the hitresults multiple times.
	 * 
	 * TODO: should not apply to multiple hits from multiple ricochets
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Target Data")
		bool bAllowMultipleHitsPerActor;


	/** Filter out hit results that do not pass filter and removes multiple hits per actor if needed */
	void FilterHitResults(TArray<FHitResult>& OutHitResults, const FGATDF_MultiFilterHandle FilterHandle, const bool inAllowMultipleHitsPerActor) const;




	/** Max range of this target actor (not required for all target actors)		(We made this virual so we can just return GunAttributeSet->GetMaxRange() that way we don't have to bind to that attribute's delegate)*/
	virtual float GetMaxRange() const;

	/** Trace channel for this target actor (not required for all target actors) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		TEnumAsByte<ECollisionChannel> TraceChannel;

	/** Does the trace affect the aiming pitch */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		bool bTraceAffectsAimPitch;

	/** Outputs a point that the player controller is looking at (within the MaxRange) (also this uses TraceChannel) */
	void AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceEnd) const;
	/** Outputs a direction to use rather than a trace endpoint */
	void DirWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceDir) const;

	static bool ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition);

};
