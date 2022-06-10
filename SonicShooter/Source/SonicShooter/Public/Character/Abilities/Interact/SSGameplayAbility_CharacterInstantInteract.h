// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character\Abilities\Interact\SSGameplayAbility_CharacterInteract.h"

#include "SSGameplayAbility_CharacterInstantInteract.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSGameplayAbility_CharacterInstantInteract : public USSGameplayAbility_CharacterInteract
{
	GENERATED_BODY()

public:
	USSGameplayAbility_CharacterInstantInteract(const FObjectInitializer& ObjectInitializer);
protected:
	//BEGIN UGameplayAbility Interface
	virtual void ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface





#pragma region Gameplay Tags

#pragma endregion
};
