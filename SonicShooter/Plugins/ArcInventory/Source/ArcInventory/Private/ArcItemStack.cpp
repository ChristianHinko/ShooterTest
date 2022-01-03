// Copyright 2017-2020 Puny Human, All Rights Reserved.

#include "ArcItemStack.h"
#include "ArcInventory.h"

#include "Net/UnrealNetwork.h"

#include "Engine/ActorChannel.h" 
#include "Engine/NetDriver.h"
#include "Engine/NetConnection.h"

#include "GameFramework/PlayerController.h"


UArcItemStack::UArcItemStack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	StackSize = 1;
	ItemName = NSLOCTEXT("ItemStack", "DefaultItemName", "Default Item Name");
	SubItemStacks.ParentStack = this;
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
		for (FArcSubItemArrayEntry& SubStack : ItemStack->SubItemStacks.Items)
		{
			TransferStackOwnership(SubStack.SubItemStack, Owner);
		}
		ItemStack->SubItemStacks.MarkArrayDirty();
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
	DOREPLIFETIME(UArcItemStack, ItemName);
	DOREPLIFETIME(UArcItemStack, StackSize);
}

bool UArcItemStack::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool bWroteSomething = false;

	for (FArcSubItemArrayEntry SubStack : SubItemStacks.Items)
	{
		if (IsValid(SubStack.SubItemStack))
		{
			bWroteSomething |= Channel->ReplicateSubobject(SubStack.SubItemStack, *Bunch, *RepFlags);
			bWroteSomething |= SubStack.SubItemStack->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
		
	}

	return bWroteSomething;
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

		TArray<UArcItemStack*> OldSubItems;
		GetSubItems(OldSubItems);
		SubItemStacks.Items.Empty(OldSubItems.Num());
		for (auto SubItem : OldSubItems)
		{
			UArcItemStack* NewSubItem = DuplicateObject(SubItem, GetOuter());
			AddSubItemStack(NewSubItem);
		}
	}
}

AActor* UArcItemStack::GetOwner() const
{
	return GetTypedOuter<AActor>();
}

void UArcItemStack::OnRep_Rarity(UArcItemRarity* PreviousRarity)
{
	//Blank, so that subclasses can override this function
}

void UArcItemStack::OnRep_ItemName(FText PreviousItemName)
{
	//Blank, so that subclasses can override this function
}

void UArcItemStack::OnRep_ItemDefinition(TSubclassOf<UArcItemDefinition_New> PreviousItemDefinition)
{
	//Blank, so that subclasses can override this function
}

void UArcItemStack::OnRep_StackSize(int32 PreviousStackSize)
{
	//Blank, so that subclasses can override this function
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
		int32 Diff = (MaxStacks + OtherStack->StackSize) - StackSize;
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

	if (SubItemStacks.Items.ContainsByPredicate([SubItemStack](auto x) { return x.SubItemStack == SubItemStack; }))
	{
		return false;
	}

	if (Cast<AActor>(GetOuter()))
	{
		if (SubItemStack->GetOuter() != GetOuter())
		{
			TransferStackOwnership(SubItemStack, Cast<AActor>(GetOuter()));
		}
	}
	

	SubItemStack->ParentItemStack = this;
	FArcSubItemArrayEntry Entry;
	Entry.SubItemStack = SubItemStack;
	SubItemStacks.Items.Add(Entry);
	SubItemStacks.MarkArrayDirty();

	OnSubStackAdded.Broadcast(this, SubItemStack);

	return true;
}

bool UArcItemStack::RemoveSubItemStack(UArcItemStack* SubItemStack)
{
	if (SubItemStacks.Items.RemoveAll([SubItemStack] (auto x) {return x.SubItemStack == SubItemStack; }) > 0)
	{
		SubItemStacks.MarkArrayDirty();
		OnSubStackRemoved.Broadcast(this, SubItemStack);

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
	for (const FArcSubItemArrayEntry& Stack : SubItemStacks.Items)
	{
		FGameplayTagContainer TagContainer;
		Stack.SubItemStack->GetOwnedGameplayTags(TagContainer);

		if (StackQuery.Matches(TagContainer))
		{
			return Stack.SubItemStack;
		}
	}

	return nullptr;
}

void UArcItemStack::GetSubItems(TArray<UArcItemStack*>& SubItemArray)
{
	SubItemArray.Empty(SubItemStacks.Items.Num());
	for (const FArcSubItemArrayEntry& Stack : SubItemStacks.Items)
	{
		SubItemArray.Add(Stack.SubItemStack);
	}
}

void UArcItemStack::GetDebugStrings(TArray<FString>& OutStrings, bool Detailed) const
{
	OutStrings.Add(FString::Printf(TEXT("Name: %s (%s)"), *ItemName.ToString(), *ItemDefinition->GetName()));
	if (Detailed)
	{
		FString RarityName = IsValid(Rarity) ? Rarity->RarityName.ToString() : TEXT("null");
		OutStrings.Add(FString::Printf(TEXT("StackSize: %d, Rarity: %s, SubItems: %d"), StackSize, *RarityName, SubItemStacks.Items.Num()));		
	}	
}

void FArcSubItemArrayEntry::PreReplicatedRemove(const struct FArcSubItemStackArray& InArraySerializer)
{
	if (IsValid(InArraySerializer.ParentStack))
	{
		InArraySerializer.ParentStack->OnSubStackRemoved.Broadcast(InArraySerializer.ParentStack, SubItemStack);
	}

	PreviousStack = InArraySerializer.ParentStack;
}

void FArcSubItemArrayEntry::PostReplicatedChange(const struct FArcSubItemStackArray& InArraySerializer)
{
	if (!PreviousStack.IsValid() && IsValid(InArraySerializer.ParentStack))
	{
		InArraySerializer.ParentStack->OnSubStackAdded.Broadcast(InArraySerializer.ParentStack, SubItemStack);
	}

	PreviousStack = SubItemStack;
}
