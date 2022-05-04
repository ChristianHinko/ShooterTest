// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_BulletTrace.h"

#include "BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"
#include "PhysicalMaterial/PM_Shooter.h"

#include "DrawDebugHelpers.h"



const float UO_BulletTrace::TraceStartWallAvoidancePadding = .01f;
const float UO_BulletTrace::RangeFalloffNerf = .02f;

UO_BulletTrace::UO_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MaxPenetrations(0)
	, MaxRicochets(0)
{

}

void UO_BulletTrace::ScanWithLineTraces(TArray<FHitResult>& OutHitResults, const FVector& InScanStart, const FVector& InScanDirection, const float InDistanceCap, const UWorld* InWorld, const ECollisionChannel InTraceChannel, const FCollisionQueryParams& InCollisionQueryParams, const TFunctionRef<bool(const FHitResult&)>& ShouldRicochetOffOf)
{
	FVector TraceStart = InScanStart;
	FVector TraceDirection = InScanDirection;
	float RemainingScanDistance = InDistanceCap;

	// The first iteration of this loop is the initial trace and the rest of the iterations are ricochet traces
	int32 PenetrationNumber = 0;
	for (int32 RicochetNumber = 0; (RicochetNumber <= MaxRicochets || MaxRicochets == -1); ++RicochetNumber)
	{
		TArray<FExitAwareHitResult> TraceHitResults;
		const FVector TraceEnd = TraceStart + (TraceDirection * RemainingScanDistance);

		// Penetration line trace that stops at a user defined ricochetable surface
		const bool bHitRicochetableSurface = UBFL_CollisionQueryHelpers::ExitAwareLineTraceMultiByChannelWithPenetrations(InWorld, TraceHitResults, TraceStart, TraceEnd, InTraceChannel, InCollisionQueryParams, ShouldRicochetOffOf, true);

		// Add found hit results to the return value
		OutHitResults.Reserve(OutHitResults.Num() + TraceHitResults.Num()); // assume that we will add all of the hits but if we run out of speed we will not need this extra space
		for (const FExitAwareHitResult& Hit : TraceHitResults)
		{
			OutHitResults.Add(Hit);

			if (ShouldRicochetOffOf(Hit))
			{
				// We are a ricochet hit so make us the last hit (forget about the rest of the hits)
				break;
			}

			// Check if we ran out of penetrations
			if (Hit.bBlockingHit)
			{
				if (Hit.bIsExitHit == false) // if we are penetrating through an entrance
				{
					++PenetrationNumber;
					if (PenetrationNumber > MaxPenetrations && MaxPenetrations != -1)
					{
						return;
					}
				}
			}
		}

		if (!bHitRicochetableSurface)
		{
			// Nothing to ricochet off of
			break;
		}

		// SETUP FOR OUR NEXT TRACE

		// Take away the distance traveled of this trace from our RemainingScanDistance
		RemainingScanDistance -= OutHitResults.Last().Distance; // since we stopped at a ricochet, the last hit is our ricochet hit
		if (RemainingScanDistance <= 0.f)
		{
			break;
		}

		// Reflect our TraceDirection off of the ricochetable surface and calculate TraceStart for next ricochet trace
		TraceDirection = TraceDirection.MirrorByVector(OutHitResults.Last().ImpactNormal);
		TraceStart = OutHitResults.Last().Location + (TraceDirection * TraceStartWallAvoidancePadding);
	}
}

