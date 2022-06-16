// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArcInventoryComponent_Active.h"

#include "SSInventoryComponent_Active.generated.h"


class UArkItemStack;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSInventoryComponent_Active : public UArcInventoryComponent_Active
{
	GENERATED_BODY()
	
public:
	USSInventoryComponent_Active(const FObjectInitializer& ObjectInitializer);


	int32 StartingActiveItemSlot;
	uint8 bUseOnEquipItemSwappingThingRoyMade : 1;

	// The Game Mode should populate the Inventory with these Items
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
		void OnAttributeSetCreatedEvent(UArcInventoryComponent_Equippable* Inventory, UAttributeSet* AttributeSet, UArcItemStack* AttributeSource);
	
	virtual void MakeItemActive(int32 NewActiveItemSlot) override;
	virtual bool MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack) override;

private:
	// Used in to tell us when to apply the default stats Effect filled out in USSItemDefinition_Active::InitializationEffectTSub
	uint8 bCreatedAttributeSets : 1;

};
