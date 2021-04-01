// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/GunGenerator.h"

#include "Item/Weapons/GunStack.h"



UGunGenerator::UGunGenerator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultFiringMode = EGunFireMode::MODE_SemiAuto;
}


UArcItemStack* UGunGenerator::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	UArcItemStack* NewItemStack = Super::GenerateItemStack_Implementation(Context);


	if (UGunStack* NewGunStack = Cast<UGunStack>(NewItemStack))
	{
		NewGunStack->BulletTraceTargetActorTSub						= DefaultBulletTraceTargetActorTSub;
		NewGunStack->BulletHitEffectTSub							= DefaultBulletHitEffectTSub;
		NewGunStack->FiringMode										= DefaultFiringMode;
	}


	return NewItemStack;
}
