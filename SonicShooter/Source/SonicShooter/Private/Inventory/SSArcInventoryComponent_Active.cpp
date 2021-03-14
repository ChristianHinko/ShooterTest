// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSArcInventoryComponent_Active.h"

#include "ArcItemStack.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Input/ArcInvInputBinder.h"
#include "AbilitySystemGlobals.h"



USSArcInventoryComponent_Active::USSArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	maxItemHistoryBufferSize = 30;
}

bool USSArcInventoryComponent_Active::IsActiveItemSlotIndexValid(int32 InActiveItemSlot)
{
	if (InActiveItemSlot < 0)
	{
		return false;
	}
	if (InActiveItemSlot >= CachedActiveItemSlots.Num())
	{
		return false;
	}
	return true;
}

void USSArcInventoryComponent_Active::ClientRecieveStartingActiveItemHistoryArray_Implementation(const TArray<FArcInventoryItemSlotReference>& ServerActiveItemHistoryArr)
{
	ActiveItemHistory = ServerActiveItemHistoryArr;
	bStartupItemsGiven = true;	// Since this bool is not replicated we must set it now since we just rpced to the client
}


void USSArcInventoryComponent_Active::OnItemEquipped(class UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack)
{
	if (!bStartupItemsGiven)
	{
		AddToActiveItemHistory(ItemSlotRef);
	}

	// In our game we want items to auto set active whenever we equip an active item. However, if we havn't begun play yet, equiping an item will still work, just only with the most recent one before beginplay happens
	if (IsActiveItemSlot(ItemSlotRef) && IsValid(ItemStack))
	{
		int32 ItemSlotIndex = GetActiveItemIndexBySlotRef(ItemSlotRef);
		PendingItemSlot = ItemSlotIndex;

		//If we've begun play, send the gameplay event now.  Otherwise we'll get it in BeginPlay
		if (HasBegunPlay())
		{
			SwitchToPendingItemSlot();
		}
	}


	//If we are unequipping an item and it's the currently active item, either go to the next available active item or go to neutral
	if (!IsValid(ItemStack))
	{
		int32 ItemSlotIndex = GetActiveItemIndexBySlotRef(ItemSlotRef);
		if (ItemSlotIndex == ActiveItemSlot)
		{
			PendingItemSlot = GetNextValidActiveItemSlot();
			MakeItemInactive_Internal(ItemSlotRef, PreviousItemStack);
			SwitchToPendingItemSlot();
		}
	}
}

bool USSArcInventoryComponent_Active::MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack)
{
	bool bSuccess = Super::MakeItemActive_Internal(ItemSlot, ItemStack);

	if (bStartupItemsGiven)		// We don't want to touch the item history array if the startup items have not been given yet. Adding to it will be taken care of in OnItemEquipped
	{
		AddToActiveItemHistory(ItemSlot);
	}

	return bSuccess;
}

void USSArcInventoryComponent_Active::AddToActiveItemHistory(FArcInventoryItemSlotReference NewActiveItemSlotReference)
{
	int32 sizeChange = 0;

	if (ActiveItemHistory.RemoveSingle(NewActiveItemSlotReference) == 1)		// Remove the item from the history buffer so we can make it a new recent
	{
		sizeChange--;
	}
	ActiveItemHistory.Insert(NewActiveItemSlotReference, 0);						// Make item new recent
	++sizeChange;



	if (ActiveItemHistory.Num() > maxItemHistoryBufferSize)
	{
		ActiveItemHistory.RemoveAt(ActiveItemHistory.Num() - 1);						// Remove oldest stored item if we are passed the max buffer size
	}



}

