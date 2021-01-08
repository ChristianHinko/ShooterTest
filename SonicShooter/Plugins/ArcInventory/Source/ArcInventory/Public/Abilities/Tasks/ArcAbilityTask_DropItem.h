// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/ArcAbilityTask_SimpleTarget.h"
#include "ArcInventoryItemTypes.h"
#include "ArcAbilityTask_DropItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArcDropItemRecieved, const FArcInventoryItemSlotReference&, FromSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FArcDropItemCancelled);


USTRUCT(BlueprintType)
struct ARCINVENTORY_API FGameplayAbilityTargetData_DropItem : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
		FArcInventoryItemSlotReference FromSlot;
	

	// -------------------------------------

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayAbilityTargetData_DropItem::StaticStruct();
	}

	virtual FString ToString() const override
	{
		return TEXT("FGameplayAbilityTargetData_DropItem");
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_DropItem> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_DropItem>
{
	enum
	{
		WithNetSerializer = true	// For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};


/**
 * 
 */
UCLASS()
class ARCINVENTORY_API UArcAbilityTask_DropItem : public UArcInvAbilityTask_SimpleTarget
{
	GENERATED_BODY()
public:
	UArcAbilityTask_DropItem(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms = "Instigator"), Category = "Ability|Tasks")
	static UArcAbilityTask_DropItem* DropItemFromInventory(UGameplayAbility* OwningAbility, const FArcInventoryItemSlotReference& FromSlot);


	virtual FGameplayAbilityTargetDataHandle GenerateTargetHandle() override;
	virtual void HandleTargetData(const FGameplayAbilityTargetDataHandle& Data) override;
	virtual void HandleCancelled() override;

	UPROPERTY(BlueprintAssignable)
	FArcDropItemRecieved OnDataRecieved;
	UPROPERTY(BlueprintAssignable)
	FArcDropItemCancelled OnDataCancelled;

protected:
	FArcInventoryItemSlotReference SlotReference;
	
};
