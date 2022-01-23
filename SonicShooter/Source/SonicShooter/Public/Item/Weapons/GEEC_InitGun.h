// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "GEEC_InitGun.generated.h"



/**
 * Attribute Set default values for UAS_Gun.
 * Children can subclass this (in BP or cpp) and fill out default values.
 * 
 * Useful for non-Attribute typed properties that exist on the Attribute Set or anywhere else.
 * Useful for any Attributes that require more complex default value calculations.
 */
UCLASS()
class SONICSHOOTER_API UGEEC_InitGun : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEEC_InitGun(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;



	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float MinBulletSpread;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float MovingBulletSpread;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float BulletSpreadIncRate;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float FireBulletSpread;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float BulletSpreadDecSpeed;


	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float NumberOfBulletsPerFire;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float MaxRange;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float Penetrations;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float Ricochets;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float InitialBulletSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float BulletSpeedFalloff;


	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float bFullAuto;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float TimeBetweenShots;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float TimeBetweenFiresOverride;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float TimeBetweenBurstsOverride;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float NumShotsPerBurst;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
		float AmmoCost;

};
