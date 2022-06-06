// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyWrappers/PWFloatPropertyWrapper.h"
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
 * NOTE: Searches externally for Stamina-related Attributes
 */
UCLASS()
class SONICSHOOTER_API UO_BulletSpread : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override;
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);

public:
	UO_BulletSpread(const FObjectInitializer& ObjectInitializer);


	/** Current bullet spread. Non-replicated because set every frame */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "BulletSpread")
		mutable FPWFloatPropertyWrapper CurrentBulletSpread;


	float GetRestBulletSpread() const;

	void ApplyFireBulletSpread();
	void ResetBulletSpread();

	bool IsMovingToIncBulletSpread() const;


	void SetAbilitySystemComponent(const UAbilitySystemComponent* NewASC);

protected:
	//BEGIN FTickableObjectBase interface
	virtual bool IsTickable() const override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { return TStatId(); }
	//END FTickableObjectBase interface

	//BEGIN FTickableGameObject interface
	virtual bool IsTickableWhenPaused() const override { return false; };
	//END FTickableGameObject interface


	UPROPERTY()
		TWeakObjectPtr<const UAbilitySystemComponent> OwnerASC;
	UPROPERTY()
		TWeakObjectPtr<const UCharacterMovementComponent> CMC;

	mutable float MinBulletSpread;
	mutable float MovingBulletSpread;
	mutable float BulletSpreadIncRate;
	mutable float FireBulletSpread;
	mutable float BulletSpreadDecSpeed;

};
