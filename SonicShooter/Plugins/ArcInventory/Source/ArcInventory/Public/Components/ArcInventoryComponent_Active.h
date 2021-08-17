// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArcInventoryComponent_Equippable.h"
#include "ArcInventoryComponent_Active.generated.h"

class UArcItemStack;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FArcOnItemActivationDelegate, UArcInventoryComponent_Active*, InventoryComponent, UArcItemStack*, ItemStack);

/**
 * 
 */
UCLASS(ClassGroup = (Inventory), meta = (BlueprintSpawnableComponent))
class ARCINVENTORY_API UArcInventoryComponent_Active : public UArcInventoryComponent_Equippable
{
	GENERATED_BODY()
public:
	UArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer);

	virtual void InitializeComponent() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnItemEquipped(class UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack) override;
	   
	UFUNCTION(BlueprintPure, Category = "Inventory")
		virtual FArcInventoryItemSlotReference GetActiveItemSlot();

	UFUNCTION(BlueprintPure, Category = "Inventory")
		virtual UArcItemStack* GetActiveItemStack();

	UFUNCTION(BlueprintPure, Category = "Inventory")
		virtual FArcInventoryItemSlotReference GetActiveItemSlotInSlot(int32 InActiveItemSlot);

	UFUNCTION(BlueprintPure, Category = "Inventory")
		virtual UArcItemStack* GetActiveItemStackInSlot(int32 InActiveItemSlot);

	UFUNCTION(BlueprintPure, Category = "Inventory")
		virtual bool IsValidActiveItemSlot(int32 InActiveItemSlot);

	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, ReplicatedUsing = OnRep_ActiveItemSlot, Category = "Inventory")
		int32 ActiveItemSlot;
	UFUNCTION()
		virtual void OnRep_ActiveItemSlot(int32 PreviousItemSlot);


	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, ReplicatedUsing = OnRep_PendingItemSlot, Category = "Inventory")
		int32 PendingItemSlot;
	UFUNCTION()
		virtual void OnRep_PendingItemSlot(int32 PreviousItemSlot);

	//Returns the next Active Item Slot, regardless if that slot has a valid item
	UFUNCTION(BlueprintPure, Category = "Inventory")
		virtual int32 GetNextActiveItemSlot() const;

	//Returns the previous Active Item Slot, regardless if that slot has a valid item
	UFUNCTION(BlueprintPure, Category = "Inventory")
		virtual int32 GetPreviousActiveItemSlot() const;

	//Returns the next Active Item Slot, but only if it has a valid item.  
	UFUNCTION(BlueprintPure, Category = "Inventory")
	virtual int32 GetNextValidActiveItemSlot();

	//Returns the previous Active Item Slot, but only if it has a valid item.  
	UFUNCTION(BlueprintPure, Category = "Inventory")
	virtual int32 GetPreviousValidActiveItemSlot();

	virtual int32 GetNextItemSlotFrom(int32 InActiveItemSlot) const;
	virtual int32 GetPreviousItemSlotFrom(int32 InActiveItemSlot) const;

	virtual void MakeItemInactive();
	virtual void MakeItemActive(int32 NewActiveItemSlot);
	virtual void MakeItemActive(const FArcInventoryItemSlotReference& ItemSlotRef);

	virtual bool IsActiveItemSlot(const FArcInventoryItemSlotReference& ItemSlotRef) const;
	
	virtual int32 GetActiveItemIndexBySlotRef(const FArcInventoryItemSlotReference& ItemSlotRef);
	virtual int32 GetActiveItemIndexByTag(FGameplayTag Tag);

	virtual void SwitchToPendingItemSlot();

	UFUNCTION()
	virtual void UpdateActiveItemSlots(UArcInventoryComponent* InventoryComp);

	bool bSwitchingWeapons;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void SwapActiveItems(int32 NewItemSlot);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities", Replicated)
	TArray< FArcInventoryItemInfoEntry> ActiveItemAbilityInfos;

	UPROPERTY(BlueprintAssignable)
	FArcOnItemActivationDelegate OnItemActive;
	UPROPERTY(BlueprintAssignable)
	FArcOnItemActivationDelegate OnItemInactive;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetIndexForActiveItemSlotTagQuery(const FGameplayTagQuery& TagQuery);

protected:
	virtual bool MakeItemInactive_Internal(const FArcInventoryItemSlotReference& ItemSlot);
	virtual bool MakeItemInactive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack);
	virtual bool MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot);
	virtual bool MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack);

	TArray<FArcInventoryItemSlotReference> CachedActiveItemSlots;

};
