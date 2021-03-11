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


	/** This gun's target actor (what it will shoot) */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		TSubclassOf<AGATA_BulletTrace> DefaultBulletTraceTargetActorTSub;

	/** The effect that will be applied to the target that this bullet hits */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		TSubclassOf<UGameplayEffect> DefaultBulletHitEffectTSub;
	

	/** Firing mode */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		EGunFireMode DefaultFiringMode;

	/** Number of bursts (ie. 3 for 3-round burst). Set to 0 for full auto - no burst */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing", meta = (EditCondition = "DefaultFiringMode == EGunFireMode::MODE_FullAuto"))
		int32 DefaultNumBursts;

	/**
	 * Rate of fire in seconds between each shot. (maybe this should be in bullets per second?)
	 * 
	 * If full-auto, time between each bullet fired.
	 * If semi-auto, min time between each fire.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		float DefaultFireRate;


	/** How much clip ammo will we lose for each shot. (Pretty much always just 1 but it's here if you need it) */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		float DefaultAmmoCost;

protected:
	virtual UArcItemStack* GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context) override;
};
