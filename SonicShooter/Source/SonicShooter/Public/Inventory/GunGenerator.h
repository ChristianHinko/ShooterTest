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


	/**
	 * This gun's target actor (what it will shoot)
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		TSubclassOf<AGATA_BulletTrace> DefaultBulletTraceTargetActorTSub;

	/**
	 * The effect that will be applied to the target that this bullet hits
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		TSubclassOf<UGameplayEffect> DefaultBulletHitEffectTSub;


	/**
	 * If true, just hold down to fire gun - no need to keep clicking. This applies to burst guns aswell.
	 * TODO: make this a tag instead
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gun Firing")
		uint8 bDefaultFullAuto : 1;


protected:
	virtual UArcItemStack* GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context) override;
};
