// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Item/AIEItemStack.h"

#include "SSItemStack_Gun.generated.h"


class AGameplayAbilityTargetActor;
class USSObject_ClipAmmo;
class USSObject_BulletSpread;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSItemStack_Gun : public UAIEItemStack
{
	GENERATED_BODY()

public:
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Ammo")
		TObjectPtr<USSObject_ClipAmmo> ClipAmmoSubobject;
	UPROPERTY(VisibleInstanceOnly, Category = "Gun")
		TObjectPtr<USSObject_BulletSpread> BulletSpreadSubobject;
	
public:
	USSItemStack_Gun(const FObjectInitializer& ObjectInitializer);


	USSObject_ClipAmmo* GetClipAmmoSubobject() const { return ClipAmmoSubobject; }
	USSObject_BulletSpread* GetBulletSpreadSubobject() const { return BulletSpreadSubobject; }

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
