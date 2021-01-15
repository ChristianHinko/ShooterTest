// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "ArcInventoryComponent.h"
#include "ArcInventory.h"
#include "ArcItemStack.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "ArcInventoryAttributeSet.h"

#include "Engine.h"
#include "Engine/Canvas.h"
#include "DisplayDebugHelpers.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "DisplayDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"


// Sets default values for this component's properties
UArcInventoryComponent::UArcInventoryComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);

}

void UArcInventoryComponent::PostInitProperties()
{
	BagInventory.Owner = this;
	Super::PostInitProperties();
}

void UArcInventoryComponent::InitializeComponent()
{	
	if (GetOwnerRole() == ROLE_Authority)
	{
		for (FArcInventoryItemSlotDefinition& SlotDef : CustomInventorySlots)
		{
			CreateInventorySlot(SlotDef.Tags, FArcInventoryItemSlotFilterHandle(new FArcInventoryItemSlotFilter(SlotDef.Filter)));
		}
	}
	
	
	Super::InitializeComponent();
}

void UArcInventoryComponent::CreateInventorySlot(const FGameplayTagContainer& SlotTags, const FArcInventoryItemSlotFilterHandle& Filter)
{
	FArcInventoryItemSlot Slot;
	Slot.SlotId = BagInventory.Slots.Num();
	Slot.SlotTags = SlotTags;
	Slot.ItemSlotFilter = Filter;
	Slot.Owner = this;

	BagInventory.Slots.Add(Slot);
	BagInventory.MarkItemDirty(Slot);
	
}

void UArcInventoryComponent::RemoveInventorySlot(const FArcInventoryItemSlotReference& Slot)
{
	if (!IsValidItemSlot(Slot))
	{
		return;
	}

	FArcInventoryItemSlot& ItemSlot = GetItemSlot(Slot);

	BagInventory.Slots.Remove(ItemSlot);
	BagInventory.MarkArrayDirty();
}

void UArcInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UArcInventoryComponent, BagInventory);
}


bool UArcInventoryComponent::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool WroteSomething = false;
	WroteSomething |= Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (auto Slot : BagInventory.Slots)
	{
		if (IsValid(Slot.ItemStack))
		{
			WroteSomething |= Channel->ReplicateSubobject(Slot.ItemStack, *Bunch, *RepFlags);
			WroteSomething |= Slot.ItemStack->ReplicateSubobjects(Channel, Bunch, RepFlags);
		}
	}

	return WroteSomething;
}

bool UArcInventoryComponent::LootItem(UArcItemStack* Item)
{
	//We can't do this on clients
	if (GetOwnerRole() != ROLE_Authority)
	{
		return false;
	}

	//Find the first empty item slot
	for (auto Slot : BagInventory.Slots)
	{
		FArcInventoryItemSlotReference SlotRef(Slot, this);
		if (AcceptsItem(Item, SlotRef) && PlaceItemIntoSlot(Item, SlotRef))
		{
			return true;
		}
	}

	return false;
}

bool UArcInventoryComponent::PlaceItemIntoSlot(UArcItemStack* Item, const FArcInventoryItemSlotReference& ItemSlot)
{
	//We can't do this on clients
	if (GetOwnerRole() != ROLE_Authority)
	{
		return false;
	}
	
	if (!AcceptsItem(Item, ItemSlot))
	{
		return false;
	}

	//Kinda Hack: The Item must be owned by our owning actor for it to be replicated as part of that actor.
	//We can't change ownership over the network (UE4 issue), so instead we duplicate it under the hood.  
	//Only do this if the item owner is not the owner of our component.
	if (IsValid(Item) && Item->GetOwner() != GetOwner())
	{
		UArcItemStack::TransferStackOwnership(Item, GetOwner());
	}

	//Place the item into the slot
	FArcInventoryItemSlot& Slot = GetItemSlot(ItemSlot);
	UArcItemStack* PreviousItem = Slot.ItemStack;
	Slot.ItemStack = Item;



	//Inform the world that we have placed this item here
	OnInventoryUpdate.Broadcast(this);
	OnItemSlotChange.Broadcast(this, ItemSlot, Item, PreviousItem);
	
	GetOwner()->ForceNetUpdate();
	return true;
}

