// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Abilities/SSGameplayAbility_DropItem.h"

#include "Character/SSCharacter_Shooter.h"
#include "ArcInventoryComponent.h"
#include "Abilities/Tasks/ArcAbilityTask_DropItem.h"
#include "ArcInventoryItemTypes.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Inventory/SSInventoryComponent_Active.h"
#include "ArcItemStack.h"
#include "Item/ArcItemDefinition_New.h"
#include "ArcInventory.h"
#include "ArcItemBPFunctionLibrary.h"



USSGameplayAbility_DropItem::USSGameplayAbility_DropItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityInputID = ESSAbilityInputID::DropItem;
	AbilityTags.AddTag(FArcInvDropItemAbilityTag);	// ArcInventory's Tag (maybe we should just make our own so there isn't a gap in tags for our inventory system for our game tags)
}

void USSGameplayAbility_DropItem::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time
	if (!ActorInfo)
	{
		return;
	}

	ShooterCharacter = Cast<ASSCharacter_Shooter>(ActorInfo->AvatarActor);
	Inventory = UArcItemBPFunctionLibrary::GetInventoryComponent(ActorInfo->AvatarActor.Get(), true);
}

bool USSGameplayAbility_DropItem::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (ShooterCharacter.IsValid() == false)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ShooterCharacter was NULL. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	if (Inventory.IsValid() == false)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Inventory was NULL. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	// This ability doesn't currently support non active items. We can do something similer to what we did in the SSGameplayAbility_SwapActiveItem and make this an abstract ability and force BP subclasses and allow them to choose the drop method using an exposed enum or something (e.g. EDropMethod::ActiveItem or EDropMethod::SlotIndex)
	UArcInventoryComponent_Active* ActiveItemInventory = Cast<UArcInventoryComponent_Active>(Inventory);
	if (IsValid(ActiveItemInventory) == false)
	{
		return false;
	}
	FArcInventoryItemSlotReference ActiveItem = ActiveItemInventory->GetActiveItemSlot();
	if (ActiveItemInventory->IsValidActiveItemSlot(ActiveItem.SlotId) == false)
	{
		return false;
	}

	return true;
}

void USSGameplayAbility_DropItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UArcInventoryComponent_Active* ActiveItemInventory = Cast<UArcInventoryComponent_Active>(Inventory);
	if (IsValid(ActiveItemInventory) == false)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActiveItemInventory was NULL when activationg drop ability. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	UArcAbilityTask_DropItem* DropItemTask = UArcAbilityTask_DropItem::DropItemFromInventory(this, Inventory->PendingItemDrop);
	if (!DropItemTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() DropItemTask was NULL when trying to activate DropItem ability. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	DropItemTask->OnDataRecieved.AddDynamic(this, &USSGameplayAbility_DropItem::OnDataRecieved);
	DropItemTask->OnDataCancelled.AddDynamic(this, &USSGameplayAbility_DropItem::OnDataCancelled);

	ActiveItemInventory->PendingItemDrop = ActiveItemInventory->GetActiveItemSlot();
	DropItemTask->ReadyForActivation();
}


void USSGameplayAbility_DropItem::OnDataRecieved(const FArcInventoryItemSlotReference& FromSlot)
{
	RemovedItemStack = UArcItemBPFunctionLibrary::GetItemFromSlot(FromSlot);
	if (!RemovedItemStack.IsValid())
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s() RemovedItemStack was NULL when trying to spawn the removed item into the world. Spawning into the world without a valid stack D:"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	if (Inventory->RemoveItemFromInventory(FromSlot))
	{
		FTransform SpawnTransform = ShooterCharacter->GetActorTransform();
		SpawnTransform.SetLocation(SpawnTransform.GetLocation() + (ShooterCharacter->GetActorForwardVector() * 200));

		UArcItemBPFunctionLibrary::SpawnWorldItem(this, RemovedItemStack.Get(), SpawnTransform);
	}


	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void USSGameplayAbility_DropItem::OnDataCancelled()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}




void USSGameplayAbility_DropItem::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{

	Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
