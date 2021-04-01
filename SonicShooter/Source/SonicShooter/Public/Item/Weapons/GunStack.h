// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcItemStack.h"
#include "GunStack.generated.h"


class AGATA_BulletTrace;



UENUM()
enum class EGunFireMode : uint8
{
	MODE_SemiAuto									UMETA(DisplayName = "Semi-auto"),
	MODE_FullAuto									UMETA(DisplayName = "Full-auto"),
	MODE_Burst										UMETA(DisplayName = "Burst")
};

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGunStack : public UArcItemStack
{
	GENERATED_BODY()
	
public:
	/**
	 * This gun's target actor (what it will shoot)
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Gun Firing")
		TSubclassOf<AGATA_BulletTrace> BulletTraceTargetActorTSub;

	/**
	 * The effect that will be applied to the target that this bullet hits
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Gun Firing")
		TSubclassOf<UGameplayEffect> BulletHitEffectTSub;


	/**
	 * Firing mode
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Gun Firing")
		EGunFireMode FiringMode;

protected:
	//UWeaponDefinition* WeaponDefinition;
};
