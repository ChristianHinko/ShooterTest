// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/TargetActors/GATA_Trace.h"
#include "GATA_BulletTrace.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API AGATA_BulletTrace : public AGATA_Trace
{
	GENERATED_BODY()

public:
	AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer);

	/** Number of line traces to perform, above 1 would be considered a shotgun */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true, UIMin = 1), Category = "Bullet Config")
		uint8 numberOfBullets;
	/** Radius of cone which bullets can spread. In degrees (90 degs will make a right angle cone) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true, UIMin = 0, UIMax = 360), Category = "Bullet Config")
		float bulletSpread;

	/** This is injected in every fire */
	int16 fireSpecificNetSafeRandomSeed;

protected:
	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor);
};
