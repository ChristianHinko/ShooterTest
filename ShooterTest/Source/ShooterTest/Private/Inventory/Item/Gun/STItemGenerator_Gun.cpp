// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/STItemGenerator_Gun.h"

#include "Inventory/Item/AIEItemDefinition_Active.h"
#include "Inventory/Item/Gun/STItemStack_Gun.h"
#include "Inventory/Item/Gun/STItemDefinition_Gun.h"



USTItemGenerator_Gun::USTItemGenerator_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


UArcItemStack* USTItemGenerator_Gun::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	UArcItemStack* ItemStack = Super::GenerateItemStack_Implementation(Context);


	// Inject gun-specific defaults into our new Item Stack
	USTItemDefinition_Gun* ItemDefinitionGun = Cast<USTItemDefinition_Gun>(ItemDefinition.GetDefaultObject());
	if (IsValid(ItemDefinitionGun))
	{
		USTItemStack_Gun* ItemStackGun = Cast<USTItemStack_Gun>(ItemStack);
		if (IsValid(ItemStackGun))
		{
			ItemStackGun->BulletTargetActorTSub			= ItemDefinitionGun->DefaultBulletTargetActorTSub;
			ItemStackGun->BulletInflictEffectTSub		= ItemDefinitionGun->DefaultBulletInflictEffectTSub;
		}
	}

	return ItemStack;
}
