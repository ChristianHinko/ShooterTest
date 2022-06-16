// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Abilities/SSGameplayAbility_SwapActiveItem.h"

#include "Character/SSCharacter_Shooter.h"
#include "Inventory/SSInventoryComponent_Active.h"
#include "ArcItemBPFunctionLibrary.h"



USSGameplayAbility_SwapActiveItem::USSGameplayAbility_SwapActiveItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemSlotIndexToSwitchTo = INDEX_NONE;
	ItemSlotTagQueryForSwitching = FGameplayTagQuery::EmptyQuery;
}


void USSGameplayAbility_SwapActiveItem::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time
	if (!ActorInfo)
	{
		return;
	}

	ShooterCharacter = Cast<ASSCharacter_Shooter>(ActorInfo->AvatarActor);
	InventoryComponent = Cast<USSInventoryComponent_Active>(UArcItemBPFunctionLibrary::GetInventoryComponent(ActorInfo->AvatarActor.Get(), true));
}

bool USSGameplayAbility_SwapActiveItem::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
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

void USSGameplayAbility_SwapActiveItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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


void USSGameplayAbility_SwapActiveItem::PerformSwap()
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	TArray<FArcInventoryItemSlotReference> SlotsWithMatchingQuery;	// If size of this is > 1 we will be told (because that might mean we incorrectly filled out a tag query in the editor)
#endif // !(UE_BUILD_SHIPPING || UE_BUILD_TEST)


	switch (SlotSwapMethod)
	{
	case ESSSlotSwapMethod::ByIndex:
	{
		if (InventoryComponent->IsActiveItemSlotIndexValid(ItemSlotIndexToSwitchTo) == false)
		{
			UE_LOG(LogGameplayAbility, Warning, TEXT("%s() No valid index to switch to"), ANSI_TO_TCHAR(__FUNCTION__));
			break;
		}
		InventoryComponent->SwapActiveItems(ItemSlotIndexToSwitchTo);
		break;
	}
	case ESSSlotSwapMethod::ByTagQuery:
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
	case ESSSlotSwapMethod::Forward:
	{
		// We are not totaly sure what is the right way to swap to next and previous item slots for active items, but from what we've been reading, it seams active item slots maintain order so we're going with this until we notice something unexpected happens
		InventoryComponent->SwapActiveItems(InventoryComponent->GetNextActiveItemSlot());
		break;
	}
	case ESSSlotSwapMethod::Backward:
	{
		// We are not totaly sure what is the right way to swap to next and previous item slots for active items, but from what we've been reading, it seams active item slots maintain order so we're going with this until we notice something unexpected happens
		InventoryComponent->SwapActiveItems(InventoryComponent->GetPreviousActiveItemSlot());
		break;
	}
	case ESSSlotSwapMethod::ByItemHistory:
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


void USSGameplayAbility_SwapActiveItem::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{

	Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
