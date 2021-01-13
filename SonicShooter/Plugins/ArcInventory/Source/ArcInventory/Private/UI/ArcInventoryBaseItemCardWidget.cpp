// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "UI/ArcInventoryBaseItemCardWidget.h"

UArcInventoryBaseItemCardWidget::UArcInventoryBaseItemCardWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UArcItemStack* UArcInventoryBaseItemCardWidget::GetItemStack() const
{
	return ItemStack;
}

void UArcInventoryBaseItemCardWidget::SetItemStack(UArcItemStack* InItemStack)
{
	ItemStack = InItemStack;
	BP_OnItemStackSet(ItemStack);
}
