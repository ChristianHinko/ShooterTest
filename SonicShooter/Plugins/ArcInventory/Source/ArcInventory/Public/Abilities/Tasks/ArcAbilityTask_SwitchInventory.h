// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/ArcAbilityTask_SimpleTarget.h"
#include "ArcInventoryItemTypes.h"
#include "ArcAbilityTask_SwitchInventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FArcSwitchItemsRecieved, const FArcInventoryItemSlotReference&, FromSlot, const FArcInventoryItemSlotReference&, ToSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FArcItemSwitchCancelled);



USTRUCT(BlueprintType)
struct FGameplayAbilityTargetData_ItemSwitch : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
	FArcInventoryItemSlotReference FromSlot;
	UPROPERTY()
	FArcInventoryItemSlotReference ToSlot;

	// -------------------------------------

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayAbilityTargetData_ItemSwitch::StaticStruct();
	}

	virtual FString ToString() const override
	{
		return TEXT("FGameplayAbilityTargetData_ItemSwitch");
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_ItemSwitch> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_ItemSwitch>
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
class ARCINVENTORY_API UArcAbilityTask_SwitchInventory : public UArcInvAbilityTask_SimpleTarget
{
	GENERATED_BODY()
public:
	UArcAbilityTask_SwitchInventory(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms = "Instigator"), Category = "Ability|Tasks")
	static UArcAbilityTask_SwitchInventory* SwitchInventorySlots(UGameplayAbility* OwningAbility, const FArcInventoryItemSlotReference& FromSlot, const FArcInventoryItemSlotReference& ToSlot);
	
	virtual FGameplayAbilityTargetDataHandle GenerateTargetHandle() override;
	virtual void HandleTargetData(const FGameplayAbilityTargetDataHandle& Data) override;
	virtual void HandleCancelled() override;

	UPROPERTY(BlueprintAssignable)
	FArcSwitchItemsRecieved OnSlotsRecieved;

	UPROPERTY(BlueprintAssignable)
	FArcItemSwitchCancelled OnSlotsCancelled;

protected:

	FArcInventoryItemSlotReference FromSlot;
	FArcInventoryItemSlotReference ToSlot;
	
	
};
