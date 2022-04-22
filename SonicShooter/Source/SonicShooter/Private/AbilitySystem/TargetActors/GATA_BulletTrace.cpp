// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/GATA_BulletTrace.h"

#include "Abilities/GameplayAbility.h"
#include "Utilities/CollisionChannels.h"
#include "AbilitySystem/Types/SSGameplayAbilityTargetTypes.h"
#include "AbilitySystemComponent.h"
#include "BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"
#include "PhysicalMaterial/PM_Shooter.h"
#include "BlueprintFunctionLibraries/BFL_HitResultHelpers.h"
#include "BlueprintFunctionLibraries/BFL_MathHelpers.h"

#include "Kismet/KismetSystemLibrary.h"



AGATA_BulletTrace::AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TraceChannel = COLLISION_BULLET;


}


void AGATA_BulletTrace::ConfirmTargetingAndContinue()
{
	Super::Super::ConfirmTargetingAndContinue(); // skip AGATA_Trace's stuff


	// Our Target Data to broadcast
	FGameplayAbilityTargetDataHandle TargetDataHandle;

	// Perform our scans
	TArray<TArray<FHitResult>> ScansHitResults;
	PerformScans(ScansHitResults);

	// Loop through our scans
	for (int32 ScanNumber = 0; ScanNumber < ScansHitResults.Num(); ScanNumber++)
	{
		FGATD_BulletTraceTargetHit* ThisScanTargetData = new FGATD_BulletTraceTargetHit(); // These are cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr)
		
		const TArray<FHitResult>& ScanHitResults = ScansHitResults[ScanNumber];


		float TotalDistanceUpUntilThisTrace = 0.f; // accumulated distance of the previous traces
		TArray<FVector_NetQuantize> ScanTracePoints; // this is used to tell target data where this bullet went
		if (ScanHitResults.Num() > 0)
		{
			ScanTracePoints.Add(ScanHitResults[0].TraceStart);
		}




		FHitResult PreviousHit;
		for (int32 index = 0, iteration = 0; index < ScanHitResults.Num(); ++index, ++iteration)
		{
			const FHitResult& Hit = ScanHitResults[index];

			if (iteration != 0)
			{
				const bool bIsNewTrace = !UBFL_HitResultHelpers::AreHitsFromSameTrace(Hit, PreviousHit);
				if (bIsNewTrace)
				{
					// Accumulate last trace's distance
					TotalDistanceUpUntilThisTrace += PreviousHit.Distance;

					if (ShouldRicochetOffOf(PreviousHit))
					{
						// We ricocheted and are changing tracing direction so add this point to the ScanTracePoints
						ScanTracePoints.Add(Hit.TraceStart);
					}
				}
			}


			if (HitResultFailsFilter(ScanHitResults, index, Filter, bAllowMultipleHitsPerActor)) // don't actually filter it, just check if it passes the filter
			{
				// This index did not pass the filter, stop here so that we don't add target data for it
				PreviousHit = Hit;
				continue;
			}


			// If we got here, we are an unfiltered hit (e.g. we hit a Character), add info to our Target Data:

			// This Hit Result's distance plus the previous tracing direction's traveled distance
			const float RicochetAwareDistance = TotalDistanceUpUntilThisTrace + Hit.Distance;
			const float BulletSpeedOnHit = GetBulletSpeedAtPoint(Hit.ImpactPoint, ScanNumber);

			FActorHitInfo ActorHitInfo = FActorHitInfo(Hit.GetActor(), RicochetAwareDistance, BulletSpeedOnHit);
			ThisScanTargetData->ActorHitInfos.Add(ActorHitInfo);
			



			PreviousHit = Hit;
		}

		if (ScanHitResults.Num() > 0)
		{
			ScanTracePoints.Add(ScanHitResults.Last().TraceEnd);
		}
		ThisScanTargetData->BulletTracePoints = ScanTracePoints;


		TargetDataHandle.Add(ThisScanTargetData);
	}
	

	TargetDataReadyDelegate.Broadcast(TargetDataHandle);
}

