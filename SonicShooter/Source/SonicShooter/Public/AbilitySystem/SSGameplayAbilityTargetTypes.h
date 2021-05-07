// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "Engine/NetSerialization.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "SSGameplayAbilityTargetTypes.generated.h"

/** Target data with a single hit result, data is packed into the hit result */
USTRUCT(BlueprintType)
struct SONICSHOOTER_API FGameplayAbilityTargetData_BulletTraceTargetHit : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

		FGameplayAbilityTargetData_BulletTraceTargetHit()
	{
	}

	FGameplayAbilityTargetData_BulletTraceTargetHit(FHitResult InHitResult)
		: HitResult(MoveTemp(InHitResult))
	{
	}

	virtual void AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray) const override;


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

	/** If this hit resulted from a ricochet, this hit result will be the last one (the hit result from the last hit wall to the target) */
	UPROPERTY()
		FHitResult	HitResult;
	UPROPERTY()
		float bulletTotalTravelDistanceBeforeHit;	// Total distance bullet traveled across all ricochets until it hit the target (info for UAS_Gun::DamageFalloff)
	UPROPERTY()
		uint8 ricochetsBeforeHit;					// This is the amount of ricochets resulting from blocking hits (info for UAS_Gun::   fill in attribute name here)

	UPROPERTY()
		bool bHitReplaced = false;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayAbilityTargetData_BulletTraceTargetHit::StaticStruct();
	}
};

template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_BulletTraceTargetHit> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_BulletTraceTargetHit>
{
	enum
	{
		WithNetSerializer = true	// For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};
