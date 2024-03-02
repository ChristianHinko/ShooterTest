// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Types/ASSGameplayEffectTypes.h"
#include "AbilitySystem/Types/STGameplayAbilityTargetTypes.h"

#include "STGameplayEffectTypes.generated.h"



/**
 * Game's base GameplayEffectContext
 */
USTRUCT()
struct SHOOTERTEST_API FSTGameplayEffectContext : public FASSGameplayEffectContext
{
    GENERATED_BODY()

public:
    FSTGameplayEffectContext();

    virtual UScriptStruct* GetScriptStruct() const override { return StaticStruct(); }

    virtual FSTGameplayEffectContext* Duplicate() const override
    {
        FSTGameplayEffectContext* NewContext = new FSTGameplayEffectContext(); // allocate our version
        *NewContext = *this;
        if (GetHitResult())
        {
            // Does a deep copy of the hit result
            NewContext->AddHitResult(*GetHitResult(), true);
        }
        return NewContext;
    }

    virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
};

template<>
struct TStructOpsTypeTraits<FSTGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FSTGameplayEffectContext>
{
    enum
    {
        WithNetSerializer = true,
        WithCopy = true // necessary so that TSharedPtr<FHitResult> Data is copied around
    };
};



////////////////////////////////////////////////////////////////
/// FSTGameplayEffectContext_Shooter
////////////////////////////////////////////////////////////////



/**
 *
 */
USTRUCT()
struct SHOOTERTEST_API FSTGameplayEffectContext_Shooter : public FSTGameplayEffectContext
{
    GENERATED_BODY()

public:
    FSTActorHitInfo GetHitInfo() const { return HitInfo; }
    TArray<FVector_NetQuantize> GetBulletTracePoints() const { return BulletTracePoints; }
    int32 GetNumRicochetsBeforeHit() const
    {
        // This adds up all of the ricochet points (if any) disregarding the start and end location
        return FMath::Max((BulletTracePoints.Num() - 2), 0);
    }

    void SetHitInfo(const FSTActorHitInfo& InHitInfo) { HitInfo = InHitInfo; }
    void SetBulletTracePoints(const TArray<FVector_NetQuantize>& InBulletTracePoints) { BulletTracePoints = InBulletTracePoints; }

protected:
    UPROPERTY()
        FSTActorHitInfo HitInfo;

    UPROPERTY()
        TArray<FVector_NetQuantize> BulletTracePoints;

public:
    virtual UScriptStruct* GetScriptStruct() const override { return StaticStruct(); }

    virtual FSTGameplayEffectContext_Shooter* Duplicate() const override
    {
        FSTGameplayEffectContext_Shooter* NewContext = new FSTGameplayEffectContext_Shooter(); // allocate our version
        *NewContext = *this;
        if (GetHitResult())
        {
            // Does a deep copy of the hit result
            NewContext->AddHitResult(*GetHitResult(), true);
        }
        return NewContext;
    }

    virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
};

template<>
struct TStructOpsTypeTraits<FSTGameplayEffectContext_Shooter> : public TStructOpsTypeTraitsBase2<FSTGameplayEffectContext_Shooter>
{
    enum
    {
        WithNetSerializer = true,
        WithCopy = true // necessary so that TSharedPtr<FHitResult> Data is copied around
    };
};
