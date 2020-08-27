// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "GA_Fire.generated.h"

class AGATA_LineTrace;

/**
 * 
 */
UCLASS()
class SONICSIEGE_API UGA_Fire : public USSGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Fire();

protected:
	UPROPERTY(EditAnywhere, Category = "Effects To Apply")
		TSubclassOf<UGameplayEffect> FireEffectTSub;
	FActiveGameplayEffectHandle FireEffectActiveHandle;
	UPROPERTY(EditAnywhere, Category = "Effects To Apply")
		TSubclassOf<UGameplayEffect> BulletHitEffectTSub;

	UPROPERTY(EditAnywhere, Category = "Target Actor Config")
		TEnumAsByte<ECollisionChannel> TraceChannel;
	UPROPERTY(EditAnywhere, Category = "Target Actor Config")
		uint8 numberOfLines;
	UPROPERTY(EditAnywhere, Category = "Target Actor Config")
		float scatterRadius;



	//BEGIN UGameplayAbility Interface
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface

	UPROPERTY()
		AGATA_LineTrace* TargetTraceActor;

	UFUNCTION()
		void OnValidData(const FGameplayAbilityTargetDataHandle& Data);
	UFUNCTION()
		void OnCancelled(const FGameplayAbilityTargetDataHandle& Data);
};
