// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_BulletTrace.h"

#include "BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"



const float UO_BulletTrace::TraceStartWallAvoidancePadding = .01f;

UO_BulletTrace::UO_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UO_BulletTrace::ScanWithLineTraces(TArray<FHitResult>& OutHitResults, FVector ScanStart, FVector ScanDirection, float DistanceToTravel, const int32 InMaxPenetrations, const int32 InMaxRicochets, const UWorld* InWorld, const ECollisionChannel InTraceChannel, const FCollisionQueryParams& InCollisionQueryParams, const TFunctionRef<bool(const FHitResult&)>& ShouldRicochetOffOf)
{
	// The first iteration of this loop is the initial trace and the rest of the iterations are ricochet traces
	int32 PenetrationNumber = 0;
	for (int32 RicochetNumber = 0; (RicochetNumber <= InMaxRicochets || InMaxRicochets == -1); ++RicochetNumber)
	{
		TArray<FHitResult> TraceHitResults;
		const FVector TraceEnd = ScanStart + (ScanDirection * DistanceToTravel);

		// Penetration line trace that stops at a user defined ricochetable surface
		const bool bHitRicochetableSurface = UBFL_CollisionQueryHelpers::DoubleSidedLineTraceMultiByChannelWithPenetrations(InWorld, TraceHitResults, ScanStart, TraceEnd, InTraceChannel, InCollisionQueryParams, ShouldRicochetOffOf);

		// Add found hit results to the return value
		bool bRanOutOfPenetrations = false;
		OutHitResults.Reserve(OutHitResults.Num() + TraceHitResults.Num());
		for (const FHitResult& Hit : TraceHitResults)
		{
			OutHitResults.Add(Hit);

			if (Hit.bBlockingHit)
			{
				if (IsEntranceHitResult(ScanDirection, Hit) && !ShouldRicochetOffOf(Hit))
				{
					++PenetrationNumber;
					if (PenetrationNumber > InMaxPenetrations && InMaxPenetrations != -1)
					{
						bRanOutOfPenetrations = true;
						break;
					}
				}
			}
		}

		if (bRanOutOfPenetrations)
		{
			return;
		}

		if (!bHitRicochetableSurface)
		{
			// Nothing to ricochet off of
			break;
		}

		// Take away the distance traveled of this trace from our CurrentBulletMaxRange
		DistanceToTravel -= OutHitResults.Last().Distance; // since we stopped at a ricochet, the last hit is our ricochet hit
		if (DistanceToTravel <= 0.f)
		{
			break;
		}

		// Reflect our ScanDirection off of the ricochetable surface and calculate ScanStart for next ricochet
		ScanDirection = ScanDirection.MirrorByVector(OutHitResults.Last().ImpactNormal);
		ScanStart = OutHitResults.Last().Location + (ScanDirection * TraceStartWallAvoidancePadding);
	}
}
