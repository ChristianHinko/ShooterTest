// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "Interfaces/Interactable.h"

#include "GA_CharacterInstantInteract.generated.h"

class AAbilitySystemCharacter;

/**
 * 
 */
UCLASS()
class SONICSIEGE_API UGA_CharacterInstantInteract : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_CharacterInstantInteract();

	IInteractable* Interactable;
protected:
	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;


	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface





#pragma region Gameplay Tags

#pragma endregion
};
