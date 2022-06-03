// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/ArcItemGenerator_Gun.h"

#include "Inventory/Item/SSArcItemDefinition_Active.h"
#include "Inventory/Item/Gun/ArcItemStack_Gun.h"
#include "Inventory/Item/Gun/ArcItemDefinition_Gun.h"



UArcItemGenerator_Gun::UArcItemGenerator_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


UArcItemStack* UArcItemGenerator_Gun::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	UArcItemStack* ItemStack = Super::GenerateItemStack_Implementation(Context);


	// Inject defaults into our new Item Stack
	USSArcItemDefinition_Active* SSItemDefinition = Cast<USSArcItemDefinition_Active>(ItemDefinition.GetDefaultObject());
	if (IsValid(SSItemDefinition))
	{
		if (ItemStack->ItemName.IsEmpty())
		{
			ItemStack->ItemName = SSItemDefinition->DefaultItemName;
		}


		// Inject gun-specific defaults into our new Item Stack
		UArcItemDefinition_Gun* GunDefinition = Cast<UArcItemDefinition_Gun>(SSItemDefinition);
		if (IsValid(GunDefinition))
		{
			UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(ItemStack);
			if (IsValid(GunStack))
			{
				GunStack->BulletTargetActorTSub			= GunDefinition->DefaultBulletTargetActorTSub;
				GunStack->BulletInflictEffectTSub		= GunDefinition->DefaultBulletInflictEffectTSub;
			}
		}
	}

	return ItemStack;
}