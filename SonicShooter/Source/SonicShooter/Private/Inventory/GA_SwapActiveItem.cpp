// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/GA_SwapActiveItem.h"


#include "Character/ShooterCharacter.h"
#include "Components/ArcInventoryComponent_Active.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"

UGA_SwapActiveItem::UGA_SwapActiveItem()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Ability.ItemSwitch")));

	itemSlotIndexToSwitchTo = -1;
	ItemSlotTagToSwitchTo = FGameplayTag::EmptyTag;
}


void UGA_SwapActiveItem::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

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

	InventoryComponentActive = ShooterCharacter->InventoryComponentActive;
	if (!InventoryComponentActive)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InventoryComponentActive was NULL"), *FString(__FUNCTION__));
		return;
	}
}

bool UGA_SwapActiveItem::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
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

	if (!InventoryComponentActive)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InventoryComponentActive was NULL"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_SwapActiveItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	/////////////////////////////////////////////    we've passed the checks //////


	// Change the item
	PerformSwap();


	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}


void UGA_SwapActiveItem::PerformSwap()
{
	switch (SwapMethod)
	{
		case ESwapMethod::ByIndex:
			if (itemSlotIndexToSwitchTo <= -1)
			{
				UE_LOG(LogGameplayAbility, Warning, TEXT("%s() Can't switch to item index below 0 (none exist)"), *FString(__FUNCTION__));
				break;
			}
			InventoryComponentActive->SwapActiveItems(itemSlotIndexToSwitchTo);
			break;
		case ESwapMethod::ByTag:
			if (ItemSlotTagToSwitchTo.IsValid() || ItemSlotTagToSwitchTo == FGameplayTag::EmptyTag)
			{
				UE_LOG(LogGameplayAbility, Warning, TEXT("%s() Tag not valid when trying to switch to inventory slot with the tag"), *FString(__FUNCTION__));
				break;
			}
			InventoryComponentActive->SwapActiveItems(InventoryComponentActive->GetActiveItemIndexByTag(ItemSlotTagToSwitchTo));
			break;
		case ESwapMethod::NextItem:
			InventoryComponentActive->SwapActiveItems(InventoryComponentActive->GetNextActiveItemSlot());
			break;
		case ESwapMethod::PrecedingItem:
			InventoryComponentActive->SwapActiveItems(InventoryComponentActive->GetPreviousActiveItemSlot());
			break;
		case ESwapMethod::LastActiveItem:

			break;
		default:
			break;
	}
}


void UGA_SwapActiveItem::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Super wraps the whole EndAbility() in IsEndAbilityValid()
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	// Make sure we bind our child class' version of EndAbility() instead of using the Super's version of this part
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_SwapActiveItem::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
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
