// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "STGameplayAbility_CharacterRun.generated.h"


class ASTCharacter;
class USTCharacterMovementComponent;



/**
 * 
 */
UCLASS()
class SHOOTERTEST_API USTGameplayAbility_CharacterRun : public UASSGameplayAbility
{
    GENERATED_BODY()

public:
    USTGameplayAbility_CharacterRun(const FObjectInitializer& ObjectInitializer);


protected:
    UPROPERTY(EditAnywhere)
        TSubclassOf<UGameplayEffect> RunningEffectTSub;    // asset manager we need you D:
    FActiveGameplayEffectHandle RunningEffectActiveHandle;

    UPROPERTY()
        TWeakObjectPtr<ASTCharacter> STCharacter;
    UPROPERTY()
        TWeakObjectPtr<USTCharacterMovementComponent> CMC;



    //  BEGIN UGameplayAbility Interface
    virtual void ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
    //  END UGameplayAbility Interface
};
