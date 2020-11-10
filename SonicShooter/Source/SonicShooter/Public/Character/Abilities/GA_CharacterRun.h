// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "GA_CharacterRun.generated.h"

class AAbilitySystemCharacter;
class USSCharacterMovementComponent;
class UAS_Character;
class UAbilityTask_WaitInputPress;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGA_CharacterRun : public USSGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_CharacterRun();


protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> RunningEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle RunningEffectActiveHandle;

	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;
	UPROPERTY()
		USSCharacterMovementComponent* CMC;
	UPROPERTY()
		UAS_Character* CharacterAttributeSet;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> DisableRunEffectTSub;	// asset manager we need you D:



	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	UFUNCTION()
		void OnTick(float DeltaTime, float currentTime, float timeRemaining);
	bool ShouldBeAbleToRun() const;

	UFUNCTION()
		void OnStaminaFullyDrained();
	UFUNCTION()
		void OnWasNotAbleToRun();

#pragma region Gameplay Tags
	FGameplayTag RunDisabledTag;
#pragma endregion

	UAbilityTask_WaitInputPress* InputPressTask;
	// We want to give the player option to togle or hold so we will need to do some small rework in future
	UFUNCTION()
		virtual void OnRelease(float TimeHeld);		
	UFUNCTION()
		virtual void OnPress(float TimeElapsed);
};
