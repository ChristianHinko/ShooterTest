// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "Components/ArcInventoryComponent_Equippable.h"
#include "ArcItemStack.h"
#include "Perks/ArcItemStack_Perk.h"
#include "ArcItemBPFunctionLibrary.h"

#include "Input/ArcInvInputBinder.h"
#include "Item/Definitions//ArcItemDefinition_Equipment.h"

#include "AbilitySystemGlobals.h"

#include "Net/UnrealNetwork.h"

UArcInventoryComponent_Equippable::UArcInventoryComponent_Equippable(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UArcInventoryComponent_Equippable::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetOwner()->GetLocalRole() == ROLE_Authority)
	{
		OnItemSlotChange.AddDynamic(this, &UArcInventoryComponent_Equippable::OnItemEquipped);
	}
}

void UArcInventoryComponent_Equippable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(UArcInventoryComponent_Equippable, EquippedItemAbilityInfos, COND_OwnerOnly);
}

void UArcInventoryComponent_Equippable::OnItemEquipped(class UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack)
{
	if (IsValid(PreviousItemStack) && IsEquippedItemSlot(ItemSlotRef))
	{
		MakeItemUnequipped_Internal(ItemSlotRef, PreviousItemStack);
	}
	if (IsValid(ItemStack) && IsEquippedItemSlot(ItemSlotRef))
	{
		MakeItemEquipped_Internal(ItemSlotRef, ItemStack);	
	}
	
}

bool UArcInventoryComponent_Equippable::IsEquippedItemSlot(const FArcInventoryItemSlotReference& ItemSlotRef)
{
	if (!ItemSlotRef.SlotTags.HasTagExact(FArcInvEquipSlotTag))
	{
		return false;
	}
	return true;
}

bool UArcInventoryComponent_Equippable::MakeItemEquipped_Internal(const FArcInventoryItemSlotReference& ItemSlot)
{
	if (!IsValidItemSlot(ItemSlot))
	{
		return false;
	}
	UArcItemStack* ItemStack = GetItemInSlot(ItemSlot);

	return MakeItemEquipped_Internal(ItemSlot, ItemStack);
}

bool UArcInventoryComponent_Equippable::MakeItemEquipped_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack)
{
	if (!IsValid(ItemStack))
	{
		return false;
	}
	
	TSubclassOf<UArcItemDefinition_Equipment> ItemDefinition(ItemStack->GetItemDefinition());
	if (!IsValid(ItemDefinition))
	{
		return false;
	}

	FArcInventoryItemInfoEntry* Entry = EquippedItemAbilityInfos.FindByPredicate([ItemSlot](FArcInventoryItemInfoEntry& x) {
		return x.ItemSlotRef.SlotId == ItemSlot.SlotId;
	});
	if (Entry == nullptr)
	{
		Entry = &EquippedItemAbilityInfos.Add_GetRef(FArcInventoryItemInfoEntry(ItemSlot));
	}

	bool bSuccess = ApplyAbilityInfo_Internal(ItemDefinition.GetDefaultObject()->EquippedItemAbilityInfo, (*Entry).EquippedItemInfo, ItemStack);

	if (bSuccess)
	{
		//Apply this item's modifiers
		ApplyPerks(ItemStack, ItemSlot);

		OnEquippedItem.Broadcast(this, ItemSlot, ItemStack);
	}

	//if there are any post-equip things to do aside from apply abilities, do them here.
	return 	bSuccess;
}

bool UArcInventoryComponent_Equippable::MakeItemUnequipped_Internal(const FArcInventoryItemSlotReference& ItemSlot)
{
	if (!IsValidItemSlot(ItemSlot))
	{
		return false;
	}
	UArcItemStack* ItemStack = GetItemInSlot(ItemSlot);

	return MakeItemUnequipped_Internal(ItemSlot, ItemStack);
}

bool UArcInventoryComponent_Equippable::MakeItemUnequipped_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack)
{
	//Ensure we have valid data for this item
	if (!IsValid(ItemStack))
	{
		return false;
	}

	TSubclassOf<UArcItemDefinition_Equipment> ItemDefinition(ItemStack->GetItemDefinition());
	if (!IsValid(ItemDefinition))
	{
		return false;
	}

	FArcInventoryItemInfoEntry* Entry = EquippedItemAbilityInfos.FindByPredicate([ItemSlot](FArcInventoryItemInfoEntry& x) {
		return x.ItemSlotRef.SlotId == ItemSlot.SlotId;
	});
	if (Entry == nullptr)
	{
		return false;
	}


	RemovePerks(ItemStack, ItemSlot);
	//Clear the active ability info
	bool bSuccess = ClearAbilityInfo_Internal(ItemDefinition.GetDefaultObject()->EquippedItemAbilityInfo, (*Entry).EquippedItemInfo);

	//IF there is more that needs to be done aside from ability info, put it here
	if (bSuccess)
	{
		OnUnEquippedItem.Broadcast(this, ItemSlot, ItemStack);
	}

	return 	bSuccess;
}

bool UArcInventoryComponent_Equippable::ApplyAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto, UArcItemStack* AbilitySource)
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
				FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromClass(ExtraAbility);
				if (AbilitySpec != nullptr && !(!!AbilitySpec->PendingRemove))
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

