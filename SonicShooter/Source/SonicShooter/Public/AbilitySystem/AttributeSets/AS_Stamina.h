// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAttributeSet.h"
#include "GameplayAbilities/Public/TickableAttributeSetInterface.h"
#include "AbilitySystemComponent.h"
#include "Wrappers/PropertyWrappers.h"

#include "AS_Stamina.generated.h"



DECLARE_MULTICAST_DELEGATE(FStaminaStatus)


/**
 *
 */
UCLASS()
class SONICSHOOTER_API UAS_Stamina : public UASSAttributeSet, public ITickableAttributeSetInterface
{
	GENERATED_BODY()

public:
	UAS_Stamina();

#pragma region Stamina Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Attributes")
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UAS_Stamina, MaxStamina)

		UPROPERTY(BlueprintReadOnly, Replicated, Category = "Attributes")
		FFloatPropertyWrapper Stamina;

	/** How fast your stamina drains while running */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaDrain, Category = "Attributes")
		FGameplayAttributeData StaminaDrain;
	ATTRIBUTE_ACCESSORS(UAS_Stamina, StaminaDrain)

		void SetStaminaDraining(bool newStaminaDraining);

	FStaminaStatus OnStaminaFullyDrained;
	FStaminaStatus OnStaminaFullyGained;

	/** How fast your stamina regenerates durring stamina regeneration */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaGain, Category = "Attributes")
		FGameplayAttributeData StaminaGain;
	ATTRIBUTE_ACCESSORS(UAS_Stamina, StaminaGain)

		/** The time it takes for your stamina to start regening again (the pause) */
		UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegenPause, Category = "Attributes")
		FGameplayAttributeData StaminaRegenPause;
	ATTRIBUTE_ACCESSORS(UAS_Stamina, StaminaRegenPause)
#pragma endregion

protected:
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTick() const override;
	virtual void SetShouldTick(bool newShouldTick);


	UFUNCTION()
		virtual void OnRep_MaxStamina(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_StaminaDrain(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_StaminaGain(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_StaminaRegenPause(const FGameplayAttributeData& ServerBaseValue);

private:
	bool bShouldTick;

	bool bStaminaDraining;
	float timeSinceStaminaDrain;
};
