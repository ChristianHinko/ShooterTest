// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "GA_FireGun.generated.h"

class AGATA_BulletTrace;
class UAS_Ammo;
class UGunStack;
class UAT_SSWaitTargetData;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGA_FireGun : public USSGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_FireGun();

protected:
	UPROPERTY(EditAnywhere, Category = "Effects To Apply")
		TSubclassOf<UGameplayEffect> FireEffectTSub;
	FActiveGameplayEffectHandle FireEffectActiveHandle;



	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface


	UPROPERTY()
		UGunStack* GunToFire;
	UPROPERTY()
		AGATA_BulletTrace* BulletTraceTargetActor;
	UPROPERTY()
		UAS_Ammo* AmmoAttributeSet;

	UFUNCTION()
		void OnFullAutoTick(float DeltaTime, float CurrentTime, float TimeRemaining);

	void Fire();

	UFUNCTION()
		void OnRelease(float TimeHeld);
	UFUNCTION()
		void OnValidData(const FGameplayAbilityTargetDataHandle& Data);
	UFUNCTION()
		void OnCancelled(const FGameplayAbilityTargetDataHandle& Data);

private:
	int32 timesBursted;
};
