// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "STAttributeSet_Stamina.generated.h"



/**
 *
 */
UCLASS()
class SHOOTERTEST_API USTAttributeSet_Stamina : public UASSAttributeSet
{
	GENERATED_BODY()

public:
	USTAttributeSet_Stamina(const FObjectInitializer& ObjectInitializer);


	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Attributes")
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(USTAttributeSet_Stamina, MaxStamina)

	/** How fast your stamina drains while running */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaDrain, Category = "Attributes")
		FGameplayAttributeData StaminaDrain;
	ATTRIBUTE_ACCESSORS(USTAttributeSet_Stamina, StaminaDrain)

	/** How fast your stamina regenerates durring stamina regeneration */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaGain, Category = "Attributes")
		FGameplayAttributeData StaminaGain;
	ATTRIBUTE_ACCESSORS(USTAttributeSet_Stamina, StaminaGain)

	/** The time it takes for your stamina to start regening again (the pause) */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegenPause, Category = "Attributes")
		FGameplayAttributeData StaminaRegenPause;
	ATTRIBUTE_ACCESSORS(USTAttributeSet_Stamina, StaminaRegenPause)

protected:
	// OnReps
	UFUNCTION()
		virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_StaminaDrain(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_StaminaGain(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_StaminaRegenPause(const FGameplayAttributeData& OldValue);
};
