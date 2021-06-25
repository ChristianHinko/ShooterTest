// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "GA_FireGun.generated.h"


class AGATA_BulletTrace;
class UAS_Gun;
class UAS_Ammo;
class UGunStack;
class USSAbilityTask_WaitTargetData;
class UAT_Ticker;



/**
 * Notes:
 *	This seems to be overall a really good implementation, however, we are creating a PlayMontageAndWait task every shot and playing the shoot montage, which may
 *	become a problem over the network with fast rate of fire guns such at the Vector from MW2. We could maybe optimize what we send over the network if we want to later.
 */
UCLASS()
class SONICSHOOTER_API UGA_FireGun : public UASSGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_FireGun();

protected:
	UPROPERTY(EditAnywhere, Category = "Effects To Apply")
		TSubclassOf<UGameplayEffect> IsFireingGunEffectTSub;
	FActiveGameplayEffectHandle IsFireingGunEffectActiveHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* ShootMontage;

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
		void OnValidData(const FGameplayAbilityTargetDataHandle& Data);
	UFUNCTION()
		void OnCancelled(const FGameplayAbilityTargetDataHandle& Data);



#pragma region Helpers
	bool EnoughAmmoToShoot() const;
#pragma endregion



	UFUNCTION()
		void OnRelease(float TimeHeld);

private:
	int32 timesBursted; // we could get the current burst by % modding shotNumber by NumShotsPerBurst but i think this would be less reliable: what if they cancel a burst and don't shoot all of the burst. Or what if NumShotsPerBurst changes while shooting

	float timestampPreviousFireEnd;
	// Client only bool
	uint8 bInputPressed : 1;
};
