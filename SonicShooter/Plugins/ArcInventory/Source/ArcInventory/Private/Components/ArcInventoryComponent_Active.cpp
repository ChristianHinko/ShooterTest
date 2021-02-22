// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "Components/ArcInventoryComponent_Active.h"
#include "ArcItemStack.h"
#include "Interfaces/ArcHeldItemInterface.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"

#include "AbilitySystemGlobals.h"

#include "Net/UnrealNetwork.h"

//=@MODIFIED MARKER@=
#include "ArcItemBPFunctionLibrary.h"
#include "Input/ArcInvInputBinder.h"

UArcInventoryComponent_Active::UArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActiveItemSlot = INDEX_NONE;
	PendingItemSlot = INDEX_NONE;
}

void UArcInventoryComponent_Active::InitializeComponent()
{
	Super::InitializeComponent();


	UpdateActiveItemSlots(this);
	OnInventoryUpdate.AddDynamic(this, &UArcInventoryComponent_Active::UpdateActiveItemSlots);
}

void UArcInventoryComponent_Active::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UArcInventoryComponent_Active, ActiveItemSlot, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UArcInventoryComponent_Active, PendingItemSlot, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION(UArcInventoryComponent_Active, ActiveItemAbilityInfos, COND_OwnerOnly);
}

void UArcInventoryComponent_Active::BeginPlay()
{
	//Make sure we have nothing stored when we begin play.  We want to have a clean start to this active slot if we reset
	int32 OldActiveItem = ActiveItemSlot;
	MakeItemInactive();
	ActiveItemSlot = OldActiveItem;

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
	{
		//Check to see if we have an active item in our first slot and set it to that to start with  
		if (PendingItemSlot != INDEX_NONE)
		{
			this->SwitchToPendingItemSlot();
		}
		//Sometimes, on the client, we get the initial ActiveItemSlot before we've begun play
		//In that case, PendingItemSlot would be none, and we have a valid ActiveItemSlot that hasn't been made active yet
		//So we'll do it here.
		else if (ActiveItemSlot != INDEX_NONE && GetOwnerRole() != ROLE_Authority)
		{
			this->MakeItemActive(ActiveItemSlot);
		}
	});

	Super::BeginPlay();
}

