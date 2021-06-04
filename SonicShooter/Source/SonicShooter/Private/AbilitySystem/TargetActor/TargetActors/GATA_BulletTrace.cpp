// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h"

#include "Utilities\LogCategories.h"
#include "Abilities/GameplayAbility.h"
#include "Utilities/CollisionChannels.h"
#include "AbilitySystem/SSGameplayAbilityTargetTypes.h"
#include "GameplayAbilities\Public\AbilitySystemComponent.h"
#include "Item/Weapons/AS_Gun.h"
#include "Utilities\BlueprintFunctionLibraries\BFL_CollisionQueryHelpers.h"
#include "PhysicalMaterial/ShooterPhysicalMaterial.h"

#include "Kismet/KismetSystemLibrary.h"



AGATA_BulletTrace::AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TraceChannel = COLLISION_BULLET;
}

float AGATA_BulletTrace::GetMaxRange() const
{
	if (GunAttributeSet)
	{
		return GunAttributeSet->GetMaxRange();
	}

	UE_LOG(LogGameplayAbilityTargetActor, Error, TEXT("%s() GunAttributeSet null when trying to read its MaxRange attribute! Will return default value from Super instead!"), *FString(__FUNCTION__));
	return Super::GetMaxRange();
}
int32 AGATA_BulletTrace::GetNumberOfTraces() const
{
	if (GunAttributeSet)
	{
		return GunAttributeSet->GetNumberOfBulletsPerFire();
	}

	UE_LOG(LogGameplayAbilityTargetActor, Error, TEXT("%s() GunAttributeSet null when trying to read its NumberOfBulletsPerFire attribute! Will return default value from Super instead!"), *FString(__FUNCTION__));
	return Super::GetNumberOfTraces();
}
int32 AGATA_BulletTrace::GetRicochets() const
{
	// Go infinitely because we have our Bullet Speed system
	return -1;
}
int32 AGATA_BulletTrace::GetPenetrations() const
{
	// Go infinitely because we have our Bullet Speed system
	return -1;
}
float AGATA_BulletTrace::GetInitialBulletSpeed() const
{
	return 100.f; // TODO: make attribute for this
}

void AGATA_BulletTrace::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());


	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle TargetDataHandle;


		TArray<TArray<FHitResult>> TraceResults;
		PerformTraces(TraceResults, SourceActor);


		for (TArray<FHitResult>& ThisBulletHitResults : TraceResults)
		{
			/** Note: These are cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr) */
			FGATD_BulletTraceTargetHit* ThisBulletTargetData = new FGATD_BulletTraceTargetHit();


			float totalDistanceUpUntilThisTrace = 0.f; // accumulated distance of the previous traces

			TArray<FVector_NetQuantize> BulletTracePoints; // used to tell target data where this bullet went
			if (ThisBulletHitResults.Num() > 0)
			{
				BulletTracePoints.Emplace(ThisBulletHitResults[0].TraceStart);
			}

			FHitResult PreviousHit;
			for (int32 index = 0, iteration = 0; index < ThisBulletHitResults.Num(); ++index, ++iteration)
			{
				const FHitResult& Hit = ThisBulletHitResults[index];

				if (iteration != 0)
				{
					const bool bIsNewTrace = !AreHitsFromSameTrace(Hit, PreviousHit);
					if (bIsNewTrace)
					{
						// Accumulate last trace's distance
						totalDistanceUpUntilThisTrace += PreviousHit.Distance;

						if (ShouldRicochetOffOf(PreviousHit))
						{
							// We ricocheted and are changing trace direction so add this point to the BulletTracePoints
							BulletTracePoints.Emplace(Hit.TraceStart);
						}
					}
				}


				if (HitResultFailsFilter(ThisBulletHitResults, index, MultiFilterHandle, bAllowMultipleHitsPerActor)) // don't actually filter it, just check if it passes the filter
				{
					// This index did not pass the filter, stop here so that we don't add target data for it
					PreviousHit = Hit;
					continue;
				}


				// If we got here, we are an unfiltered hit (ie. we hit a character), add info to our target data:

				// This Hit Result's distance plus the previous ricochet(s)'s traveled distance
				const float ricochetAwareDistance = totalDistanceUpUntilThisTrace + Hit.Distance;
				float bulletSpeedOnHit = GetBulletSpeedAtPoint(Hit.ImpactPoint);
				ThisBulletTargetData->ActorHitInfos.Emplace(Hit.GetActor(), ricochetAwareDistance, bulletSpeedOnHit);




				PreviousHit = Hit;
			}

			if (ThisBulletHitResults.Num() > 0)
			{
				BulletTracePoints.Emplace(ThisBulletHitResults.Last().TraceEnd);
			}
			ThisBulletTargetData->BulletTracePoints = BulletTracePoints;


			TargetDataHandle.Add(ThisBulletTargetData);
		}
		

		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}

