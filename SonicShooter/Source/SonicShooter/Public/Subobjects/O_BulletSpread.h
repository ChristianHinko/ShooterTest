// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wrappers/PropertyWrappers.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"

#include "O_BulletSpread.generated.h"


class UAbilitySystemComponent;
class UCharacterMovementComponent;
class UArcInventoryComponent_Active;
class UArcItemStack;



/**
 * Has CurrentBulletSpread float.
 * 
 * Currently searches for external required variables - this is bad. We should change to
 * using injection of these variables and events into the subobject.
 */
UCLASS()
class SONICSHOOTER_API UO_BulletSpread : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override;
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);
	virtual void BeginDestroy() override;

public:
	UO_BulletSpread(const FObjectInitializer& ObjectInitializer);


	TSharedRef<FFloatValueChange> OnCurrentBulletSpreadChange;

	/** Current bullet spread. Non-replicated because set every frame */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Gun")
		FFloatPropertyWrapper CurrentBulletSpread;


	float GetRestBulletSpread() const;

	void ApplyFireBulletSpread();
	void ResetBulletSpread();

	bool IsMovingToIncBulletSpread() const;


	void SetAbilitySystemComponent(UAbilitySystemComponent* NewASC);

protected:
	//BEGIN FTickableObjectBase interface
	virtual bool IsTickable() const override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { return TStatId(); }
	//END FTickableObjectBase interface

	//BEGIN FTickableGameObject interface
	virtual bool IsTickableWhenPaused() const override { return false; };
	//END FTickableGameObject interface

private:
	UAbilitySystemComponent* OwnerASC;
	const UCharacterMovementComponent* CMC;


	// BEGIN Attribute value change
	float MinBulletSpread;
	void OnMinBulletSpreadChange(const FOnAttributeChangeData& Data) { MinBulletSpread = Data.NewValue; }

	float MovingBulletSpread;
	void OnMovingBulletSpreadChange(const FOnAttributeChangeData& Data) { MovingBulletSpread = Data.NewValue; }

	float BulletSpreadIncRate;
	void OnBulletSpreadIncRateChange(const FOnAttributeChangeData& Data) { BulletSpreadIncRate = Data.NewValue; }

	float FireBulletSpread;
	void OnFireBulletSpreadChange(const FOnAttributeChangeData& Data) { FireBulletSpread = Data.NewValue; }

	float BulletSpreadDecSpeed;
	void OnBulletSpreadDecSpeedChange(const FOnAttributeChangeData& Data) { BulletSpreadDecSpeed = Data.NewValue; }
	// END Attribute value change
};
