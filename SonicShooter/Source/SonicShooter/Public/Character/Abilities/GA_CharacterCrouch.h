// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"

#include "GA_CharacterCrouch.generated.h"

class AAbilitySystemCharacter;
class USSCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGA_CharacterCrouch : public USSGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_CharacterCrouch();


protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> CrouchingEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle CrouchingEffectActiveHandle;

	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;
	UPROPERTY()
		USSCharacterMovementComponent* CMC;



	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface
};