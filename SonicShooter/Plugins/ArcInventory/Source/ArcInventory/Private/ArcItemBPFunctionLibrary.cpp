// Copyright 2017-2020 Puny Human, All Rights Reserved.

#include "ArcItemBPFunctionLibrary.h"

#include "ArcInventoryDeveloperSettings.h"

#include "Item/ArcItemRarity.h"

#include "Item/ArcItemStackWorldObject.h"
#include "ArcInventoryComponent.h"
#include "ArcInventory.h"

#include "Components/ArcInventoryComponent_Bag.h"
#include "Components/ArcInventoryComponent_Equippable.h"
#include "Components/ArcInventoryComponent_Active.h"

#include "Interfaces/ArcInventoryInterface.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/AssetManager.h"

#include "Item/Definitions/ArcItemDefinition_Equipment.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"



UArcItemBPFunctionLibrary::UArcItemBPFunctionLibrary()
	: Super()
{

}


FString UArcItemBPFunctionLibrary::GetAttributeString(FGameplayAttribute Attribute)
{
	return Attribute.GetName();
}


template <typename T>
bool UArcItemBPFunctionLibrary::QueryMatchingAssets(FGameplayTagQuery Query, TArray<T*>& OutResults)
{	
	UClass* AssetClass = T::StaticClass();

	//If we don't implement the GameplayTagAssetInterface, dont bother searching deeper.
	if (!AssetClass->ImplementsInterface(UGameplayTagAssetInterface::StaticClass()))
	{
		return false;
	}

	//Find the Primary Asset Type for T, if we have it one
	TArray<FPrimaryAssetTypeInfo> AssetTypeInfoList;
	UAssetManager::Get().GetPrimaryAssetTypeInfoList(AssetTypeInfoList);

	FPrimaryAssetType PrimaryAssetType;
	for (auto AssetTypeInfo : AssetTypeInfoList)
	{
		if (AssetClass->IsChildOf(AssetTypeInfo.AssetBaseClassLoaded))
		{
			PrimaryAssetType = FPrimaryAssetType(AssetTypeInfo.PrimaryAssetType);
			break;
		}
	}

	if (!PrimaryAssetType.IsValid())
	{
		return false;
	}

	//Get All objects of this type
	TArray<UObject*> Objects;
	bool bSuccess = UAssetManager::Get().GetPrimaryAssetObjectList(PrimaryAssetType, Objects);

	//And match them against the query
	for (int32 i  = 0; i < Objects.Num(); i++)
	{		
		UObject* Obj = Objects[i];
		if (UClass* Class = Cast<UClass>(Obj))
		{
			Obj = Class->GetDefaultObject();
		}

		if (IGameplayTagAssetInterface* InterfacePtr = Cast< IGameplayTagAssetInterface>(Obj))
		{
			FGameplayTagContainer TagContainer;
			InterfacePtr->GetOwnedGameplayTags(TagContainer);

			if (Query.Matches(TagContainer))
			{
				OutResults.Add(Cast<T>(Obj));
			}
		}		
	}

	return bSuccess;
}

template <typename T>
bool UArcItemBPFunctionLibrary::QueryMatchingAssetClasses(FGameplayTagQuery Query, TArray<TSubclassOf<T>>& OutResults)
{
	TArray<T*> DefaultObjects;
	bool bSuccess = QueryMatchingAssets<T>(Query, DefaultObjects);

	if (bSuccess)
	{
		for (T* Object : DefaultObjects)
		{
			OutResults.Add(Object->GetClass());
		}
	}

	return bSuccess;
}



bool UArcItemBPFunctionLibrary::QueryMatchingItemDefinitions(FGameplayTagQuery Query, TArray<TSubclassOf<UArcItemDefinition_New>>& OutItemDefinitions)
{
	return QueryMatchingAssetClasses<UArcItemDefinition_New>(Query, OutItemDefinitions);
}

bool UArcItemBPFunctionLibrary::QueryMatchingItemRarities(FGameplayTagQuery Query, TArray<UArcItemRarity*>& OutItemRarities)
{
	return QueryMatchingAssets<UArcItemRarity>(Query, OutItemRarities);
}

bool UArcItemBPFunctionLibrary::QueryMatchingItemGenerators(FGameplayTagQuery Query, TArray<UArcItemGenerator*>& OutItemGenerators)
{
	return QueryMatchingAssets<UArcItemGenerator>(Query, OutItemGenerators);
}

UArcInventoryComponent* UArcItemBPFunctionLibrary::GetInventoryComponent(AActor* Actor, bool bSearchComponents /*= false*/)
{
	if (IArcInventoryInterface* InventoryInterface = Cast<IArcInventoryInterface>(Actor))
	{
		return InventoryInterface->GetInventoryComponent();
	}

	if (bSearchComponents)
	{
		if (UArcInventoryComponent* IC = Cast<UArcInventoryComponent>(Actor->GetComponentByClass(UArcInventoryComponent::StaticClass())))
		{
			return IC;
		}
	}
		
	return nullptr;
}

