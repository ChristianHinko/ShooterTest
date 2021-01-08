// Copyright 2017-2020 Puny Human, All Rights Reserved.

#include "Abilities/Tasks/ArcAbilityTask_DropItem.h"




bool FGameplayAbilityTargetData_DropItem::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	bOutSuccess = true;
	FromSlot.NetSerialize(Ar, Map, bOutSuccess);

	return true;
}



UArcAbilityTask_DropItem::UArcAbilityTask_DropItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UArcAbilityTask_DropItem* UArcAbilityTask_DropItem::DropItemFromInventory(UGameplayAbility* OwningAbility, const FArcInventoryItemSlotReference& FromSlot)
{
	UArcAbilityTask_DropItem* Task = NewAbilityTask<UArcAbilityTask_DropItem>(OwningAbility);
	Task->SlotReference = FromSlot;

	return Task;
}

FGameplayAbilityTargetDataHandle UArcAbilityTask_DropItem::GenerateTargetHandle()
{
	FGameplayAbilityTargetData_DropItem* ItemSwitchData = new FGameplayAbilityTargetData_DropItem();
	ItemSwitchData->FromSlot = SlotReference;
	

	return FGameplayAbilityTargetDataHandle(ItemSwitchData);
}

void UArcAbilityTask_DropItem::HandleTargetData(const FGameplayAbilityTargetDataHandle& Data)
{
	const FGameplayAbilityTargetData_DropItem* SwitchData = static_cast<const FGameplayAbilityTargetData_DropItem*>(Data.Get(0));
	if (SwitchData != nullptr)
	{
		OnDataRecieved.Broadcast(SwitchData->FromSlot);
	}
	else
	{
		OnDataCancelled.Broadcast();
	}
}

void UArcAbilityTask_DropItem::HandleCancelled()
{
	OnDataCancelled.Broadcast();
}
