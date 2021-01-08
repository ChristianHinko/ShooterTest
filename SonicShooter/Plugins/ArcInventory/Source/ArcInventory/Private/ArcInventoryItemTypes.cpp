// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "ArcInventoryItemTypes.h"
#include "ArcInventory.h"

#include "GameplayTags.h"
#include "ArcInventoryComponent.h"
#include "Item/ArcItemRarity.h"


const int32 NAMED_ITEM_SLOT = -1;


bool IsValid(const FArcInventoryItemSlotReference& ItemRef)
{
	if (!IsValid(ItemRef.ParentInventory))
	{
		return false;
	}

	return ItemRef.ParentInventory->IsValidItemSlot(ItemRef);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////


bool FArcInventoryItemSlotFilter::AcceptsItem(UArcItemStack* ItemStack) const
{
	if (!IsValid(ItemStack))
	{
		return false;
	}

	if (!ItemStack->HasValidItemData())
	{
		return false;
	}

	if (ForceSingleStack)
	{
		if (ItemStack->GetStackSize() > 1)
		{
			return false;
		}		
	}

	FGameplayTagContainer StackTags;
	ItemStack->GetOwnedGameplayTags(StackTags);
	if (!FilterQuery.IsEmpty())
	{
		if (!FilterQuery.Matches(StackTags))
		{
			return false;
		}
	}	

	return true;
}

bool FArcInventoryItemSlotFilterHandle::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	uint8 RepBits = 0;

	bOutSuccess = true;

	if (Ar.IsSaving())
	{
		if (Data.IsValid())
		{
			RepBits |= 1 << 0;
		}
	}

	Ar.SerializeBits(&RepBits, 1);

	if (RepBits & (1 << 0))
	{
		if (Ar.IsLoading())
		{
			Data = MakeShareable(new FArcInventoryItemSlotFilter());
		}

		FArcInventoryItemSlotFilter::StaticStruct()->GetCppStructOps()->NetSerialize(Ar, Map, bOutSuccess, Data.Get());
	}

	return true;
}

bool FArcInventoryItemSlotReference::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	Ar << SlotId;
	SlotTags.NetSerialize(Ar, Map, bOutSuccess);
	Ar << ParentInventory;

	bOutSuccess = true;
	return true;
}

FString FArcInventoryItemSlotReference::ToString() const
{
	return FString::Printf(TEXT("Slot(%d)(%s)-%s"), SlotId, *SlotTags.ToString(), ParentInventory ? *ParentInventory->GetName() : TEXT("nullptr"));
}

void FArcInventoryItemSlot::ToDebugStrings(TArray<FString>& OutStrings, bool Detailed) const
{
	FString SlotName = FString::Printf(TEXT("Slot: %d %s"), SlotId, *SlotTags.ToString()); 
	OutStrings.Add(SlotName);
	if (Detailed)
	{
		//TODO: Add the slot filter here if we are detailed
		if (ItemSlotFilter.IsValid())
		{
			OutStrings.Add(TEXT("Filtered"));
		}
	}
	if (IsValid(ItemStack))
	{
		ItemStack->GetDebugStrings(OutStrings, Detailed);
	}
}


bool FArcInventoryItemSlot::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	bOutSuccess = true;
	Ar << SlotId;
	Ar << ItemStack;
	SlotTags.NetSerialize(Ar, Map, bOutSuccess);
	ItemSlotFilter.NetSerialize(Ar, Map, bOutSuccess);

	return true;
}



void FArcInventoryItemSlot::PreReplicatedRemove(const struct FArcInventoryItemSlotArray& InArraySerializer)
{
	Owner = InArraySerializer.Owner;
}

void FArcInventoryItemSlot::PostReplicatedAdd(const struct FArcInventoryItemSlotArray& InArraySerializer)
{
	Owner = InArraySerializer.Owner;
	Owner->OnInventoryUpdate.Broadcast(Owner);
}

void FArcInventoryItemSlot::PostReplicatedChange(const struct FArcInventoryItemSlotArray& InArraySerializer)
{
	Owner = InArraySerializer.Owner;
	Owner->OnInventoryUpdate.Broadcast(Owner);
	Owner->OnItemSlotChange.Broadcast(Owner, FArcInventoryItemSlotReference(*this, Owner), ItemStack, nullptr);
}

/////////////////////////////////////////////////////////////////



bool FArcInventoryQuery::MatchesSlot(const FArcInventoryItemSlot& ItemSlot)	const
{
	//Slot Tag Matching
	bool Matches = true;

	//Check to see if we have a matching slot type
	if (!SlotTypeQuery.IsEmpty())
	{
		Matches &= SlotTypeQuery.Matches(ItemSlot.SlotTags); 						 		
	}	

	if (!ItemTypeQuery.IsEmpty())
	{
		//If we are looking for a specific item and this slot doesn't have any item, it's a failed match
		if (!::IsValid(ItemSlot.ItemStack))
		{
			return false;
		}

		FGameplayTagContainer StackContainer;
		ItemSlot.ItemStack->GetOwnedGameplayTags(StackContainer);

		Matches &= ItemTypeQuery.Matches(StackContainer);
	}

	return Matches;
}

FArcInventoryQuery FArcInventoryQuery::QuerySlotMatchingTag(FGameplayTag Tag)
{
	FArcInventoryQuery Query;
	Query.SlotTypeQuery = FGameplayTagQuery::MakeQuery_MatchTag(Tag);

	return Query;
}

FArcInventoryQuery FArcInventoryQuery::QueryForMatchingItemTag(FGameplayTag Tag)
{
	FArcInventoryQuery Query;
	Query.ItemTypeQuery = FGameplayTagQuery::MakeQuery_MatchTag(Tag);

	return Query;
}

FArcInventoryQuery FArcInventoryQuery::QueryForSlot(const FGameplayTagQuery& SlotQuery)
{
	FArcInventoryQuery Query;
	Query.SlotTypeQuery = SlotQuery;

	return Query;
}

FArcInventoryQuery FArcInventoryQuery::QueryForItemType(const FGameplayTagQuery& ItemQuery)
{
	FArcInventoryQuery Query;
	Query.ItemTypeQuery = ItemQuery;

	return Query;
}

bool FArcInventoryQuery::IsValid() const
{
	return !SlotTypeQuery.IsEmpty() || !ItemTypeQuery.IsEmpty();
}
