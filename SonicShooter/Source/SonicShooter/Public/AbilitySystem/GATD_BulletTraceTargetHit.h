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

	//virtual bool HasEndPoint() const override
	//{
	//	return true;
	//}
	//virtual FVector GetEndPoint() const override
	//{
	//	return HitResult.Location;
	//}


	// -------------------------------------

	UPROPERTY()
		float bulletTotalTravelDistanceBeforeHit;	// Total distance bullet traveled across all ricochets until it hit the target (info for UAS_Gun::DamageFalloff)
	UPROPERTY()
		uint8 ricochetsBeforeHit;					// This is the amount of ricochets resulting from blocking hits (info for UAS_Gun::   fill in attribute name here)


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
