// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Abilities/GA_SwapActiveItem.h"

#include "Character/C_Shooter.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "ArcItemBPFunctionLibrary.h"



UGA_SwapActiveItem::UGA_SwapActiveItem()
{
	ItemSlotIndexToSwitchTo = INDEX_NONE;
	ItemSlotTagQueryForSwitching = FGameplayTagQuery::EmptyQuery;
}


void UGA_SwapActiveItem::OnAvatarSetThatWorks(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSetThatWorks(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time
	if (!ActorInfo)
	{
		return;
	}

	ShooterCharacter = Cast<AC_Shooter>(ActorInfo->AvatarActor);
	InventoryComponent = Cast<USSArcInventoryComponent_Active>(UArcItemBPFunctionLibrary::GetInventoryComponent(ActorInfo->AvatarActor.Get(), true));
}

bool UGA_SwapActiveItem::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	// Returning false in here for checks is better than doing checks in ActivateAbility() since returning false triggers a rollback on the client if Server returns false. In our previous method we called EndAbility() inside ActivateAbility() if a check didn't pass, which doesn't even cancel it on the remote machine if client since bRespectsRemoteAbilityToCancel most of the time will be false.
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!ShooterCharacter.IsValid())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ShooterCharacter was NULL. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (!InventoryComponent.IsValid())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InventoryComponent was NULL"), ANSI_TO_TCHAR(__FUNCTION__));
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
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	TArray<FArcInventoryItemSlotReference> SlotsWithMatchingQuery;	// If size of this is > 1 we will be told (because that might mean we incorrectly filled out a tag query in the editor)
#endif // !(UE_BUILD_SHIPPING || UE_BUILD_TEST)


	switch (SlotSwapMethod)
	{
	case ESlotSwapMethod::ByIndex:
	{
		if (InventoryComponent->IsActiveItemSlotIndexValid(ItemSlotIndexToSwitchTo) == false)
		{
			UE_LOG(LogGameplayAbility, Warning, TEXT("%s() No valid index to switch to"), ANSI_TO_TCHAR(__FUNCTION__));
			break;
		}
		InventoryComponent->SwapActiveItems(ItemSlotIndexToSwitchTo);
		break;
	}
	case ESlotSwapMethod::ByTagQuery:
	{
		if (ItemSlotTagQueryForSwitching.IsEmpty())
		{
			UE_LOG(LogGameplayAbility, Warning, TEXT("%s() ItemSlotTagQueryForSwitching empty when trying to switch to inventory slot with the matching query"), ANSI_TO_TCHAR(__FUNCTION__));
			break;
		}
		InventoryComponent->SwapActiveItems(InventoryComponent->GetIndexForActiveItemSlotTagQuery(ItemSlotTagQueryForSwitching));

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		InventoryComponent->Query_GetAllSlots(FArcInventoryQuery::QueryForSlot(ItemSlotTagQueryForSwitching), SlotsWithMatchingQuery);

		if (SlotsWithMatchingQuery.Num() > 1)
		{
			UE_LOG(LogGameplayAbility, Warning, TEXT("%s() More than one slot matched the tag query when switching. Ambiguous which one is wanted (check to make sure you made your query how you wanted it). Making active the first match"), ANSI_TO_TCHAR(__FUNCTION__));
		}
#endif // !(UE_BUILD_SHIPPING || UE_BUILD_TEST)

		break;
	}
	case ESlotSwapMethod::Forward:
	{
		// We are not totaly sure what is the right way to swap to next and previous item slots for active items, but from what we've been reading, it seams active item slots maintain order so we're going with this until we notice something unexpected happens
		InventoryComponent->SwapActiveItems(InventoryComponent->GetNextActiveItemSlot());
		break;
	}
	case ESlotSwapMethod::Backward:
	{
		// We are not totaly sure what is the right way to swap to next and previous item slots for active items, but from what we've been reading, it seams active item slots maintain order so we're going with this until we notice something unexpected happens
		InventoryComponent->SwapActiveItems(InventoryComponent->GetPreviousActiveItemSlot());
		break;
	}
	case ESlotSwapMethod::ByItemHistory:
	{
		if (InventoryComponent->ActiveItemHistory.IsValidIndex(ItemHistoryIndex) == false)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() No valid index to switch to"), ANSI_TO_TCHAR(__FUNCTION__));
			break;
		}

		InventoryComponent->SwapActiveItems(InventoryComponent->ActiveItemHistory[ItemHistoryIndex].SlotId);
		break;
	}
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
