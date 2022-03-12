// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/GunGenerator.h"

#include "Item/Weapons/GunStack.h"
#include "Item/Weapons/ArcItemDefinition_Gun.h"



UGunGenerator::UGunGenerator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


UArcItemStack* UGunGenerator::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	UArcItemStack* NewItemStack = Super::GenerateItemStack_Implementation(Context);

	
	UGunStack* NewGunStack = Cast<UGunStack>(NewItemStack);
	if (IsValid(NewGunStack))
	{
		UArcItemDefinition_Gun* GunDefinition = Cast<UArcItemDefinition_Gun>(ItemDefinition.GetDefaultObject());
		if (IsValid(GunDefinition))
		{
			// Inject defaults into our new Item Stack
			NewGunStack->BulletTraceTargetActorTSub			= GunDefinition->DefaultBulletTraceTargetActorTSub;
			NewGunStack->BulletHitEffectTSub				= GunDefinition->DefaultBulletHitEffectTSub;
		}
	}

	return NewItemStack;
}
