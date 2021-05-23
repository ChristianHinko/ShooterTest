// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem\SSGameplayAbilityTargetTypes.h"

#include "GATD_BulletTraceTargetHit.generated.h"



/**
 * 
 */
USTRUCT(BlueprintType)
struct SONICSHOOTER_API FGATD_BulletTraceTargetHit : public FSSGameplayAbilityTargetData
{
	GENERATED_BODY()

	FGATD_BulletTraceTargetHit();


	virtual void AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray) const override;

	/** Return true in subclasses if GetHitResult will work */
	virtual bool HasHitResult() const override
	{
		return false;
	}

	//virtual bool HasOrigin() const override
	//{
	//	return true;
	//}
	//virtual FTransform GetOrigin() const override
	//{
	//	return FTransform((HitResult.TraceEnd - HitResult.TraceStart).Rotation(), HitResult.TraceStart);
	//}

	virtual bool HasEndPoint() const override
	{
		return true;
	}
	virtual FVector GetEndPoint() const override
	{
		if (BulletTracePoints.Num() > 0)
		{
			return BulletTracePoints.Last();
		}

		return FVector();
	}


	// -------------------------------------
	
	/** Total distance bullet traveled across all ricochets until it hit the target (info for UAS_Gun::DamageFalloff) */
	UPROPERTY()
		float BulletTotalTravelDistanceBeforeHit;

	/**
	 * The points which describe this bullet's path. If you "connect the dots" you will get the bullet's path. The last point is the hit location.
	 * To get the number of times ricocheted, do (BulletTracePoints.Num() - 1). This adds up all of the ricochet points (if any) disregarding the last hit location.
	 */
	UPROPERTY()
		TArray<FVector_NetQuantize> BulletTracePoints;

	int32 GetNumRicochetsBeforeHit() const
	{
		// This adds up all of the ricochet points (if any) disregarding the last hit location
		return (BulletTracePoints.Num() - 1);
	}



	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGATD_BulletTraceTargetHit::StaticStruct();
	}
};

template<>
struct TStructOpsTypeTraits<FGATD_BulletTraceTargetHit> : public TStructOpsTypeTraitsBase2<FGATD_BulletTraceTargetHit>
{
	enum
	{
		WithNetSerializer = true	// For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};