void AGATA_BulletTrace::CalculateAimDirection(FVector& OutAimStart, FVector& OutAimDir) const
{
	Super::CalculateAimDirection(OutAimStart, OutAimDir); // call Super so we get the PC's view dir, and then we can add bullet spread ontop of that


	// Calculate new OutAimDir with random bullet spread offset if needed
	if (CurrentBulletSpread > SMALL_NUMBER)
	{
		// Our injected random seed is only unique to each fire. We need a random seed that is also unique to each bullet in the fire, so we will do this by using t
		const int32 FireAndBulletSpecificNetSafeRandomSeed = FireSpecificNetSafeRandomSeed - ((CurrentScanIndex + 2) * FireSpecificNetSafeRandomSeed);	// Here, the 'number' multiplied to t makes the random pattern noticable after firing 'number' of times. I use the prediction key as that 'number' which i think eliminates the threshold for noticeability entirely. - its confusing to think about but i think it works
		FMath::RandInit(FireAndBulletSpecificNetSafeRandomSeed);
		const FRandomStream RandomStream = FRandomStream(FMath::Rand());

		// Get and apply random offset to OutAimDir using randomStream
		const float ConeHalfAngleRadius = FMath::DegreesToRadians(CurrentBulletSpread * 0.5f);
		OutAimDir = RandomStream.VRandCone(OutAimDir, ConeHalfAngleRadius);
	}
}
bool AGATA_BulletTrace::ShouldRicochetOffOf(const FHitResult& Hit) const
{
	const UPM_Shooter* ShooterPhysMat = Cast<const UPM_Shooter>(Hit.PhysMaterial.Get());
	if (IsValid(ShooterPhysMat))
	{
		if (ShooterPhysMat->bRichochetsBullets)
		{
			return true;
		}
	}

	return false;
}



void AGATA_BulletTrace::PerformScan(TArray<FHitResult>& OutHitResults)
{
	OutHitResults.Empty();

	// Perform line trace
	ScanWithLineTraces(OutHitResults, GetAimDirectionOfStartLocation());

}


void AGATA_BulletTrace::OnPrePerformScans(TArray<TArray<FHitResult>>& OutScansResults)
{
	Super::OnPrePerformScans(OutScansResults);

	// Initialize the BulletSteps for these scans to defaulted bullet steps
	BulletSteps.SetNum(NumOfScans);
}





/////////////////////////////////////////////////////////////// BEGIN ScanWithLineTraces() events /////////////////////