bool UArcInventoryComponent::RemoveItemFromInventory(const FArcInventoryItemSlotReference& ItemSlot)
{
	//We can't do this on clients
	if (GetOwnerRole() != ROLE_Authority)
	{
		return false;
	}

	//Check if we have a valid item slot
	if (!IsValid(ItemSlot))
	{
		return false;
	}

	FArcInventoryItemSlot& Item = GetItemSlot(ItemSlot);
	UArcItemStack* PreviousItem = Item.ItemStack;

	//Check to make sure we have a valid item in this slot
	if (!IsValid(Item.ItemStack))
	{
		return false;
	}

	//then remove the item
	Item.ItemStack = nullptr;
	OnInventoryUpdate.Broadcast(this);
	OnItemSlotChange.Broadcast(this, ItemSlot, Item.ItemStack, PreviousItem);

	GetOwner()->ForceNetUpdate();

	return true;
}

bool UArcInventoryComponent::RemoveAllItemsFromInventory(TArray<UArcItemStack*>& OutItemsRemoved)
{
	for (FArcInventoryItemSlot& ItemSlot : BagInventory.Slots)
	{
		if (!IsValid(ItemSlot.ItemStack))
		{
			continue;
		}

		OutItemsRemoved.Add(ItemSlot.ItemStack);
		RemoveItemFromInventory(FArcInventoryItemSlotReference(ItemSlot, this));
	}

	return true;
}

bool UArcInventoryComponent::SwapItemSlots(const FArcInventoryItemSlotReference& FromSlot, const FArcInventoryItemSlotReference& ToSlot)
{
	//If we aren't the server, Call the server RPC
	if (GetOwnerRole() != ROLE_Authority)
	{
		return false;
	}


	//Make sure both slots are valid
	//This checks if ParentInventory is valid, which is important later.  
	if (!IsValid(FromSlot) || !IsValid(ToSlot))
	{
		return false;
	}	

	UArcInventoryComponent* SourceInventory = FromSlot.ParentInventory;
	UArcInventoryComponent* DestinationInventory = ToSlot.ParentInventory;

	//If neither the source nor the destination is us... what are we even doing here?
	if (SourceInventory != this && DestinationInventory != this)
	{
		return false;
	}

	UArcItemStack* FromItem = SourceInventory->GetItemInSlot(FromSlot);
	UArcItemStack* ToItem = DestinationInventory->GetItemInSlot(ToSlot);
														 	
	//Ensure that the two slots can hold these items
	if (!SourceInventory->AcceptsItem_AssumeEmptySlot(FromItem, ToSlot) || !DestinationInventory->AcceptsItem_AssumeEmptySlot(ToItem, FromSlot))
	{
		return false;
	}

	SourceInventory->RemoveItemFromInventory(FromSlot);
	DestinationInventory->RemoveItemFromInventory(ToSlot);

	SourceInventory->PlaceItemIntoSlot(FromItem, ToSlot);
	DestinationInventory->PlaceItemIntoSlot(ToItem, FromSlot);

	return true;
}

bool UArcInventoryComponent::AcceptsItem(UArcItemStack* Item, const FArcInventoryItemSlotReference& Slot)
{
	
	if (!AcceptsItem_AssumeEmptySlot(Item, Slot))
	{
		return false;
	}
	
	FArcInventoryItemSlot& SlotSlot = GetItemSlot(Slot);

	//We have an item already in here!
	if (IsValid(SlotSlot.ItemStack))
	{
		return false;
	}

	return true;

}

