// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modular/ArcItemFragment.h"
#include "Types/PropertyWrappers/GCPropertyWrappers.h"

#include "STItemFragment_BulletSpread.generated.h"

class UAbilitySystemComponent;
class UCharacterMovementComponent;

/**
 *
 */
UCLASS()
class SHOOTERTEST_API USTItemFragment_BulletSpread : public UArcItemFragment
{
    GENERATED_BODY()

public:

    USTItemFragment_BulletSpread();
};

/**
 * Has CurrentBulletSpread float.
 *
 * NOTE: Searches externally for Stamina-related Attributes
 */
UCLASS()
class SHOOTERTEST_API USTItemFragment_BulletSpreadInstanced : public UArcItemFragment, public FTickableGameObject
{
    GENERATED_BODY()

public:
    USTItemFragment_BulletSpreadInstanced();


    /** Current bullet spread. Non-replicated because set every frame */
    UPROPERTY(BlueprintReadOnly, Replicated, Category = "BulletSpread")
    mutable FGCFloatPropertyWrapper CurrentBulletSpread;


    float GetRestBulletSpread() const;

    void ApplyFireBulletSpread();
    void ResetBulletSpread();

    bool IsMovingToIncBulletSpread() const;


    void SetAbilitySystemComponent(const UAbilitySystemComponent* NewASC);

protected:
    //  BEGIN FTickableObjectBase interface
    virtual bool IsTickable() const override;
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override { return TStatId(); }
    //  END FTickableObjectBase interface

    //  BEGIN FTickableGameObject interface
    virtual bool IsTickableWhenPaused() const override { return false; };
    //  END FTickableGameObject interface

    UPROPERTY(Transient)
    TObjectPtr<const UAbilitySystemComponent> OwnerASC;
    UPROPERTY(Transient)
    TObjectPtr<const UCharacterMovementComponent> CMC;

    mutable float MinBulletSpread;
    mutable float MovingBulletSpread;
    mutable float BulletSpreadIncRate;
    mutable float FireBulletSpread;
    mutable float BulletSpreadDecSpeed;
};
