// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcItemStack.h"

#include "GunStack.generated.h"


class AGATA_BulletTrace;



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
	 * If true, just hold down to fire gun - no need to keep clicking. This applies to burst guns aswell.
	 * TODO: make this a tag instead
	 */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = "Gun Firing")
		uint8 bFullAuto : 1;

protected:
	//UWeaponDefinition* WeaponDefinition;
};
