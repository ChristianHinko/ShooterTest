// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"
#include "ArcInventoryItemTypes.h"

#include "GA_DropItem.generated.h"


class AC_Shooter;
class UArcInventoryComponent;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGA_DropItem : public UASSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_DropItem();


protected:
	UPROPERTY()
		TWeakObjectPtr<AC_Shooter> ShooterCharacter;
	UPROPERTY()
		TWeakObjectPtr<UArcInventoryComponent> Inventory;


	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSetThatWorks(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	UPROPERTY()
		TWeakObjectPtr<UArcItemStack> RemovedItemStack;

	UFUNCTION()
		void OnDataRecieved(const FArcInventoryItemSlotReference& FromSlot);
	UFUNCTION()
		void OnDataCancelled();

};
