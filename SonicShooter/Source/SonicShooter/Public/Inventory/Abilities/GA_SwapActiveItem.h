// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "GA_SwapActiveItem.generated.h"


class AC_Shooter;
class USSArcInventoryComponent_Active;



/**
 * How we want to be able to swap item
 */
UENUM()
enum class ESwapMethod : uint8
{
	/** Swap to an item slot given an item slot index */
	ByIndex,
	/** Find the item slot with a given tag and swap to it */
	ByTagQuery,
	/** Go up an index in the inventory */
	NextItem,
	/** Go down an index in the inventory */
	PreviousItem,
	/** Find the item slot of an item that was recently held and swap to it. 0 represents most recent item (your current item) */
	ByItemHistory
};

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGA_SwapActiveItem : public UASSGameplayAbility
{
	GENERATED_BODY()
	

public:
	UGA_SwapActiveItem();


protected:
	UPROPERTY()
		TWeakObjectPtr<AC_Shooter> ShooterCharacter;
	UPROPERTY()
		TWeakObjectPtr<USSArcInventoryComponent_Active> InventoryComponent;



	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "SwapMethod == ESwapMethod::ByIndex", EditConditionHides), Category = "Config")
		int32 itemSlotIndexToSwitchTo;
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "SwapMethod == ESwapMethod::ByItemHistory", EditConditionHides), Category = "Config")
		int32 itemHistoryIndex;
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "SwapMethod == ESwapMethod::ByTagQuery", EditConditionHides), Category = "Config")
		FGameplayTagQuery ItemSlotTagQueryForSwitching;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
		ESwapMethod SwapMethod;


	void PerformSwap();


	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface
};
