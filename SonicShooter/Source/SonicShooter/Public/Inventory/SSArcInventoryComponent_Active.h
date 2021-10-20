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
	
private:

public:
	USSArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	int32 startingActiveItemSlot;
	uint8 bUseOnEquipItemSwappingThingRoyMade : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		TArray<FArcStartingItemEntry> StartingItems;

	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool IsActiveItemSlotIndexValid(int32 InActiveItemSlot);

	


	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 maxItemHistoryBufferSize;
	UPROPERTY(Replicated)
		TArray<FArcInventoryItemSlotReference> ActiveItemHistory;




	
	virtual void OnItemEquipped(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack) override;
	
	UFUNCTION()
		void AddToActiveItemHistory(const FArcInventoryItemSlotReference& NewActiveItemSlotReference);

protected:
	UFUNCTION()
		void OnItemSlotChangeEvent(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack);
	UFUNCTION()
		void OnItemActiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack);
	UFUNCTION()
		void OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack);
	virtual bool MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack) override;
	
	virtual bool ApplyAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto, UArcItemStack* AbilitySource) override;

};
