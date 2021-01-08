// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "ArcItemStack.h"
#include "Item/ArcItemDefinition_New.h"
#include "ArcInventoryComponent.h"
#include "ArcInventoryItemTypes.h"
#include "ArcInventoryDeveloperSettings.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Generators/ArcItemGenerator.h"
#include "Item/ArcItemRarity.h"
#include "Item/ArcItemStackWorldObject.h"
#include "Perks/ArcItemPerkTypes.h"

//#include "ArcInventory.generated.h"  //Uncomment this if we put something in here that generates code


DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Display, All);

class FArcInventoryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