void UArcInventoryComponent_Active::OnItemEquipped(class UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack)
{
	//If we are an active item slot, make it active if we don't already have an active item		
	if (ActiveItemSlot == INDEX_NONE && IsActiveItemSlot(ItemSlotRef) && IsValid(ItemStack))
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

FArcInventoryItemSlotReference UArcInventoryComponent_Active::GetActiveItemSlot()
{
	return GetActiveItemSlotInSlot(ActiveItemSlot);
}

UArcItemStack* UArcInventoryComponent_Active::GetActiveItemStack()
{
	return GetActiveItemStackInSlot(ActiveItemSlot);
}

FArcInventoryItemSlotReference UArcInventoryComponent_Active::GetActiveItemSlotInSlot(int32 InActiveItemSlot)
{
	if (InActiveItemSlot == INDEX_NONE)
	{
		return FArcInventoryItemSlotReference();
	}

	FArcInventoryItemSlotReference ItemSlotRef = CachedActiveItemSlots[InActiveItemSlot];
	return ItemSlotRef;
}

UArcItemStack* UArcInventoryComponent_Active::GetActiveItemStackInSlot(int32 InActiveItemSlot)
{
	FArcInventoryItemSlotReference ItemSlotRef = GetActiveItemSlotInSlot(InActiveItemSlot);
	return GetItemInSlot(ItemSlotRef);
}

bool UArcInventoryComponent_Active::IsValidActiveItemSlot(int32 InActiveItemSlot)
{
	//Do we have a valid index?
	if (InActiveItemSlot < 0)
	{
		return false;
	}
	if (InActiveItemSlot >= CachedActiveItemSlots.Num())
	{
		return false;
	}

	//Is the index a valid item?
	UArcItemStack* ItemStack = GetActiveItemStackInSlot(InActiveItemSlot);
	if (!IsValid(ItemStack))
	{
		return false;
	}

	return true;
}

void UArcInventoryComponent_Active::OnRep_ActiveItemSlot(int32 PreviousItemSlot)
{
	//If we haven't begun play yet, we'll do this on BeginPlay
	//Otherwise, do it as soon as we get the item slot change from the server
	if (HasBegunPlay())
	{
		if (ActiveItemSlot != PreviousItemSlot)
		{
			if (PreviousItemSlot != INDEX_NONE)
			{
				MakeItemInactive_Internal(GetActiveItemSlotInSlot(PreviousItemSlot));
			}
			if (ActiveItemSlot != INDEX_NONE)
			{
				MakeItemActive(ActiveItemSlot);
			}
		}
	}
}

void UArcInventoryComponent_Active::OnRep_PendingItemSlot(int32 PreviousItemSlot)
{

}

int32 UArcInventoryComponent_Active::GetNextActiveItemSlot() const
{
	return GetNextItemSlotFrom(ActiveItemSlot);
}

int32 UArcInventoryComponent_Active::GetPreviousActiveItemSlot() const
{
	return GetPreviousItemSlotFrom(ActiveItemSlot);
}

int32 UArcInventoryComponent_Active::GetNextValidActiveItemSlot() 
{
	int32 TestItemSlot = GetNextActiveItemSlot();

	while (TestItemSlot != ActiveItemSlot)
	{
		if (CachedActiveItemSlots.IsValidIndex(TestItemSlot))
		{
			FArcInventoryItemSlotReference ItemSlotRef = CachedActiveItemSlots[TestItemSlot];

			if (IsValid(GetItemInSlot(ItemSlotRef)))
			{
				return TestItemSlot;
			}
		}

		TestItemSlot = GetNextItemSlotFrom(TestItemSlot);
	}
	
	return INDEX_NONE;
	
}

int32 UArcInventoryComponent_Active::GetPreviousValidActiveItemSlot()
{
	int32 TestItemSlot = GetPreviousActiveItemSlot();

	while (TestItemSlot != ActiveItemSlot)
	{
		if (CachedActiveItemSlots.IsValidIndex(TestItemSlot))
		{
			FArcInventoryItemSlotReference ItemSlotRef = CachedActiveItemSlots[TestItemSlot];

			if (IsValid(GetItemInSlot(ItemSlotRef)))
			{
				return TestItemSlot;
			}
		}

		TestItemSlot = GetPreviousItemSlotFrom(TestItemSlot);
	}

	return INDEX_NONE;
}

int32 UArcInventoryComponent_Active::GetNextItemSlotFrom(int32 InActiveItemSlot) const
{
	int32 NextItemSlot = InActiveItemSlot + 1;
	if (NextItemSlot >= CachedActiveItemSlots.Num())
	{
		NextItemSlot = 0;
	}

	return NextItemSlot;
}

int32 UArcInventoryComponent_Active::GetPreviousItemSlotFrom(int32 InActiveItemSlot) const
{
	int32 PreviousItemSlot = InActiveItemSlot - 1;
	if (PreviousItemSlot < 0)
	{
		PreviousItemSlot = CachedActiveItemSlots.Num() - 1;
	}

	return PreviousItemSlot;
}

void UArcInventoryComponent_Active::MakeItemInactive()
{
	MakeItemInactive_Internal(GetActiveItemSlot());

	//If we are not actively switching weapons, set the active itemslot to none
	//bSwitchingWeapons is true when the item switch task is doing the switching, and we expect that a new item will become active
	if (/*GetOwnerRole() == ROLE_Authority &&*/ !bSwitchingWeapons)
	{
		ActiveItemSlot = INDEX_NONE;
	}
}

void UArcInventoryComponent_Active::MakeItemActive(int32 NewActiveItemSlot)
{
	if (NewActiveItemSlot == INDEX_NONE)
	{
		return;
	}

	if (!ensure(CachedActiveItemSlots.IsValidIndex(NewActiveItemSlot)))
	{
		return;
	}

	FArcInventoryItemSlotReference ItemSlotRef = CachedActiveItemSlots[NewActiveItemSlot];

	

	if (!MakeItemActive_Internal(ItemSlotRef))
	{
		if (IsValid(GetItemInSlot(ItemSlotRef)))
		{
			//If we fail to make the new item active and we have a valid item, then set the active slot to none
			//Swaping to an active item slot without a valid item is a valid action.  Any other failure, reset to INDEX_NONE
			NewActiveItemSlot = INDEX_NONE;
		}		
	}

	//If we are not actively switching weapons, set the active itemslot to none
	//bSwitchingWeapons is true when the item switch task is doing the switching, and we expect that a new item will become active	
	//if (GetOwnerRole() == ROLE_Authority)
	{
		ActiveItemSlot = NewActiveItemSlot;
	}
}

void UArcInventoryComponent_Active::MakeItemActive(const FArcInventoryItemSlotReference& ItemSlotRef)
{
	int32 Slot = GetActiveItemIndexBySlotRef(ItemSlotRef);
	MakeItemActive(Slot);
}

bool UArcInventoryComponent_Active::IsActiveItemSlot(const FArcInventoryItemSlotReference& ItemSlotRef) const
{
	FGameplayTag ActiveSlotTag = GetDefault<UArcInventoryDeveloperSettings>()->ActiveItemSlotTag;
	return ItemSlotRef.SlotTags.HasTagExact(ActiveSlotTag);
}

int32 UArcInventoryComponent_Active::GetActiveItemIndexBySlotRef(const FArcInventoryItemSlotReference& ItemSlotRef)
{
	int32 SlotIndex = INDEX_NONE;
	CachedActiveItemSlots.Find(ItemSlotRef, SlotIndex);

	return SlotIndex;
}

int32 UArcInventoryComponent_Active::GetActiveItemIndexByTag(FGameplayTag Tag)
{
	FArcInventoryItemSlotReference Ref = Query_GetFirstSlot(FArcInventoryQuery::QuerySlotMatchingTag(Tag));
	return GetActiveItemIndexBySlotRef(Ref);
}

void UArcInventoryComponent_Active::SwitchToPendingItemSlot()
{
	//If we have an Ability System Component on this actor, lets send a gameplay event to allow a GameplayAbility handle the item switching.
	//This will handle animations and timing and all the important bits.
	bool bActivatedAbility = false;
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::Get().GetAbilitySystemComponentFromActor(GetOwner()))
	{
		FGameplayTag SwitchWeaponsAbilityTag = FGameplayTag::RequestGameplayTag(TEXT("Ability.ItemSwitch.Pending"), false);
		if (SwitchWeaponsAbilityTag.IsValid())
		{
			bActivatedAbility = ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(SwitchWeaponsAbilityTag));
		}		
	}

	if (!bActivatedAbility)//Otherwise just quickly switch the item
	{
		MakeItemInactive();
		MakeItemActive(PendingItemSlot);		
	}

	PendingItemSlot = INDEX_NONE;
}

