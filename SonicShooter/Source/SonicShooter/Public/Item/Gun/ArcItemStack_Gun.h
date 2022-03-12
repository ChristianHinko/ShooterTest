// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/SSArcItemStack.h"

#include "ArcItemStack_Gun.generated.h"


class AGATA_BulletTrace;
class UO_Ammo;
class UO_Gun;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UArcItemStack_Gun : public USSArcItemStack
{
	GENERATED_BODY()

public:
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Ammo")
		UO_Ammo* AmmoSubobject;
	UPROPERTY(VisibleAnywhere, Category = "Gun")
		UO_Gun* GunSubobject;
	
public:
	UArcItemStack_Gun(const FObjectInitializer& ObjectInitializer);


	UO_Ammo* GetAmmoSubobject() const { return AmmoSubobject; }
	UO_Gun* GetGunSubobject() const { return GunSubobject; }

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
