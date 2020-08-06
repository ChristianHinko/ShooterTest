// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"

#include "GA_CharacterJump.generated.h"



/**
 * This is a nice minimal implementation of the CMC jumping into the ability system
 */
UCLASS()
class SONICSIEGE_API UGA_CharacterJump : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_CharacterJump();

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> JumpEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle JumpEffectActiveHandle;

	//BEGIN UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	UFUNCTION()
		virtual void OnRelease(float TimeHeld);
};
