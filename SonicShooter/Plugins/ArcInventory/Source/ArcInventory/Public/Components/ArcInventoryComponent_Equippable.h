// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArcInventoryComponent_Bag.h"
#include "ArcInventoryComponent_Equippable.generated.h"

USTRUCT(BlueprintType)
struct FArcInventoryItemInfoEntry
{
	GENERATED_USTRUCT_BODY()
public:
	FArcInventoryItemInfoEntry()
	{

	}
	FArcInventoryItemInfoEntry(const FArcInventoryItemSlotReference& Ref)
		: ItemSlotRef(Ref)
	{

	}
	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
		FArcInventoryItemSlotReference ItemSlotRef;
	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
		FArcEquippedItemInfo EquippedItemInfo;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FArcInvOnItemEquippedDelegate, class UArcInventoryComponent*, Inventory, const FArcInventoryItemSlotReference&, ItemSlotRef, UArcItemStack*, ItemStack);

/**
 * 
 */
UCLASS(ClassGroup = (Inventory), meta = (BlueprintSpawnableComponent))
class ARCINVENTORY_API UArcInventoryComponent_Equippable : public UArcInventoryComponent_Bag
{
	GENERATED_BODY()
public:
	UArcInventoryComponent_Equippable(const FObjectInitializer& ObjectInitializer);

	virtual void InitializeComponent() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



	UFUNCTION()
	virtual void OnItemEquipped(class UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack);

	virtual bool IsEquippedItemSlot(const FArcInventoryItemSlotReference& ItemSlotRef);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities", Replicated, meta = (AllowPrivateAccess = "true"))
		TArray< FArcInventoryItemInfoEntry> EquippedItemAbilityInfos;

	UPROPERTY(BlueprintAssignable)
	FArcInvOnItemEquippedDelegate OnEquippedItem;

	UPROPERTY(BlueprintAssignable)
	FArcInvOnItemEquippedDelegate OnUnEquippedItem;
	
protected:
	virtual bool MakeItemEquipped_Internal(const FArcInventoryItemSlotReference& ItemSlot);
	virtual bool MakeItemEquipped_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack);
	virtual bool MakeItemUnequipped_Internal(const FArcInventoryItemSlotReference& ItemSlot);
	virtual bool MakeItemUnequipped_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack);

	virtual bool ApplyAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto, UArcItemStack* AbilitySource);
	virtual bool ClearAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto);

	virtual void ApplyPerks(UArcItemStack* ItemStack, const FArcInventoryItemSlotReference& ItemSlot);
	virtual void RemovePerks(UArcItemStack* ItemStack, const FArcInventoryItemSlotReference& ItemSlot);

private: 	
	virtual void Debug_Internal(struct FInventoryComponentDebugInfo& Info) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory | Item Queries", meta = (ScriptName = "ItemQuery_GetAllEquippableSlots"))
		bool Query_GetAllEquippableSlots(TArray<FArcInventoryItemSlotReference>& OutSlotRefs);

};
