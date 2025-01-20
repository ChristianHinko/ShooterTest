// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/STGameplayAbility.h"

#include "STGameplayAbility_ADS.generated.h"

/**
 *
 */
UCLASS()
class SHOOTERTEST_API USTGameplayAbility_ADS : public USTGameplayAbility
{
    GENERATED_BODY()

public:
    USTGameplayAbility_ADS(const FObjectInitializer& ObjectInitializer);

protected:
    UPROPERTY(EditAnywhere)
        TSubclassOf<UGameplayEffect> ADSEffectTSub;    // asset manager we need you D:
    FActiveGameplayEffectHandle ADSEffectActiveHandle;

    //  BEGIN UGameplayAbility Interface
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
    virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
    //  END UGameplayAbility Interface

    // ~ IASSGameplayAbilityExtensionInterface overrides.
    virtual void ASSEndAbility(
        const FGameplayAbilitySpecHandle& inSpecHandle,
        const FGameplayAbilityActorInfo& inActorInfo,
        const FGameplayAbilityActivationInfo& inActivationInfo,
        const bool inShouldReplicateEndAbility,
        const bool inWasCanceled) override;
    // ~ IASSGameplayAbilityExtensionInterface overrides.

    UFUNCTION()
        virtual void OnRelease(float TimeHeld);
};
