// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Abilities/GA_DropItem.h"

#include "Utilities/LogCategories.h"
#include "Character/ShooterCharacter.h"
#include "ArcInventoryComponent.h"
#include "Abilities\Tasks\ArcAbilityTask_DropItem.h"
#include "ArcInventoryItemTypes.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "ArcItemStack.h"
#include "Inventory\SSArcItemBPFunctionLibrary.h"
#include "Item/ArcItemDefinition_New.h"

UGA_DropItem::UGA_DropItem()
{
	AbilityInputID = EAbilityInputID::DropItem;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Inventory.DropItem")));
}

void UGA_DropItem::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	TryCallOnAvatarSetOnPrimaryInstance
	// Good place to cache references so we don't have to cast every time. If this event gets called too early from a GiveAbiliy(), AvatarActor will be messed up and some reason and this gets called 3 times
	if (!ActorInfo)
	{
		return;
	}
	if (!ActorInfo->AvatarActor.Get())
	{
		return;
	}


	ShooterCharacter = Cast<AShooterCharacter>(ActorInfo->AvatarActor.Get());
	if (!ShooterCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ShooterCharacter was NULL"), *FString(__FUNCTION__));
		return;
	}

	IArcInventoryInterface* InventoryInterface = Cast<IArcInventoryInterface>(ShooterCharacter);
	if (!InventoryInterface)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Cast to InventoryInterface failed"), *FString(__FUNCTION__));
		return;
	}
	Inventory = InventoryInterface->GetInventoryComponent();
}

bool UGA_DropItem::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	// Returning false in here for checks is better than doing checks in ActivateAbility() since returning false triggers a rollback on the client if Server returns false. In our previous method we called EndAbility() inside ActivateAbility() if a check didn't pass, which doesn't even cancel it on the remote machine if client since bRespectsRemoteAbilityToCancel most of the time will be false.
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!ShooterCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ShooterCharacter was NULL. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!Inventory)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Inventory was NULL. Returned false"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_DropItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	/////////////////////////////////////////////    we've passed the checks //////
	UArcAbilityTask_DropItem* DropItemTask = UArcAbilityTask_DropItem::DropItemFromInventory(this, Inventory->PendingItemDrop);
	if (!DropItemTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() DropItemTask was NULL when trying to activate DropItem ability. Called EndAbility()"), *FString(__FUNCTION__));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	DropItemTask->OnDataRecieved.AddDynamic(this, &UGA_DropItem::OnDataRecieved);
	DropItemTask->OnDataCancelled.AddDynamic(this, &UGA_DropItem::OnDataCancelled);

	DropItemTask->ReadyForActivation();
}

void UGA_DropItem::OnDataRecieved(const FArcInventoryItemSlotReference& FromSlot)
{
	RemovedItemStack = UArcItemBPFunctionLibrary::GetItemFromSlot(FromSlot);
	if (!RemovedItemStack)
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s() RemovedItemStack was NULL when trying to spawn the removed item into the world. Spawning into the world without a valid stack D:"), *FString(__FUNCTION__));
	}
	if (Inventory->RemoveItemFromInventory(FromSlot))
	{
		FTransform SpawnTransform = ShooterCharacter->GetActorTransform();
		SpawnTransform.SetLocation(SpawnTransform.GetLocation() + ShooterCharacter->GetActorForwardVector() * 200);

		USSArcItemBPFunctionLibrary::SpawnWorldItem(this, RemovedItemStack, SpawnTransform, RemovedItemStack->GetItemDefinition().GetDefaultObject()->WorldItemActor);
	}
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_DropItem::OnDataCancelled()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}




void UGA_DropItem::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Super wraps the whole EndAbility() in IsEndAbilityValid()
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	// Make sure we bind our child class' version of EndAbility() instead of using the Super's version of this part
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_DropItem::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}










	//Now call the Super to finish ending the ability.
	/*
		IMPORTANT: If part of your gameplay logic in EndAbility() uses an async task, make sure you wait until the task is completed before you call Super::EndAbility.
		Otherwise the task may not complete. Call Super::EndAbility inside the task's OnComplete delegate.
	*/
	// super end ability loops through all tasks and calls OnDestroy; however, this is a virtual function, some tasks may not be destroyed on end ability (this is probably a super rare case tho) (dan says WaitTargetData doesn't end)
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

