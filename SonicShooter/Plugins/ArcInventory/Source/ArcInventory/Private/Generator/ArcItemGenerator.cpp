// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "Generators/ArcItemGenerator.h"
#include "ArcInventory.h"




UArcItemGenerator::UArcItemGenerator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemStackClass = UArcItemStack::StaticClass();
}


FPrimaryAssetId UArcItemGenerator::GetPrimaryAssetId() const
{
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		UClass* SearchNativeClass = GetClass();

		while (SearchNativeClass && !SearchNativeClass->HasAnyClassFlags(CLASS_Native | CLASS_Intrinsic))
		{
			SearchNativeClass = SearchNativeClass->GetSuperClass();
		}

		if (SearchNativeClass && SearchNativeClass != GetClass())
		{
			// If blueprint, return native class and asset name
			return FPrimaryAssetId(TEXT("ArcItemGenerator"), FPackageName::GetShortFName(GetOutermost()->GetFName()));
		}

		// Native CDO, return nothing
		return FPrimaryAssetId();
	}

	return  GetClass()->GetDefaultObject()->GetPrimaryAssetId();
}

UArcItemStack* UArcItemGenerator::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	return nullptr;
}

UArcItemStack* UArcItemGenerator::CreateNewItemStack(TSubclassOf<UArcItemDefinition_New> ItemDefinition, UArcItemRarity* ItemRarity)
{	
	TSubclassOf<UArcItemStack> ISC = ItemStackClass;

	if (IsValid(ISC))
	{
		//Check to see if our ItemStack Class is a child of what the item def wants.  If not, use the item def's class
		if (IsValid(ItemDefinition.GetDefaultObject()->DefaultItemStackClass) && !ISC->IsChildOf(ItemDefinition.GetDefaultObject()->DefaultItemStackClass))
		{
			ISC = ItemDefinition.GetDefaultObject()->DefaultItemStackClass;
		}
	}

	if (!IsValid(ISC))
	{
		//If we don't have a valid item stack class, use the one in the developer settings.
		ISC = GetDefault<UArcInventoryDeveloperSettings>()->DefaultItemStackClass;
		if (!IsValid(ISC))
		{
			//If we still don't have a valid one, use the default item stack class.  That's good enough
			ISC = UArcItemStack::StaticClass();
		}
	}
	UArcItemStack* NewItemStack = NewObject<UArcItemStack>(GetTransientPackage(), ISC);
	NewItemStack->ItemDefinition = ItemDefinition;
	NewItemStack->Rarity = ItemRarity;

	return NewItemStack;
}


UArcItemGenerator_Static::UArcItemGenerator_Static(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UArcItemStack* UArcItemGenerator_Static::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	if (IsValid(StaticGenerator))
	{
		return StaticGenerator->GetDefaultObject<UArcItemGenerator>()->GenerateItemStack(Context);
	}

	return nullptr;
}