void AGATA_BulletTrace::CalculateAimDirection(FVector& ViewStart, FVector& ViewDir) const
{
	Super::CalculateAimDirection(ViewStart, ViewDir); // call Super so we get the PC's ViewDir, and then we can add bullet spread ontop of that


	// Calculate new ViewDir with random bullet spread offset if needed
	float currentBulletSpread = GunAttributeSet->CurrentBulletSpread;
	if (currentBulletSpread > SMALL_NUMBER)
	{
		// Our injected random seed is only unique to each fire. We need a random seed that is also unique to each bullet in the fire, so we will do this by using t
		const int32 fireAndBulletSpecificNetSafeRandomSeed = FireSpecificNetSafeRandomSeed - ((CurrentTraceIndex + 2) * FireSpecificNetSafeRandomSeed);	// Here, the 'number' multiplied to t makes the random pattern noticable after firing 'number' of times. I use the prediction key as that 'number' which i think eliminates the threshold for noticeability entirely. - its confusing to think about but i think it works
		FMath::RandInit(fireAndBulletSpecificNetSafeRandomSeed);
		const FRandomStream RandomStream = FRandomStream(FMath::Rand());

		// Get and apply random offset to ViewDir using randomStream
		const float coneHalfAngleRadius = FMath::DegreesToRadians(currentBulletSpread * 0.5f);
		ViewDir = RandomStream.VRandCone(ViewDir, coneHalfAngleRadius);
	}
}

