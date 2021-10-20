// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArcInventoryItemTypes.h"
#include "AttributeSet.h"
#include "ArcItemStack.h"
#include "ArcInventoryComponent.generated.h"

class UArcInventoryAttributeSet;
class UArcItemStack;

USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcInventoryItemSlotDefinition
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory")
		FGameplayTagContainer Tags;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inventory")
		FArcInventoryItemSlotFilter Filter;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArcOnInventoryUpdate, class UArcInventoryComponent*, Inventory);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FArcOnItemSlotUpdate, class UArcInventoryComponent*, Inventory, const FArcInventoryItemSlotReference&, ItemSlotRef, UArcItemStack*, ItemStack, UArcItemStack*, PreviousItemStack );


UCLASS( )
class ARCINVENTORY_API UArcInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArcInventoryComponent(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitProperties() override;
	virtual void InitializeComponent() override;

protected:
	//Creates a new slot with given tags
	virtual void CreateInventorySlot(const FGameplayTagContainer& SlotTags, const FArcInventoryItemSlotFilterHandle& Filter);

	virtual void RemoveInventorySlot(const FArcInventoryItemSlotReference& Slot);

public:		
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	//Returns true if the item slot reference is valid.  Override this if adding additional item slots
	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory")
	virtual bool IsValidItemSlot(const FArcInventoryItemSlotReference& Slot);

	//Returns a reference to the item slot.  Call IsValidItemSlot before this to ensure you get a valid item slot
	virtual FArcInventoryItemSlot& GetItemSlot(const FArcInventoryItemSlotReference& RefSlot);
		
	//Returns true if the item has been add to this inventory.  False if the item can't fit. 
	UFUNCTION(BlueprintCallable, Category="Arc|Inventory")
	virtual bool LootItem(UArcItemStack* Item);

	//Places the item into the slot.  Returns false if hte item cannot be put there.
	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory")
	virtual bool PlaceItemIntoSlot(UArcItemStack* Item, const FArcInventoryItemSlotReference& ItemSlot);

	//Returns true if the item was in the inventory and is now removed, false if the item could not be removed for whatever reason
	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory")
	virtual bool RemoveItemFromInventory(const FArcInventoryItemSlotReference& ItemSlot);

	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory")
	virtual bool RemoveAllItemsFromInventory(TArray<UArcItemStack*>& OutItemsRemoved);

	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory")
	virtual bool SwapItemSlots(const FArcInventoryItemSlotReference& FromSlot, const FArcInventoryItemSlotReference& ToSlot);

	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory")
	virtual bool AcceptsItem(UArcItemStack* Item, const FArcInventoryItemSlotReference& Slot);

	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory")
	virtual bool AcceptsItem_AssumeEmptySlot(UArcItemStack* Item, const FArcInventoryItemSlotReference& Slot);

	virtual UArcItemStack* GetItemInSlot(const FArcInventoryItemSlotReference& Reference);
	  
	//UPROPERTY(ReplicatedUsing=OnRep_BagInventory)
	//TArray<FArcInventoryItemSlot> BagInventory;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		FArcInventoryItemSlotReference SwapFromSlot;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		FArcInventoryItemSlotReference SwapToSlot;

	UFUNCTION(Category = "Arc|Inventory")
	virtual void OnRep_BagInventory();
	   
	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	virtual int32 GetInventorySize();	    											  

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory")
	virtual TArray<FArcInventoryItemSlotReference> GetAllSlotReferences();


	UPROPERTY(BlueprintAssignable, Category = "Arc|Inventory")
	FArcOnInventoryUpdate OnInventoryUpdate;

	UPROPERTY(BlueprintAssignable, Category = "Arc|Inventory")
	FArcOnItemSlotUpdate OnItemSlotChange;

	//TMap<FArcInventoryItemSlotReference, FArcOnItemSlotUpdate> ItemSlotUpdates;

	//FArcOnItemSlotUpdate& GetItemSlotUpdateDelegate(const FArcInventoryItemSlotReference& ItemSlotRef);
	 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Layout")
	TArray< FArcInventoryItemSlotDefinition> CustomInventorySlots;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Input")
	FArcInventoryItemSlotReference PendingItemDrop;

	virtual class UAbilitySystemComponent* GetOwnerAbilitySystem();


private:
	UPROPERTY(Replicated)
	FArcInventoryItemSlotArray BagInventory;

	//Inventory Searching
public:
	UFUNCTION(BlueprintCallable, Category="Inventory | Item Queries", meta = (ScriptName = "ItemQuery_GetAll"))
	bool Query_GetAllSlots(const FArcInventoryQuery& Query, TArray<FArcInventoryItemSlotReference>& OutSlotRefs);

	UFUNCTION(BlueprintCallable, Category = "Inventory | Item Queries", meta = (ScriptName = "ItemQuery_GetFirst"))
	FArcInventoryItemSlotReference Query_GetFirstSlot(const FArcInventoryQuery& Query);

	UFUNCTION(BlueprintCallable, Category = "Inventory | Item Queries", meta = (ScriptName = "ItemQuery_GetAllItems"))
	void Query_GetAllItems(const FArcInventoryQuery& Query, TArray<UArcItemStack*>& OutItems);


	//Debugging Section
public:
	struct FInventoryComponentDebugInfo
	{
		FInventoryComponentDebugInfo()
		{
			FMemory::Memzero(*this);
		}

		class UCanvas* Canvas;

		bool bPrintToLog;
									  		
		float XPos;
		float YPos;
		float OriginalX;
		float OriginalY;
		float MaxY;
		float NewColumnYPadding;
		float YL;

		bool Accumulate;
		TArray<FString>	Strings;

		int32 GameFlags; // arbitrary flags for games to set/read in Debug_Internal
	};

	static void OnShowDebugInfo(class AHUD* HUD, class UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);

	virtual void DisplayDebug(class UCanvas* Canvas, const class FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos);
	virtual void PrintDebug();

	void AccumulateScreenPos(FInventoryComponentDebugInfo& Info);
	virtual void Debug_Internal(struct FInventoryComponentDebugInfo& Info);
	void DebugLine(struct FInventoryComponentDebugInfo& Info, FString Str, float XOffset, float YOffset);	
};
