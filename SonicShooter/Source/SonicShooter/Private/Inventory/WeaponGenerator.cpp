// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/WeaponGenerator.h"

#include "Item/Weapons/WeaponStack.h"



UWeaponGenerator::UWeaponGenerator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultFiringMode = EWeaponFireMode::MODE_SemiAuto;
	DefaultFireRate = 1.f;
	DefaultNumBursts = 3;
	DefaultAutoShootingRate = 1.f;
	DefaultAmmoCost = 1.f;
}


UArcItemStack* UWeaponGenerator::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	UArcItemStack* NewItemStack = Super::GenerateItemStack_Implementation(Context);


	if (UWeaponStack* NewWeaponStack = Cast<UWeaponStack>(NewItemStack))
	{
		NewWeaponStack->BulletTraceTargetActorTSub				= DefaultBulletTraceTargetActorTSub;
		NewWeaponStack->BulletHitEffectTSub						= DefaultBulletHitEffectTSub;
		NewWeaponStack->FiringMode								= DefaultFiringMode;
		NewWeaponStack->FireRate								= DefaultFireRate;
		NewWeaponStack->NumBursts								= DefaultNumBursts;
		NewWeaponStack->AutoShootingRate						= DefaultAutoShootingRate;
		NewWeaponStack->AmmoCost								= DefaultAmmoCost;
	}


	return NewItemStack;
}
