// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbility.h"

#include "GA_FireGun.generated.h"


class AGATA_BulletTrace;
class UAS_Gun;
class UAS_Ammo;
class UGunStack;
class USSAbilityTask_WaitTargetData;
class UAT_Ticker;



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
		TSubclassOf<UGameplayEffect> IsFireingGunEffectTSub;
	FActiveGameplayEffectHandle IsFireingGunEffectActiveHandle;

	// Used to give each fire a unique random seed since machine guns only have 1 prediction key across fires
	int32 shotNumber;


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
		UAS_Gun* GunAttributeSet;
	UPROPERTY()
		UAS_Ammo* AmmoAttributeSet;

	void Shoot();

	UAT_Ticker* TickerTask;
	UFUNCTION()
		void OnShootTick(float DeltaTime, float CurrentTime, float TimeRemaining);

	UFUNCTION()
		void OnRelease(float TimeHeld);
	UFUNCTION()
		void OnValidData(const FGameplayAbilityTargetDataHandle& Data);
	UFUNCTION()
		void OnCancelled(const FGameplayAbilityTargetDataHandle& Data);

private:
	int32 timesBursted; // we could get the current burst by % modding shotNumber by NumShotsPerBurst but i think this would be less reliable: what if they cancel a burst and don't shoot all of the burst. Or what if NumShotsPerBurst changes while shooting

	float timestampPreviousFireEnd;
};
