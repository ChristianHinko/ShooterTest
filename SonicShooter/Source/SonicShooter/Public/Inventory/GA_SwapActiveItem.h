// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "GA_SwapActiveItem.generated.h"

class AShooterCharacter;
class USSArcInventoryComponent_Active;

/** How we want to be able to swap item */
UENUM()
enum class ESwapMethod : uint8
{
	/**  */
	ByIndex,
	/**  */
	ByTag,
	/**  */
	NextItem,
	/**  */
	PrecedingItem,
	/**  */
	LastActiveItem
};

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGA_SwapActiveItem : public USSGameplayAbility
{
	GENERATED_BODY()
	

public:
	UGA_SwapActiveItem();


protected:
	UPROPERTY()
		AShooterCharacter* ShooterCharacter;
	UPROPERTY()
		USSArcInventoryComponent_Active* SSInventoryComponentActive;



	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "SwapMethod == ESwapMethod::ByIndex", EditConditionHides), Category = "Config")
		int32 itemSlotIndexToSwitchTo;
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "SwapMethod == ESwapMethod::ByTag", EditConditionHides), Category = "Config")
		FGameplayTag ItemSlotTagToSwitchTo;

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
