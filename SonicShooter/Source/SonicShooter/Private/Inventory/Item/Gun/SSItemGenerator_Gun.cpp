// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/SSItemGenerator_Gun.h"

#include "Inventory/Item/AIEItemDefinition_Active.h"
#include "Inventory/Item/Gun/SSItemStack_Gun.h"
#include "Inventory/Item/Gun/SSItemDefinition_Gun.h"



USSItemGenerator_Gun::USSItemGenerator_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


UArcItemStack* USSItemGenerator_Gun::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	UArcItemStack* ItemStack = Super::GenerateItemStack_Implementation(Context);


	// Inject gun-specific defaults into our new Item Stack
	USSItemDefinition_Gun* ItemDefinitionGun = Cast<USSItemDefinition_Gun>(ItemDefinition.GetDefaultObject());
	if (IsValid(ItemDefinitionGun))
	{
		USSItemStack_Gun* ItemStackGun = Cast<USSItemStack_Gun>(ItemStack);
		if (IsValid(ItemStackGun))
		{
			ItemStackGun->BulletTargetActorTSub			= ItemDefinitionGun->DefaultBulletTargetActorTSub;
			ItemStackGun->BulletInflictEffectTSub		= ItemDefinitionGun->DefaultBulletInflictEffectTSub;
		}
	}

	return ItemStack;
}
