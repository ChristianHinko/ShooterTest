// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcItemStack.h"
#include "WeaponStack.generated.h"


class AGATA_BulletTrace;



UENUM()
enum class EWeaponFireMode : uint8
{
	MODE_SemiAuto									UMETA(DisplayName = "Semi-auto"),
	MODE_FullAuto									UMETA(DisplayName = "Full-auto"),
	MODE_Burst										UMETA(DisplayName = "Burst")
};

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UWeaponStack : public UArcItemStack
{
	GENERATED_BODY()
	
public:
	/**
	 * This weapon's target actor (what it will shoot)
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing")
		TSubclassOf<AGATA_BulletTrace> BulletTraceTargetActorTSub;

	/**
	 * The effect that will be applied to the target that this bullet hits
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing")
		TSubclassOf<UGameplayEffect> BulletHitEffectTSub;


	/**
	 * Firing mode
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing")
		EWeaponFireMode FiringMode;

	/**
	 * Minimum time that must pass before we can fire again
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing")
		float FireRate;

	/**
	 * Number of bursts (ie. 3 for 3-round burst)
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing", meta = (EditCondition = "DefaultFiringMode == EWeaponFireMode::MODE_Burst"))
		int32 NumBursts;

	/**
	 * Amount of seconds between each shot for auto shooting. TODO: make this in bullets per second
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing", meta = (EditCondition = "DefaultFiringMode != EWeaponFireMode::MODE_SemiAuto"))
		float AutoShootingRate;


	/**
	 * How much clip ammo will we lose for each shot. (Pretty much always just 1 but it's here if you need it)
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Weapon Firing")
		float AmmoCost;
};