void UArcInventoryComponent_Active::UpdateActiveItemSlots(UArcInventoryComponent* InventoryComp)
{

	//Cache the Active Item Slots
	FGameplayTag ActiveSlotTag = GetDefault<UArcInventoryDeveloperSettings>()->ActiveItemSlotTag;

	CachedActiveItemSlots.Empty(CachedActiveItemSlots.Num());
	Query_GetAllSlots(FArcInventoryQuery::QuerySlotMatchingTag(ActiveSlotTag), CachedActiveItemSlots);
}

void UArcInventoryComponent_Active::SwapActiveItems(int32 NewItemSlot)
{
	bSwitchingWeapons = true;

	//=@MODIFIED MARKER@=
	pendingSwapIndex = NewItemSlot;

	MakeItemInactive();
	MakeItemActive(NewItemSlot);
	bSwitchingWeapons = false;
}

int32 UArcInventoryComponent_Active::GetIndexForActiveItemSlotTagQuery(const FGameplayTagQuery& TagQuery)
{
	for (int32 i = 0; i < CachedActiveItemSlots.Num(); i++)
	{
		if (TagQuery.Matches(CachedActiveItemSlots[i].SlotTags))
		{
			return i;
		}
	}

	return INDEX_NONE;
}



bool UArcInventoryComponent_Active::MakeItemInactive_Internal(const FArcInventoryItemSlotReference& ItemSlot)
{
	if (!IsActiveItemSlot(ItemSlot))
	{
		return false;
	}

	UArcItemStack* ItemStack = GetItemInSlot(ItemSlot);

	return MakeItemInactive_Internal(ItemSlot, ItemStack);
}

bool UArcInventoryComponent_Active::MakeItemInactive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack)
{
	if (!IsValid(ItemStack))
	{
		//If we have a valid item slot, but no valid item stack, lets just call the OnItemInactive event because we have nothing to remove.
		//This is most likely to happen on the client when an item has already been to removed from the slot but we are trying to do the client side removal
		if (IsValid(ItemSlot))
		{
			OnItemInactive.Broadcast(this, ItemStack);
		}
		return false;
	}

	TSubclassOf<UArcItemDefinition_Active> ItemDefinition(ItemStack->GetItemDefinition());
	if (!IsValid(ItemDefinition))
	{
		return false;
	}

	FArcInventoryItemInfoEntry* Entry = ActiveItemAbilityInfos.FindByPredicate([ItemSlot](const FArcInventoryItemInfoEntry& x) {
		return x.ItemSlotRef.SlotId == ItemSlot.SlotId;
	});
	if (Entry == nullptr)
	{
		return false;
	}

	RemovePerks(ItemStack, ItemSlot);
	bool bSuccess = ClearAbilityInfo_Internal(ItemDefinition.GetDefaultObject()->ActiveItemAbilityInfo, (*Entry).EquippedItemInfo);
		

	OnItemInactive.Broadcast(this, ItemStack);

	return bSuccess;
}

