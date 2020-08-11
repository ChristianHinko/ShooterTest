// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem\SSGameplayAbility.h"



#include "GA_StaminaRegen.generated.h"


class AAbilitySystemCharacter;
class UAT_StaminaRegen;

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
		TSubclassOf<UAT_StaminaRegen> StaminaRegenTaskTSub;	// asset manager we need you D:
	UAT_StaminaRegen* StaminaRegenTask;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> StaminaGainEffectTSub;	// asset manager we need you D:

	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;

	//BEGIN UGameplayAbility Interface
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	//	Don't make this a UFUNCTION because otherwise the struct parameter causes an error
	void OnStaminaAttributeChange(const FOnAttributeChangeData& Data);

	//	Task Events....
	void OnTimerTick();
	void OnRegenTaskEnd();
	//

	virtual void BeginDestroy() override;

#pragma region Gameplay Tags
	FGameplayTag TagHasMaxStamina;
	FGameplayTag TagRunning;
#pragma endregion
};
