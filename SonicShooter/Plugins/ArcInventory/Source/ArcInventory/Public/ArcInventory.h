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

#include "Net/UnrealNetwork.h"
#include "NativeGameplayTags.h"

//#include "ArcInventory.generated.h"  //Uncomment this if we put something in here that generates code

ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvBagSlotTag);
ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvEquipSlotTag);
ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvActiveSlotTag);

ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvDropItemAbilityTag);
ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvSwapItemSlotsAbilityTag);
ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvSwapPendingAbilityTag);


DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Display, All);

class FArcInventoryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
