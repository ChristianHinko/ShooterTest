// Copyright 2017-2020 Puny Human, All Rights Reserved.

#include "ArcItemStack.h"
#include "ArcInventory.h"

#include "Engine/ActorChannel.h"


UArcItemStack::UArcItemStack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StackSize = 1;
	ItemName = NSLOCTEXT("ItemStack", "DefaultItemName", "Default Item Name");
}

const int32 Method_Rename = 0;
const int32 Method_Duplicate = 1;

void UArcItemStack::TransferStackOwnership(UArcItemStack*& ItemStack, AActor* Owner)
{
	const int32 TransferMethod = Method_Duplicate;

	if (TransferMethod == Method_Rename)
	{		
		ItemStack->Rename(nullptr, Owner);
		//Recursively rename out substacks
		for (UArcItemStack* SubStack : ItemStack->SubItemStacks)
		{
			TransferStackOwnership(SubStack, Owner);
		}
	}
	else if (TransferMethod == Method_Duplicate)
	{
		UArcItemStack* Original = ItemStack;
		ItemStack = DuplicateObject(Original, Owner);
		//We don't duplicate our sub objects here, because PostDuplicate handles it
	}	
}

void UArcItemStack::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UArcItemStack, Rarity);
	DOREPLIFETIME(UArcItemStack, ItemDefinition);
	DOREPLIFETIME(UArcItemStack, SubItemStacks);
	DOREPLIFETIME_CONDITION(UArcItemStack, ItemName, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UArcItemStack, StackSize, COND_OwnerOnly);
}

bool UArcItemStack::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool bWroteSomething = false;

	for (UArcItemStack* SubSack : SubItemStacks)
	{
		bWroteSomething |= Channel->ReplicateSubobject(SubSack, *Bunch, *RepFlags);
		//bWroteSomething |= SubSack->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return bWroteSomething;
}

bool UArcItemStack::IsNameStableForNetworking() const
{
	return GetOuter()->IsNameStableForNetworking();
}

bool UArcItemStack::IsSupportedForNetworking() const
{
	return true;
}

void UArcItemStack::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (HasValidItemData())
	{
		ItemDefinition.GetDefaultObject()->GetOwnedGameplayTags(TagContainer);
	}
	if (IsValid(Rarity))
	{
		Rarity->GetOwnedGameplayTags(TagContainer);
	}

}

void UArcItemStack::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);

	if (DuplicateMode == EDuplicateMode::Normal)
	{
		//Duplicate the SubItems
		TArray<UArcItemStack*> OldSubItems(SubItemStacks);
		SubItemStacks.Empty(OldSubItems.Num());
		for (auto SubItem : OldSubItems)
		{
			UArcItemStack* NewSubItem = DuplicateObject(SubItem, GetOuter());
			SubItemStacks.Add(NewSubItem);
		}
	}
}

AActor* UArcItemStack::GetOwner() const
{
	return Cast<AActor>(GetOuter());
}

TSubclassOf<UArcItemDefinition_New> UArcItemStack::GetItemDefinition() const
{
	return ItemDefinition;
}

int32 UArcItemStack::GetStackSize() const
{
	return StackSize;
}

void UArcItemStack::SetStackSize(int32 NewStackSize)
{
	if (!HasValidItemData())
	{
		return;
	}
	StackSize = FMath::Clamp(NewStackSize, 0, ItemDefinition.GetDefaultObject()->MaxStackSize);
}

bool UArcItemStack::HasValidItemData() const
{
	return IsValid(ItemDefinition);
}

bool UArcItemStack::CanStackWith(UArcItemStack* OtherStack) const
{
	if (!IsValid(OtherStack))
	{
		return false;
	}
	if (!HasValidItemData() || !OtherStack->HasValidItemData())
	{
		return false;
	}

	bool bCanStack = ItemDefinition.GetDefaultObject()->MaxStackSize > 1;
	return bCanStack && ItemDefinition == OtherStack->ItemDefinition;
}

bool UArcItemStack::MergeItemStacks(UArcItemStack* OtherStack)
{
	if (!IsValid(OtherStack))
	{
		return false;
	}
	if (!CanStackWith(OtherStack))
	{
		return false;
	}

	const int32 MaxStacks = ItemDefinition.GetDefaultObject()->MaxStackSize;

	if (StackSize + OtherStack->StackSize > MaxStacks)
	{
		int32 Diff = MaxStacks - StackSize;
		StackSize = MaxStacks;
		OtherStack->StackSize = Diff;

		return false;
	}
	else
	{
		StackSize = StackSize + OtherStack->StackSize;
		return true;
	}
}

UArcItemStack* UArcItemStack::SplitItemStack(int32 SplitAmount)
{
	if (!HasValidItemData())
	{
		return nullptr;
	}
	//Cant split out more items than we have in this stack
	if (SplitAmount >= StackSize)
	{
		return nullptr;
	}

	//Can't split 0 or less items
	if (SplitAmount <= 0)
	{
		return nullptr;
	}


	UArcItemStack* NewItemStack = DuplicateObject<UArcItemStack>(this, GetOuter());
	NewItemStack->StackSize = SplitAmount;

	StackSize -= SplitAmount;

	return NewItemStack;
}

bool UArcItemStack::CanAttachTo_Implementation(UArcItemStack* OtherStack)
{
	//By default we can't attach to another item
	return false;
}

bool UArcItemStack::AddSubItemStack(UArcItemStack* SubItemStack)
{
	if (!IsValid(SubItemStack))
	{
		return false;
	}
	if (!HasValidItemData())
	{
		return false;
	}
	//If an item can stack, then it can't have perks
	if (ItemDefinition.GetDefaultObject()->MaxStackSize > 1)
	{
		return false;
	}
	if (!SubItemStack->CanAttachTo(this))
	{
		return false;
	}

	if (SubItemStacks.Contains(SubItemStack))
	{
		return false;
	}

	SubItemStack->ParentItemStack = this;
	return SubItemStacks.AddUnique(SubItemStack) >= 0;
}

bool UArcItemStack::RemoveSubItemStack(UArcItemStack* SubItemStack)
{
	if (SubItemStacks.Remove(SubItemStack) > 0)
	{
		SubItemStack->ParentItemStack = nullptr;
		return true;
	}
	return false;
}

UArcUIData_ItemDefinition* UArcItemStack::GetUIData()
{
	return ItemDefinition.GetDefaultObject()->UIData;
}

UArcItemStack* UArcItemStack::QueryForSubItem(const FGameplayTagQuery& StackQuery)
{
	for (UArcItemStack* Stack : SubItemStacks)
	{
		FGameplayTagContainer TagContainer;
		Stack->GetOwnedGameplayTags(TagContainer);

		if (StackQuery.Matches(TagContainer))
		{
			return Stack;
		}
	}

	return nullptr;
}

void UArcItemStack::GetDebugStrings(TArray<FString>& OutStrings, bool Detailed) const
{
	OutStrings.Add(FString::Printf(TEXT("Name: %s (%s)"), *ItemName.ToString(), *ItemDefinition->GetName()));
	if (Detailed)
	{
		FString RarityName = IsValid(Rarity) ? Rarity->RarityName.ToString() : TEXT("null");
		OutStrings.Add(FString::Printf(TEXT("StackSize: %d, Rarity: %s, SubItems: %d"), StackSize, *RarityName, SubItemStacks.Num()));
		
	}
	
}

