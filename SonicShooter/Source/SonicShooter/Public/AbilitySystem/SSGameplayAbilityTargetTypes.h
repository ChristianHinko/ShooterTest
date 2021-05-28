// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "SSGameplayAbilityTargetTypes.generated.h"



/**
 * Our base Target Data struct
 */
USTRUCT()
struct SONICSHOOTER_API FSSGameplayAbilityTargetData : public FGameplayAbilityTargetData
{
	GENERATED_BODY()

		
	FSSGameplayAbilityTargetData();

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FSSGameplayAbilityTargetData::StaticStruct();
	}
};



////////////////////////////////////////////////////////////////
/// FGATD_BulletTraceTargetHit
////////////////////////////////////////////////////////////////


/**
 * 
 */
USTRUCT()
struct FActorHitInfo
{
	GENERATED_BODY()

	FActorHitInfo()
	{

	}
	FActorHitInfo(const TWeakObjectPtr<AActor>& inHitActor, float inTotalTraveledDistanceBeforeHit)
	{
		HitActor = inHitActor;
		totalTraveledDistanceBeforeHit = inTotalTraveledDistanceBeforeHit;
	}
	void operator=(const FActorHitInfo& Other)
	{
		HitActor = Other.HitActor;
		totalTraveledDistanceBeforeHit = Other.totalTraveledDistanceBeforeHit;
	}
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		Ar << HitActor;
		Ar << totalTraveledDistanceBeforeHit;

		bOutSuccess = true;
		return true;
	}

	UPROPERTY()
		TWeakObjectPtr<AActor> HitActor;
	UPROPERTY()
		float totalTraveledDistanceBeforeHit;
};

template<>
struct TStructOpsTypeTraits<FActorHitInfo> : public TStructOpsTypeTraitsBase2<FActorHitInfo>
{
	enum
	{
		WithNetSerializer = true
	};
};

/**
 * This is the target data struct that represents the targets that were hit by a certain bullet. This is a pretty good GATD code wise :O
 */
USTRUCT(BlueprintType)
struct SONICSHOOTER_API FGATD_BulletTraceTargetHit : public FSSGameplayAbilityTargetData
{
	GENERATED_BODY()

	FGATD_BulletTraceTargetHit();

	/** Applies a previously created gameplay effect spec to each target represented */
	virtual TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectSpec(FGameplayEffectSpec& Spec, FPredictionKey PredictionKey = FPredictionKey());

	virtual void AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray) const override;
	virtual void AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray, int32 hitInfosIndex) const;		// Custom overload that asks for the hit target actor (by passing in the ActorHitInfos index)


	virtual TArray<TWeakObjectPtr<AActor>> GetActors() const override
	{
		TArray<TWeakObjectPtr<AActor>> RetVal;
		for (const FActorHitInfo& ActorHitInfo : ActorHitInfos)
		{
			RetVal.Emplace(ActorHitInfo.HitActor);
		}
		return RetVal;
	}

	virtual bool HasOrigin() const override
	{
		return true;
	}
	virtual FTransform GetOrigin() const override
	{
		if (BulletTracePoints.Num() > 0)
		{
			FRotator Rotation;
			if (BulletTracePoints.Num() >= 2)
			{
				Rotation = (BulletTracePoints[1] - BulletTracePoints[0]).Rotation();
			}

			return FTransform(Rotation, BulletTracePoints[0]);
		}

		return FTransform();
	}

	virtual bool HasEndPoint() const override
	{
		if (BulletTracePoints.Num() > 0)
		{
			return true;
		}
		return false;
	}
	virtual FVector GetEndPoint() const override
	{
		if (HasEndPoint())
		{
			return BulletTracePoints.Last();
		}

		return FVector();
	}


	// -------------------------------------
	/**
	 * The points which describe this bullet's path. If you "connect the dots" you will get the bullet's path. The first point is the start point and the last point is the end point.
	 * To get the number of times ricocheted, do (BulletTracePoints.Num() - 2). This adds up all of the ricochet points (if any) disregarding the start and end location.
	 */
	UPROPERTY()
		TArray<FVector_NetQuantize> BulletTracePoints;
	UPROPERTY()
		TArray<FActorHitInfo> ActorHitInfos;

	int32 GetNumRicochetsBeforeHit() const
	{
		// This adds up all of the ricochet points (if any) disregarding the start and end location
		return FMath::Max((BulletTracePoints.Num() - 2), 0);
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
