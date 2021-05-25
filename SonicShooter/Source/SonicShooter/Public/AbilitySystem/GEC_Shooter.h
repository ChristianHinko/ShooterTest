// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayEffectTypes.h"
#include "AbilitySystem\GATD_BulletTraceTargetHit.h"

#include "GEC_Shooter.generated.h"

/**
 * 
 */
USTRUCT()
struct SONICSHOOTER_API FGEC_Shooter : public FSSGameplayEffectContext
{
    GENERATED_BODY()

public:
    FActorHitInfo GetHitInfo() const { return HitInfo; }
    TArray<FVector_NetQuantize> GetBulletTracePoints() const { return BulletTracePoints; }
    int32 GetNumRicochetsBeforeHit() const
    {
        // This adds up all of the ricochet points (if any) disregarding the last hit location
        return (BulletTracePoints.Num() - 1);
    }

    void SetHitInfo(const FActorHitInfo& inHitInfo) { HitInfo = inHitInfo; }
    void SetBulletTracePoints(const TArray<FVector_NetQuantize>& InBulletTracePoints) { BulletTracePoints = InBulletTracePoints; }

protected:
    UPROPERTY()
        FActorHitInfo HitInfo;

    UPROPERTY()
        TArray<FVector_NetQuantize> BulletTracePoints;

public:
    /** Returns the actual struct used for serialization, subclasses must override this! */
    virtual UScriptStruct* GetScriptStruct() const override
    {
        return StaticStruct();
    }

    /** Creates a copy of this context, used to duplicate for later modifications */
    virtual FGEC_Shooter* Duplicate() const override
    {
        FGEC_Shooter* NewContext = new FGEC_Shooter();
        *NewContext = *this;
        NewContext->AddActors(Actors);
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
struct TStructOpsTypeTraits<FGEC_Shooter> : public TStructOpsTypeTraitsBase2<FGEC_Shooter>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};
