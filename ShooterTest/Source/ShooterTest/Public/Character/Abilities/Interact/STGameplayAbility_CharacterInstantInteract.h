// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Abilities/Interact/STGameplayAbility_CharacterInteract.h"

#include "STGameplayAbility_CharacterInstantInteract.generated.h"

/**
 *
 */
UCLASS()
class SHOOTERTEST_API USTGameplayAbility_CharacterInstantInteract : public USTGameplayAbility_CharacterInteract
{
    GENERATED_BODY()

public:
    USTGameplayAbility_CharacterInstantInteract(const FObjectInitializer& ObjectInitializer);
protected:
    //  BEGIN UGameplayAbility Interface
    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
    //  END UGameplayAbility Interface

    // ~ IASSGameplayAbilityExtensionInterface overrides.
    virtual void ASSEndAbility(
        const FGameplayAbilitySpecHandle& inSpecHandle,
        const FGameplayAbilityActorInfo& inActorInfo,
        const FGameplayAbilityActivationInfo& inActivationInfo,
        const bool inShouldReplicateEndAbility,
        const bool inWasCanceled) override;
    // ~ IASSGameplayAbilityExtensionInterface overrides.




#pragma region Gameplay Tags

#pragma endregion
};
