// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "STGameplayAbility_CharacterJump.generated.h"



/**
 * This is a nice minimal implementation of the CMC jumping into the ability system
 */
UCLASS()
class SHOOTERTEST_API USTGameplayAbility_CharacterJump : public UASSGameplayAbility
{
	GENERATED_BODY()

public:
	USTGameplayAbility_CharacterJump(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> JumpEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle JumpEffectActiveHandle;

	//  BEGIN UGameplayAbility Interface
	virtual void ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//  END UGameplayAbility Interface
};
