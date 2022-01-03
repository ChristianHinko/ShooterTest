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

ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvBagSlotTag); // =@MODIFIED MARKER@=					add ``ARCINVENTORY_API`` so that we can use these tags in our module (Roy might fix this in an update later)
ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvEquipSlotTag); // =@MODIFIED MARKER@=				add ``ARCINVENTORY_API`` so that we can use these tags in our module (Roy might fix this in an update later)
ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvActiveSlotTag); // =@MODIFIED MARKER@=				add ``ARCINVENTORY_API`` so that we can use these tags in our module (Roy might fix this in an update later)

ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvDropItemAbilityTag); // =@MODIFIED MARKER@=			add ``ARCINVENTORY_API`` so that we can use these tags in our module (Roy might fix this in an update later)
ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvSwapItemSlotsAbilityTag); // =@MODIFIED MARKER@=		add ``ARCINVENTORY_API`` so that we can use these tags in our module (Roy might fix this in an update later)
ARCINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FArcInvSwapPendingAbilityTag); // =@MODIFIED MARKER@=		add ``ARCINVENTORY_API`` so that we can use these tags in our module (Roy might fix this in an update later)


DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Display, All);

class FArcInventoryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