bool UArcInventoryComponent_Equippable::ClearAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto)
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
				for (auto Handle : StoreInto.AddedAbilities)
				{
					ASC->CancelAbilityHandle(Handle);
					ASC->ClearAbility(Handle);
				}
				StoreInto.AddedAbilities.Empty();
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

void UArcInventoryComponent_Equippable::ApplyPerks(UArcItemStack* ItemStack, const FArcInventoryItemSlotReference& ItemSlot)
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		return;
	}

	//Get our Ability System
	UAbilitySystemComponent* ASC = GetOwnerAbilitySystem();
	

	//If the Ability System doesn't exist we can't really do much here
	if (!IsValid(ASC))
	{
		return;
	}
	TArray<UArcItemStack*> SubItemStacks;
	ItemStack->GetSubItems(SubItemStacks);
	for (UArcItemStack* SubStack : SubItemStacks)
	{
		if (UArcItemStack_Perk* Perk = Cast<UArcItemStack_Perk>(SubStack))
		{
			TArray<FArcPerkModifierData> ModifierData;
			
			for (auto Modifier : Perk->Modifiers)
			{
				ModifierData.Add(Modifier);
			}
			

			for (FArcPerkModifierData& Modifier : ModifierData)
			{
				if (!Modifier.SlotApplicationRequirement.Matches(ItemSlot.SlotTags))
				{
					continue;
				}

				//Apply the Modifier to the ASC
				ASC->ApplyModToAttribute(Modifier.Attribute, Modifier.ModifierOp, Modifier.Value);
			}
		}
	}
	
}

void UArcInventoryComponent_Equippable::RemovePerks(UArcItemStack* ItemStack, const FArcInventoryItemSlotReference& ItemSlot)
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		return;
	}

	if (!IsValid(ItemStack))
	{
		return;
	}

	//Get our Ability System
	UAbilitySystemComponent* ASC = GetOwnerAbilitySystem();
	//If the Ability System doesn't exist we can't really do much here
	if (!IsValid(ASC))
	{
		return;
	}
	TArray<UArcItemStack*> SubItemStacks;
	ItemStack->GetSubItems(SubItemStacks);
	for (UArcItemStack* SubStack : SubItemStacks)
	{
		if (UArcItemStack_Perk* Perk = Cast<UArcItemStack_Perk>(SubStack))
		{


			for (FArcPerkModifierData& Modifier : Perk->Modifiers)
			{
				if (!ASC->HasAttributeSetForAttribute(Modifier.Attribute))
				{
					continue;
				}

				if (!Modifier.SlotApplicationRequirement.Matches(ItemSlot.SlotTags))
				{
					continue;
				}

				//Figure out the opposite of what we applied
				float Value = Modifier.Value;
				TEnumAsByte<EGameplayModOp::Type> ModOp = Modifier.ModifierOp;

				//Invert Additive 
				if (Modifier.ModifierOp == EGameplayModOp::Additive)
				{
					Value = Value * -1;
				}
				//Invert Mult and Div
				if (ModOp == EGameplayModOp::Multiplicitive)
				{
					ModOp = EGameplayModOp::Division;
				}
				else if (ModOp == EGameplayModOp::Division)
				{
					ModOp = EGameplayModOp::Multiplicitive;
				}

				//Apply the Modifier to the ASC
				ASC->ApplyModToAttribute(Modifier.Attribute, ModOp, Value);
			}
		}
	}
}

void UArcInventoryComponent_Equippable::Debug_Internal(struct FInventoryComponentDebugInfo& Info)
{
	Super::Debug_Internal(Info);
	/*
	//Draw the equipment
	{
		FGameplayTag EquipSlotTag = GetDefault<UArcInventoryDeveloperSettings>()->EquippedSlotTag;

		DebugLine(Info, FString::Printf(TEXT("Equipment Slots (Slots: %d)"), GetInventorySize()), 0.0f, 0.0f);
		TArray< FArcInventoryItemSlotReference> QueriedEquipmentSlots;

		Query_GetAllSlots(FArcInventoryQuery::QuerySlotMatchingTag(EquipSlotTag), QueriedEquipmentSlots);

		for (auto InventorySlot : QueriedEquipmentSlots)
		{
			FArcInventoryItemSlot Slot = this->GetItemSlot(InventorySlot);
			TArray<FString> DebugStrings;
			Slot.ToDebugStrings(DebugStrings, false);
			if (Info.Canvas)
			{
				Info.Canvas->SetDrawColor(FColor::Yellow);
			}
			DebugLine(Info, DebugStrings[0], 4.0f, 0.0f);

			if (Info.Canvas)
			{
				Info.Canvas->SetDrawColor(FColor::Cyan);
			}
			for (int i = 1; i < DebugStrings.Num(); i++)
			{
				DebugLine(Info, DebugStrings[i], 12.0f, 0.0f);
			}
		}
	}
	*/
}

bool UArcInventoryComponent_Equippable::Query_GetAllEquippableSlots(TArray<FArcInventoryItemSlotReference>& OutSlotRefs)
{
	return Query_GetAllSlots(FArcInventoryQuery::QuerySlotMatchingTag(FArcInvEquipSlotTag), OutSlotRefs);
}
