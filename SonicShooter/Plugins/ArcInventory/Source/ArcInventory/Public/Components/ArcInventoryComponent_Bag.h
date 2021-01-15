// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcInventoryComponent.h"
#include "GameplayEffectTypes.h"
#include "AttributeSet.h"
#include "ArcInventoryComponent_Bag.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Inventory), meta = (BlueprintSpawnableComponent))
class ARCINVENTORY_API UArcInventoryComponent_Bag : public UArcInventoryComponent
{
	GENERATED_BODY()
public:
	UArcInventoryComponent_Bag(const FObjectInitializer& ObjectInitializer);

public:
	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

	virtual void UpdateBagInventorySlots();

	//Number of slots this inventory contains
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
	int32 BagSlotCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	FGameplayAttribute InventorySizeAttribute;
protected:
	
	virtual void OnInventorySizeAttributeChange(const FOnAttributeChangeData& ChangeData);

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory | Item Queries", meta = (ScriptName = "ItemQuery_GetAllBagSlots"))
	bool Query_GetAllBagSlots(TArray<FArcInventoryItemSlotReference>& OutSlotRefs);
	
};