bool AGATA_BulletTrace::ShouldContinueTracingAfterFirstTrace(TArray<FHitResult>& FirstTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams)
{
	bool RetVal = Super::ShouldContinueTracingAfterFirstTrace(FirstTraceHitResults, World, CurrentTracingDirection, QueryParams);


	// Initialize CurrentTracingDirectionBlockingHits
	CurrentTracingDirectionBlockingHits.Empty();
	CurrentTracingDirectionStartIndex = 0;

	// Intialize CurrentBulletSpeed
	CurrentBulletSpeed = InitialBulletSpeed;

	// Initialize this scans's BulletSteps
	BulletSteps[CurrentScanIndex].Empty();


	NerfCurrentBulletSpeedByDistanceTraveled(FirstTraceHitResults);

	return RetVal;
}
bool AGATA_BulletTrace::ShouldContinueTracingAfterPenetrationTrace(TArray<FHitResult>& ScanHitResults, TArray<FHitResult>& PenetrationTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams)
{
	bool RetVal = Super::ShouldContinueTracingAfterPenetrationTrace(ScanHitResults, PenetrationTraceHitResults, World, CurrentTracingDirection, QueryParams);

	const FHitResult& PenetratedThrough = ScanHitResults.Last();

	// Add what we penetrated through as a blocking hit for CurrentTracingDirectionBlockingHits
	CurrentTracingDirectionBlockingHits.Add(PenetratedThrough);


	NerfCurrentBulletSpeedByDistanceTraveled(PenetrationTraceHitResults);

	return RetVal;
}
bool AGATA_BulletTrace::ShouldContinueTracingAfterRicochetHit(TArray<FHitResult>& ScanHitResults, TArray<FHitResult>& RicochetTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams)
{
	bool RetVal = Super::ShouldContinueTracingAfterRicochetHit(ScanHitResults, RicochetTraceHitResults, World, CurrentTracingDirection, QueryParams);


	// Add what we are ricocheting off of as a blocking hit for CurrentTracingDirectionBlockingHits
	const FHitResult& RicochetOffOf = ScanHitResults.Last();
	CurrentTracingDirectionBlockingHits.Add(RicochetOffOf);


	TArray<FBulletStep> ThisTracingDirectionBulletSteps;

	// Fill out ThisTracingDirectionBulletSteps
	{
		// We are about to change our tracing direction so BuildTraceSegments() for the current tracing direction's blocking hits
		if (CurrentTracingDirectionBlockingHits.Num() > 0)
		{
			// Calculate trace segments for the current tracing direction's blocking hits
			TArray<FTraceSegment> ThisTracingDirectionTraceSegments;
			UBFL_CollisionQueryHelpers::BuildTraceSegments(ThisTracingDirectionTraceSegments, CurrentTracingDirectionBlockingHits, RicochetOffOf.Location, World, QueryParams, TraceChannel);
			
			// Add these trace segments as bullet steps
			for (const FTraceSegment& PenetrationSegment : ThisTracingDirectionTraceSegments)
			{
				ThisTracingDirectionBulletSteps.Add(FBulletStep(PenetrationSegment));
			}
		}

		// Add this ricochet point as a bullet step
		FTracePoint RicochetPoint = FTracePoint(RicochetOffOf.Location, RicochetOffOf.PhysMaterial.Get());
		ThisTracingDirectionBulletSteps.Add(FBulletStep(RicochetPoint));
	}

	// Add the current tracing direction's bullet steps to this scan's list of bullet steps
	BulletSteps[CurrentScanIndex].Append(ThisTracingDirectionBulletSteps);


	FVector StoppedAtPoint;
	bool bStoppedInSegment = false;
	if (ApplyBulletStepsToBulletSpeed(ThisTracingDirectionBulletSteps, StoppedAtPoint, bStoppedInSegment))
	{
		if (bStoppedInSegment) // only if we stopped inside of a segment
		{
			// Loop through this tracing direction's Hit Results until we find the first hit that happened after StoppedAtPoint, then remove it and all of the ones proceeding it
			for (int32 i = CurrentTracingDirectionStartIndex; i < ScanHitResults.Num(); ++i)
			{
				const FHitResult& Hit = ScanHitResults[i];

				const FVector LocationPointToStoppedPoint = (StoppedAtPoint - Hit.Location);
				const bool bIsAfterStoppedPoint = (FVector::DotProduct(LocationPointToStoppedPoint, CurrentTracingDirection) <= 0); // if this Hit's Location is after StoppedAtLocation
				if (bIsAfterStoppedPoint)
				{
					// Remove the hits that happened after StoppedAtPoint
					ScanHitResults.RemoveAt(i, ScanHitResults.Num() - i);

					// Add TraceInfo so we have where the Segment ended
					FHitResult TraceInfo;
					TraceInfo.TraceStart = Hit.TraceStart;
					TraceInfo.TraceEnd = StoppedAtPoint;
					ScanHitResults.Add(TraceInfo);

					break;
				}
			}
		}

		RetVal = false;
	}


	NerfCurrentBulletSpeedByDistanceTraveled(RicochetTraceHitResults);


	// Reset the blocking Hit Results for the next group of blocking hits
	CurrentTracingDirectionBlockingHits.Empty();
	CurrentTracingDirectionStartIndex = (ScanHitResults.Num() - 1);

	return RetVal;
}
void AGATA_BulletTrace::OnFinishedScanWithLineTraces(TArray<FHitResult>& ScanHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams)
{
	Super::OnFinishedScanWithLineTraces(ScanHitResults, World, CurrentTracingDirection, QueryParams);



	TArray<FBulletStep> ThisTracingDirectionBulletSteps;

	// Fill out ThisTracingDirectionBulletSteps
	{
		// Apply any Trace Segments left to our CurrentBulletSpeed
		if (CurrentTracingDirectionBlockingHits.Num() > 0)
		{
			TArray<FTraceSegment> ThisTracingDirectionTraceSegments;
			UBFL_CollisionQueryHelpers::BuildTraceSegments(ThisTracingDirectionTraceSegments, CurrentTracingDirectionBlockingHits, World, QueryParams, TraceChannel);
			for (const FTraceSegment& TraceSegment : ThisTracingDirectionTraceSegments)
			{
				ThisTracingDirectionBulletSteps.Add(TraceSegment);
			}

		}

	}

	BulletSteps[CurrentScanIndex].Append(ThisTracingDirectionBulletSteps);


	FVector StoppedAtPoint;
	bool bStoppedInSegment = false;
	if (ApplyBulletStepsToBulletSpeed(ThisTracingDirectionBulletSteps, StoppedAtPoint, bStoppedInSegment))
	{
		if (bStoppedInSegment) // only if we stopped inside of a segment
		{
			// Loop through this tracing direction's Hit Results until we find the first hit that happened after StoppedAtPoint, then remove it and all of the ones proceeding it
			for (int32 i = CurrentTracingDirectionStartIndex; i < ScanHitResults.Num(); ++i)
			{
				const FHitResult& Hit = ScanHitResults[i];

				const FVector LocationPointToStoppedPoint = (StoppedAtPoint - Hit.Location);
				const bool bIsAfterStoppedPoint = (FVector::DotProduct(LocationPointToStoppedPoint, CurrentTracingDirection) <= 0); // if this Hit's Location is after StoppedAtLocation
				if (bIsAfterStoppedPoint)
				{
					// Remove the hits that happened after StoppedAtPoint
					ScanHitResults.RemoveAt(i, ScanHitResults.Num() - i);

					// Add TraceInfo so we have where the Segment ended
					FHitResult TraceInfo;
					TraceInfo.TraceStart = Hit.TraceStart;
					TraceInfo.TraceEnd = StoppedAtPoint;
					ScanHitResults.Add(TraceInfo);

					break;
				}
			}
		}
	}




	CurrentTracingDirectionBlockingHits.Empty();
	CurrentTracingDirectionStartIndex = 0;

}