UArcInventoryComponent_Bag* UArcItemBPFunctionLibrary::GetBagInventoryComponent(AActor* Actor)
{
	return Cast<UArcInventoryComponent_Bag>(GetInventoryComponent(Actor));
}

UArcInventoryComponent_Equippable* UArcItemBPFunctionLibrary::GetEquippableInventoryComponent(AActor* Actor)
{
	return Cast<UArcInventoryComponent_Equippable>(GetInventoryComponent(Actor));
}

UArcInventoryComponent_Active* UArcItemBPFunctionLibrary::GetActiveInventoryComponent(AActor* Actor)
{
	return Cast<UArcInventoryComponent_Active>(GetInventoryComponent(Actor));
}


bool UArcItemBPFunctionLibrary::IsValidItemSlotRef(const FArcInventoryItemSlotReference& ItemSlotRef)
{
	return IsValid(ItemSlotRef);
}

UArcItemStack* UArcItemBPFunctionLibrary::GetItemFromSlot(const FArcInventoryItemSlotReference& ItemSlotRef)
{
	if (!IsValid(ItemSlotRef))
	{
		return nullptr;
	}

	return ItemSlotRef.ParentInventory->GetItemSlot(ItemSlotRef).ItemStack;
}

bool UArcItemBPFunctionLibrary::EqualEqual_FArcInventoryItemSlotReference(const FArcInventoryItemSlotReference& ItemSlotRef, const FArcInventoryItemSlotReference& OtherItemSlotRef)
{
	return ItemSlotRef == OtherItemSlotRef;
}

bool UArcItemBPFunctionLibrary::IsValidInventoryQuery(const FArcInventoryQuery& Query)
{
	return Query.IsValid();
}

FGameplayTagQuery UArcItemBPFunctionLibrary::MakeGameplayTagQuery_AnyTag(const FGameplayTagContainer& TagContainer)
{
	return FGameplayTagQuery::MakeQuery_MatchAnyTags(TagContainer);
}

