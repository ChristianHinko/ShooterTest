// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalMaterial/STPhysicalMaterial_Shooter.h"



USTPhysicalMaterial_Shooter::USTPhysicalMaterial_Shooter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    , bRicochets(false)
    , PerCmPenetrationSpeedNerf(0.20f)
    , RicochetSpeedNerf(30.f)
{

}