void UO_BulletTrace::ScanWithLineTracesUsingSpeed(FScanResult& OutScanResult, const FVector& InScanStart, const FVector& InScanDirection, const float InDistanceCap, const UWorld* InWorld, const ECollisionChannel InTraceChannel, FCollisionQueryParams CollisionQueryParams)
{
	OutScanResult.BulletStart = InScanStart;

	CollisionQueryParams.bReturnPhysicalMaterial = true; // this is required for bullet speed reduction calculations and determining whether to ricochet

	float BulletSpeed = InitialBulletSpeed;
	TArray<const UPhysicalMaterial*> PhysMatStack;

	FVector TraceStart = InScanStart;
	FVector TraceDirection = InScanDirection;
	float RemainingScanDistance = InDistanceCap;

	// The first iteration of this loop is the initial trace and the rest of the iterations are ricochet traces
	int32 PenetrationNumber = 0;
	for (int32 RicochetNumber = 0; (RicochetNumber <= MaxRicochets || MaxRicochets == -1); ++RicochetNumber)
	{
		TArray<FExitAwareHitResult> TraceHitResults;
		const FVector TraceEnd = TraceStart + (TraceDirection * RemainingScanDistance);

		// Penetration line trace that stops at a user defined ricochetable surface
		const bool bHitRicochetableSurface = UBFL_CollisionQueryHelpers::ExitAwareLineTraceMultiByChannelWithPenetrations(InWorld, TraceHitResults, TraceStart, TraceEnd, InTraceChannel, CollisionQueryParams, ShouldRicochetOffOf, true);

		// Apply speed nerfs and see if we stopped (from TraceStart to the first hit)
		{
			float DistanceToFirstHit;
			if (TraceHitResults.Num() > 0)
			{
				DistanceToFirstHit = TraceHitResults[0].Distance;
			}
			else
			{
				// Traced into thin air - so use the distance of the whole trace
				DistanceToFirstHit = RemainingScanDistance;
			}

			// Range falloff nerf
			float SpeedToTakeAwayPerCm = RangeFalloffNerf;

			// Accumulate all of the speed nerfs from the PhysMatStack
			// This can only have items at this point for ricochet traces because this system allows ricochets traces to start inside of Phys Mats
			for (const UPhysicalMaterial* PhysMat : PhysMatStack)
			{
				const UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(PhysMat);
				if (IsValid(ShooterPhysMat))
				{
					SpeedToTakeAwayPerCm += ShooterPhysMat->PenetrationSpeedNerf;
				}
			}

			// Apply the speed nerf
			const float TraveledDistance = NerfSpeedPerCm(BulletSpeed, DistanceToFirstHit, SpeedToTakeAwayPerCm);
			if (BulletSpeed <= 0.f)
			{
				// Ran out of speed. Get the point stopped at
				OutScanResult.BulletEnd = TraceStart + (TraveledDistance * TraceDirection);
				return;
			}
		}

		// Add found hit results to the return value
		OutScanResult.BulletHits.Reserve(OutScanResult.BulletHits.Num() + TraceHitResults.Num()); // assume that we will add all of the hits but if we run out of speed we will not need this extra space
		for (int32 i = 0; i < TraceHitResults.Num(); ++i)
		{
			if (TraceHitResults[i].bStartPenetrating)
			{
				// Initial overlaps would mess up our PhysMat stack so skip it
				// Btw this is only a thing for non-bTraceComplex queries
				continue;
			}

			// Add this hit to our bullet hits
			FBulletHit& AddedBulletHit = OutScanResult.BulletHits.Add_GetRef(TraceHitResults[i]);
			AddedBulletHit.RicochetNumber = RicochetNumber;
			AddedBulletHit.bIsRicochet = ShouldRicochetOffOf(AddedBulletHit);

			// Handle ricochet hit
			if (AddedBulletHit.bIsRicochet)
			{
				// Apply speed nerf and see if we stopped
				const UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(AddedBulletHit.PhysMaterial);
				if (IsValid(ShooterPhysMat))
				{
					float SpeedToTakeAway = ShooterPhysMat->RicochetSpeedNerf;

					BulletSpeed -= SpeedToTakeAway;
					if (BulletSpeed <= 0.f)
					{
						// Ran out of speed. Get the point stopped at
						OutScanResult.BulletEnd = AddedBulletHit.Location;
						return;
					}
				}

				// We are a ricochet hit so make us the last hit (forget about the rest of the hits)
				break;
			}

			// Update our PhysMat stack with this hit's Physical Materials
			if (AddedBulletHit.bIsExitHit == false)
			{
				PhysMatStack.Push(AddedBulletHit.PhysMaterial.Get());
			}
			else
			{
				const int32 IndexOfPhysMatThatWeAreExiting = PhysMatStack.FindLast(AddedBulletHit.PhysMaterial.Get());

				if (IndexOfPhysMatThatWeAreExiting != INDEX_NONE)
				{
					PhysMatStack.RemoveAt(IndexOfPhysMatThatWeAreExiting);
				}
				else
				{
					UE_LOG(LogBulletTrace, Error, TEXT("%s() Bullet exited a Physical Material that was never entered. This means that the bullet started from within a collider. We can't account for that object's phys mat which means our speed values for the bullet scan will be wrong. Make sure to not allow player to start shot from within a colider. Hit Actor: [%s], owner Actor: [%s]"), ANSI_TO_TCHAR(__FUNCTION__), GetData(TraceHitResults[i].GetActor()->GetName()), GetData(GetNameSafe(GetTypedOuter<AActor>())));
				}
			}

			// Apply speed nerfs and see if we stopped (from this hit to the next hit)
			{
				float DistanceToNextHit;
				if (TraceHitResults.IsValidIndex(i + 1))
				{
					// Get distance from this hit to the next hit
					DistanceToNextHit = (TraceHitResults[i + 1].Distance - AddedBulletHit.Distance); // distance from [i] to [i + 1]
				}
				else
				{
					// Get distance from this hit to trace end
					DistanceToNextHit = (RemainingScanDistance - AddedBulletHit.Distance);
				}

				// Range falloff nerf
				float SpeedToTakeAwayPerCm = RangeFalloffNerf;

				// Accumulate all of the speed nerfs from the PhysMatStack
				for (const UPhysicalMaterial* PhysMat : PhysMatStack)
				{
					const UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(PhysMat);
					if (IsValid(ShooterPhysMat))
					{
						SpeedToTakeAwayPerCm += ShooterPhysMat->PenetrationSpeedNerf;
					}
				}

				// Apply the speed nerf
				const float TraveledDistance = NerfSpeedPerCm(BulletSpeed, DistanceToNextHit, SpeedToTakeAwayPerCm);
				if (BulletSpeed <= 0.f)
				{
					// Ran out of speed. Get the point stopped at
					OutScanResult.BulletEnd = AddedBulletHit.Location + (TraveledDistance * TraceDirection);
					return;
				}
			}
			AddedBulletHit.Speed = BulletSpeed;

			// Check if we ran out of penetrations
			if (AddedBulletHit.bBlockingHit)
			{
				if (AddedBulletHit.bIsExitHit == false) // if we are penetrating through an entrance
				{
					++PenetrationNumber;
					if (PenetrationNumber > MaxPenetrations && MaxPenetrations != -1)
					{
						return;
					}
				}
			}
		}

		if (!bHitRicochetableSurface)
		{
			// Nothing to ricochet off of
			break;
		}

		// SETUP FOR OUR NEXT TRACE

		// Take away the distance traveled of this trace from our RemainingScanDistance
		RemainingScanDistance -= OutScanResult.BulletHits.Last().Distance; // since we stopped at a ricochet, the last hit is our ricochet hit
		if (RemainingScanDistance <= 0.f)
		{
			break;
		}

		// Reflect our TraceDirection off of the ricochetable surface and calculate TraceStart for next ricochet trace
		TraceDirection = TraceDirection.MirrorByVector(OutScanResult.BulletHits.Last().ImpactNormal);
		TraceStart = OutScanResult.BulletHits.Last().Location + (TraceDirection * TraceStartWallAvoidancePadding);
	}
}

