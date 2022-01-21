// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArcInventoryComponent_Active.h"

#include "SSArcInventoryComponent_Active.generated.h"


class UArkItemStack;
class UArcInventoryComponent;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSArcInventoryComponent_Active : public UArcInventoryComponent_Active
{
	GENERATED_BODY()
	
public:
	USSArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer);


	int32 StartingActiveItemSlot;
	uint8 bUseOnEquipItemSwappingThingRoyMade : 1;

	// The GM should populate the Inventory with these items
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		TArray<FArcStartingItemEntry> StartingItems;

	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool IsActiveItemSlotIndexValid(int32 InActiveItemSlot);


	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 MaxItemHistoryBufferSize;
	UPROPERTY(Replicated)
		TArray<FArcInventoryItemSlotReference> ActiveItemHistory;


	
	virtual void OnItemEquipped(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack) override;
	
	UFUNCTION()
		void AddToActiveItemHistory(const FArcInventoryItemSlotReference& NewActiveItemSlotReference);

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	UFUNCTION()
		void OnItemSlotChangeEvent(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack);
	UFUNCTION()
		void OnItemActiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack);
	UFUNCTION()
		void OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack);

	UFUNCTION()
		void OnAttributeSetCreatedEvent(UArcInventoryComponent_Equippable* Inventory, UAttributeSet* AttributeSet, UArcItemStack* AttributeSource);
	

	virtual bool MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack) override;
	
	virtual bool ApplyAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto, UArcItemStack* AbilitySource) override;


private:
	// Used in ApplyAbilityInfo_Internal() override to tell us when to apply the default stats Effect filled out in USSArcItemDefinition_Active::InitializationEffectTSub
	uint8 bCreatedAttributeSets : 1;

};
