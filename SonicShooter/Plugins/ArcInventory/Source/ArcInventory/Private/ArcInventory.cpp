// Copyright 2017-2020 Puny Human, All Rights Reserved.

#include "ArcInventory.h"

UE_DEFINE_GAMEPLAY_TAG(FArcInvBagSlotTag, TEXT("Inventory.Slot.Bag"));
UE_DEFINE_GAMEPLAY_TAG(FArcInvEquipSlotTag, TEXT("Inventory.Slot.Equipped"));
UE_DEFINE_GAMEPLAY_TAG(FArcInvActiveSlotTag, TEXT("Inventory.Slot.Active"));

UE_DEFINE_GAMEPLAY_TAG(FArcInvDropItemAbilityTag, TEXT("Ability.Inventory.DropItem"));
UE_DEFINE_GAMEPLAY_TAG(FArcInvSwapItemSlotsAbilityTag, TEXT("Ability.Inventory.SwapItems"));
UE_DEFINE_GAMEPLAY_TAG(FArcInvSwapPendingAbilityTag, TEXT("Ability.Inventory.SwapPending"));




DEFINE_LOG_CATEGORY(LogInventory);


#define LOCTEXT_NAMESPACE "FArcInventoryModule"

void FArcInventoryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FArcInventoryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FArcInventoryModule, ArcInventory)