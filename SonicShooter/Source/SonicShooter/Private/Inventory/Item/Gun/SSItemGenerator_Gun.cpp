// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/SSItemGenerator_Gun.h"

#include "Inventory/Item/SSItemDefinition_Active.h"
#include "Inventory/Item/Gun/SSItemStack_Gun.h"
#include "Inventory/Item/Gun/SSItemDefinition_Gun.h"



USSItemGenerator_Gun::USSItemGenerator_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


UArcItemStack* USSItemGenerator_Gun::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	UArcItemStack* ItemStack = Super::GenerateItemStack_Implementation(Context);


	// Inject defaults into our new Item Stack
	USSItemDefinition_Active* SSItemDefinition = Cast<USSItemDefinition_Active>(ItemDefinition.GetDefaultObject());
	if (IsValid(SSItemDefinition))
	{
		if (ItemStack->ItemName.IsEmpty())
		{
			ItemStack->ItemName = SSItemDefinition->DefaultItemName;
		}


		// Inject gun-specific defaults into our new Item Stack
		USSItemDefinition_Gun* GunDefinition = Cast<USSItemDefinition_Gun>(SSItemDefinition);
		if (IsValid(GunDefinition))
		{
			USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(ItemStack);
			if (IsValid(GunStack))
			{
				GunStack->BulletTargetActorTSub			= GunDefinition->DefaultBulletTargetActorTSub;
				GunStack->BulletInflictEffectTSub		= GunDefinition->DefaultBulletInflictEffectTSub;
			}
		}
	}

	return ItemStack;
}
