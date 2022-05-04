// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"

#include "O_BulletTrace.generated.h"



struct FBulletHit : public FExitAwareHitResult
{
	FBulletHit(const FExitAwareHitResult& HitResult)
		: FExitAwareHitResult(HitResult)
		, RicochetNumber(0)
		, bIsRicochet(false)
		, Speed(0.f)
	{
	}

	int32 RicochetNumber;
	uint8 bIsRicochet : 1;
	float Speed;
};

/**
 * 
 */
struct FScanResult
{
	TArray<FBulletHit> BulletHits;
	FVector BulletStart;
	FVector BulletEnd;

	// This was unfinished and is not even needed anymore but I just want to keep it here for a commit
	float GetBulletSpeedAtScanTime(const float InScanTime) const
	{
		const int32 TotalScanTime = BulletHits.Last().RicochetNumber + 1; // equivalent to the total number of traces

		const float RemappedInScanTime = InScanTime * TotalScanTime; // remapped to the total scan time
		const int32 TraceNumberToUse = FMath::Floor(RemappedInScanTime);

		for (int32 i = 0; i < BulletHits.Num(); ++i)
		{
			if (BulletHits[i].RicochetNumber == TraceNumberToUse)
			{
				if (BulletHits.IsValidIndex(i + 1))
				{
					const float& ThisHitTime = BulletHits[i].Time;
					const float& NextHitTime = BulletHits[i + 1].Time;
					if (NextHitTime > InScanTime) // if the next bullet hit overshoots our desired time
					{
						// InTime is between ThisHitTime and NextHitTime
						FVector2D RangeA = FVector2D(ThisHitTime, NextHitTime);
						FVector2D RangeB = FVector2D(0.f, 1.f);
						const float RemappedTime = FMath::GetMappedRangeValueClamped(RangeA, RangeB, InScanTime);

						return FMath::Lerp(BulletHits[i].Speed, BulletHits[i + 1].Speed, RemappedTime);
					}
				}
			}
		}
	}

	void DebugScan(const UWorld* InWorld) const;
};

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UO_BulletTrace : public UObject
{
	GENERATED_BODY()
	
public:
	UO_BulletTrace(const FObjectInitializer& ObjectInitializer);


	/** (Injected) Max times to penetrate through blocking hits (-1 is unlimited) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		float MaxPenetrations;
	/** (Injected) Max times to ricochet off of owner defined ricochetable hits (defined through TFunction parameter) (-1 is unlimited) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Trace")
		float MaxRicochets;

	/** The falloff of range for this bullet */
	static const float RangeFalloffNerf;

	/** (Injected) Basically our gun's range */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float InitialBulletSpeed;

	/** (Injected) Basically our gun's range */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
		float SpeedNerfImunity;


	/**
	 * Performs traces from a given ScanStart into a given ScanDirection with ricochets and penetrations.
	 * May want to re-use an array for OutHitResults when calling multiple times to avoid useless allocations and deallocations.
	 * 
	 * @param  ShouldRicochetOffOf      TFunction where caller tells us if a hit result causes a ricochet
	 */
	void ScanWithLineTraces(TArray<FHitResult>& OutHitResults, const FVector& InScanStart, const FVector& InScanDirection, const float InDistanceCap, const UWorld* InWorld, const ECollisionChannel InTraceChannel, const FCollisionQueryParams& InCollisionQueryParams = FCollisionQueryParams::DefaultQueryParam, const TFunctionRef<bool(const FHitResult&)>& ShouldRicochetOffOf = [](const FHitResult&) { return false; });

	/**
	 * ScanWithLineTraces but uses bullet speed that is slowed down by ricochets and penetrations and stops when we run out
	 */
	void ScanWithLineTracesUsingSpeed(FScanResult& OutScanResult, const FVector& InScanStart, const FVector& InScanDirection, const float InDistanceCap, const UWorld* InWorld, const ECollisionChannel InTraceChannel, FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams::DefaultQueryParam);

private:
	/** Moves our traces' start points in the trace direction by a small amount to ensure we don't get stuck hitting the same object over and over again. This allows us to avoid ignoring the component so that we can hit the same component's geometry again */
	static const float TraceStartWallAvoidancePadding;

	static bool ShouldRicochetOffOf(const FHitResult& HitResult);

	static float NerfSpeedPerCm(float& InOutSpeed, const float InDistanceToTravel, const float InNerfPerCm);
};
