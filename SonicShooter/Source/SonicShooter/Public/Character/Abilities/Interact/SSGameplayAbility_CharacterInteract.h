// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"
#include "Interfaces/SSInteractableInterface.h"

#include "SSGameplayAbility_CharacterInteract.generated.h"

class ASSCharacter_Shooter;

/**
 * 
 */
UCLASS(Abstract)
class SONICSHOOTER_API USSGameplayAbility_CharacterInteract : public UASSGameplayAbility
{
	GENERATED_BODY()

public:
	USSGameplayAbility_CharacterInteract();

	ISSInteractableInterface* Interactable;
protected:
	UPROPERTY()
		TSubclassOf<UGameplayEffect> InteractEffectTSub;	// Implementor assigns this so we don't need "EditAnywhere"
	FActiveGameplayEffectHandle InteractEffectActiveHandle;

	UPROPERTY()
		TWeakObjectPtr<ASSCharacter_Shooter> ShooterCharacter;

	ESSDurationInteractEndReason InteractEndReason;
	float timeHeld;

#pragma region Tags
	
#pragma endregion


	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSetThatWorks(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	//END UGameplayAbility Interface
};
