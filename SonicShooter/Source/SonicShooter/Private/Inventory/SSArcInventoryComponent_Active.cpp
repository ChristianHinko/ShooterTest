// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSArcInventoryComponent_Active.h"

#include "ArcItemStack.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"



USSArcInventoryComponent_Active::USSArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	maxItemHistoryBufferSize = 30;
}

bool USSArcInventoryComponent_Active::IsActiveItemSlotIndexValid(int32 InActiveItemSlot)
{
	if (InActiveItemSlot < 0)
	{
		return false;
	}
	if (InActiveItemSlot >= CachedActiveItemSlots.Num())
	{
		return false;
	}
	return true;
}

void USSArcInventoryComponent_Active::OnItemEquipped(class UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack)
{
	if (!bStartupItemsGiven)
	{
		AddToActiveItemHistory(ItemSlotRef);
	}

	// In our game we want items to auto set active whenever we equip an active item. However, if we havn't begun play yet, equiping an item will still work, just only with the most recent one before beginplay happens
	if (IsActiveItemSlot(ItemSlotRef) && IsValid(ItemStack))
	{
		int32 ItemSlotIndex = GetActiveItemIndexBySlotRef(ItemSlotRef);
		PendingItemSlot = ItemSlotIndex;

		//If we've begun play, send the gameplay event now.  Otherwise we'll get it in BeginPlay
		if (HasBegunPlay())
		{
			SwitchToPendingItemSlot();
		}
	}


	//If we are unequipping an item and it's the currently active item, either go to the next available active item or go to neutral
	if (!IsValid(ItemStack))
	{
		int32 ItemSlotIndex = GetActiveItemIndexBySlotRef(ItemSlotRef);
		if (ItemSlotIndex == ActiveItemSlot)
		{
			PendingItemSlot = GetNextValidActiveItemSlot();
			MakeItemInactive_Internal(ItemSlotRef, PreviousItemStack);
			SwitchToPendingItemSlot();
		}
	}
}

bool USSArcInventoryComponent_Active::MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack)
{
	bool bSuccess = Super::MakeItemActive_Internal(ItemSlot, ItemStack);

	if (bStartupItemsGiven)		// We don't want to touch the item history array if the startup items have not been given yet. Adding to it will be taken care of in OnItemEquipped
	{
		AddToActiveItemHistory(ItemSlot);
	}

	return bSuccess;
}

void USSArcInventoryComponent_Active::AddToActiveItemHistory(FArcInventoryItemSlotReference NewActiveItemSlotReference)
{
	int32 sizeChange = 0;

	if (ActiveItemHistory.RemoveSingle(NewActiveItemSlotReference) == 1)		// Remove the item from the history buffer so we can make it a new recent
	{
		sizeChange--;
	}
	ActiveItemHistory.Insert(NewActiveItemSlotReference, 0);						// Make item new recent
	sizeChange++;



	if (ActiveItemHistory.Num() > maxItemHistoryBufferSize)
	{
		ActiveItemHistory.RemoveAt(ActiveItemHistory.Num() - 1);						// Remove oldest stored item if we are passed the max buffer size
	}



}


