// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetActors/GATA_Trace.h"
#include "BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"
#include "PhysicalMaterial/PM_Shooter.h"

#include "GATA_BulletTrace.generated.h"

class UO_BulletTrace;


/**
 * 
 */
UCLASS()
class SONICSHOOTER_API AGATA_BulletTrace : public AASSGameplayAbilityTargetActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		UO_BulletTrace* BulletTraceSubobject;

public:
	/** Number of scans to perform (a shotgun-like feature) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Scan")
		int32 NumOfScans;
	/** Max times to penetrate through blocking hits (assign a value of -1 for an unbound number of penetrations) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Scan")
		int32 MaxPenetrations;
	/** Max times to ricochet (assign a value of -1 for an unbound number of ricochets) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Scan")
		int32 MaxRicochets;

	AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer);


	virtual void ConfirmTargetingAndContinue() override;

	/** Injected */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float InitialBulletSpeed;

	/** Injected */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float BulletSpeedFalloff;

	/** Injected */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float CurrentBulletSpread;

	/** This is injected in every fire */
	UPROPERTY(/*BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet"*/)
		int16 FireSpecificNetSafeRandomSeed;

protected:
	bool ShouldRicochetOffOf(const FHitResult& Hit) const;
	virtual void CalculateAimDirection(FVector& OutAimStart, FVector& OutAimDir) const override;


private:
	/** Indicates which PerformScan() call we are. */
	int32 CurrentScanIndex;
};
