// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Abilities/Interact/STGameplayAbility_CharacterInteract.h"

#include "STGameplayAbility_CharacterDurationInteract.generated.h"

/**
 *    TODO: Currently the abilty only does a check if both client and server have an interactable. If one of them don't, it doesn't activate.
 *  But another check is needed for this system to be fully stable. We need to make another check to see if the client and server have the
 *  same object as theinteractable.
 */
UCLASS()
class SHOOTERTEST_API USTGameplayAbility_CharacterDurationInteract : public USTGameplayAbility_CharacterInteract
{
    GENERATED_BODY()

public:
    USTGameplayAbility_CharacterDurationInteract(const FObjectInitializer& ObjectInitializer);
protected:
    ESTDurationInteractEndReason InteractEndReason;
    float timeHeld;


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
    UFUNCTION()
        void OnInteractTick(float DeltaTime, float TimeHeld);
    UFUNCTION()
        void OnRelease(float TimeHeld);
    UFUNCTION()
        void OnInteractionSweepMiss(float TimeHeld);
    UFUNCTION()
        void OnCharacterLeftInteractionOverlap(float TimeHeld);
    UFUNCTION()
        void OnNewInteractionPriority(float TimeHeld);
    UFUNCTION()
        void OnSuccessfullInteract(float TimeHeld);
};
