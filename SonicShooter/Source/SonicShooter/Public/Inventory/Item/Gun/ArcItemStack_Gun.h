// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Item/SSArcItemStack.h"

#include "ArcItemStack_Gun.generated.h"


class AGameplayAbilityTargetActor;
class UO_ClipAmmo;
class UO_BulletSpread;



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
	UPROPERTY(VisibleInstanceOnly, Category = "Ammo")
		TObjectPtr<UO_ClipAmmo> ClipAmmoSubobject;
	UPROPERTY(VisibleInstanceOnly, Category = "Gun")
		TObjectPtr<UO_BulletSpread> BulletSpreadSubobject;
	
public:
	UArcItemStack_Gun(const FObjectInitializer& ObjectInitializer);


	UO_ClipAmmo* GetClipAmmoSubobject() const { return ClipAmmoSubobject; }
	UO_BulletSpread* GetBulletSpreadSubobject() const { return BulletSpreadSubobject; }

	/**
	 * This gun's Target Actor (what it will shoot)
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Gun Firing", Replicated)
		TSubclassOf<AGameplayAbilityTargetActor> BulletTargetActorTSub;

	/**
	 * The Effect that will be applied to the target that this bullet hits
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Gun Firing", Replicated)
		TSubclassOf<UGameplayEffect> BulletInflictEffectTSub;

protected:

};