bool UArcInventoryComponent::AcceptsItem_AssumeEmptySlot(UArcItemStack* Item, const FArcInventoryItemSlotReference& Slot)
{
	//First step, ensure that the slot is valid
	if (!IsValidItemSlot(Slot))
	{
		return false;
	}
		
	FArcInventoryItemSlot& SlotSlot = GetItemSlot(Slot);

	//Check if we have a filter, and if we do determine if the filter will let the item in
	if (IsValid(SlotSlot.ItemSlotFilter) && IsValid(Item))
	{
		return SlotSlot.ItemSlotFilter.AcceptsItem(Item);
	}

	//No filter and a valid item?  This slot will hold it
	return true;
}

UArcItemStack* UArcInventoryComponent::GetItemInSlot(const FArcInventoryItemSlotReference& Reference)
{
	if (!IsValidItemSlot(Reference))
	{
		return nullptr;
	}

	FArcInventoryItemSlot& ItemSlot = GetItemSlot(Reference);
	BagInventory.MarkItemDirty(ItemSlot);
	return ItemSlot.ItemStack;
}
	   
void UArcInventoryComponent::OnRep_BagInventory()
{
	//Check all of the item stacks and ensure they have a proper outer.  
	for (int32 i = 0; i < BagInventory.Slots.Num(); i++)
	{
		FArcInventoryItemSlot& Slot = BagInventory.Slots[i];
		if (IsValid(Slot.ItemStack) && Slot.ItemStack->GetOuter() != GetOwner())
		{
			Slot.ItemStack->Rename(nullptr, GetOwner());
		}
	}
	OnInventoryUpdate.Broadcast(this);
}

bool UArcInventoryComponent::IsValidItemSlot(const FArcInventoryItemSlotReference& Slot)
{	
	//Check if we are in range
	if (!BagInventory.Slots.IsValidIndex(Slot.SlotId))
	{
		return false;
	}

	//Check if this reference matches the slot inside the inventory
	FArcInventoryItemSlotReference TestSlot = FArcInventoryItemSlotReference(BagInventory.Slots[Slot.SlotId], this);
	if (TestSlot != Slot)
	{
		return false;
	}

	return true;
}

FArcInventoryItemSlot& UArcInventoryComponent::GetItemSlot(const FArcInventoryItemSlotReference& RefSlot)
{
	check(IsValidItemSlot(RefSlot));

	FArcInventoryItemSlot&	SlotSlot = BagInventory.Slots[RefSlot.SlotId];	
	BagInventory.MarkItemDirty(SlotSlot);
	return SlotSlot;
} 


int32 UArcInventoryComponent::GetInventorySize()
{	
	return BagInventory.Slots.Num();
}


TArray<FArcInventoryItemSlotReference> UArcInventoryComponent::GetAllSlotReferences()
{
	TArray<FArcInventoryItemSlotReference> InventoryRefs;
	for (int i = 0; i < BagInventory.Slots.Num(); i++)
	{
		FArcInventoryItemSlotReference SlotRef(BagInventory.Slots[i], this);
		InventoryRefs.Add(SlotRef);
	}
	return InventoryRefs;
}

#pragma region Debugging

struct FArcInventoryDebugTargetInfo
{
	FArcInventoryDebugTargetInfo()
	{

	}

	TWeakObjectPtr<UWorld> TargetWorld;
	TWeakObjectPtr<UArcInventoryComponent> LastDebugTarget;
};

TArray<FArcInventoryDebugTargetInfo> InventoryDebugInfoList;

FArcInventoryDebugTargetInfo* GetDebugTargetInfo(UWorld* World)
{
	FArcInventoryDebugTargetInfo* TargetInfo = nullptr;
	for (FArcInventoryDebugTargetInfo& Info : InventoryDebugInfoList)
	{
		if (Info.TargetWorld.Get() == World)
		{
			TargetInfo = &Info;
			break;
		}
	}
	if (TargetInfo == nullptr)
	{
		TargetInfo = &InventoryDebugInfoList[InventoryDebugInfoList.AddDefaulted()];
		TargetInfo->TargetWorld = World;
	}

	return TargetInfo;
}

