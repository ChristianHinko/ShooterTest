// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "GA_ADS.generated.h"

/**
 * 
 */
UCLASS()
class SONICSIEGE_API UGA_ADS : public USSGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_ADS();

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> ADSEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle ADSEffectActiveHandle;

	//BEGIN UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	UFUNCTION()
		virtual void OnRelease(float TimeHeld);

#pragma region Gameplay Tags
	FGameplayTag TagAimingDownSights;
#pragma endregion
};
