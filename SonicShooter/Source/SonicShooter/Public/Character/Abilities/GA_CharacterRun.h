// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "GA_CharacterRun.generated.h"

class AAbilitySystemCharacter;
class USSCharacterMovementComponent;
class UAS_Character;


/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGA_CharacterRun : public USSGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_CharacterRun();


protected:
	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;
	UPROPERTY()
		USSCharacterMovementComponent* CMC;
	UPROPERTY()
		UAS_Character* CharacterAttributeSet;



	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

#pragma region Gameplay Tags

#pragma endregion

	UFUNCTION()
		virtual void OnRelease(float TimeHeld);
};
