// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "GameplayAbilities/Public/TickableAttributeSetInterface.h"
#include "AbilitySystemComponent.h"
#include "Utilities/PropertyWrappers.h"

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
#pragma region BulletSpread
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
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpreadIncRate, Category = "Attributes")
		FGameplayAttributeData BulletSpreadIncRate;
	ATTRIBUTE_ACCESSORS(UAS_Gun, BulletSpreadIncRate)

	/**
	 * The increase in bullet spread per shot in degrees
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireBulletSpread, Category = "Attributes")
		FGameplayAttributeData FireBulletSpread;
	ATTRIBUTE_ACCESSORS(UAS_Gun, FireBulletSpread)

	/**
	 * The speed of decrease in bullet spread to smooth interp to. Will be continuously interping spread at
	 * this speed until reached minimum spread (or moving spread if we are moving)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpreadDecSpeed, Category = "Attributes")
		FGameplayAttributeData BulletSpreadDecSpeed;
	ATTRIBUTE_ACCESSORS(UAS_Gun, BulletSpreadDecSpeed)


	/**
	 * Current bullet spread. Non-replicated because set every frame
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (HideFromModifiers))
		FFloatPropertyWrapper CurrentBulletSpread;
#pragma endregion

	












	/**
	 * The number of bullets every fire will shoot out
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_NumberOfBulletsPerFire, Category = "Attributes")
		FGameplayAttributeData NumberOfBulletsPerFire;
	ATTRIBUTE_ACCESSORS(UAS_Gun, NumberOfBulletsPerFire)

	/**
	 *
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxRange, Category = "Attributes")
		FGameplayAttributeData MaxRange;
	ATTRIBUTE_ACCESSORS(UAS_Gun, MaxRange)

	/**
	 * Number of times the trace can ricochet off of blocking hits - Zero for no ricochet
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Ricochets, Category = "Attributes")
		FGameplayAttributeData Ricochets;
	ATTRIBUTE_ACCESSORS(UAS_Gun, Ricochets)

	/**
	 * The amount of damage lost to the bullet base damage every 10000cm (328ft) the bullet travels
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageFalloff, Category = "Attributes")
		FGameplayAttributeData DamageFalloff;
	ATTRIBUTE_ACCESSORS(UAS_Gun, DamageFalloff)




	/**
	 * If full-auto enabled or not (0 is false, 1 is true).
	 * If true, just hold down to fire gun - no need to keep clicking. This applies to burst guns aswell.
	 * This should be a tag but this feels better because its closer related to the gun rather than just added to the ASC
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_bFullAuto, Category = "Attributes")
		FGameplayAttributeData bFullAuto;
	ATTRIBUTE_ACCESSORS(UAS_Gun, bFullAuto)

	/**
	 * (For semi-auto, full-auto, and burst)
	 * 
	 * Time between firing/shooting.
	 * Minimum time that must pass between each fires or shots. (Fires if semi-auto, Shots if full-auto)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TimeBetweenShots, Category = "Attributes")
		FGameplayAttributeData TimeBetweenShots;
	ATTRIBUTE_ACCESSORS(UAS_Gun, TimeBetweenShots)

	/**
	 * (For full-auto)
	 * 
	 * Override time between fires for full-auto. NOT the time between shots! This allows full-auto guns to have a delay
	 * between fires that differ from their time between shots.
	 * 
	 * Leave at -1 to not override (not overriding uses TimeBetweenShots as the time between fires)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TimeBetweenFiresOverride, Category = "Attributes")
		FGameplayAttributeData TimeBetweenFiresOverride;
	ATTRIBUTE_ACCESSORS(UAS_Gun, TimeBetweenFiresOverride)

	/**
	 * (For burst)
	 * 
	 * Time between each burst (a burst is a collection of shots)
	 * 
	 * Leave at -1 to not override (not overriding uses TimeBetweenShots as the time between each burst)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TimeBetweenBurstsOverride, Category = "Attributes")
		FGameplayAttributeData TimeBetweenBurstsOverride;
	ATTRIBUTE_ACCESSORS(UAS_Gun, TimeBetweenBurstsOverride)



	/**
	 * Number of shots per burst (ie. 3 for 3-round burst)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_NumShotsPerBurst, Category = "Attributes")
		FGameplayAttributeData NumShotsPerBurst;
	ATTRIBUTE_ACCESSORS(UAS_Gun, NumShotsPerBurst)


	/**
	 * How much clip ammo will we lose for each shot. (Pretty much always just 1 but it's here if you need it)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AmmoCost, Category = "Attributes")
		FGameplayAttributeData AmmoCost;
	ATTRIBUTE_ACCESSORS(UAS_Gun, AmmoCost)




	bool IsMovingToIncBulletSpread() const;

	float GetRestBulletSpread() const;

	void ApplyFireBulletSpread();
	 

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
		virtual void OnRep_BulletSpreadIncRate(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_FireBulletSpread(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BulletSpreadDecSpeed(const FGameplayAttributeData& ServerBaseValue);



	UFUNCTION()
		virtual void OnRep_NumberOfBulletsPerFire(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_MaxRange(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_Ricochets(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_DamageFalloff(const FGameplayAttributeData& ServerBaseValue);



	UFUNCTION()
		virtual void OnRep_bFullAuto(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_TimeBetweenShots(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_TimeBetweenFiresOverride(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_TimeBetweenBurstsOverride(const FGameplayAttributeData& ServerBaseValue);


	UFUNCTION()
		virtual void OnRep_NumShotsPerBurst(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_AmmoCost(const FGameplayAttributeData& ServerBaseValue);
};
