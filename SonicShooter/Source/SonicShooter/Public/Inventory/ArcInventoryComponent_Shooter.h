// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/SSArcInventoryComponent_Active.h"

#include "ArcInventoryComponent_Shooter.generated.h"


class UArkItemStack;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UArcInventoryComponent_Shooter : public USSArcInventoryComponent_Active
{
	GENERATED_BODY()
	
public:
	UArcInventoryComponent_Shooter(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void InitializeComponent() override;


	UFUNCTION()
		void OnItemSlotChangeEvent(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack);

	// We use this rather than the OnItemActive delegate because that one is unsafe
	virtual void MakeItemActive(int32 NewActiveItemSlot) override;

	UFUNCTION()
		void OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack);

};
