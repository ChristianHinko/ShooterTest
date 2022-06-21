// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "SSGameplayAbility_Reload.generated.h"


class USSObject_ClipAmmo;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSGameplayAbility_Reload : public UASSGameplayAbility
{
	GENERATED_BODY()

public:
	USSGameplayAbility_Reload(const FObjectInitializer& ObjectInitializer);


protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> ReloadingEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle ReloadingEffectActiveHandle;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> DepleteBackupAmmoEffectTSub;	// asset manager we need you D:


	//BEGIN UGameplayAbility Interface
	virtual void ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	UPROPERTY()
		TWeakObjectPtr<USSObject_ClipAmmo> ClipAmmoSubobject;
};
