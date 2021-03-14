// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "AbilitySystem/TargetActor/GATDF_MultiFilter.h"

#include "GATA_Trace.generated.h"


class UGameplayAbility;



/**
 * 
 */
UCLASS(notplaceable)
class SONICSHOOTER_API AGATA_Trace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AGATA_Trace(const FObjectInitializer& ObjectInitializer);


	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;

	void AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceEnd, bool bIgnorePitch = false) const;
	void DirWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceDir, bool bIgnorePitch = false) const;
	static bool ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition);

	/** Traces as normal, but will manually filter all hit actors */
	void LineTraceMultiWithFilter(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams Params, const bool inDebug) const;
	/** Sweeps as normal, but will manually filter all hit actors */
	void SweepMultiWithFilter(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FQuat& Rotation, const FCollisionShape CollisionShape, const FCollisionQueryParams Params, const bool inDebug) const;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		float MaxRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		TEnumAsByte<ECollisionChannel> TraceChannel;

	/** Number of times the trace can ricochet off of blocking hits - Zero for no ricochet */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		uint8 ricochets;

	/** Does the trace affect the aiming pitch */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		bool bTraceAffectsAimPitch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		FGATDF_MultiFilter MultiFilter;
	FGATDF_MultiFilterHandle MultiFilterHandle;

	/**
	 * If true, when a trace overlaps an actor's multiple collisions, those multiple collision hits will add
	 * that actor to the hitresults multiple times.
	 */
	bool bAllowMultipleHitsPerActor;

protected:
	virtual void PreInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor) PURE_VIRTUAL(AGameplayAbilityTargetActor_Trace);

	TWeakObjectPtr<AGameplayAbilityWorldReticle> ReticleActor;
};
