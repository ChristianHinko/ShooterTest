// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "SSGameplayAbility_FireGun.generated.h"


class ASSGameplayAbilityTargetActor_BulletTrace;
class USSAttributeSet_Gun;
class USSObject_ClipAmmo;
class USSObject_BulletSpread;
class USSItemStack_Gun;
class USSAbilityTask_WaitTargetData;
class UASSEAbilityTask_Ticker;
struct FOnAttributeChangeData;



/**
 * Notes:
 *	This seems to be overall a really good implementation, however, we are creating a PlayMontageAndWait task every shot and playing the shoot montage, which may
 *	become a problem over the network with fast rate of fire guns such at the Vector from MW2. We could maybe optimize what we send over the network if we want to later.
 */
UCLASS()
class SONICSHOOTER_API USSGameplayAbility_FireGun : public UASSGameplayAbility
{
	GENERATED_BODY()
	
public:
	USSGameplayAbility_FireGun(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, Category = "Effects To Apply")
		TSubclassOf<UGameplayEffect> IsFiringGunEffectTSub;
	FActiveGameplayEffectHandle IsFiringGunEffectActiveHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		TObjectPtr<UAnimMontage> ShootMontage;

	// Used to give each fire a unique random seed since machine guns only have 1 prediction key across fires
	int32 ShotNumber;


	//BEGIN UGameplayAbility Interface
	virtual void ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual bool CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//END UGameplayAbility Interface


	/**
	 * Our gun source object
	 */
	UPROPERTY()
		TWeakObjectPtr<USSItemStack_Gun> GunToFire;
	UPROPERTY()
		TWeakObjectPtr<USSObject_ClipAmmo> ClipAmmoSubobject;
	UPROPERTY()
		TWeakObjectPtr<USSObject_BulletSpread> BulletSpreadSubobject;

	/**
	 * Our spawned Target Actor from the GunToFire.
	 * NOTE: this is spawned every time the Ability is given and destroyed on Ability cleared. Maybe
	 * instead we should keep the Actor alive on the GunToFire - but then it is less scalable.
	 */
	UPROPERTY()
		TObjectPtr<ASSGameplayAbilityTargetActor_BulletTrace> BulletTraceTargetActor;

	/**
	 * Actually shoot a bullet out of our GunToFire
	 */
	void Shoot();


	UPROPERTY()
		TObjectPtr<UASSEAbilityTask_Ticker> TickerTask;

	UFUNCTION()
		void OnShootTick(float DeltaTime, float CurrentTime, float TimeRemaining);

	UFUNCTION()
		void OnValidData(const FGameplayAbilityTargetDataHandle& Data);
	UFUNCTION()
		void OnCancelled(const FGameplayAbilityTargetDataHandle& Data);


	//BEGIN Attribute Set helpers
	bool IsFullAuto() const;
	bool IsBurst() const;

	float GetTimeBetweenFires() const;
	float GetTimeBetweenBursts() const;

	bool CurrentlyBursting() const;
	//END Attribute Set helpers



	UFUNCTION()
		void OnPress(float TimeWaited);
	UFUNCTION()
		void OnRelease(float TimeHeld);

private:
	int32 TimesBursted; // we could get the current burst by % modding shotNumber by NumShotsPerBurst but i think this would be less reliable: what if they cancel a burst and don't shoot all of the burst. Or what if NumShotsPerBurst changes while shooting

	float TimestampPreviousFireEnd;
	// Client only bool
	uint8 bInputPressed : 1;



	// BEGIN Attribute value change
	
	// For attributes used in the SSGameplayAbility_FireGun
	float AmmoCost;
	void OnAmmoCostChange(const FOnAttributeChangeData& Data) { AmmoCost = Data.NewValue; }

	float NumShotsPerBurst;
	void OnNumShotsPerBurstChange(const FOnAttributeChangeData& Data) { NumShotsPerBurst = Data.NewValue; }

	float bFullAuto;
	void OnbFullAutoChange(const FOnAttributeChangeData& Data) { bFullAuto = Data.NewValue; }

	float TimeBetweenFiresOverride;
	void OnTimeBetweenFiresOverrideChange(const FOnAttributeChangeData& Data) { TimeBetweenFiresOverride = Data.NewValue; }

	float TimeBetweenShots;
	void OnTimeBetweenShotsChange(const FOnAttributeChangeData& Data);

	float TimeBetweenBurstsOverride;
	void OnTimeBetweenBurstsOverrideChange(const FOnAttributeChangeData& Data) { TimeBetweenBurstsOverride = Data.NewValue; }

	// For attributes to inject into the SSGameplayAbilityTargetActor_BulletTrace
	float MaxRange;
	void OnMaxRangeChange(const FOnAttributeChangeData& Data);

	float NumberOfBulletsPerFire;
	void OnNumberOfBulletsPerFireChange(const FOnAttributeChangeData& Data);

	float Penetrations;
	void OnPenetrationsChange(const FOnAttributeChangeData& Data);

	float Ricochets;
	void OnRicochetsChange(const FOnAttributeChangeData& Data);

	float InitialBulletSpeed;
	void OnInitialBulletSpeedChange(const FOnAttributeChangeData& Data);

	float BulletSpeedFalloff;
	void OnBulletSpeedFalloffChange(const FOnAttributeChangeData& Data);
	// END Attribute value change
};
