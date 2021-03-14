// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "GameplayAbilities/Public/TickableAttributeSetInterface.h"
#include "AbilitySystemComponent.h"

#include "AS_Gun.generated.h"



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
	 * The minimum bullet spread in degrees (90 degs would be a right-angled cone)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MinBulletSpread, Category = "Attributes")
		FGameplayAttributeData MinBulletSpread;
	ATTRIBUTE_ACCESSORS(UAS_Gun, MinBulletSpread)

	/**
	 * The maximum bullet spread in degrees (90 degs would be a right-angled cone)
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxBulletSpread, Category = "Attributes")
		FGameplayAttributeData MaxBulletSpread;
	ATTRIBUTE_ACCESSORS(UAS_Gun, MaxBulletSpread)

	/**
	 * The increase in bullet spread per shot in degrees. This amount of degs will be added to
	 * current bullet spread every shot until reached maximum spread
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpreadIncPerShot, Category = "Attributes")
		FGameplayAttributeData BulletSpreadIncPerShot;
	ATTRIBUTE_ACCESSORS(UAS_Gun, BulletSpreadIncPerShot)

	/**
	 * The rate of decrease in bullet spread in degrees per second. Will be continuously decrease spread by
	 * this rate until reached minimum spread
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpreadDecRate, Category = "Attributes")
		FGameplayAttributeData BulletSpreadDecRate;
	ATTRIBUTE_ACCESSORS(UAS_Gun, BulletSpreadDecRate)


	/**
	 * Current bullet spread. Non-replicated because set every frame
	 */
	UPROPERTY(BlueprintReadOnly/*, ReplicatedUsing = OnRep_CurrentBulletSpread*/, Category = "Attributes", meta = (HideFromModifiers))
		FGameplayAttributeData CurrentBulletSpread;
	ATTRIBUTE_ACCESSORS(UAS_Gun, CurrentBulletSpread)


	void IncCurrentBulletSpread();


protected:
	virtual void SetSoftAttributeDefaults() override;


	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTick() const override;



	UFUNCTION()
		virtual void OnRep_MinBulletSpread(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_MaxBulletSpread(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BulletSpreadIncPerShot(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BulletSpreadDecRate(const FGameplayAttributeData& ServerBaseValue);
};
