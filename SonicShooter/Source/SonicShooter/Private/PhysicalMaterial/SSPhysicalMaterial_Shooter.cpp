// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalMaterial/SSPhysicalMaterial_Shooter.h"



USSPhysicalMaterial_Shooter::USSPhysicalMaterial_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bRicochets(false)
	, PerCmPenetrationSpeedNerf(0.20f)
	, RicochetSpeedNerf(30.f)
{

}