bool UArcInventoryComponent_Active::MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot)
{
	if (!IsActiveItemSlot(ItemSlot))
	{
		return false;
	}

	UArcItemStack* ItemStack = GetItemInSlot(ItemSlot);

	if (!IsValid(ItemStack))
	{
		return false;
	}

	return MakeItemActive_Internal(ItemSlot, ItemStack);
}

bool UArcInventoryComponent_Active::MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack)
{
	if (!IsValid(ItemStack))
	{
		return false;
	}

	TSubclassOf<UArcItemDefinition_Active> ItemDefinition(ItemStack->GetItemDefinition());
	if (!IsValid(ItemDefinition))
	{
		return false;
	}

	FArcInventoryItemInfoEntry* Entry = ActiveItemAbilityInfos.FindByPredicate([ItemSlot](const FArcInventoryItemInfoEntry& x) {
		return x.ItemSlotRef.SlotId == ItemSlot.SlotId;
	});
	if (Entry == nullptr)
	{
		Entry = &ActiveItemAbilityInfos.Add_GetRef(FArcInventoryItemInfoEntry(ItemSlot));
	}

	//Add this item's Active Abilities
	bool bSuccess = ApplyAbilityInfo_Internal(ItemDefinition.GetDefaultObject()->ActiveItemAbilityInfo, (*Entry).EquippedItemInfo, ItemStack);

	if (bSuccess)
	{
		ApplyPerks(ItemStack, ItemSlot);		
	}

	OnItemActive.Broadcast(this, ItemStack);

	return bSuccess;
}


bool UArcInventoryComponent_Active::ApplyAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto, UArcItemStack* AbilitySource)
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
				if (ASC->GetActivatableAbilities().ContainsByPredicate([&AbilitySource](const FGameplayAbilitySpec& Spec)
					{ return Spec.SourceObject == AbilitySource; }))
				{
					continue;
				}


				FGameplayAbilitySpec Spec(ExtraAbility.GetDefaultObject(), 1, INDEX_NONE, AbilitySource);

				FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
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

bool UArcInventoryComponent_Active::ClearAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto)
{
	//Remove any abilities this item adds

	if (UAbilitySystemComponent* ASC = GetOwnerAbilitySystem())
	{
		if (GetOwnerRole() == ROLE_Authority)
		{
			//Remove all of the gameplay effects
			{
				for (auto Handle : StoreInto.AddedGameplayEffects)
				{
					ASC->RemoveActiveGameplayEffect(Handle);
				}
			}

			//Remove all the abilities we added
			{
				UArcItemStack* ActiveItem = GetItemInSlot(GetActiveItemSlot());

				for (int32 i = 0; i < StoreInto.AddedAbilities.Num(); ++i) //=@MODIFIED MARKER@=
				{
					FGameplayAbilitySpecHandle Handle = StoreInto.AddedAbilities[i];

					//=@MODIFIED MARKER@=
					bool bDontClear = false;
					for (FGameplayAbilitySpec Spec : ASC->GetActivatableAbilities())
					{
						if (bSwitchingWeapons)
						{
							if (Spec.SourceObject == GetItemInSlot(GetActiveItemSlotInSlot(pendingSwapIndex)))
							{
								bDontClear = true;
							}
						}
					}
					if (bDontClear)
					{
						continue;
					}

					ASC->CancelAbilityHandle(Handle);
					ASC->ClearAbility(Handle);

					//=@MODIFIED MARKER@=
					StoreInto.AddedAbilities.Remove(Handle);
					--i;
				}
				//StoreInto.AddedAbilities.Empty();
			}

			//Remove Attribute Sets			
			for (UAttributeSet* AttributeSet : StoreInto.InstancedAttributeSets)
			{
				UArcItemBPFunctionLibrary::ASCRemoveInstancedAttributeSet(ASC, AttributeSet);
			}

		}

		//Remove any extra granted tags from the player				
		ASC->RemoveLooseGameplayTags(AbilityInfo.GrantedTags);
	}


	return true;
}
