// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "ArcInventoryItemTypes.h"

#include "GA_DropItem.generated.h"

class AShooterCharacter;
class UArcInventoryComponent;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGA_DropItem : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_DropItem();


protected:
	UPROPERTY()
		AShooterCharacter* ShooterCharacter;
	UPROPERTY()
		UArcInventoryComponent* Inventory;

	UArcItemStack* RemovedItemStack;


	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	UFUNCTION()
		void OnDataRecieved(const FArcInventoryItemSlotReference& FromSlot);
	UFUNCTION()
		void OnDataCancelled();

};
