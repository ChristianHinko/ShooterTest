// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalMaterial/PM_Shooter.h"



UPM_Shooter::UPM_Shooter()
{
	bRichochetsBullets = false;
	BulletPenetrationSpeedReduction = 20.f;
	BulletRicochetSpeedReduction = 30.f;
}
