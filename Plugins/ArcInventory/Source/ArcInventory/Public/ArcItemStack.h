// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "UObject/NoExportTypes.h"
#include "CoreMinimal.h"
#include "Perks/ArcItemPerkTypes.h"
#include "ArcItemStack.generated.h"

class UArcItemDefinition_New;
class UArcItemRarity;
class UArcItemPerkDefinition;

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

	virtual bool IsNameStableForNetworking() const override;
	virtual bool IsSupportedForNetworking() const override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;

	AActor* GetOwner() const;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", Replicated)
	UArcItemRarity* Rarity;	

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="UI", Replicated)
	FText ItemName;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", Replicated)
	TSubclassOf<UArcItemDefinition_New> ItemDefinition;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", Replicated)
	TArray<UArcItemStack*> SubItemStacks;

	UPROPERTY()
	UArcItemStack* ParentItemStack;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", Replicated)
	int32 StackSize;

public:
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

	TArray<UArcItemStack*>& GetSubItemStacks() { return SubItemStacks; }

	virtual void GetDebugStrings(TArray<FString>& OutStrings, bool Detailed) const;
};