void AGATA_BulletTrace::PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor)
{
	check(GunAttributeSet);
	OutHitResults.Empty();


	const bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(InSourceActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGATA_BulletTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.bTraceComplex = true;
	Params.bReturnFaceIndex = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();
	FVector TraceEnd;
	AimWithPlayerController(InSourceActor, Params, TraceStart, TraceEnd);		//Effective on server and launching client only

	// ------------------------------------------------------


	// Perform line trace
	LineTraceMulti(OutHitResults, InSourceActor->GetWorld(), TraceStart, TraceEnd, Params, bDebug);

}


bool AGATA_BulletTrace::OnInitialTrace(TArray<FHitResult>& OutInitialHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams& TraceParams)
{
	bool RetVal = Super::OnInitialTrace(OutInitialHitResults, World, Start, End, TraceParams);


	// Initialize ThisRicochetBlockingHits
	ThisRicochetBlockingHits.Empty();
	ThisRicochetStartingIndex = 0;
	ThisRicochetTraceDir = UKismetMathLibrary::GetDirectionUnitVector(Start, End);

	// Intialize CurrentBulletSpeed
	CurrentBulletSpeed = GetInitialBulletSpeed();

	// Initialize BulletSteps
	BulletSteps.Empty();


	return RetVal;
}
bool AGATA_BulletTrace::OnPenetrate(TArray<FHitResult>& HitResults, TArray<FHitResult>& OutPenetrateHitResults, const UWorld* World, const FVector& PenetrateStart, const FVector& PenetrateEnd, const FCollisionQueryParams& TraceParams)
{
	bool RetVal = Super::OnPenetrate(HitResults, OutPenetrateHitResults, World, PenetrateStart, PenetrateEnd, TraceParams);

	const FHitResult& PenetratedThrough = HitResults.Last();

	// Add what we penetrated through as a blocking hit for ThisRicochetBlockingHits
	ThisRicochetBlockingHits.Emplace(PenetratedThrough);

	return RetVal;
}
bool AGATA_BulletTrace::OnRicochet(TArray<FHitResult>& HitResults, TArray<FHitResult>& OutRicoHitResults, const UWorld* World, const FVector& RicoStart, const FVector& RicoEnd, const FCollisionQueryParams& TraceParams)
{
	bool RetVal = true;

	const FHitResult& RicochetOffOf = HitResults.Last();


	ThisRicochetBlockingHits.Emplace(RicochetOffOf);

	// We are ricocheting so BuildTraceSegments about this previous ricochet's blocking hits
	if (ThisRicochetBlockingHits.Num() > 0)
	{
		// We are about to ricochet so calculate Trace Segments for these blocking Hits before we move on to the next ricochet
		TArray<FTraceSegment> ThisRicochetTraceSegments;
		UBFL_CollisionQueryHelpers::BuildTraceSegments(ThisRicochetTraceSegments, ThisRicochetBlockingHits, RicochetOffOf.Location, World, TraceParams, TraceChannel);

		FVector StoppedAtPoint;
		if (ApplyTraceSegmentsToBulletSpeed(ThisRicochetTraceSegments, StoppedAtPoint))
		{
			// Loop through this ricochet's Hit Results until we find the first hit that happened after StoppedAtPoint, then remove it and all of the ones proceeding it
			for (int32 i = ThisRicochetStartingIndex; i < HitResults.Num(); ++i)
			{
				const FHitResult& Hit = HitResults[i];

				const FVector LocationPointToStoppedPoint = (StoppedAtPoint - Hit.Location);
				const bool bIsAfterStoppedPoint = (FVector::DotProduct(LocationPointToStoppedPoint, ThisRicochetTraceDir) <= 0); // if this Hit's Location is after StoppedAtLocation
				if (bIsAfterStoppedPoint)
				{
					// Remove the hits that happened after StoppedAtPoint
					HitResults.RemoveAt(i, HitResults.Num() - i);

					// Add TraceInfo so we have where the Segment ended
					FHitResult TraceInfo;
					TraceInfo.TraceStart = Hit.TraceStart;
					TraceInfo.TraceEnd = StoppedAtPoint;
					HitResults.Emplace(TraceInfo);

					break;
				}
			}

			RetVal = false;
		}

		for (const FTraceSegment& TraceSegment : ThisRicochetTraceSegments)
		{
			BulletSteps.Emplace(TraceSegment);
		}
	}


	// Take away ricochet speed reduction using RicochetOffOf's physical materials
	if (const UShooterPhysicalMaterial* ShooterPhysMat = Cast<UShooterPhysicalMaterial>(RicochetOffOf.PhysMaterial.Get()))
	{
		CurrentBulletSpeed -= (ShooterPhysMat->BulletRicochetSpeedReduction);

		// If we ran out of Bullet Speed from this ricochet
		if (CurrentBulletSpeed <= 0)
		{
			CurrentBulletSpeed = 0;
			RetVal = false;
		}
	}

	FTracePoint RicochetPoint = FTracePoint(RicoStart, RicochetOffOf.PhysMaterial.Get());
	BulletSteps.Emplace(RicochetPoint);


	// Reset the blocking Hit Results for the next group of blocking hits
	ThisRicochetBlockingHits.Empty();
	ThisRicochetStartingIndex = (HitResults.Num() - 1);
	ThisRicochetTraceDir = UKismetMathLibrary::GetDirectionUnitVector(RicoStart, RicoEnd);

	if (RetVal)
	{
		RetVal = Super::OnRicochet(HitResults, OutRicoHitResults, World, RicoStart, RicoEnd, TraceParams);
	}
	return RetVal;
}
void AGATA_BulletTrace::OnPostTraces(TArray<FHitResult>& HitResults, const UWorld* World, const FCollisionQueryParams& TraceParams)
{
	Super::OnPostTraces(HitResults, World, TraceParams);


	// Apply any Trace Segments left to our CurrentBulletSpeed
	if (ThisRicochetBlockingHits.Num() > 0)
	{
		TArray<FTraceSegment> ThisRicochetTraceSegments;
		UBFL_CollisionQueryHelpers::BuildTraceSegments(ThisRicochetTraceSegments, ThisRicochetBlockingHits, World, TraceParams, TraceChannel);

		FVector StoppedAtPoint;
		if (ApplyTraceSegmentsToBulletSpeed(ThisRicochetTraceSegments, StoppedAtPoint))
		{
			// Loop through this ricochet's Hit Results until we find the first hit that happened after StoppedAtPoint, then remove it and all of the ones proceeding it
			for (int32 i = ThisRicochetStartingIndex; i < HitResults.Num(); ++i)
			{
				const FHitResult& Hit = HitResults[i];

				const FVector LocationPointToStoppedPoint = (StoppedAtPoint - Hit.Location);
				const bool bIsAfterStoppedPoint = (FVector::DotProduct(LocationPointToStoppedPoint, ThisRicochetTraceDir) <= 0); // if this Hit's Location is after StoppedAtLocation
				if (bIsAfterStoppedPoint)
				{
					// Remove the hits that happened after StoppedAtPoint
					HitResults.RemoveAt(i, HitResults.Num() - i);

					// Add TraceInfo so we have where the Segment ended
					FHitResult TraceInfo;
					TraceInfo.TraceStart = Hit.TraceStart;
					TraceInfo.TraceEnd = StoppedAtPoint;
					HitResults.Emplace(TraceInfo);

					break;
				}
			}
		}

		for (const FTraceSegment& TraceSegment : ThisRicochetTraceSegments)
		{
			BulletSteps.Emplace(TraceSegment);
		}
	}

	ThisRicochetBlockingHits.Empty();
	ThisRicochetStartingIndex = 0;
	ThisRicochetTraceDir = FVector::ZeroVector;

}

bool AGATA_BulletTrace::ApplyTraceSegmentsToBulletSpeed(const TArray<FTraceSegment>& TraceSegments, FVector& OutStoppedAtPoint)
{
	// If we were already out of Bullet Speed
	if (CurrentBulletSpeed <= 0)
	{
		// Try to set a valid OutStoppedAtPoint
		if (TraceSegments.IsValidIndex(0))
		{
			OutStoppedAtPoint = TraceSegments[0].GetEntrancePoint();
		}

		CurrentBulletSpeed = 0;
		return true;
	}


	// For each Segment
	for (const FTraceSegment& Segment : TraceSegments)
	{
		const float& SegmentDistance = Segment.GetSegmentDistance();
		const float& SpeedToTakeAway = Segment.GetBulletSpeedToTakeAway();



		// Take away Bullet Speed from this Segment
		CurrentBulletSpeed -= SpeedToTakeAway;

		// If we ran out of Bullet Speed
		if (CurrentBulletSpeed <= 0)
		{
			// The speed we had before we took away
			const float PreLossBulletSpeed = (CurrentBulletSpeed + SpeedToTakeAway); // if this is somehow negative, that means we already were below zero. But this calculation still works on it - it calculates the point that we should've stopped at when we first went below zero. This would never happen but still its kinda cool how it still works if that happens

			// How far we traveled through this Segment
			const float GotThroughnessRatio = (PreLossBulletSpeed / SpeedToTakeAway);
			const float TraveledThroughDistance = GotThroughnessRatio * SegmentDistance;

			// The point which we ran out of speed
			OutStoppedAtPoint = Segment.GetEntrancePoint() + (TraveledThroughDistance * Segment.GetTraceDir());


			// We ran out of speed and have a valid OutStoppedAtPoint
			CurrentBulletSpeed = 0;
			return true;
		}

	}

	return false;
}

float AGATA_BulletTrace::GetBulletSpeedAtPoint(const FVector& Point)
{
	float retVal = GetInitialBulletSpeed();
	int i = 0;
	for (const FBulletStep& BulletStep : BulletSteps)	// Some reason rn first step is ricochet when you shoot at a ricochetable surface. So there ends up being 2 ricochets when you only shoot 1 ricocheable surface :/
	{
		retVal -= BulletStep.GetBulletSpeedToTakeAway();

		if (const FTraceSegment* TraceSegment = BulletStep.GetTraceSegment())	// if we're a TraceSegment
		{
			if ((TraceSegment->GetExitPoint() - Point).IsNearlyZero()) // if the given Point is this segment's Exit Point
			{
				break;
			}


			const FVector BulletDir = TraceSegment->GetExitPoint() - TraceSegment->GetEntrancePoint();
			const FVector PointDir = Point - TraceSegment->GetEntrancePoint();

			const FVector ProjectedDir = PointDir.ProjectOnTo(BulletDir);
			if ((ProjectedDir - PointDir).IsNearlyZero())	// If projecting the point's dir onto the bullet's dir makes the point dir no different, then Point is already on the bullet trace before projection, meaning the point is on the path of this bullet segment
			{
				UKismetSystemLibrary::PrintString(this, "Found line!!! TraceSegment: " + FString::SanitizeFloat(i), true, false, FLinearColor::Green, 1);
				// Calc the speed before breaking.....

				// We took away the whole Segment's speed even though this point is within the Segment. So add back the part of the Segment that we didn't travel through
				float UntraveledDistanceRatio = (TraceSegment->GetSegmentDistance() / PointDir.Size());
				retVal += BulletStep.GetBulletSpeedToTakeAway() * UntraveledDistanceRatio;

				break;
			}

		}
		else if (const FTracePoint* RicochetPoint = BulletStep.GetRicochetPoint())	// if we're a RicochetPoint
		{
			if ((RicochetPoint->Point - Point).IsNearlyZero())
			{
				break;
			}
		}
		else
		{
			UE_LOG(LogGameplayAbilityTargetActor, Warning, TEXT("%s() A BulletStep had no RicochetPoint or TraceSegment.... Something's wrong"), *FString(__FUNCTION__));
		}


		i++;	// just here for debugging
	}
	
	return retVal;
}
