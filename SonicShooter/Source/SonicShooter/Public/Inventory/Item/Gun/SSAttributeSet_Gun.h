// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "SSAttributeSet_Gun.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSAttributeSet_Gun : public UASSAttributeSet
{
	GENERATED_BODY()

public:
	USSAttributeSet_Gun(const FObjectInitializer& ObjectInitializer);


	//BEGIN  BulletSpread
	/**
	 * The minimum bullet spread while staying still in degrees (90 degs would be a right-angled cone)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MinBulletSpread, Category = "Attributes")
		FGameplayAttributeData MinBulletSpread;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, MinBulletSpread)

	/**
	 * The minimum bullet spread while moving in degrees (90 degs would be a right-angled cone)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovingBulletSpread, Category = "Attributes")
		FGameplayAttributeData MovingBulletSpread;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, MovingBulletSpread)

	/**
	 * The rate of increase in bullet spread in degrees per second. Will be continuously increasing spread by
	 * this rate while moving until we've reached MovingBulletSpread
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpreadIncRate, Category = "Attributes")
		FGameplayAttributeData BulletSpreadIncRate;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, BulletSpreadIncRate)

	/**
	 * The increase in bullet spread per shot in degrees
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireBulletSpread, Category = "Attributes")
		FGameplayAttributeData FireBulletSpread;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, FireBulletSpread)

	/**
	 * The speed of decrease in bullet spread to smooth interp to. Will be continuously interping spread at
	 * this speed until reached minimum spread (or moving spread if we are moving)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpreadDecSpeed, Category = "Attributes")
		FGameplayAttributeData BulletSpreadDecSpeed;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, BulletSpreadDecSpeed)
	//END BulletSpread

	












	/**
	 * The number of bullets every fire will shoot out
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_NumberOfBulletsPerFire, Category = "Attributes")
		FGameplayAttributeData NumberOfBulletsPerFire;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, NumberOfBulletsPerFire)

	/**
	 * Passed in to GATA
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxRange, Category = "Attributes")
		FGameplayAttributeData MaxRange;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, MaxRange)

	/**
	 * Number of times a bullet can penetrate blocking hits - Zero for no penetrations, -1 for letting speed decide
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Penetrations, Category = "Attributes")
		FGameplayAttributeData Penetrations;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, Penetrations)

	/**
	 * Number of times a bullet can ricochet - (Zero for no ricochets and -1 for letting speed decide)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Ricochets, Category = "Attributes")
		FGameplayAttributeData Ricochets;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, Ricochets)

	/**
	 * The initial speed of the bullet (bullet speed directly affects bullet damage and how far it travels)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_InitialBulletSpeed, Category = "Attributes")
		FGameplayAttributeData InitialBulletSpeed;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, InitialBulletSpeed)

	/**
	 * Speed nerf on the bullet every centimeter. Decreases bullet's speed as it travels through the air. (bullet speed directly affects bullet damage and how far it travels)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpeedFalloff, Category = "Attributes")
		FGameplayAttributeData BulletSpeedFalloff;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, BulletSpeedFalloff)







	/**
	 * If full-auto enabled or not (0 is false, 1 is true).
	 * If true, just hold down to fire gun - no need to keep clicking. This applies to burst guns aswell.
	 * This should be a tag but this feels better because its closer related to the gun rather than just added to the ASC
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_bFullAuto, Category = "Attributes")
		FGameplayAttributeData bFullAuto;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, bFullAuto)

	/**
	 * (For semi-auto, full-auto, and burst)
	 * 
	 * Time between firing/shooting.
	 * Minimum time that must pass between each fires or shots. (Fires if semi-auto, Shots if full-auto)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TimeBetweenShots, Category = "Attributes")
		FGameplayAttributeData TimeBetweenShots;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, TimeBetweenShots)

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
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, TimeBetweenFiresOverride)

	/**
	 * (For burst)
	 * 
	 * Time between each burst (a burst is a collection of shots)
	 * 
	 * Leave at -1 to not override (not overriding uses TimeBetweenShots as the time between each burst)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TimeBetweenBurstsOverride, Category = "Attributes")
		FGameplayAttributeData TimeBetweenBurstsOverride;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, TimeBetweenBurstsOverride)



	/**
	 * Number of shots per burst (ie. 3 for 3-round burst)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_NumShotsPerBurst, Category = "Attributes")
		FGameplayAttributeData NumShotsPerBurst;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, NumShotsPerBurst)


	/**
	 * How much clip ammo will we lose for each shot. (Pretty much always just 1 but it's here if you need it)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AmmoCost, Category = "Attributes")
		FGameplayAttributeData AmmoCost;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Gun, AmmoCost)





protected:
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
		virtual void OnRep_Penetrations(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_InitialBulletSpeed(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BulletSpeedFalloff(const FGameplayAttributeData& ServerBaseValue);



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
