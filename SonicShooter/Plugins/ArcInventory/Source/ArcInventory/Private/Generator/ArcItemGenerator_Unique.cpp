// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "Generators/ArcItemGenerator_Unique.h"

#include "ArcInventory.h"




UArcItemGenerator_Unique::UArcItemGenerator_Unique(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UArcItemStack* UArcItemGenerator_Unique::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	if (!IsValid(ItemDefinition))
	{
		return nullptr;
	}

	UArcItemStack* ItemStack = CreateNewItemStack(ItemDefinition, ItemRarity);
	ItemStack->ItemName = ItemDisplayName; 

	for (UArcItemGenerator* SubItemGenerator : SubItemGenerators)
	{
		if (IsValid(SubItemGenerator))
		{
			UArcItemStack* SubItem = SubItemGenerator->GenerateItemStack(Context);

			//TODO: 
			//SubItem->OnGenerated();

			ItemStack->AddSubItemStack(SubItem);

			//TODO: 
			//SubItem->OnAddedToItemStack(ItemStack); //Or put this in AddSubItemStack?
		}
	}	

	return ItemStack;
}
