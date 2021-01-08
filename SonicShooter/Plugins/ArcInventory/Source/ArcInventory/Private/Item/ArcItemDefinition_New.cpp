// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Item/ArcItemDefinition_New.h"
#include "ArcInventory.h"


const FName ItemDefinitionName = TEXT("ArcItemDefinition_New");

UArcItemDefinition_New::UArcItemDefinition_New()
	: Super()
{
	MaxStackSize = 1;
	DefaultItemStackClass = UArcItemStack::StaticClass();
}

FPrimaryAssetId UArcItemDefinition_New::GetPrimaryAssetId() const
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
			return FPrimaryAssetId(ItemDefinitionName, FPackageName::GetShortFName(GetOutermost()->GetFName()));
		}

		// Native CDO, return nothing
		return FPrimaryAssetId();
	}

	return  GetClass()->GetDefaultObject()->GetPrimaryAssetId();
}

UArcUIData_ItemDefinition::UArcUIData_ItemDefinition()
	: Super()
{

}