UArcInventoryComponent* GetDebugTarget(FArcInventoryDebugTargetInfo* TargetInfo)
{
	//Return the Target if we have one
	if (UArcInventoryComponent* Inv = TargetInfo->LastDebugTarget.Get())
	{
		return Inv;
	}

	//Find one
	for (TObjectIterator<UArcInventoryComponent> It; It; ++It)
	{
		if (UArcInventoryComponent* Inv = *It)
		{
			if (Inv->GetWorld() == TargetInfo->TargetWorld.Get() && MakeWeakObjectPtr(Inv).Get())
			{
				TargetInfo->LastDebugTarget = Inv;

				//Default to local player
				if (APawn* Pawn = Cast<APawn>(Inv->GetOwner()))
				{
					if (Pawn->IsLocallyControlled())
					{
						break;
					}
				}
			}
		}
	}
	return TargetInfo->LastDebugTarget.Get();
}



//FArcOnItemSlotUpdate& UArcInventoryComponent::GetItemSlotUpdateDelegate(const FArcInventoryItemSlotReference& ItemSlotRef)
//{
//	return ItemSlotUpdates.FindOrAdd(ItemSlotRef);
//}

class UAbilitySystemComponent* UArcInventoryComponent::GetOwnerAbilitySystem()
{
	return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
}

bool UArcInventoryComponent::Query_GetAllSlots(const FArcInventoryQuery& Query, TArray<FArcInventoryItemSlotReference>& OutSlotRefs)
{
	for (FArcInventoryItemSlot& ItemSlot : BagInventory.Slots)
	{
		if (Query.MatchesSlot(ItemSlot))
		{
			OutSlotRefs.Add(FArcInventoryItemSlotReference(ItemSlot, this));
		}
	}
	return OutSlotRefs.Num() > 0;
}

FArcInventoryItemSlotReference UArcInventoryComponent::Query_GetFirstSlot(const FArcInventoryQuery& Query)
{
	TArray<FArcInventoryItemSlotReference> OutSlotRefs;
	
	if (!Query_GetAllSlots(Query, OutSlotRefs))
	{
		UE_LOG(LogInventory, Warning, TEXT("Tried to query for %s but didn't find it"), *Query.SlotTypeQuery.GetDescription())
		return FArcInventoryItemSlotReference();
	}

	return OutSlotRefs[0];
}



void UArcInventoryComponent::Query_GetAllItems(const FArcInventoryQuery& Query, TArray<UArcItemStack*>& OutItems)
{
	for (FArcInventoryItemSlot& ItemSlot : BagInventory.Slots)
	{
		if (!IsValid(ItemSlot.ItemStack))
		{
			continue;
		}

		if (Query.MatchesSlot(ItemSlot))
		{
			OutItems.Add(ItemSlot.ItemStack);
		}
	}
}

static TAutoConsoleVariable<int32> DetailedItemStackInfo(TEXT("ArcInventory.DebugDetailedItemInfo"), 0, TEXT(""), ECVF_Default);

void UArcInventoryComponent::OnShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos)
{
	if (DisplayInfo.IsDisplayOn(TEXT("Inventory")) )
	{
		UWorld* World = HUD->GetWorld();
		FArcInventoryDebugTargetInfo* TargetInfo = GetDebugTargetInfo(World);

		if (UArcInventoryComponent* Inv = GetDebugTarget(TargetInfo))
		{
			TArray<FName> LocalDisplayNames;
			LocalDisplayNames.Add(TEXT("CInventory"));
			FDebugDisplayInfo LocalDisplayInfo(LocalDisplayNames, TArray<FName>());

			Inv->DisplayDebug(Canvas, LocalDisplayInfo, YL, YPos);
		}
	}
}

void UArcInventoryComponent::DisplayDebug(class UCanvas* Canvas, const class FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
	if (DebugDisplay.IsDisplayOn(TEXT("CInventory")))
	{
		FInventoryComponentDebugInfo DebugInfo;

		DebugInfo.bPrintToLog = false;
		DebugInfo.Canvas = Canvas;
		DebugInfo.XPos = 0.f;
		DebugInfo.YPos = YPos;
		DebugInfo.OriginalX = 0.f;
		DebugInfo.OriginalY = YPos;
		DebugInfo.MaxY = Canvas->ClipY - 150.f; // Give some padding for any non-columnizing debug output following this output
		DebugInfo.NewColumnYPadding = 30.f;

		Debug_Internal(DebugInfo);

		YPos = DebugInfo.YPos;
		YL = DebugInfo.YL;
	}
}

