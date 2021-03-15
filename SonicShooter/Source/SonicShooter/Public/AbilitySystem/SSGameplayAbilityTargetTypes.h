// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "Engine/NetSerialization.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "SSGameplayAbilityTargetTypes.generated.h"

/** Target data with a single hit result, data is packed into the hit result */
USTRUCT(BlueprintType)
struct SONICSHOOTER_API FGameplayAbilityTargetData_RicochetTargetHit : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	FGameplayAbilityTargetData_RicochetTargetHit()
	{ }

	FGameplayAbilityTargetData_RicochetTargetHit(FHitResult InHitResult)
		: HitResult(MoveTemp(InHitResult))
	{ }

	// -------------------------------------

	virtual TArray<TWeakObjectPtr<AActor> >	GetActors() const override
	{
		TArray<TWeakObjectPtr<AActor> >	Actors;
		if (HitResult.Actor.IsValid())
		{
			Actors.Push(HitResult.Actor);
		}
		return Actors;
	}

	// SetActors() will not work here because the actor "array" is drawn from the hit result data, and changing that doesn't make sense.

	// -------------------------------------

	virtual bool HasHitResult() const override
	{
		return true;
	}

	virtual const FHitResult* GetHitResult() const override
	{
		return &HitResult;
	}

	virtual bool HasOrigin() const override
	{
		return true;
	}

	virtual FTransform GetOrigin() const override
	{
		return FTransform((HitResult.TraceEnd - HitResult.TraceStart).Rotation(), HitResult.TraceStart);
	}

	virtual bool HasEndPoint() const override
	{
		return true;
	}

	virtual FVector GetEndPoint() const override
	{
		return HitResult.Location;
	}

	virtual void ReplaceHitWith(AActor* NewHitActor, const FHitResult* NewHitResult)
	{
		bHitReplaced = true;

		HitResult = FHitResult();
		if (NewHitResult != nullptr)
		{
			HitResult = *NewHitResult;
		}
	}

	// -------------------------------------

	/** Hit result that stores data */
	UPROPERTY()
	FHitResult	HitResult;
	UPROPERTY()
	float totalDistanceTraveled;	// This data is important because it is the total distance traveled (all wall bounses accounted for). The HitResult itself doesn't have an acurate distance variable for a ricochet since it takes many FHitResults to 

	UPROPERTY()
	bool bHitReplaced = false;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayAbilityTargetData_RicochetTargetHit::StaticStruct();
	}
};

template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_RicochetTargetHit> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_RicochetTargetHit>
{
	enum
	{
		WithNetSerializer = true	// For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};
