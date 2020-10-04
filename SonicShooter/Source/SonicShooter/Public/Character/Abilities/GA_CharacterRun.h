// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"

#include "GA_CharacterRun.generated.h"

class AAbilitySystemCharacter;

/**
 * This serves as a good demonstration as to how you should go about making Instanced-per-Actor abilities. Or any kind really
 * Client and server must both call EndAbility(). NOTE: If you want to use bReplicateEndAbility in EndAbility() the client's 
 * ability must already be confirmed by the server. This means replicating EndAbility() to the server could fail (and often does).
 * This is a nice minimal implementation of the CMC running into the ability system.
 */
UCLASS()
class SONICSHOOTER_API UGA_CharacterRun : public USSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_CharacterRun();


protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> DrainStaminaFromRunEffectTSub;	// asset manager we need you D:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> RunningEffectTSub;	// asset manager we need you D:
	FActiveGameplayEffectHandle RunningEffectActiveHandle;
	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;


	//BEGIN UGameplayAbility Interface
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	virtual void BeginDestroy() override;

	FTimerHandle TickTimerHandle;
	FTimerDelegate TickTimerDel;

	UFUNCTION()
		void OnTimerTick();

#pragma region Gameplay Tags
	FGameplayTag TagOutOfStamina;
#pragma endregion

	UFUNCTION()
		virtual void OnRelease(float TimeHeld);
};
