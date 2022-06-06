// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/SSInventoryComponent_Active.h"

#include "SSInventoryComponent_Shooter.generated.h"


class UArkItemStack;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSInventoryComponent_Shooter : public USSInventoryComponent_Active
{
	GENERATED_BODY()
	
public:
	USSInventoryComponent_Shooter(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void InitializeComponent() override;


	UFUNCTION()
		void OnItemSlotChangeEvent(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack);

	// We use this rather than the OnItemActive delegate because that one is unsafe
	virtual void MakeItemActive(int32 NewActiveItemSlot) override;

	UFUNCTION()
		void OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack);

private:
	void OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC);
};
