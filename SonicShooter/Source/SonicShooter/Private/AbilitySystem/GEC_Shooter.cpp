// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEC_Shooter.h"



bool FGEC_Shooter::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
    uint32 RepBits = 0;
    if (Ar.IsSaving())
    {
        if (Instigator.IsValid())
        {
            RepBits |= 1 << 0;
        }
        if (EffectCauser.IsValid())
        {
            RepBits |= 1 << 1;
        }
        if (AbilityCDO.IsValid())
        {
            RepBits |= 1 << 2;
        }
        if (bReplicateSourceObject && SourceObject.IsValid())
        {
            RepBits |= 1 << 3;
        }
        if (Actors.Num() > 0)
        {
            RepBits |= 1 << 4;
        }
        if (HitResult.IsValid())
        {
            RepBits |= 1 << 5;
        }
        if (bHasWorldOrigin)
        {
            RepBits |= 1 << 6;
        }

        if (CartridgeID > 0)
        {
            RepBits |= 1 << 7;
        }
        if (bulletTotalTravelDistanceBeforeHit)
        {
            RepBits |= 1 << 8;
        }
    }


    Ar.SerializeBits(&RepBits, 9);


    if (RepBits & (1 << 0))
    {
        Ar << Instigator;
    }
    if (RepBits & (1 << 1))
    {
        Ar << EffectCauser;
    }
    if (RepBits & (1 << 2))
    {
        Ar << AbilityCDO;
    }
    if (RepBits & (1 << 3))
    {
        Ar << SourceObject;
    }
    if (RepBits & (1 << 4))
    {
        SafeNetSerializeTArray_Default<31>(Ar, Actors);
    }
    if (RepBits & (1 << 5))
    {
        if (Ar.IsLoading())
        {
            if (!HitResult.IsValid())
            {
                HitResult = MakeShared<FHitResult>();
            }
        }
        HitResult->NetSerialize(Ar, Map, bOutSuccess);
    }
    if (RepBits & (1 << 6))
    {
        Ar << WorldOrigin;
        bHasWorldOrigin = true;
    }
    else
    {
        bHasWorldOrigin = false;
    }

    if (RepBits & (1 << 7))
    {
        Ar << CartridgeID;
    }

    if (RepBits & (1 << 8))
    {
        Ar << bulletTotalTravelDistanceBeforeHit;
    }



    if (Ar.IsLoading())
    {
        AddInstigator(Instigator.Get(), EffectCauser.Get()); // Just to initialize InstigatorAbilitySystemComponent
    }


    bOutSuccess = true;
    return true;
}
