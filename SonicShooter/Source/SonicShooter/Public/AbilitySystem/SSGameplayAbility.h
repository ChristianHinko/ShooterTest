// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "SSGameplayAbility.generated.h"



/**
 * Base gameplay ability class
 */
UCLASS()
class SONICSHOOTER_API USSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	bool ActivateAbilityOnGrant = false;
	USSGameplayAbility();

	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;


	//virtual void OnCurrentAbilityPredictionKeyRejected(); // Not implemented or hooked up yet

	virtual void OnActivationPredictionKeyRejected(); // Not implemented or hooked up yet

};

/** stupid */
#define TryCallOnAvatarSetOnPrimaryInstance																						\
if (HasAnyFlags(RF_ClassDefaultObject) && InstancingPolicy != EGameplayAbilityInstancingPolicy::NonInstanced)					\
{																																\
	if (UGameplayAbility* PrimaryInstance = Spec.GetPrimaryInstance())															\
	{																															\
		PrimaryInstance->OnAvatarSet(ActorInfo, Spec);																			\
		return;																													\
	}																															\
}																																
