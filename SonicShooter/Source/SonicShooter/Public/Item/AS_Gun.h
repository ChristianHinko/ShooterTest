// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "GameplayAbilities/Public/TickableAttributeSetInterface.h"
#include "AbilitySystemComponent.h"

#include "AS_Gun.generated.h"


class USSArcInventoryComponent_Active;
class USSCharacterMovementComponent;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAS_Gun : public USSAttributeSet, public ITickableAttributeSetInterface
{
	GENERATED_BODY()

public:
	UAS_Gun();


	// Attributes:

	/**
	 * The minimum bullet spread while staying still in degrees (90 degs would be a right-angled cone)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MinBulletSpread, Category = "Attributes")
		FGameplayAttributeData MinBulletSpread;
	ATTRIBUTE_ACCESSORS(UAS_Gun, MinBulletSpread)

	/**
	 * The minimum bullet spread while moving in degrees (90 degs would be a right-angled cone)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovingBulletSpread, Category = "Attributes")
		FGameplayAttributeData MovingBulletSpread;
	ATTRIBUTE_ACCESSORS(UAS_Gun, MovingBulletSpread)

	/**
	 * The rate of increase in bullet spread in degrees per second. Will be continuously increasing spread by
	 * this rate while moving until we've reached MovingBulletSpread
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpreadMovingIncRate, Category = "Attributes")
		FGameplayAttributeData BulletSpreadMovingIncRate;
	ATTRIBUTE_ACCESSORS(UAS_Gun, BulletSpreadMovingIncRate)

	/**
	 * The increase in bullet spread per shot in degrees
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpreadIncPerShot, Category = "Attributes")
		FGameplayAttributeData BulletSpreadIncPerShot;
	ATTRIBUTE_ACCESSORS(UAS_Gun, BulletSpreadIncPerShot)

	/**
	 * The rate of decrease in bullet spread in degrees per second. Will be continuously decreasing spread by
	 * this rate until reached minimum spread (or moving spread if we are moving)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpreadDecSpeed, Category = "Attributes")
		FGameplayAttributeData BulletSpreadDecSpeed;
	ATTRIBUTE_ACCESSORS(UAS_Gun, BulletSpreadDecSpeed)


	/**
	 * Current bullet spread. Non-replicated because set every frame
	 */
	UPROPERTY(BlueprintReadOnly/*, ReplicatedUsing = OnRep_CurrentBulletSpread*/, Category = "Attributes", meta = (HideFromModifiers))
		FGameplayAttributeData CurrentBulletSpread;
	ATTRIBUTE_ACCESSORS(UAS_Gun, CurrentBulletSpread)




	/**
	* The number of bullets every fire will shoot out
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_NumberOfBulletsPerFire, Category = "Attributes")
		FGameplayAttributeData NumberOfBulletsPerFire;
	ATTRIBUTE_ACCESSORS(UAS_Gun, NumberOfBulletsPerFire)

	/**
	 * 
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageFalloff, Category = "Attributes")
		FGameplayAttributeData DamageFalloff;
	ATTRIBUTE_ACCESSORS(UAS_Gun, DamageFalloff)

	/**
	 * Minimum time that must pass before we can fire again
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireRate, Category = "Attributes")
		FGameplayAttributeData FireRate;
	ATTRIBUTE_ACCESSORS(UAS_Gun, FireRate)

	/**
	 * Number of bursts (ie. 3 for 3-round burst)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_NumBursts, Category = "Attributes")
		FGameplayAttributeData NumBursts;
	ATTRIBUTE_ACCESSORS(UAS_Gun, NumBursts)

	/**
	 * Bullets per second for auto-type shooting
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AutoShootingRate, Category = "Attributes")
		FGameplayAttributeData AutoShootingRate;
	ATTRIBUTE_ACCESSORS(UAS_Gun, AutoShootingRate)


	/**
	 * How much clip ammo will we lose for each shot. (Pretty much always just 1 but it's here if you need it)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AmmoCost, Category = "Attributes")
		FGameplayAttributeData AmmoCost;
	ATTRIBUTE_ACCESSORS(UAS_Gun, AmmoCost)




	bool IsMovingToIncBulletSpread() const;

	float GetRestBulletSpread() const;

	void FireBulletSpread();


protected:
	virtual void PostInitProperties() override;


	virtual void SetSoftAttributeDefaults() override;


	void OnActorInfoInited();

	void UpdateFromActorInfo();

	USSArcInventoryComponent_Active* Inventory;
	UFUNCTION()
		void OnInventoryItemActive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack);
	UFUNCTION()
		void OnInventoryItemInactive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack);

	USSCharacterMovementComponent* CMC;

	void OnAccelerationStartCMC();
	void OnAccelerationStopCMC();

	void OnStartedFallingCMC();
	void OnStoppedFallingCMC();



	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTick() const override;





	UFUNCTION()
		virtual void OnRep_MinBulletSpread(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_MovingBulletSpread(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BulletSpreadMovingIncRate(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BulletSpreadIncPerShot(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BulletSpreadDecSpeed(const FGameplayAttributeData& ServerBaseValue);



	UFUNCTION()
		virtual void OnRep_NumberOfBulletsPerFire(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_DamageFalloff(const FGameplayAttributeData& ServerBaseValue);



	UFUNCTION()
		virtual void OnRep_FireRate(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_NumBursts(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_AutoShootingRate(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_AmmoCost(const FGameplayAttributeData& ServerBaseValue);
};
