// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#include "ShooterPhysicalMaterial.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UShooterPhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()

public:
	UShooterPhysicalMaterial();

	/** Bullet can ricochet off of this physical material if there is enough speed. If not enough speed, it will stop */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter")
		uint8 bRichochetsBullets : 1;

	/** Slows down bullet speed by this much PER METER in penetration */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bRichochetsBullets == false", EditConditionHides), Category = "Shooter")
		float BulletPenetrationSpeedReduction;

	/** Slows down bullet speed by subtracting this much on ricochet */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bRichochetsBullets == true", EditConditionHides), Category = "Shooter")
		float BulletRicochetSpeedReduction;
};
