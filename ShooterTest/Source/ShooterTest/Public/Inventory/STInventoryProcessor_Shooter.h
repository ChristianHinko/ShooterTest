// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/AIEInventoryProcessor_Active.h"

#include "STInventoryProcessor_Shooter.generated.h"


class UArcItemStackModular;



/**
 * 
 */
UCLASS()
class SHOOTERTEST_API USTInventoryProcessor_Shooter : public UAIEInventoryProcessor_Active
{
    GENERATED_BODY()
    
public:
    USTInventoryProcessor_Shooter();


protected:
    virtual void OnInventoryInit_Implementation() override;

    virtual void OnItemSlotChange_Implementation(const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStackModular* ItemStack, UArcItemStackModular* PreviousItemStack, FGameplayTag Context) override;

    // We use this rather than the OnItemActive delegate because that one is unsafe
    virtual void MakeItemActive(int32 NewActiveItemSlot) override;

    virtual void MakeItemInactive() override;

private:
    void OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC);
};
