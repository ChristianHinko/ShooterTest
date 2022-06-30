// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Item/AIEItemStack.h"

#include "STItemStack_Gun.generated.h"


class AGameplayAbilityTargetActor;
class USTObject_ClipAmmo;
class USTObject_BulletSpread;



/**
 * 
 */
UCLASS()
class SHOOTERTEST_API USTItemStack_Gun : public UAIEItemStack
{
	GENERATED_BODY()

public:
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Ammo")
		TObjectPtr<USTObject_ClipAmmo> ClipAmmoSubobject;
	UPROPERTY(VisibleInstanceOnly, Category = "Gun")
		TObjectPtr<USTObject_BulletSpread> BulletSpreadSubobject;
	
public:
	USTItemStack_Gun(const FObjectInitializer& ObjectInitializer);


	USTObject_ClipAmmo* GetClipAmmoSubobject() const { return ClipAmmoSubobject; }
	USTObject_BulletSpread* GetBulletSpreadSubobject() const { return BulletSpreadSubobject; }

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
