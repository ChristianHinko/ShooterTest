// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "GA_StaminaRegen.generated.h"

class AAbilitySystemCharacter;


/**
 * 
 */
UCLASS()
class SONICSIEGE_API UGA_StaminaRegen : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_StaminaRegen();


protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> StaminaGainEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle StaminaGainActiveHandle;
	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;

	//BEGIN UGameplayAbility Interface
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	virtual void BeginDestroy() override;

	FTimerHandle TickTimerHandle;

#pragma region Gameplay Tags
	FGameplayTag TagOutOfStamina;
	FGameplayTag TagRunning;
#pragma endregion
};
