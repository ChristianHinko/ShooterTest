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
 * 
 * Note: In its current state, UO_Stamina isn't super modular, since it requries a supposed "UAS_Stamina". This means in order
 * for your game to use this UObject, it would require you to create an "UAS_Stamina" attribute set with those required attributes.
 * To decouple, we could use injection so you can give the UObject values without it knowing where you got it from (but we haven't don't this yet).
 */
UCLASS()
class SONICSHOOTER_API UO_Stamina : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override;
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);

public:
	UO_Stamina(const FObjectInitializer& ObjectInitializer);
	void SetStaminaDraining(bool newStaminaDraining);

	// BEGIN exposed floats
	float MaxStamina;
	float StaminaDrain;
	float StaminaGain;
	float StaminaRegenPause;
	// END exposed floats


	TSharedRef<FFloatValueChange> OnStaminaChange;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Stamina")
		FFloatPropertyWrapper Stamina;

	FStaminaStatus OnStaminaFullyDrained;
	FStaminaStatus OnStaminaFullyGained;
protected:
	// BEGIN FTickableObjectBase interface
	virtual bool IsTickable() const override { return bShouldTick; }	// IsTickable() gets ignored if ETickableTickType is set to "Always" or "Never". If you don't want this. If you want it to always be checked you would instead use IsAllowedToTick() ( in most cases just use IsTickable() )
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { return TStatId(); }
	// END FTickableObjectBase interface
	virtual void SetShouldTick(bool newShouldTick);

	// BEGIN FTickableGameObject interface
	virtual bool IsTickableWhenPaused() const override { return false; }
	// END FTickableGameObject interface
private:
	bool bShouldTick;

	bool bStaminaDraining;
	float TimeSinceStaminaDrain;
};
