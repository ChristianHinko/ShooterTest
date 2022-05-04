// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalMaterial/PM_Shooter.h"



UPM_Shooter::UPM_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bRicochets(false)
	, PenetrationSpeedNerf(0.20f)
	, RicochetSpeedNerf(30.f)
{

}
