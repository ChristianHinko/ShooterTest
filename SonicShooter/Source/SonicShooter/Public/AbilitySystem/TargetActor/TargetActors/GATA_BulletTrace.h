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

	virtual void ConfirmTargetingAndContinue() override;

	/** Number of line traces to perform, above 1 would be considered a shotgun */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true, UIMin = 1), Category = "Bullet Config")
		uint8 NumberOfBullets;

	/** This is injected in every fire. Radius of cone which bullets can spread. In degrees (90 degs will make a right angle cone) */
	float BulletSpread;

	/** This is injected in every fire */
	int16 FireSpecificNetSafeRandomSeed;

protected:
	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor);

private:
	uint8 currentBulletNumber;
};
