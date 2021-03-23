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
	 * The rate of increase in bullet spread in degrees per second. Will be continuously increasing spread by
	 * this rate while the avatar actor's velocity is greater than zero until reached maximum spread
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BulletSpreadMovingIncRate, Category = "Attributes")
		FGameplayAttributeData BulletSpreadMovingIncRate;
	ATTRIBUTE_ACCESSORS(UAS_Gun, BulletSpreadMovingIncRate)

	/**
	 * The rate of decrease in bullet spread in degrees per second. Will be continuously decreasing spread by
	 * this rate until reached minimum spread
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
	 * The rate of decrease in bullet spread in degrees per second. Will be continuously decreasing spread by
	 * this rate until reached minimum spread
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageFalloff, Category = "Attributes")
		FGameplayAttributeData DamageFalloff;
	ATTRIBUTE_ACCESSORS(UAS_Gun, DamageFalloff)







	void IncCurrentBulletSpread();

	uint8 bIsMovingForIncRate : 1;




	virtual void PostInitProperties() override;

protected:
	virtual void SetSoftAttributeDefaults() override;


	USSArcInventoryComponent_Active* Inventory;
	UFUNCTION()
		void OnInventoryItemActive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack);
	UFUNCTION()
		void OnInventoryItemInactive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack);

	USSCharacterMovementComponent* CMC;

	bool IsMovingToIncBulletSpread() const;


	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTick() const override;


	void OnAccelerationStartCMC();
	void OnAccelerationStopCMC();

	void OnStartedFallingCMC();
	void OnStoppedFallingCMC();



	UFUNCTION()
		virtual void OnRep_MinBulletSpread(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_MaxBulletSpread(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BulletSpreadIncPerShot(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BulletSpreadMovingIncRate(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BulletSpreadDecSpeed(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_DamageFalloff(const FGameplayAttributeData& ServerBaseValue);
};
