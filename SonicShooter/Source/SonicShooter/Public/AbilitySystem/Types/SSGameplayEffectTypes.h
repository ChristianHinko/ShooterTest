// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Types/ASSGameplayEffectTypes.h"
#include "AbilitySystem/Types/SSGameplayAbilityTargetTypes.h"

#include "SSGameplayEffectTypes.generated.h"



/**
 * Our custom Gameplay Effect Context
 */
USTRUCT()
struct SONICSHOOTER_API FSSGameplayEffectContext : public FASSGameplayEffectContext
{
	GENERATED_BODY()

public:
	FSSGameplayEffectContext();

	// Returns the actual struct used for serialization, subclasses must override this!
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	// Creates a copy of this context, used to duplicate for later modifications
	virtual FSSGameplayEffectContext* Duplicate() const override
	{
		FSSGameplayEffectContext* NewContext = new FSSGameplayEffectContext();
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
struct TStructOpsTypeTraits<FSSGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FSSGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true // necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};



////////////////////////////////////////////////////////////////
/// FGEC_Shooter
////////////////////////////////////////////////////////////////



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
		// This adds up all of the ricochet points (if any) disregarding the start and end location
		return FMath::Max((BulletTracePoints.Num() - 2), 0);
	}

	void SetHitInfo(const FActorHitInfo& inHitInfo) { HitInfo = inHitInfo; }
	void SetBulletTracePoints(const TArray<FVector_NetQuantize>& InBulletTracePoints) { BulletTracePoints = InBulletTracePoints; }

protected:
	UPROPERTY()
		FActorHitInfo HitInfo;

	UPROPERTY()
		TArray<FVector_NetQuantize> BulletTracePoints;

public:
	// Returns the actual struct used for serialization, subclasses must override this!
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	// Creates a copy of this context, used to duplicate for later modifications
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
		WithCopy = true // necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};
