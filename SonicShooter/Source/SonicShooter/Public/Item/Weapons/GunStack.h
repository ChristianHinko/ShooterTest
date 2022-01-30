// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/SSArcItemStack.h"

#include "GunStack.generated.h"


class AGATA_BulletTrace;
class UO_Ammo;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGunStack : public USSArcItemStack
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Ammo")
		UO_Ammo* AmmoSubobject;
	
public:
	UGunStack(const FObjectInitializer& ObjectInitializer);


	UO_Ammo* GetAmmoSubobject() const { return AmmoSubobject; }

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

protected:

};
