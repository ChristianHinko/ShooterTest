// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalMaterial/ShooterPhysicalMaterial.h"



UShooterPhysicalMaterial::UShooterPhysicalMaterial()
{
	bRichochetsBullets = false;
	BulletPenetrationSpeedReduction = 20.f;
	BulletRicochetSpeedReduction = 30.f;
}
