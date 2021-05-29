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


	/** Slows down bullet speed by this much PER METER in penetration */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shooter)
		float BulletPenetrationSpeedReduction;

	/** Slows down bullet speed by subtracting this much on ricochet */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shooter)
		float BulletRicochetSpeedReduction;
};