void UArcItemBPFunctionLibrary::CopyAttributeSet(UAttributeSet* Src, UAttributeSet* Destination)
{
	//Have to be the same class to copy
	if (Src->GetClass() != Destination->GetClass())
	{
		return;
	}

	for (TFieldIterator<FProperty> PropertyIt(Src->GetClass(), EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
	{
		FProperty* Property = *PropertyIt;
		FGameplayAttribute Attribute(Property);

		float AttributeValue = Attribute.GetNumericValue(Src);
		Attribute.SetNumericValueChecked(AttributeValue, Destination);
	}
}

bool UArcItemBPFunctionLibrary::ASCHasAttributeSet(UAbilitySystemComponent* ASC, TSubclassOf<UAttributeSet> AttributeSetClass)
{
	for (UAttributeSet* AttributeSet : ASC->GetSpawnedAttributes_Mutable())
	{
		if (AttributeSet->GetClass() == AttributeSetClass)
		{
			return true;
		}
	}

	return false;
}

bool UArcItemBPFunctionLibrary::ASCAddInstancedAttributeSet(UAbilitySystemComponent* ASC, UAttributeSet* AttributeSet)
{
	if (ASC->GetOwnerRole() != ROLE_Authority)
	{
		return false;
	}
	if (!IsValid(AttributeSet))
	{
		return false;
	}
	//We don't want to double up attributes.  If we already have this attribute set added we need to fix that
	ensure(!ASC->GetSpawnedAttributes_Mutable().Contains(AttributeSet));

	ASC->GetSpawnedAttributes_Mutable().AddUnique(AttributeSet);
	ASC->bIsNetDirty = true;

	return false;
}

bool UArcItemBPFunctionLibrary::ASCRemoveInstancedAttributeSet(UAbilitySystemComponent* ASC, UAttributeSet* AttributeSet)
{
	if (!IsValid(AttributeSet))
	{
		return false;
	}
	//TODO: Reset the Attribute Set

	ASC->GetSpawnedAttributes_Mutable().Remove(AttributeSet);
	ASC->bIsNetDirty = true;

	return true;
}

namespace FArcInventoryStatics
{
	void ConvertAttributeData(FArcItemDefinition_AbilityInfo& AbilityInfo)
	{
		if (AbilityInfo.AttributeSets.Num() <= 0)
		{
			return;
		}

		AbilityInfo.AttributeInitalizers.Empty();

		for (int32 i = 0; i < AbilityInfo.AttributeSets.Num(); i++)		
		{
			UAttributeSet* AttributeSet = AbilityInfo.AttributeSets[i];
			if (!IsValid(AttributeSet))
			{
				continue;
			}

			for (TFieldIterator<FProperty> PropertyIt(AttributeSet->GetClass(), EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
			{
				FGameplayAttribute Attribute(*PropertyIt);
				if (!Attribute.IsValid())
				{
					continue;
				}

				if (Attribute.GetNumericValue(AttributeSet) != Attribute.GetNumericValue(AttributeSet->GetClass()->GetDefaultObject<UAttributeSet>()))
				{
					AbilityInfo.AttributeInitalizers.Add(Attribute, Attribute.GetNumericValue(AttributeSet));
				}
			}

			AbilityInfo.AttributeSetsToAdd.Add(AttributeSet->GetClass());
		}

		AbilityInfo.AttributeSets.Empty();
	}
}

void UArcItemBPFunctionLibrary::ConvertOldAttributeModelToNew(TSubclassOf<UArcItemDefinition_Equipment> EquipmentItemDef)
{
	if (!IsValid(EquipmentItemDef))
	{

		return;
	}

	UArcItemDefinition_Equipment* ItemDefCDO = EquipmentItemDef.GetDefaultObject();

	FArcInventoryStatics::ConvertAttributeData(ItemDefCDO->EquippedItemAbilityInfo);

	if (UArcItemDefinition_Active* ActiveItemDefCDO = Cast<UArcItemDefinition_Active>(ItemDefCDO))
	{
		FArcInventoryStatics::ConvertAttributeData(ActiveItemDefCDO->ActiveItemAbilityInfo);
	}
	
}

float UArcItemBPFunctionLibrary::GetActiveAttributeFromItemSlot(const FArcInventoryItemSlotReference& ItemSlotRef, FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute)
{
	bSuccessfullyFoundAttribute = false;
	UArcInventoryComponent_Active* Inventory = Cast<UArcInventoryComponent_Active>(ItemSlotRef.ParentInventory);

	if (!IsValid(Inventory) || !Inventory->IsValidItemSlot(ItemSlotRef))
	{
		return 0.0f;
	}	

	//BUGBUG: 4.23 doesn't properly serialize FGameplayAttribute properties in BP Pins.  
	//This means Attribute is sometimes invalid. It needs to be fixed in blueprint
	//TODO: In 4.24, uncomment the ensure line and remove the non-ensure version
	//if (!ensure(Attribute.IsValid()))
	if(!Attribute.IsValid())
	{
		return 0.0f;
	}
	
	FArcInventoryItemInfoEntry* Entry = Inventory->ActiveItemAbilityInfos.FindByPredicate([ItemSlotRef](FArcInventoryItemInfoEntry& x) {
		return x.ItemSlotRef == ItemSlotRef;
	});

	if (Entry == nullptr)
	{
		return 0.0f;
	}

	for (UAttributeSet* AttributeSet : (*Entry).EquippedItemInfo.InstancedAttributeSets)
	{
		if (!IsValid(AttributeSet))
		{
			continue;
		}

		if (AttributeSet->GetClass() == Attribute.GetAttributeSetClass())
		{
			bSuccessfullyFoundAttribute = true;
			return Attribute.GetNumericValue(AttributeSet);
		}
	}  	
	
	return 0.0f;
}

float UArcItemBPFunctionLibrary::GetEquippedAttributeFromItemSlot(const FArcInventoryItemSlotReference& ItemSlotRef, FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute)
{
	bSuccessfullyFoundAttribute = false;
	UArcInventoryComponent_Equippable* Inventory = Cast<UArcInventoryComponent_Equippable>(ItemSlotRef.ParentInventory);

	if (!IsValid(Inventory) || !Inventory->IsValidItemSlot(ItemSlotRef))
	{
		return 0.0f;
	}
	
	FArcInventoryItemInfoEntry* Entry = Inventory->EquippedItemAbilityInfos.FindByPredicate([ItemSlotRef](FArcInventoryItemInfoEntry& x) {
		return x.ItemSlotRef == ItemSlotRef;
	});

	if (Entry == nullptr)
	{
		return 0.0f;
	}

	for (UAttributeSet* AttributeSet : (*Entry).EquippedItemInfo.InstancedAttributeSets)
	{
		if (AttributeSet->GetClass() == Attribute.GetAttributeSetClass())
		{
			bSuccessfullyFoundAttribute = true;
			return Attribute.GetNumericValue(AttributeSet);
		}
	}  

	return 0.0f;
}

class AArcItemStackWorldObject* UArcItemBPFunctionLibrary::SpawnWorldItem(UObject* WorldContextObject, UArcItemStack* ItemStack, const FTransform& Transform)
{
	UWorld* World = WorldContextObject->GetWorld();

	if (IsValid(World))
	{
		TSubclassOf<AArcItemStackWorldObject> WorldStackClass = AArcItemStackWorldObject::StaticClass();
		if (IsValid(GetDefault<UArcInventoryDeveloperSettings>()->ItemStackWorldObjectClass))
		{
			WorldStackClass = GetDefault<UArcInventoryDeveloperSettings>()->ItemStackWorldObjectClass;
		}

		AArcItemStackWorldObject* StackObject = World->SpawnActorDeferred<AArcItemStackWorldObject>(WorldStackClass, Transform);
		if (IsValid(StackObject))
		{
			StackObject->SetInventoryStack(ItemStack);
			UGameplayStatics::FinishSpawningActor(StackObject, Transform);
			return StackObject;
		}
	}
	return nullptr;
}

class UArcUIData_ItemDefinition* UArcItemBPFunctionLibrary::GetUIDataFromItemDefinition(TSubclassOf<UArcItemDefinition_New> ItemDefinition)
{
	if (IsValid(ItemDefinition))
	{
		return ItemDefinition.GetDefaultObject()->UIData;
	}
	return nullptr;	
}
