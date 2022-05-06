// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/ASSGameplayAbilityTargetActor.h"

#include "GATA_BulletTrace.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API AGATA_BulletTrace : public AASSGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer);

	/** Number of scans to perform (a shotgun-like feature) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Scan")
		int32 NumOfScans;
	/** Max times to penetrate through blocking hits (assign a value of -1 for an unbound number of penetrations) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Scan")
		int32 MaxPenetrations;
	/** Max times to ricochet (assign a value of -1 for an unbound number of ricochets) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Scan")
		int32 MaxRicochets;
	/** Bullet speed that is slowed down by ricochets and penetrations. Bullet stops when we run out of bullet speed. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float InitialBulletSpeed;
	/** The falloff of range for this bullet per cm	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float RangeFalloffNerf;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float CurrentBulletSpread;


	virtual void ConfirmTargetingAndContinue() override;

	/** This is injected in every fire */
	UPROPERTY(/*BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet"*/)
		int16 FireSpecificNetSafeRandomSeed;

protected:
	virtual void CalculateAimDirection(FVector& OutAimStart, FVector& OutAimDir) const override;


private:
	/** Indicates which PerformScan() call we are. */
	int32 CurrentScanIndex;
};
