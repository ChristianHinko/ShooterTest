// Copyright 2017-2020 Puny Human, All Rights Reserved.

#include "Abilities/Tasks/ArcAbilityTask_WaitItemSwitch.h"
#include "ArcInventory.h"
#include "Components/ArcInventoryComponent_Active.h"
#include "TimerManager.h"




UArcAbilityTask_WaitItemSwitch::UArcAbilityTask_WaitItemSwitch(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UArcAbilityTask_WaitItemSwitch* UArcAbilityTask_WaitItemSwitch::WaitActiveItemSwitch(UGameplayAbility* OwningAbility, int32 ItemIndex)
{
	UArcAbilityTask_WaitItemSwitch* Task = NewAbilityTask<UArcAbilityTask_WaitItemSwitch>(OwningAbility);
	Task->ItemIndex = ItemIndex;

	return Task;
}

void UArcAbilityTask_WaitItemSwitch::Activate()
{	 	
	//TODO: Animations here
	//for now, lets just wait a small amount of time and switch weapons

	AActor* Actor = GetAvatarActor();
	if (!IsValid(Actor))
	{
		return;
	}

	Inventory = UArcItemBPFunctionLibrary::GetActiveInventoryComponent(GetAvatarActor());
	if (!IsValid(Inventory))
	{
		return;
	}
	Inventory->bSwitchingWeapons = true;

	Inventory->MakeItemInactive();

	

	Actor->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UArcAbilityTask_WaitItemSwitch::DoItemEquip, .25f, false, .25f);


}

void UArcAbilityTask_WaitItemSwitch::BeginDestroy()
{
	if (IsValid(Inventory))
	{
		Inventory->bSwitchingWeapons = false;
	}

	Super::BeginDestroy();
}

void UArcAbilityTask_WaitItemSwitch::DoItemEquip()
{
	if (!IsValid(Inventory))
	{
		return;
	}

	Inventory->MakeItemActive(ItemIndex);
	Inventory->bSwitchingWeapons = false;

	OnItemSwitched.Broadcast();
}
