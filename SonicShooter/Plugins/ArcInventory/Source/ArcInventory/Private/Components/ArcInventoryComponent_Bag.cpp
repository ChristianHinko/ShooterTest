// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "Components/ArcInventoryComponent_Bag.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "ArcInventory.h"

UArcInventoryComponent_Bag::UArcInventoryComponent_Bag(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BagSlotCount = 12;
}


void UArcInventoryComponent_Bag::InitializeComponent()
{
	Super::InitializeComponent();

	UpdateBagInventorySlots();
}

void UArcInventoryComponent_Bag::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::Get().GetAbilitySystemComponentFromActor(GetOwner()))
		{
			if (ASC->HasAttributeSetForAttribute(InventorySizeAttribute))
			{
				BagSlotCount = FMath::TruncToInt(ASC->GetNumericAttributeBase(InventorySizeAttribute));
				ASC->GetGameplayAttributeValueChangeDelegate(InventorySizeAttribute).AddUObject(this, &UArcInventoryComponent_Bag::OnInventorySizeAttributeChange);
				UpdateBagInventorySlots();
			}
		}		
	}	
}


void UArcInventoryComponent_Bag::UpdateBagInventorySlots()
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		return;
	}

	FGameplayTag BagTag = GetDefault<UArcInventoryDeveloperSettings>()->BagItemSlotTag;


	//First, Count how many bag slots we have
	TArray<FArcInventoryItemSlotReference> Slots;
	Query_GetAllBagSlots(Slots);

	int32 SlotCount = Slots.Num();

	int32 BagSlotsToCreate = BagSlotCount - SlotCount;

	if (BagSlotsToCreate > 0)
	{
		for (int32 i = 0; i < BagSlotsToCreate; i++)
		{
			CreateInventorySlot(BagTag.GetSingleTagContainer(), nullptr);
		}
	}
	else if(BagSlotsToCreate < 0)
	{
		//remove the bottom slots
		for (int i = 0; i < FMath::Abs(BagSlotsToCreate); i++)
		{
			int32 SlotToRemove = SlotCount - 1 - i;
			RemoveInventorySlot(Slots[SlotToRemove]);
		}
	}
	
}

void UArcInventoryComponent_Bag::OnInventorySizeAttributeChange(const FOnAttributeChangeData& ChangeData)
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		return;
	}

	BagSlotCount = FMath::TruncToInt(ChangeData.NewValue);
	UpdateBagInventorySlots();
}

bool UArcInventoryComponent_Bag::Query_GetAllBagSlots(TArray<FArcInventoryItemSlotReference>& OutSlotRefs)
{
	FGameplayTag BagTag = GetDefault<UArcInventoryDeveloperSettings>()->BagItemSlotTag;
	return Query_GetAllSlots(FArcInventoryQuery::QuerySlotMatchingTag(BagTag), OutSlotRefs);
}

