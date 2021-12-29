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

UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvBagSlotTag);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvEquipSlotTag);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvActiveSlotTag);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvDropItemAbilityTag);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvSwapItemSlotsAbilityTag);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvSwapPendingAbilityTag);


DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Display, All);

class FArcInventoryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
