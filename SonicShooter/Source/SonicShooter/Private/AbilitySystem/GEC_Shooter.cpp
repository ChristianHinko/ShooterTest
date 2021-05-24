// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEC_Shooter.h"



bool FGEC_Shooter::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
    Super::NetSerialize(Ar, Map, bOutSuccess);


    uint8 RepBits;
    if (Ar.IsSaving())
    {
        // Since only one GEC class is able to be in use it will have a lot of clutter that won't always be needed.
        // Because of this, we should rely on SerializeBits() optimizations to only replicate what we need.
        // For example, BulletTotalTravelDistanceBeforeHit is very specific to bullet tracing. When a GE doesn't use this, its value will be 0.f.
        // If it is 0.f, we know it isn't needed and doesn't need to replicate so its (1 << 0) spot in RepBits won't be added and hence it won't be serialized into/outof the Archive.

        if (BulletTotalTravelDistanceBeforeHit)
        {
            RepBits |= 1 << 0;
        }
        if (BulletTracePoints.Num() > 0)
        {
            RepBits |= 1 << 1;
        }
    }

    // Pack/unpack our RepBits into/outof the Archive
    Ar.SerializeBits(&RepBits, 2);


    if (RepBits & (1 << 0))
    {
        Ar << BulletTotalTravelDistanceBeforeHit;
    }
    if (RepBits & (1 << 1))
    {
        bool bOutSuccessLocal = true;
        bOutSuccessLocal = SafeNetSerializeTArray_WithNetSerialize<31>(Ar, BulletTracePoints, Map);
        bOutSuccess &= bOutSuccessLocal;
    }






    bOutSuccess = true;
    return true;
}
