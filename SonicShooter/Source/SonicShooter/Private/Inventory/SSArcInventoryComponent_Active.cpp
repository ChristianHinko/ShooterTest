// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSArcInventoryComponent_Active.h"

#include "ArcItemStack.h"



USSArcInventoryComponent_Active::USSArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OnItemActive.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemStackActive);
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

void USSArcInventoryComponent_Active::OnItemStackActive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* NewlyActiveItemStack)
{
	// Something like this:
	
	//ItemHistory.Remove(NewlyActiveItemStack);
	//ItemHistory.Add(NewlyActiveItemStack);
}
