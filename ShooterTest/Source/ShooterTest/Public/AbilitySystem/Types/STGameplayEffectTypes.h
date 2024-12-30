// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/Types/STGameplayAbilityTargetTypes.h"

#include "STGameplayEffectTypes.generated.h"

/**
 * @brief Game's gameplay effect context class.
 */
USTRUCT()
struct SHOOTERTEST_API FSTGameplayEffectContext : public FGameplayEffectContext
{
    GENERATED_BODY()

public:

    FSTGameplayEffectContext();

public:

    // ~ FGameplayEffectContext overrides.
    virtual UScriptStruct* GetScriptStruct() const override { return StaticStruct(); }
    virtual FSTGameplayEffectContext* Duplicate() const override;
    virtual bool NetSerialize(FArchive& archive, UPackageMap* packageMap, bool& outIsSuccess) override;
    // ~ FGameplayEffectContext overrides.
};

template <>
struct TStructOpsTypeTraits<FSTGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FSTGameplayEffectContext>
{
    enum
    {
        WithNetSerializer = true,
        WithCopy = true
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

    FORCEINLINE const FSTActorHitInfo& GetHitInfo() const
    {
        return HitInfo;
    }

    FORCEINLINE const TArray<FVector_NetQuantize, TInlineAllocator<8>>& GetBulletTracePoints() const
    {
        return BulletTracePoints;
    }

    FORCEINLINE_DEBUGGABLE int32 GetNumRicochetsBeforeHit() const
    {
        // This adds up all of the ricochet points (if any) disregarding the start and end location.
        constexpr int32 minNumRicochetsPoints = 0;
        return FMath::Max((BulletTracePoints.Num() - 2), minNumRicochetsPoints);
    }

    FORCEINLINE void SetHitInfo(const FSTActorHitInfo& inHitInfo)
    {
        HitInfo = inHitInfo;
    }

    FORCEINLINE void SetBulletTracePoints(
        TArray<FVector_NetQuantize, TInlineAllocator<8>>&& inBulletTracePoints)
    {
        BulletTracePoints = MoveTemp(inBulletTracePoints);
    }

public:

    // ~ FGameplayEffectContext overrides.
    virtual UScriptStruct* GetScriptStruct() const override { return StaticStruct(); }
    virtual FSTGameplayEffectContext_Shooter* Duplicate() const override;
    virtual bool NetSerialize(FArchive& archive, UPackageMap* packageMap, bool& outIsSuccess) override;
    // ~ FGameplayEffectContext overrides.

protected:

    TArray<FVector_NetQuantize, TInlineAllocator<8>> BulletTracePoints;

    UPROPERTY()
    FSTActorHitInfo HitInfo;
};

template <>
struct TStructOpsTypeTraits<FSTGameplayEffectContext_Shooter> : public TStructOpsTypeTraitsBase2<FSTGameplayEffectContext_Shooter>
{
    enum
    {
        WithNetSerializer = true,
        WithCopy = true
    };
};
