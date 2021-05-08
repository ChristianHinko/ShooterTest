// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayEffectTypes.h"

#include "GEC_Bullet.generated.h"



/**
 * 
 */
USTRUCT()
struct SONICSHOOTER_API FGEC_Bullet : public FSSGameplayEffectContext
{
    GENERATED_BODY()

public:
    uint8 GetRicochetsBeforeHit() const { return ricochetsBeforeHit; }
    float GetBulletTotalTravelDistanceBeforeHit() const { return bulletTotalTravelDistanceBeforeHit; }
    float GetCartridgeID() const { return CartridgeID; }
    float GetSourceLevel() const { return SourceLevel; }

    void SetRicochetsBeforeHit(uint8 inRicochetsBeforeHit) { ricochetsBeforeHit = inRicochetsBeforeHit; }
    void SetBulletTotalTravelDistanceBeforeHit(float bInBulletTotalTravelDistanceBeforeHit) { bulletTotalTravelDistanceBeforeHit = bInBulletTotalTravelDistanceBeforeHit; }
    void SetCartridgeID(int32 InID) { CartridgeID = InID; }
    void SetSourceLevel(float InLevel) { SourceLevel = InLevel; }

protected:
    UPROPERTY()
        float bulletTotalTravelDistanceBeforeHit;

    UPROPERTY()
        uint8 ricochetsBeforeHit;

    UPROPERTY()
        int32 CartridgeID;

    UPROPERTY()
        float SourceLevel;

public:
    /** Returns the actual struct used for serialization, subclasses must override this! */
    virtual UScriptStruct* GetScriptStruct() const override
    {
        return StaticStruct();
    }

    /** Creates a copy of this context, used to duplicate for later modifications */
    virtual FGEC_Bullet* Duplicate() const override
    {
        FGEC_Bullet* NewContext = new FGEC_Bullet();
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
struct TStructOpsTypeTraits<FGEC_Bullet> : public TStructOpsTypeTraitsBase2<FGEC_Bullet>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};