void UArcInventoryComponent::PrintDebug()
{

}

void UArcInventoryComponent::Debug_Internal(struct FInventoryComponentDebugInfo& Info)
{
	bool DetailedDisplay = DetailedItemStackInfo.GetValueOnGameThread() > 0;

	{	//Debug Title

		FString DebugTitle("Inventory ");
		
		DebugTitle += FString::Printf(TEXT("for actor %s "), *GetOwner()->GetName());
		if (GetOwnerRole() == ROLE_AutonomousProxy) DebugTitle += TEXT("(Local Player)");
		else if (GetOwnerRole() == ROLE_SimulatedProxy) DebugTitle += TEXT("(Simulated)");
		else if (GetOwnerRole() == ROLE_Authority) DebugTitle += TEXT("(Authority)");
		
		if (Info.Canvas)
		{
			Info.Canvas->SetDrawColor(FColor::White);
			Info.Canvas->DrawText(GEngine->GetLargeFont(), DebugTitle, Info.XPos + 4.f, 10.f, 1.5f, 1.5f);
		}
		else
		{
			DebugLine(Info, DebugTitle, 0.f, 0.f);
		}  	
	}

	

	//Draw the bag inventory
	{
		DebugLine(Info, FString::Printf(TEXT("Bag Inventory (Slots: %d)"), GetInventorySize()), 0.0f, 0.0f);
		for (auto InventorySlot : BagInventory.Slots)
		{
			TArray<FString> DebugStrings;
			InventorySlot.ToDebugStrings(DebugStrings, DetailedDisplay);

			if (Info.Canvas)
			{
				Info.Canvas->SetDrawColor(FColor::Yellow);
			}
			DebugLine(Info, DebugStrings[0], 4.0f, 0.0f);

			if (Info.Canvas)
			{
				Info.Canvas->SetDrawColor(FColor::Cyan);
			}
			for (int i = 1; i < DebugStrings.Num(); i++)
			{
				DebugLine(Info, DebugStrings[i], 12.0f, 0.0f);

			}
		}		
	}
}

void UArcInventoryComponent::AccumulateScreenPos(FInventoryComponentDebugInfo& Info)
{
	const float ColumnWidth = Info.Canvas ? Info.Canvas->ClipX * 0.4f : 0.f;

	float NewY = Info.YPos + Info.YL;
	if (NewY > Info.MaxY)
	{
		// Need new column, reset Y to original height
		NewY = Info.NewColumnYPadding;
		Info.XPos += ColumnWidth;
	}
	Info.YPos = NewY;
}



void UArcInventoryComponent::DebugLine(struct FInventoryComponentDebugInfo& Info, FString Str, float XOffset, float YOffset)
{
	if (Info.Canvas)
	{
		Info.YL = Info.Canvas->DrawText(GEngine->GetTinyFont(), Str, Info.XPos + XOffset, Info.YPos);
		AccumulateScreenPos(Info);
	}

	if (Info.bPrintToLog)
	{
		FString LogStr;
		for (int32 i = 0; i < (int32)XOffset; ++i)
		{
			LogStr += TEXT(" ");
		}
		LogStr += Str;
		UE_LOG(LogInventory, Warning, TEXT("%s"), *LogStr);
	}

	if (Info.Accumulate)
	{
		FString LogStr;
		for (int32 i = 0; i < (int32)XOffset; ++i)
		{
			LogStr += TEXT(" ");
		}
		LogStr += Str;
		Info.Strings.Add(Str);
	}
}

namespace InventoryDebug
{
	FDelegateHandle DebugHandle = AHUD::OnShowDebugInfo.AddStatic(&UArcInventoryComponent::OnShowDebugInfo);
}



#pragma endregion