// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "SSGameplayAbility_SwapActiveItem.generated.h"


class ASSCharacter_Shooter;
class USSInventoryComponent_Active;



/**
 * How we want to be able to swap item
 */
UENUM()
enum class ESSSlotSwapMethod : uint8
{
	/** Swap to an item slot given an item slot index */
	ByIndex,
	/** Find the item slot with a given tag and swap to it */
	ByTagQuery,
	/** Go up an index in the inventory */
	Forward,
	/** Go down an index in the inventory */
	Backward,
	/** Find the item slot of an item that was recently held and swap to it. 0 represents most recent item (your current item) */
	ByItemHistory
};

/**
 * Swaps active items on the Inventory Component.
 * Must subclass in BP.
 * 
 * NOTE: The BulletSpread subobject looks for numeric Attribute values from the ASC. These Attribute values should be the ones
 * from this newly active item - HOWEVER, on the Client, it has to wait for the Server to replicate the UAbilitySystemComponent::SpawnedAttributes array. So it
 * ends up taking a bit to have the correct Bullet Spread values.
 * This is the result of having a predictive Gameplay Ability without having predictive Attribute Set adding and removing (because addition and removal of Attribute Sets is not meant to be predictive of course).
 * The predictive SSGameplayAbility_SwapActiveItem Ability effectively adds and removes Attribute Sets (by changing the active item) non-predictively which is the root of the problem.
 * I guess this is just a limitation of dynamically adding and removing Attribute Sets during runtime.
 * You can notice this problem by looking at the crosshair. When swapping active weapons, the gun is using the old weapon's bullet spread for a split second.
 */
UCLASS(Abstract)
class SONICSHOOTER_API USSGameplayAbility_SwapActiveItem : public UASSGameplayAbility
{
	GENERATED_BODY()
	

public:
	USSGameplayAbility_SwapActiveItem(const FObjectInitializer& ObjectInitializer);


protected:
	UPROPERTY()
		TWeakObjectPtr<ASSCharacter_Shooter> ShooterCharacter;
	UPROPERTY()
		TWeakObjectPtr<USSInventoryComponent_Active> InventoryComponent;



	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "SlotSwapMethod == ESSSlotSwapMethod::ByIndex", EditConditionHides), Category = "Config")
		int32 ItemSlotIndexToSwitchTo;
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "SlotSwapMethod == ESSSlotSwapMethod::ByItemHistory", EditConditionHides), Category = "Config")
		int32 ItemHistoryIndex;
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "SlotSwapMethod == ESSSlotSwapMethod::ByTagQuery", EditConditionHides), Category = "Config")
		FGameplayTagQuery ItemSlotTagQueryForSwitching;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
		ESSSlotSwapMethod SlotSwapMethod;


	void PerformSwap();


	//BEGIN UGameplayAbility Interface
	virtual void ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface
};
