// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ArcInventoryItemTypes.h"
#include "ArcItemBPFunctionLibrary.generated.h"

class UArcItemRarity;
class UArcOLDItemDefition;
class UArcInventoryComponent_Player;
class UArcInventoryComponent;

/**
 * 
 */
UCLASS()
class ARCINVENTORY_API UArcItemBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UArcItemBPFunctionLibrary();

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static FString GetAttributeString(FGameplayAttribute Attribute);

	// Asset Management
	template <typename T>
	static bool QueryMatchingAssets(FGameplayTagQuery Query, TArray<T*>& OutResults);

	template <typename T>
	static bool QueryMatchingAssetClasses(FGameplayTagQuery Query, TArray<TSubclassOf<T>>& OutResults);

	UFUNCTION(BlueprintCallable, Category = "Arc|Assets")
	static bool QueryMatchingItemDefinitions(FGameplayTagQuery Query, TArray<TSubclassOf<UArcItemDefinition_New>>& OutItemDefinitions);

	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory")
	static bool QueryMatchingItemRarities(FGameplayTagQuery Query, TArray<UArcItemRarity*>& OutItemRarities);
		
	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory")
	static bool QueryMatchingItemGenerators(FGameplayTagQuery Query, TArray<UArcItemGenerator*>& OutItemGenerators);



	//Inventory
	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static UArcInventoryComponent* GetInventoryComponent(AActor* Actor, bool bSearchComponents = false);

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static class UArcInventoryComponent_Bag* GetBagInventoryComponent(AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static class UArcInventoryComponent_Equippable* GetEquippableInventoryComponent(AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static class UArcInventoryComponent_Active* GetActiveInventoryComponent(AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
		static float GetActiveAttributeFromItemSlot(const FArcInventoryItemSlotReference& ItemSlotRef, FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute);

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
		static float GetEquippedAttributeFromItemSlot(const FArcInventoryItemSlotReference& ItemSlotRef, FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute);


	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory|Debug", meta = (WorldContext = "WorldContextObject"))
	static class AArcItemStackWorldObject* SpawnWorldItem(UObject* WorldContextObject,  UArcItemStack* ItemStack, const FTransform& Transform);
		
	
																														
	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static class UArcUIData_ItemDefinition* GetUIDataFromItemDefinition(TSubclassOf<UArcItemDefinition_New> ItemDefinition);


	////INVENTORY SLOTS
	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static bool IsValidItemSlotRef(const FArcInventoryItemSlotReference& ItemSlotRef);

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static UArcItemStack* GetItemFromSlot(const FArcInventoryItemSlotReference& ItemSlotRef);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal FArcInventoryItemSlotReference", CompactNodeTitle = "==", Keywords = "== equal"), Category = "Arc|Inventory")
	static bool EqualEqual_FArcInventoryItemSlotReference(const FArcInventoryItemSlotReference& ItemSlotRef, const FArcInventoryItemSlotReference& OtherItemSlotRef);

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static UArcInventoryComponent* GetInventoryFromSlot(const FArcInventoryItemSlotReference& ItemSlotRef);

	/////INVENTORY QUERY
	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static bool IsValidInventoryQuery(const FArcInventoryQuery& Query);	

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	static FGameplayTagQuery MakeGameplayTagQuery_AnyTag(const FGameplayTagContainer& TagContainer);

	static void CopyAttributeSet(UAttributeSet* Src, UAttributeSet* Destination);

	static bool ASCHasAttributeSet(UAbilitySystemComponent* ASC, TSubclassOf<UAttributeSet> AttributeSetClass);
	static bool ASCAddInstancedAttributeSet(UAbilitySystemComponent* ASC, UAttributeSet* AttributeSet);
	static bool ASCRemoveInstancedAttributeSet(UAbilitySystemComponent* ASC, UAttributeSet* AttributeSet);
};

