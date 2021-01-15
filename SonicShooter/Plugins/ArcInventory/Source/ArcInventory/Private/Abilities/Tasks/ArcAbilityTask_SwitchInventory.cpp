// Copyright 2017-2020 Puny Human, All Rights Reserved.

#include "Abilities/Tasks/ArcAbilityTask_SwitchInventory.h"
#include "ArcInventory.h"




UArcAbilityTask_SwitchInventory::UArcAbilityTask_SwitchInventory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UArcAbilityTask_SwitchInventory* UArcAbilityTask_SwitchInventory::SwitchInventorySlots(UGameplayAbility* OwningAbility, const FArcInventoryItemSlotReference& FromSlot, const FArcInventoryItemSlotReference& ToSlot)
{
	UArcAbilityTask_SwitchInventory* Task = NewAbilityTask<UArcAbilityTask_SwitchInventory>(OwningAbility);
	Task->FromSlot = FromSlot;
	Task->ToSlot = ToSlot;

	return Task;
} 	   

FGameplayAbilityTargetDataHandle UArcAbilityTask_SwitchInventory::GenerateTargetHandle()
{
	FGameplayAbilityTargetData_ItemSwitch* ItemSwitchData = new FGameplayAbilityTargetData_ItemSwitch();
	ItemSwitchData->FromSlot = FromSlot;
	ItemSwitchData->ToSlot = ToSlot;

	return FGameplayAbilityTargetDataHandle(ItemSwitchData);
}

void UArcAbilityTask_SwitchInventory::HandleTargetData(const FGameplayAbilityTargetDataHandle& Data)
{
	const FGameplayAbilityTargetData_ItemSwitch* SwitchData = static_cast<const FGameplayAbilityTargetData_ItemSwitch*>(Data.Get(0));
	if (SwitchData != nullptr)
	{
		OnSlotsRecieved.Broadcast(SwitchData->FromSlot, SwitchData->ToSlot);
	}
	else
	{
		OnSlotsCancelled.Broadcast();
	}
}

void UArcAbilityTask_SwitchInventory::HandleCancelled()
{
	OnSlotsCancelled.Broadcast();
}

bool FGameplayAbilityTargetData_ItemSwitch::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	bOutSuccess = true;
	FromSlot.NetSerialize(Ar, Map, bOutSuccess);
	ToSlot.NetSerialize(Ar, Map, bOutSuccess);

	return true;
}
