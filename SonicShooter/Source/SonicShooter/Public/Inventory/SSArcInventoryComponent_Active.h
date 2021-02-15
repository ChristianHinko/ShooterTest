// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArcInventoryComponent_Active.h"

#include "SSArcInventoryComponent_Active.generated.h"

class UArkItemStack;

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

	UFUNCTION(BlueprintPure, Category = "Inventory")
		bool IsActiveItemSlotIndexValid(int32 InActiveItemSlot);

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 maxItemHistoryBufferSize;
	TArray<FArcInventoryItemSlotReference> ItemHistory;
	
	UFUNCTION()
		void AddToItemHistory(FArcInventoryItemSlotReference NewActiveItemSlotReference);

protected:
	virtual bool MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack);


};
