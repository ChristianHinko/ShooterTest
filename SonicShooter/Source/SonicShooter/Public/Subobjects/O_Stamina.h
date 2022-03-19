// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wrappers/PropertyWrappers.h"

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
	virtual bool IsSupportedForNetworking() const override;
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);

	UO_Stamina(const FObjectInitializer& ObjectInitializer);


	TSharedRef<FFloatValueChange> OnStaminaChange;
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Stamina")
		FFloatPropertyWrapper Stamina;


	void SetMaxStamina(float newMaxStamina);
	void SetStaminaDrain(float newValue)		{ StaminaDrain			= newValue; }
	void SetStaminaGain(float newValue)			{ StaminaGain			= newValue; }
	void SetStaminaRegenPause(float newValue)	{ StaminaRegenPause		= newValue; }


	void SetStaminaDraining(bool newStaminaDraining);

	FStaminaStatus OnStaminaFullyDrained;
	FStaminaStatus OnStaminaFullyGained;

protected:
	virtual void SetShouldTick(bool newShouldTick);

	// BEGIN FTickableObjectBase interface
	virtual bool IsTickable() const override { return bShouldTick; }	// IsTickable() gets ignored if ETickableTickType is set to "Always" or "Never". If you don't want this. If you want it to always be checked you would instead use IsAllowedToTick() ( in most cases just use IsTickable() )
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { return TStatId(); }
	// END FTickableObjectBase interface
	// BEGIN FTickableGameObject interface
	virtual bool IsTickableWhenPaused() const override { return false; }
	// END FTickableGameObject interface

private:
	bool bShouldTick;

	bool bStaminaDraining;
	float TimeSinceStaminaDrain;

	float MaxStamina;
	float StaminaDrain;
	float StaminaGain;
	float StaminaRegenPause;
};
