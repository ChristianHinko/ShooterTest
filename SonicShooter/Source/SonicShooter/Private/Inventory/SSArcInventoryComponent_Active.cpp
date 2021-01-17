// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSArcInventoryComponent_Active.h"

#include "ArcItemStack.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"



USSArcInventoryComponent_Active::USSArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	maxItemHistoryBufferSize = 5;
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

bool USSArcInventoryComponent_Active::MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack)
{
	if (!IsValid(ItemStack))
	{
		return false;
	}

	TSubclassOf<UArcItemDefinition_Active> ItemDefinition(ItemStack->GetItemDefinition());
	if (!IsValid(ItemDefinition))
	{
		return false;
	}

	FArcInventoryItemInfoEntry* Entry = ActiveItemAbilityInfos.FindByPredicate([ItemSlot](const FArcInventoryItemInfoEntry& x) {
		return x.ItemSlotRef.SlotId == ItemSlot.SlotId;
		});
	if (Entry == nullptr)
	{
		Entry = &ActiveItemAbilityInfos.Add_GetRef(FArcInventoryItemInfoEntry(ItemSlot));
	}

	//Add this item's Active Abilities
	bool bSuccess = ApplyAbilityInfo_Internal(ItemDefinition.GetDefaultObject()->ActiveItemAbilityInfo, (*Entry).EquippedItemInfo, ItemStack);

	if (bSuccess)
	{
		ApplyPerks(ItemStack, ItemSlot);
	}

	OnItemActive.Broadcast(this, ItemStack);
	AddNewActiveItemToHistoryBuffer(ItemSlot);	// Only thing added from the Super

	return bSuccess;
}

void USSArcInventoryComponent_Active::AddNewActiveItemToHistoryBuffer(FArcInventoryItemSlotReference NewActiveItemSlotReference)
{
	int32 sizeChange = 0;

	if (ItemHistory.RemoveSingle(NewActiveItemSlotReference) == 1)		// Remove the item from the history buffer so we can make it a new recent
	{
		sizeChange--;
	}	
	ItemHistory.Push(NewActiveItemSlotReference);						// Make item new recent
	sizeChange++;

	

	if (ItemHistory.Num() > maxItemHistoryBufferSize)
	{
		ItemHistory.RemoveAt(ItemHistory.Num()-1);						// Remove oldest stored item if we are passed the max buffer size
	}

	

}
