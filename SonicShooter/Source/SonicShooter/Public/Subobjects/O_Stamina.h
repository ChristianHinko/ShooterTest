// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wrappers/PropertyWrappers.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"

#include "O_Stamina.generated.h"


class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE(FStaminaStatus)

/**
 * Has stamina float
 */
UCLASS()
class SONICSHOOTER_API UO_Stamina : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
		UO_Stamina(const FObjectInitializer& ObjectInitializer);
		virtual void PostInitProperties() override;

		void SetStaminaDraining(bool newStaminaDraining);



		TSharedRef<FFloatValueChange> OnStaminaChange;

		UPROPERTY(BlueprintReadOnly, Replicated, Category = "Stamina")
			FFloatPropertyWrapper Stamina;

		FStaminaStatus OnStaminaFullyDrained;
		FStaminaStatus OnStaminaFullyGained;

protected:
		//BEGIN FTickableObjectBase interface
		virtual bool IsTickable() const override;	// IsTickable() gets ignored if ETickableTickType is set to "Always" or "Never". If you don't want this. If you want it to always be checked you would instead use IsAllowedToTick() ( in most cases just use IsTickable() )
		virtual void Tick(float DeltaTime) override;
		virtual TStatId GetStatId() const override { return TStatId(); }
		//END FTickableObjectBase interface
		virtual void SetShouldTick(bool newShouldTick);

		//BEGIN FTickableGameObject interface
		virtual bool IsTickableWhenPaused() const override { return false; };
		//END FTickableGameObject interface

private:
	UAbilitySystemComponent* OwnerASC;
	bool bShouldTick;

	bool bStaminaDraining;
	float timeSinceStaminaDrain;



	float MaxStamina;
	void OnMaxStaminaAttributeChange(const FOnAttributeChangeData& Data) { MaxStamina = Data.NewValue; };

	float StaminaDrain;
	void OnStaminaDrainAttributeChange(const FOnAttributeChangeData& Data) { StaminaDrain = Data.NewValue; };

	float StaminaGain;
	void OnStaminaGainAttributeChange(const FOnAttributeChangeData& Data) { StaminaGain = Data.NewValue; };

	float StaminaRegenPause;
	void OnStaminaRegenPauseAttributeChange(const FOnAttributeChangeData& Data) { StaminaRegenPause = Data.NewValue; };
};
