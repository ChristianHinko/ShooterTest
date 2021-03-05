// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"

#include "GA_Reload.generated.h"

class UAS_Ammo;

/**
 *
 */
UCLASS()
class SONICSHOOTER_API UGA_Reload : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Reload();


protected:
	//UPROPERTY(EditAnywhere)
	//	TSubclassOf<UGameplayEffect> MyEffectTSub;	// asset manager we need you D:
	//FActiveGameplayEffectHandle MyEffectActiveHandle;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> DepleteBackupAmmoEffectTSub;	// asset manager we need you D:


	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface


	UAS_Ammo* AmmoAttributeSet;
};
