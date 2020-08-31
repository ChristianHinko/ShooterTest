// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "Interfaces/Interactable.h"

#include "GA_CharacterInteractDuration.generated.h"

class AAbilitySystemCharacter;

/**
 * This ability currently assumes you want duration to start over when stopped mid interaction. Can be implemented though
 */
UCLASS()
class SONICSIEGE_API UGA_CharacterInteractDuration : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_CharacterInteractDuration();

	IInteractable* Interactable;
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> InteractEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle InteractEffectActiveHandle;

	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;

	EDurationInteractEndReason InteractEndReason;
	float timeHeld;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	//BEGIN UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface





#pragma region Gameplay Tags

#pragma endregion
	UFUNCTION()
		virtual void OnInteractTick(float DeltaTime, float TimeHeld);
	UFUNCTION()
		virtual void OnRelease(float TimeHeld);
	UFUNCTION()
		virtual void OnInteractionSweepMiss(float TimeHeld);
	UFUNCTION()
		virtual void OnInteractCompleted(float TimeHeld);
};