bool UO_BulletTrace::ShouldRicochetOffOf(const FHitResult& HitResult)
{
	if (const UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(HitResult.PhysMaterial))
	{
		// See if we ricocheted
		if (ShooterPhysMat->bRicochets)
		{
			return true;
		}
	}

	return false;
}

float UO_BulletTrace::NerfSpeedPerCm(float& InOutSpeed, const float InDistanceToTravel, const float InNerfPerCm)
{
	const float SpeedToTakeAway = (InNerfPerCm * InDistanceToTravel);
	const float TraveledRatio = (InOutSpeed / SpeedToTakeAway);
	const float TraveledDistance = (InDistanceToTravel * TraveledRatio);
	InOutSpeed -= SpeedToTakeAway;

	return TraveledDistance;
}

void FScanResult::DebugScan(const UWorld* InWorld) const
{
#if ENABLE_DRAW_DEBUG
	const float DebugLifeTime = 5.f;
	const FColor TraceColor = FColor::Blue;
	const FColor HitColor = FColor::Red;

	for (const FHitResult& Hit : BulletHits)
	{
		DrawDebugLine(InWorld, Hit.TraceStart, Hit.Location, TraceColor, false, DebugLifeTime);
		DrawDebugPoint(InWorld, Hit.ImpactPoint, 10.f, HitColor, false, DebugLifeTime);
	}

	if (BulletHits.Num() > 0)
	{
		DrawDebugLine(InWorld, BulletHits.Last().Location, BulletEnd, TraceColor, false, DebugLifeTime);
	}
	else
	{
		DrawDebugLine(InWorld, BulletStart, BulletEnd, TraceColor, false, DebugLifeTime);
	}
#endif // ENABLE_DRAW_DEBUG
}
