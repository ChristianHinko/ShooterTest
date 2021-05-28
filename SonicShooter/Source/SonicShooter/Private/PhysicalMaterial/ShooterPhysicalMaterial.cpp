// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalMaterial/ShooterPhysicalMaterial.h"

UShooterPhysicalMaterial::UShooterPhysicalMaterial()
{
	BulletPenetrationSpeedMultiplier = 1/6;	// cut the speed down into a sixth
	BulletRicochetSpeedMultiplier = 1/3;	// cut the speed down into a third
}
