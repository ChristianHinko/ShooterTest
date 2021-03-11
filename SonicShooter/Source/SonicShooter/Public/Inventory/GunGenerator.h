// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generators/ArcItemGenerator_Unique.h"
#include "Item/Weapons/GunStack.h"

#include "GunGenerator.generated.h"


class AGATA_BulletTrace;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGunGenerator : public UArcItemGenerator_Unique
{
	GENERATED_BODY()
	
public:
	UGunGenerator(const FObjectInitializer& ObjectInitializer);


	/**
	 * This gun's target actor (what it will shoot)
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		TSubclassOf<AGATA_BulletTrace> DefaultBulletTraceTargetActorTSub;

	/**
	 * The effect that will be applied to the target that this bullet hits
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		TSubclassOf<UGameplayEffect> DefaultBulletHitEffectTSub;
	

	/**
	 * Firing mode
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		EGunFireMode DefaultFiringMode;

	/**
	 * Minimum time that must pass before we can fire again
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		float DefaultFireRate;

	/**
	 * Number of bursts (ie. 3 for 3-round burst)
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing", meta = (EditCondition = "DefaultFiringMode == EGunFireMode::MODE_Burst"))
		int32 DefaultNumBursts;

	/**
	 * Amount of seconds between each shot for auto shooting. TODO: make this in bullets per second
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing", meta = (EditCondition = "DefaultFiringMode != EGunFireMode::MODE_SemiAuto"))
		float DefaultAutoShootingRate;


	/**
	 * How much clip ammo will we lose for each shot. (Pretty much always just 1 but it's here if you need it)
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		float DefaultAmmoCost;

protected:
	virtual UArcItemStack* GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context) override;
};
