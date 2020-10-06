// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAbilityTask.h"
#include "AT_StaminaRegen.generated.h"


DECLARE_MULTICAST_DELEGATE(UAT_StaminaRegenDelegate);

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAT_StaminaRegen : public USSAbilityTask
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	UAT_StaminaRegen();

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	UAT_StaminaRegenDelegate OnRegenStoppedDueToFillStaminaCompletelyDelegate;
	UAT_StaminaRegenDelegate OnRegenStoppedDueToSpecificTagPresenceDelegate;
	UAT_StaminaRegenDelegate OnTimerTickDelegate;


	/** The ability task was explicitly cancelled by another ability */
		UAT_StaminaRegenDelegate OnRegenCancelledDelegate;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UAT_StaminaRegen* AT_StaminaRegen(
			UGameplayAbility* OwningAbility,
			FName TaskInstanceName);

};
