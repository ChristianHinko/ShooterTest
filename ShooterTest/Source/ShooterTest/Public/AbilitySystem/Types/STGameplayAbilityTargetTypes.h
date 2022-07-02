// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Types/ASSGameplayAbilityTargetTypes.h"

#include "STGameplayAbilityTargetTypes.generated.h"



/**
 * Our custom Target Data struct
 */
USTRUCT()
struct SHOOTERTEST_API FSTGameplayAbilityTargetData : public FASSGameplayAbilityTargetData
{
	GENERATED_BODY()


	FSTGameplayAbilityTargetData();

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}
};



////////////////////////////////////////////////////////////////
/// FSTGameplayAbilityTargetData_BulletTraceTargetHit
////////////////////////////////////////////////////////////////


/**
 * 
 */
USTRUCT()
struct FSTActorHitInfo
{
	GENERATED_BODY()

	FSTActorHitInfo()
		: HitActor(nullptr)
		, BulletSpeedAtImpact(0.f)
	{
	}
	FSTActorHitInfo(AActor* InHitActor, const float InBulletSpeedAtImpact)
		: FSTActorHitInfo()
	{
		HitActor = TWeakObjectPtr<AActor>(InHitActor);
		BulletSpeedAtImpact = InBulletSpeedAtImpact;
	}

	UPROPERTY()
		TWeakObjectPtr<AActor> HitActor;
	UPROPERTY()
		float BulletSpeedAtImpact;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		Ar << HitActor;
		Ar << BulletSpeedAtImpact;

		bOutSuccess = true;
		return true;
	}
};

template<>
struct TStructOpsTypeTraits<FSTActorHitInfo> : public TStructOpsTypeTraitsBase2<FSTActorHitInfo>
{
	enum
	{
		WithNetSerializer = true
	};
};

/**
 * This is the Target Data struct that represents the targets that were hit by a certain bullet. This is a pretty good GATD code wise :O
 */
USTRUCT(BlueprintType)
struct SHOOTERTEST_API FSTGameplayAbilityTargetData_BulletTraceTargetHit : public FSTGameplayAbilityTargetData
{
	GENERATED_BODY()

	FSTGameplayAbilityTargetData_BulletTraceTargetHit();


	/** Applies a previously created gameplay effect spec to each target represented */
	virtual TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectSpec(FGameplayEffectSpec& Spec, FPredictionKey PredictionKey = FPredictionKey());

	virtual void AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray) const override;
	virtual void AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray, int32 HitInfosIndex) const; // custom overload that asks for the hit target actor (by passing in the ActorHitInfos index)


	virtual TArray<TWeakObjectPtr<AActor>> GetActors() const override
	{
		TArray<TWeakObjectPtr<AActor>> RetVal;
		for (const FSTActorHitInfo& ActorHitInfo : ActorHitInfos)
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




	/**
	 * The points which describe this bullet's path. If you "connect the dots" you will get the bullet's path. The first point is the start point and the last point is the end point.
	 * To get the number of times ricocheted, do (BulletTracePoints.Num() - 2). This adds up all of the ricochet points (if any) disregarding the start and end location.
	 */
	UPROPERTY()
		TArray<FVector_NetQuantize> BulletTracePoints;
	UPROPERTY()
		TArray<FSTActorHitInfo> ActorHitInfos;

	int32 GetNumRicochetsBeforeHit() const
	{
		// This adds up all of the ricochet points (if any) disregarding the start and end location
		return FMath::Max((BulletTracePoints.Num() - 2), 0);
	}



	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}
};

template<>
struct TStructOpsTypeTraits<FSTGameplayAbilityTargetData_BulletTraceTargetHit> : public TStructOpsTypeTraitsBase2<FSTGameplayAbilityTargetData_BulletTraceTargetHit>
{
	enum
	{
		WithNetSerializer = true	// For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};
