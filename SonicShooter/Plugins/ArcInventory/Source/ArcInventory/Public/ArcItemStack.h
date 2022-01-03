// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "UObject/NoExportTypes.h"
#include "CoreMinimal.h"
#include "Perks/ArcItemPerkTypes.h"
#include "Engine/NetSerialization.h"
#include "ArcItemStack.generated.h"

class UArcItemDefinition_New;
class UArcItemRarity;
class UArcItemPerkDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FArcItemStackSubstackEvent, UArcItemStack*, ItemStack, UArcItemStack*, SubItemStack);

USTRUCT()
struct FArcSubItemArrayEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
public:
	FArcSubItemArrayEntry()
		: SubItemStack(nullptr)
		, PreviousStack(nullptr)
	{
	}

	UPROPERTY()
	UArcItemStack* SubItemStack;


	TWeakObjectPtr<UArcItemStack> PreviousStack;

	void PreReplicatedRemove(const struct FArcSubItemStackArray& InArraySerializer);
	void PostReplicatedChange(const struct FArcSubItemStackArray& InArraySerializer);
	
};

USTRUCT()
struct FArcSubItemStackArray : public FFastArraySerializer
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FArcSubItemArrayEntry> Items;

	UArcItemStack* ParentStack;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FArcSubItemArrayEntry, FArcSubItemStackArray>(Items, DeltaParms, *this);
	}

};

template<>
struct TStructOpsTypeTraits< FArcSubItemStackArray > : public TStructOpsTypeTraitsBase2< FArcSubItemStackArray >
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ARCINVENTORY_API UArcItemStack : public UObject, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	friend class UArcItemGenerator;
public:
	UArcItemStack(const FObjectInitializer& ObjectInitializer);		

	static void TransferStackOwnership(UArcItemStack*& ItemStack, AActor* Owner);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags);

	virtual bool IsSupportedForNetworking() const override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;

	AActor* GetOwner() const;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", ReplicatedUsing=OnRep_Rarity)
	UArcItemRarity* Rarity;	

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="UI", ReplicatedUsing=OnRep_ItemName)
	FText ItemName;

	UPROPERTY(BlueprintAssignable)
	FArcItemStackSubstackEvent OnSubStackAdded;
	
	UPROPERTY(BlueprintAssignable)
	FArcItemStackSubstackEvent OnSubStackRemoved;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", ReplicatedUsing=OnRep_ItemDefinition)
	TSubclassOf<UArcItemDefinition_New> ItemDefinition;

	UPROPERTY(Replicated)
	FArcSubItemStackArray SubItemStacks;

	UPROPERTY()
	UArcItemStack* ParentItemStack;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", ReplicatedUsing=OnRep_StackSize)
	int32 StackSize;

public:
	UFUNCTION()
	virtual void OnRep_Rarity(UArcItemRarity* PreviousRarity);
	UFUNCTION()
	virtual void OnRep_ItemName(FText PreviousItemName);
	UFUNCTION()
	virtual void OnRep_ItemDefinition(TSubclassOf<UArcItemDefinition_New> PreviousItemDefinition);
	UFUNCTION()
	virtual void OnRep_StackSize(int32 PreviousStackSize);

	virtual TSubclassOf<UArcItemDefinition_New> GetItemDefinition() const;
	virtual int32 GetStackSize() const;

	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory|ItemStack")
	virtual void SetStackSize(int32 NewStackSize);

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory|ItemStack")
	virtual bool HasValidItemData() const;

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory|ItemStack")
	virtual bool CanStackWith(UArcItemStack* OtherStack) const;

	//Returns true if merged completely.  False if OtherStack has elements remaining.   
	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory|ItemStack")
		virtual bool MergeItemStacks(UArcItemStack* OtherStack);

	//Returns true if the item split successfully and OutRemaining has valid data
	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory|ItemStack")
		virtual UArcItemStack* SplitItemStack(int32 SplitAmount);	

	UFUNCTION(BlueprintNativeEvent)
	bool CanAttachTo(UArcItemStack* OtherStack);
	virtual bool CanAttachTo_Implementation(UArcItemStack* OtherStack);

	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory|ItemStack")
	virtual bool AddSubItemStack(UArcItemStack* SubItemStack);
	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory|ItemStack")
	virtual bool RemoveSubItemStack(UArcItemStack* SubItemStack);

	UFUNCTION(BlueprintPure, Category="Arc|Inventory|ItemStack")
	virtual UArcUIData_ItemDefinition* GetUIData();

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory|ItemStack")
	virtual UArcItemStack* QueryForSubItem(const FGameplayTagQuery& StackQuery);

	UFUNCTION(BlueprintPure, Category = "Arc|Inventory|ItemStack")
	virtual void GetSubItems(TArray<UArcItemStack*>& SubItemArray);
	
	virtual void GetDebugStrings(TArray<FString>& OutStrings, bool Detailed) const;

};
