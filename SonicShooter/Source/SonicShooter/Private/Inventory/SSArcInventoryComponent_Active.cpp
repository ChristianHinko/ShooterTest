// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSArcInventoryComponent_Active.h"

#include "Net/UnrealNetwork.h"
#include "ArcItemStack.h"
#include "ArcInventory.h" // for Roy's Native Gameplay Tags
#include "AbilitySystem/ASSAbilitySystemComponent.h"
#include "Inventory/Item/SSArcItemDefinition_Active.h"
#include "Utilities/LogCategories.h"
#include "Inventory/Item/SSArcItemStack.h"



void USSArcInventoryComponent_Active::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;

	Params.Condition = COND_OwnerOnly;
	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(USSArcInventoryComponent_Active, ActiveItemHistory, Params);
}


USSArcInventoryComponent_Active::USSArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxItemHistoryBufferSize = 30;
	bUseOnEquipItemSwappingThingRoyMade = false;
	
	// The work below can be done in the constructor since we are dealing with CustomInventorySlots which is filled out in the editor 
	// Figures out what active item to start on (first CustomInventorySlot with the tag "Inventory.Slot.Active"). We know there should be a valid item in this slot even though it may not be replicated yet so this convieniently sets the StartingActiveItemSlot to the first active item slot regardless of wheather we have a valid item yet or not, however, this may limit certain gameplay mechanics related to runtime inventory startup editing or something since CustomInventorySlots are desined to be edited in editor. But who knows there may be a way to fix that
	const FGameplayTag& ActiveSlotTag = FArcInvActiveSlotTag;
	for (int32 i = 0; i < CustomInventorySlots.Num(); ++i)
	{
		if (CustomInventorySlots[i].Tags.HasTag(ActiveSlotTag))
		{
			StartingActiveItemSlot = i;
		}
	}

}

void USSArcInventoryComponent_Active::InitializeComponent()
{
	Super::InitializeComponent();

	OnAttributeSetCreated.AddDynamic(this, &USSArcInventoryComponent_Active::OnAttributeSetCreatedEvent);
}

void USSArcInventoryComponent_Active::BeginPlay()
{
	// Make sure we have nothing stored when we Begin Play. We want to have a clean start to this active slot if we reset
	const int32 OldActiveItem = ActiveItemSlot;
	MakeItemInactive();
	ActiveItemSlot = OldActiveItem;

	GetWorld()->GetTimerManager().SetTimerForNextTick(
		[this]()
		{
			SwapActiveItems(StartingActiveItemSlot);


			// =@OVERRIDED CODE MARKER@= We comment out this stuff from the Super since it just makes things difficult:
			
			////Check to see if we have an active item in our first slot and set it to that to start with  
			//if (PendingItemSlot != INDEX_NONE)
			//{
			//	this->SwitchToPendingItemSlot();
			//}
			////Sometimes, on the client, we get the initial ActiveItemSlot before we've begun play
			////In that case, PendingItemSlot would be none, and we have a valid ActiveItemSlot that hasn't been made active yet
			////So we'll do it here.
			//else if (ActiveItemSlot != INDEX_NONE && GetOwnerRole() != ROLE_Authority)
			//{
			//	this->MakeItemActive(ActiveItemSlot);
			//}
		}
	);

	// Skip UArcInventoryComponent_Active's stuff
	Super::Super::BeginPlay();
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
	if (!bUseOnEquipItemSwappingThingRoyMade)
	{
		// Skip Roy's Active Item equip stuff in UArcInventoryComponent_Active
		Super::Super::OnItemEquipped(Inventory, ItemSlotRef, ItemStack, PreviousItemStack);
		return;
	}

	Super::OnItemEquipped(Inventory, ItemSlotRef, ItemStack, PreviousItemStack);
}


void USSArcInventoryComponent_Active::OnAttributeSetCreatedEvent(UArcInventoryComponent_Equippable* Inventory, UAttributeSet* AttributeSet, UArcItemStack* AttributeSource)
{
	// Tells us to apply the default stats Effect
	bCreatedAttributeSets = true;
}

void USSArcInventoryComponent_Active::MakeItemActive(int32 NewActiveItemSlot)
{
	Super::MakeItemActive(NewActiveItemSlot);
	// Earliest point for the validity of UArcInventoryComponent_Active::ActiveItemSlot and hence GetActiveItemStack() can be used
	// NOTE: This is not the case for Roy's UArcInventoryComponent_Active::OnItemActive delegate (this delegate is not safe)


	UArcItemStack* ActiveItemStack = GetActiveItemStack();
	if (!IsValid(ActiveItemStack))
	{
		return;
	}


	// Check if we created any Attribute Sets
	if (bCreatedAttributeSets)
	{
		// Attribute Sets have been created! - so apply default stats Effect
		UAbilitySystemComponent* ASC = GetOwnerAbilitySystem();
		if (IsValid(ASC))
		{
			USSArcItemDefinition_Active* SSItemDefinition = Cast<USSArcItemDefinition_Active>(ActiveItemStack->GetItemDefinition().GetDefaultObject());
			if (IsValid(SSItemDefinition))
			{
				// Apply the default stats Effect
				FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
				EffectContextHandle.AddInstigator(GetOwner(), GetOwner());
				EffectContextHandle.AddSourceObject(GetOwner());

				FGameplayEffectSpecHandle NewEffectSpecHandle = ASC->MakeOutgoingSpec(SSItemDefinition->InitializationEffectTSub, 1/*GetLevel()*/, EffectContextHandle);
				if (NewEffectSpecHandle.IsValid())
				{
					ASC->ApplyGameplayEffectSpecToSelf(*NewEffectSpecHandle.Data.Get());
				}
				else
				{
					UE_LOG(LogArcInventorySetup, Warning, TEXT("%s() Tried to apply the InitializationEffectTSub but failed. Maybe check if you filled out your USSArcItemDefinition_Active::InitializationEffectTSub correctly in Blueprint"), ANSI_TO_TCHAR(__FUNCTION__));
				}
			}
		}

	}
	bCreatedAttributeSets = false;




}

bool USSArcInventoryComponent_Active::MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack)
{
	bool bSuccess = Super::MakeItemActive_Internal(ItemSlot, ItemStack);


	if (bSuccess)
	{
		AddToActiveItemHistory(ItemSlot);
	}

	return bSuccess;
}

void USSArcInventoryComponent_Active::AddToActiveItemHistory(const FArcInventoryItemSlotReference& NewActiveItemSlotReference)
{
	int32 SizeChange = 0;

	if (ActiveItemHistory.RemoveSingle(NewActiveItemSlotReference) == 1)
	{
		--SizeChange; // we don't want duplicates.... remove the item from the history buffer so we can make it a new recent
	}

	// Make item new recent
	ActiveItemHistory.Insert(NewActiveItemSlotReference, 0);
	++SizeChange;

	if (ActiveItemHistory.Num() > MaxItemHistoryBufferSize)
	{
		ActiveItemHistory.RemoveAt(ActiveItemHistory.Num() - 1); // remove oldest stored item if we are passed the max buffer size
	}

}