bool USSArcInventoryComponent_Active::ApplyAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto, UArcItemStack* AbilitySource)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		//Setup the Item Info, duplicating attribute sets if we have to
		for (auto AttributeSetClass : AbilityInfo.AttributeSetsToAdd)
		{
			//Find an attribute set with the same key
			UAttributeSet** ContainedAttributeSet = StoreInto.InstancedAttributeSets.FindByPredicate([=](UAttributeSet* Key) {
				return Key->GetClass() == AttributeSetClass.Get();
				});
			if (ContainedAttributeSet != nullptr)	 //If it exists, we've got it!
			{
				continue;
			}



			//Otherwise, create a new one
			UAttributeSet* NewAttributeSet = NewObject<UAttributeSet>(GetOwner(), AttributeSetClass);

			//and init the attributes
			for (auto KV : AbilityInfo.AttributeInitalizers)
			{
				FGameplayAttribute Attribute = KV.Key;
				float val = KV.Value;

				if (Attribute.GetAttributeSetClass() == NewAttributeSet->GetClass())
				{
					if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(Attribute.GetUProperty()))
					{
						void* ValuePtr = NumericProperty->ContainerPtrToValuePtr<void>(NewAttributeSet);
						NumericProperty->SetFloatingPointPropertyValue(ValuePtr, val);
					}
					else if (FStructProperty* StructProperty = CastField<FStructProperty>(Attribute.GetUProperty()))
					{
						FGameplayAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(NewAttributeSet);
						if (DataPtr)
						{
							DataPtr->SetBaseValue(val);
							DataPtr->SetCurrentValue(val);
						}
					}
				}
			}

			//and then tell watchers that a new attribute set has been created
			OnAttributeSetCreated.Broadcast(this, NewAttributeSet, AbilitySource);

			StoreInto.InstancedAttributeSets.Add(NewAttributeSet);
		}
	}


	if (UAbilitySystemComponent* ASC = GetOwnerAbilitySystem())
	{
		//Add any loose tags first, that way any abilities or effects we add later behave properly with the tags  
		ASC->AddLooseGameplayTags(AbilityInfo.GrantedTags, 1);

		if (GetOwnerRole() == ROLE_Authority)
		{
			//Add any attribute sets we have
			for (UAttributeSet* AttributeSet : StoreInto.InstancedAttributeSets)
			{
				if (!UArcItemBPFunctionLibrary::ASCHasAttributeSet(ASC, AttributeSet->GetClass()))
				{
					AttributeSet->Rename(nullptr, GetOwner());
					UArcItemBPFunctionLibrary::ASCAddInstancedAttributeSet(ASC, AttributeSet);

				}
			}


			//Add all the active abilities for the ability slots we have
			for (auto AbilityInfoStruct : AbilityInfo.ActiveAbilityEntries)
			{
				TSubclassOf<UGameplayAbility> AbilityClass = AbilityInfoStruct.ActiveAbilityClass;
				UArcInvInputBinder* InputBinder = AbilityInfoStruct.InputBinder;
				if (!IsValid(AbilityClass) || !IsValid(InputBinder))
				{
					continue;
				}

				int32 InputIndex = InputBinder->GetInputBinding(ASC, AbilityClass);
				FGameplayAbilitySpec Spec(AbilityClass.GetDefaultObject(), 1, InputIndex, AbilitySource);


				FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
				StoreInto.AddedAbilities.Add(Handle);
			}
			//and add any extras we have
			for (auto ExtraAbility : AbilityInfo.ExtraAbilities)
			{
				//If an ability exists already, then don't bother adding it
				//if (ASC->FindAbilitySpecFromClass(ExtraAbility))
				//{
				//	continue;
				//}

				//=@MODIFIED MARKER@= also this class doesnt even override these functions
				if (FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(ExtraAbility))
				{
					if (Spec->SourceObject == AbilitySource)
					{
						continue;
					}
				}
				//=@OVERRIDED CODE MARKER@= what we modified in this override we use our grant ability instead of give ability
				FGameplayAbilitySpecHandle Handle = Cast<USSAbilitySystemComponent>(ASC)->GrantAbility(ExtraAbility, AbilitySource);
				//FGameplayAbilitySpec Spec(ExtraAbility.GetDefaultObject(), 1, INDEX_NONE, AbilitySource);

				//FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
				StoreInto.AddedAbilities.Add(Handle);
			}



			//Add any GameplayEffects we have
			for (auto EffectClass : AbilityInfo.AddedGameplayEffects)
			{
				for (auto& Handle : StoreInto.AddedGameplayEffects)
				{
					if (ASC->GetGameplayEffectDefForHandle(Handle) == EffectClass->GetDefaultObject<UGameplayEffect>())
					{
						continue;
					}
				}

				FGameplayEffectContextHandle ECH(UAbilitySystemGlobals::Get().AllocGameplayEffectContext());
				ECH.AddInstigator(GetOwner(), GetOwner());
				FGameplayEffectSpec Spec(EffectClass->GetDefaultObject<UGameplayEffect>(), ECH, 1);


				FActiveGameplayEffectHandle Handle = ASC->ApplyGameplayEffectSpecToSelf(Spec);
				//Store any non-instant handles we get.  Instant Gameplay Effects will fall off right away so we don't need to remove them later
				//Really, items shouldn't use instant GEs.
				if (Spec.Def->DurationPolicy != EGameplayEffectDurationType::Instant)
				{
					StoreInto.AddedGameplayEffects.Add(Handle);
				}
			}

			ASC->bIsNetDirty = true;
		}


	}

	return true;
}