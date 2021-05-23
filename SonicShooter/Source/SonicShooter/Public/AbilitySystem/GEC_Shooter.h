// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayEffectTypes.h"

#include "GEC_Shooter.generated.h"



/**
 * 
 */
USTRUCT()
struct SONICSHOOTER_API FGEC_Shooter : public FSSGameplayEffectContext
{
    GENERATED_BODY()

public:
    float GetBulletTotalTravelDistanceBeforeHit() const { return bulletTotalTravelDistanceBeforeHit; }
    float GetCartridgeID() const { return CartridgeID; }

    void SetBulletTotalTravelDistanceBeforeHit(float bInBulletTotalTravelDistanceBeforeHit) { bulletTotalTravelDistanceBeforeHit = bInBulletTotalTravelDistanceBeforeHit; }
    void SetCartridgeID(int32 InID) { CartridgeID = InID; }

protected:
    UPROPERTY()
        float bulletTotalTravelDistanceBeforeHit;

    UPROPERTY()
        int32 CartridgeID;

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
