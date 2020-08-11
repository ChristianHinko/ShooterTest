// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem\SSGameplayAbility.h"



#include "GA_StaminaRegen.generated.h"


class AAbilitySystemCharacter;
class UAT_StaminaRegen;
class UAS_Character;

/**
 * 
 */
UCLASS()
class SONICSIEGE_API UGA_StaminaRegen : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_StaminaRegen();

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> StaminaGainEffectTSub;	// asset manager we need you D:

	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;
	UPROPERTY()
		UAS_Character* CharacterAttributeSet;

	//BEGIN UGameplayAbility Interface
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	//	Don't make this a UFUNCTION because otherwise the struct parameter causes an error
	void OnStaminaAttributeChange(const FOnAttributeChangeData& Data);

	virtual void BeginDestroy() override;

private:
	UFUNCTION()
		void OnTimerTick();

	FTimerHandle TickTimerHandle;
	FTimerDelegate TickTimerDel;

#pragma region Gameplay Tags
	FGameplayTag TagHasMaxStamina;
	FGameplayTag TagIsRunning;
	FGameplayTag TagIsRegeningStamina;
#pragma endregion
};
