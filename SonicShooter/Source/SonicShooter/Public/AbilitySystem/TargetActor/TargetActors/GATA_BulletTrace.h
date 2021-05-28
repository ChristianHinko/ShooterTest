// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/TargetActors/GATA_Trace.h"

#include "GATA_BulletTrace.generated.h"


class UAS_Gun;



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
	virtual bool OnInitialTrace(const FHitResult& InitialBlockingHit, const UWorld* World, const FCollisionQueryParams& TraceParams) override;
	virtual bool OnPenetrate(const FHitResult& PenetratedThrough, TArray<FHitResult>& OutPenetrateHitResults, const UWorld* World, const FVector& PenetrateStart, const FVector& PenetrateEnd, const FCollisionQueryParams& TraceParams) override;
	virtual bool OnRicochet(const FHitResult& RicochetOffOf, TArray<FHitResult>& OutRicoHitResults, const UWorld* World, const FVector& RicoStart, const FVector& RicoEnd, const FCollisionQueryParams& TraceParams) override;
	virtual void OnPostTraces(const FHitResult& LastBlockingHit, const UWorld* World, const FCollisionQueryParams& TraceParams) override;

	// This override signifies performing a trace for a ricochetable bullet (but it also might not richochet based on how this GATA is configed). The OutHitResults are the hit results from 1 bullet ricocheting off walls and hitting player(s)
	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor) override;

	virtual void CalculateAimDirection(FVector& ViewStart, FVector& ViewDir) const override;

private:
	TArray<FHitResult> ThisRicochetBlockingHits;

};
