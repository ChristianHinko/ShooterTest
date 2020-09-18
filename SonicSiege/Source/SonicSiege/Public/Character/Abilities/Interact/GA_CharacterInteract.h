// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "Interfaces/Interactable.h"

#include "GA_CharacterInteract.generated.h"

class ASiegeCharacter;

/**
 * 
 */
UCLASS(Abstract)
class SONICSIEGE_API UGA_CharacterInteract : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_CharacterInteract();

	IInteractable* Interactable;
protected:
	UPROPERTY()
		TSubclassOf<UGameplayEffect> InteractEffectTSub;	// Implementor assigns this so we don't need "EditAnywhere"
	FActiveGameplayEffectHandle InteractEffectActiveHandle;

	UPROPERTY()
		ASiegeCharacter* SiegeCharacter;

	EDurationInteractEndReason InteractEndReason;
	float timeHeld;

#pragma region Tags
	
#pragma endregion


	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	//END UGameplayAbility Interface
};
