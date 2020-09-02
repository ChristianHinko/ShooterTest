// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "Interfaces/Interactable.h"

#include "GA_CharacterDurationInteract.generated.h"

class AAbilitySystemCharacter;

/**
 * 
 */
UCLASS()
class SONICSIEGE_API UGA_CharacterDurationInteract : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_CharacterDurationInteract();

	IInteractable* Interactable;
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> InteractEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle InteractEffectActiveHandle;

	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;

	EDurationInteractEndReason InteractEndReason;
	float timeHeld;


	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface





#pragma region Gameplay Tags

#pragma endregion
	UFUNCTION()
		void OnInteractTick(float DeltaTime, float TimeHeld);
	UFUNCTION()
		void OnRelease(float TimeHeld);
	UFUNCTION()
		void OnInteractionSweepMiss(float TimeHeld);
	UFUNCTION()
		void OnInteractCompleted(float TimeHeld);
};
