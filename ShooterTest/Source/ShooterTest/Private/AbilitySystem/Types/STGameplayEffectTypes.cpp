// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Types/STGameplayEffectTypes.h"

FSTGameplayEffectContext::FSTGameplayEffectContext()
{
}

FSTGameplayEffectContext* FSTGameplayEffectContext::Duplicate() const
{
    FSTGameplayEffectContext& newContext = *new FSTGameplayEffectContext();
    newContext.operator=(*this);

    if (const FHitResult* hitResult = GetHitResult())
    {
        // Perform a deep copy of the hit result.
        constexpr bool shouldReset = true;
        newContext.AddHitResult(*hitResult, shouldReset);
    }

    return &newContext;
}

bool FSTGameplayEffectContext::NetSerialize(FArchive& archive, UPackageMap* packageMap, bool& outIsSuccess)
{
    return Super::NetSerialize(archive, packageMap, outIsSuccess);
}

////////////////////////////////////////////////////////////////
/// FSTGameplayEffectContext_Shooter
////////////////////////////////////////////////////////////////

FSTGameplayEffectContext_Shooter* FSTGameplayEffectContext_Shooter::Duplicate() const
{
    FSTGameplayEffectContext_Shooter& newContext = *new FSTGameplayEffectContext_Shooter();
    newContext.operator=(*this);

    if (const FHitResult* hitResult = GetHitResult())
    {
        // Perform a deep copy of the hit result.
        constexpr bool shouldReset = true;
        newContext.AddHitResult(*hitResult, shouldReset);
    }

    return &newContext;
}

bool FSTGameplayEffectContext_Shooter::NetSerialize(FArchive& archive, UPackageMap* packageMap, bool& outIsSuccess)
{
    if (!Super::NetSerialize(archive, packageMap, outIsSuccess))
    {
        return false;
    }

    uint8 RepBits = 0u;
    if (archive.IsSaving())
    {
        // Since only one GEC class is able to be in use it will have a lot of clutter that won't always be needed.
        // Because of this, we should rely on SerializeBits() optimizations to only replicate what we need.
        // For example, BulletTotalTravelDistanceBeforeHit is very specific to bullet tracing. When a GE doesn't use this, its value will be 0.f.
        // If it is 0.f, we know it isn't needed and doesn't need to replicate so its (1 << 0) spot in RepBits won't be added and hence it won't be serialized into/outof the archive.

        if (HitInfo.HitActor.IsValid())
        {
            RepBits |= 1 << 0;
        }
        if (BulletTracePoints.Num() > 0)
        {
            RepBits |= 1 << 1;
        }
    }

    // Pack/unpack our RepBits into/outof the archive.
    archive.SerializeBits(&RepBits, 2);

    if (RepBits & (1 << 0))
    {
        bool outIsSuccessLocal = true;
        HitInfo.NetSerialize(archive, packageMap, outIsSuccessLocal);
        outIsSuccess = outIsSuccess && outIsSuccessLocal;
    }

    if (RepBits & (1 << 1))
    {
        bool outIsSuccessLocal = true;
        outIsSuccessLocal = SafeNetSerializeTArray_WithNetSerialize<31>(archive, BulletTracePoints, packageMap);
        outIsSuccess = outIsSuccess && outIsSuccessLocal;
    }

    return true;
}
