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
	virtual void PostInitializeComponents() override;

	virtual void ConfirmTargetingAndContinue() override;

	


	/** Radius of cone which bullets can spread. In degrees (90 degs will make a right angle cone) */
	float BulletSpread;
	void OnBulletSpreadAttributeChanged(const FOnAttributeChangeData& Data);
	/** Number of line traces to perform, above 1 would be considered a shotgun */
	uint8 NumberOfBulletsPerFire;
	void OnNumberOfBulletsPerFireAttributeChanged(const FOnAttributeChangeData& Data);


	/** This is injected in every fire */
	int16 FireSpecificNetSafeRandomSeed;

protected:
	// This override signifies performing a trace for a ricochetable bullet (but it also might not richochet based on how this GATA is configed). The OutHitResults are the hit results from 1 bullet ricocheting off walls and hitting player(s)
	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor) override;



	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	uint8 currentBulletNumber;
};
