// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/WeaponGenerator.h"

#include "Item/Weapons/GunStack.h"



UWeaponGenerator::UWeaponGenerator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultFiringMode = EGunFireMode::MODE_SemiAuto;
	DefaultFireRate = 1.f;
	DefaultNumBursts = 3;
	DefaultAutoShootingRate = 1.f;
	DefaultAmmoCost = 1.f;
}


UArcItemStack* UWeaponGenerator::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	UArcItemStack* NewItemStack = Super::GenerateItemStack_Implementation(Context);


	if (UGunStack* NewGunStack = Cast<UGunStack>(NewItemStack))
	{
		NewGunStack->BulletTraceTargetActorTSub						= DefaultBulletTraceTargetActorTSub;
		NewGunStack->BulletHitEffectTSub							= DefaultBulletHitEffectTSub;
		NewGunStack->FiringMode										= DefaultFiringMode;
		NewGunStack->FireRate										= DefaultFireRate;
		NewGunStack->NumBursts										= DefaultNumBursts;
		NewGunStack->AutoShootingRate								= DefaultAutoShootingRate;
		NewGunStack->AmmoCost										= DefaultAmmoCost;
	}


	return NewItemStack;
}
