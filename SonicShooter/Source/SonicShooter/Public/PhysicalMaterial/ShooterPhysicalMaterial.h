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

	/** This affects the bullet's speed when penetrating this physical material  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shooter)
		float BulletPenetrationSpeedMultiplier;

	/** This affects the bullet's speed when ricocheting this physical material  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shooter)
		float BulletRicochetSpeedMultiplier;
};
