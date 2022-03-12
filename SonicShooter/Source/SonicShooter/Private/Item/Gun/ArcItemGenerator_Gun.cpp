// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Gun/ArcItemGenerator_Gun.h"

#include "Item/Gun/ArcItemStack_Gun.h"
#include "Item/Gun/ArcItemDefinition_Gun.h"



UArcItemGenerator_Gun::UArcItemGenerator_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


UArcItemStack* UArcItemGenerator_Gun::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	UArcItemStack* NewItemStack = Super::GenerateItemStack_Implementation(Context);

	
	UArcItemStack_Gun* NewGunStack = Cast<UArcItemStack_Gun>(NewItemStack);
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
