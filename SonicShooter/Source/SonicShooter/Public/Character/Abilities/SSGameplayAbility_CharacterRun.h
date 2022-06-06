// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "SSGameplayAbility_CharacterRun.generated.h"


class ASSCharacter;
class USSCharacterMovementComponent;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSGameplayAbility_CharacterRun : public UASSGameplayAbility
{
	GENERATED_BODY()

public:
	USSGameplayAbility_CharacterRun();


protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> RunningEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle RunningEffectActiveHandle;

	UPROPERTY()
		TWeakObjectPtr<ASSCharacter> SSCharacter;
	UPROPERTY()
		TWeakObjectPtr<USSCharacterMovementComponent> CMC;



	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSetThatWorks(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface
};