/////////////////////////////////////////////////////////////// END ScanWithLineTraces() events /////////////////////







bool AGATA_BulletTrace::ApplyBulletStepsToBulletSpeed(const TArray<FBulletStep>& BulletStepsToApply, FVector& OutStoppedAtPoint, bool& outStoppedInSegment)
{
	// Edge case: If we were already out of Bullet Speed TODO: maybe just do nothing and return false in this case
	if (CurrentBulletSpeed <= 0)
	{
		// Try to set a valid OutStoppedAtPoint
		if (BulletStepsToApply.IsValidIndex(0))
		{
			const FBulletStep& FirstStep = BulletStepsToApply[0];

			if (const FTraceSegment* TraceSegment = FirstStep.GetTraceSegment())
			{
				// Assume that the first bullet step is where we ran out of speed
				OutStoppedAtPoint = TraceSegment->GetStartPoint();
				outStoppedInSegment = true;
			}
			else if (const FTracePoint* TracePoint = FirstStep.GetRicochetPoint())
			{
				// Assume that the first bullet step is where we ran out of speed
				OutStoppedAtPoint = TracePoint->Point;
			}
		}

		CurrentBulletSpeed = 0.f;
		return true;
	}


	// Loop through the bullet steps and apply them to our bullet speed
	for (const FBulletStep& BulletStep : BulletStepsToApply)
	{
		// Take away Bullet Speed from this BulletStep
		CurrentBulletSpeed -= BulletStep.GetBulletSpeedToTakeAway();

		// If we ran out of Bullet Speed
		if (CurrentBulletSpeed <= 0)
		{
			if (const FTraceSegment* TraceSegment = BulletStep.GetTraceSegment())
			{
				// The speed we had before we took away
				const float PreLossBulletSpeed = (CurrentBulletSpeed + BulletStep.GetBulletSpeedToTakeAway());

				// How far we traveled through this Segment
				const float GotThroughnessRatio = (PreLossBulletSpeed / BulletStep.GetBulletSpeedToTakeAway());
				const float GotThroughDistance = GotThroughnessRatio * TraceSegment->GetSegmentDistance();

				// The exact point where we ran out of speed
				OutStoppedAtPoint = TraceSegment->GetStartPoint() + (GotThroughDistance * TraceSegment->GetTraceDir());
				outStoppedInSegment = true;
			}
			else if (const FTracePoint* TracePoint = BulletStep.GetRicochetPoint())
			{
				// The exact point where we ran out of speed
				OutStoppedAtPoint = TracePoint->Point;
			}

			// We ran out of speed and have a valid OutStoppedAtPoint
			CurrentBulletSpeed = 0.f;
			return true;
		}
	}




	return false;
}

