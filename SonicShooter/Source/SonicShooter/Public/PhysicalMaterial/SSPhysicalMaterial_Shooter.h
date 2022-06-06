// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#include "SSPhysicalMaterial_Shooter.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSPhysicalMaterial_Shooter : public UPhysicalMaterial
{
	GENERATED_BODY()

public:
	USSPhysicalMaterial_Shooter(const FObjectInitializer& ObjectInitializer);


	/** Bullet can ricochet off of this physical material if there is enough speed. If not enough speed, it will stop */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter")
		uint8 bRicochets : 1;
	/** Slows down bullet speed by this much PER CENTIMETER in penetration */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter", meta = (EditCondition = "bRichochetsBullets == false", EditConditionHides))
		float PenetrationSpeedNerf;
	/** Slows down bullet speed by subtracting this much on ricochet */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter", meta = (EditCondition = "bRichochetsBullets == true", EditConditionHides))
		float RicochetSpeedNerf;

};
