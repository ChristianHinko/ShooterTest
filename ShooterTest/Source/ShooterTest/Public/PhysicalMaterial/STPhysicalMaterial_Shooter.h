// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#include "STPhysicalMaterial_Shooter.generated.h"



/**
 * 
 */
UCLASS()
class SHOOTERTEST_API USTPhysicalMaterial_Shooter : public UPhysicalMaterial
{
    GENERATED_BODY()

public:
    USTPhysicalMaterial_Shooter(const FObjectInitializer& ObjectInitializer);


    /** Bullet can ricochet off of this physical material if there is enough speed. If not enough speed, it will stop */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter")
        uint8 bRicochets : 1;
    /** Slows down bullet speed by subtracting this much PER CENTIMETER of penetration */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter", meta = (EditCondition = "bRicochets == false", EditConditionHides))
        float PerCmPenetrationSpeedNerf;
    /** Slows down bullet speed by subtracting this much on ricochet */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooter", meta = (EditCondition = "bRicochets == true", EditConditionHides))
        float RicochetSpeedNerf;

};