float AGATA_BulletTrace::GetBulletSpeedAtPoint(const FVector& Point, const int32 ScanIndex)
{
	float RetVal = InitialBulletSpeed;


	float DistanceTraveledToPoint = 0.f;

	// Loop through the bullet steps of the given scan
	for (const FBulletStep& BulletStep : BulletSteps[ScanIndex])
	{
		RetVal -= BulletStep.GetBulletSpeedToTakeAway();

		float EqualsTolerance = KINDA_SMALL_NUMBER + TraceStartWallAvoidancePadding;
		if (const FTraceSegment* TraceSegment = BulletStep.GetTraceSegment()) // if we're a TraceSegment
		{
			const float& SegmentDistance = TraceSegment->GetSegmentDistance();

			DistanceTraveledToPoint += SegmentDistance;

			if (Point.Equals(TraceSegment->GetEndPoint(), EqualsTolerance)) // if the given Point is this segment's EndPoint
			{
				break;
			}

			const float TraveledDistance = FVector::Distance(TraceSegment->GetStartPoint(), Point);
			const float UntraveledDistance = FVector::Distance(Point, TraceSegment->GetEndPoint());

			if (FMath::IsNearlyEqual(TraveledDistance + UntraveledDistance, SegmentDistance)) // if StartPoint, EndPoint, and Point do not form a triangle, then Point is on the segment
			{
				// We took away the whole Segment's speed even though this point is within the Segment. So add back the part of the Segment that we didn't travel through
				const float TraveledThroughnessRatio = (TraveledDistance / SegmentDistance);
				RetVal += BulletStep.GetBulletSpeedToTakeAway() * (1 - TraveledThroughnessRatio);


				DistanceTraveledToPoint -= UntraveledDistance;

				break;
			}

		}
		else if (const FTracePoint* RicochetPoint = BulletStep.GetRicochetPoint())	// if we're a RicochetPoint
		{
			if (Point.Equals(RicochetPoint->Point, EqualsTolerance))
			{
				break;
			}
		}
		else
		{
			UE_LOG(LogGameplayAbilityTargetActor, Warning, TEXT("%s() A BulletStep had no RicochetPoint or TraceSegment.... Something's wrong"), ANSI_TO_TCHAR(__FUNCTION__));
		}
	}
	

	// Nerf RetVal by distance traveled
	const float NerfMultiplier = GetBulletSpeedFalloffNerf(BulletSpeedFalloff, DistanceTraveledToPoint);
	RetVal *= NerfMultiplier;


	return RetVal;
}




void AGATA_BulletTrace::NerfCurrentBulletSpeedByDistanceTraveled(const TArray<FHitResult>& HitResults)
{
	float DistanceTraveled = 0.f;
	for (const FHitResult& Hit : HitResults)
	{
		DistanceTraveled += Hit.Distance; // TODO: will overlaps have duplicate distances and mess this up?
	}

	const float NerfMultiplier = GetBulletSpeedFalloffNerf(BulletSpeedFalloff, DistanceTraveled);
	CurrentBulletSpeed *= NerfMultiplier;
}

float AGATA_BulletTrace::GetBulletSpeedFalloffNerf(const float BulletSpeedFalloffValue, const float TotalDistanceBulletTraveled)
{
	// BulletSpeedFalloffValue is the multiplier applied against the bullet's speed every 1000cm (32ft) or 10 blocks of our Proto material
	return FMath::Pow(BulletSpeedFalloffValue, (TotalDistanceBulletTraveled / 1000));
}
