// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSArcInventoryComponent_Active.h"

#include "ArcItemStack.h"



USSArcInventoryComponent_Active::USSArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OnItemActive.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemStackActive);
}

void USSArcInventoryComponent_Active::OnItemStackActive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* NewlyActiveItemStack)
{
	// Something like this:
	
	//ItemHistory.Remove(NewlyActiveItemStack);
	//ItemHistory.Add(NewlyActiveItemStack);
}
