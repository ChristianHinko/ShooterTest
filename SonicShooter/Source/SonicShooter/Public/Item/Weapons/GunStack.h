// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcItemStack.h"
#include "GunStack.generated.h"


class AGATA_BulletTrace;



UENUM()
enum class EWeaponFireMode : uint8
{
	MODE_SemiAuto									UMETA(DisplayName = "Semi-auto"),
	MODE_FullAuto									UMETA(DisplayName = "Full-auto")
};

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGunStack : public UArcItemStack
{
	GENERATED_BODY()
	
public:
	/** This weapon's target actor (what it will shoot) */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing")
		TSubclassOf<AGATA_BulletTrace> BulletTraceTargetActorTSub;

	/** The effect that will be applied to the target that this bullet hits */
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Weapon Firing")
		TSubclassOf<UGameplayEffect> BulletHitEffectTSub;


	/** Firing mode */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing")
		EWeaponFireMode FiringMode;

	/** Number of bursts (ie. 3-round burst). Set to 0 for full auto - no burst */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing", meta = (EditCondition = "DefaultFiringMode == EWeaponFireMode::MODE_FullAuto"))
		int32 NumBursts;

	/**
	 * Rate of fire in seconds between each shot. (maybe this should be in bullets per second?)
	 *
	 * If full-auto, time between each bullet fired.
	 * If semi-auto, min time between each fire.
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing")
		float FireRate;


	/** How much clip ammo will we lose for each shot. (Pretty much always just 1 but it's here if you need it) */
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Weapon Firing")
		float AmmoCost;
};
