// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h"

#include "Utilities\LogCategories.h"
#include "Abilities/GameplayAbility.h"
#include "Utilities/CollisionChannels.h"
#include "AbilitySystem/SSGameplayAbilityTargetTypes.h"
#include "AbilitySystemComponent.h"
#include "Item/Weapons/AS_Gun.h"
#include "Utilities\BlueprintFunctionLibraries\BFL_CollisionQueryHelpers.h"
#include "PhysicalMaterial/ShooterPhysicalMaterial.h"
#include "Utilities/BlueprintFunctionLibraries/BFL_HitResultHelpers.h"

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

	UE_LOG(LogGameplayAbilityTargetActor, Fatal, TEXT("%s() GunAttributeSet null when trying to read its MaxRange attribute! Will return value from Default Object of UAS_Gun instead!"), *FString(__FUNCTION__));
	return GetDefault<UAS_Gun>()->GetMaxRange();
}
int32 AGATA_BulletTrace::GetNumberOfTraces() const
{
	if (GunAttributeSet)
	{
		return GunAttributeSet->GetNumberOfBulletsPerFire();
	}

	UE_LOG(LogGameplayAbilityTargetActor, Fatal, TEXT("%s() GunAttributeSet null when trying to read its NumberOfBulletsPerFire attribute! Will return value from Default Object of UAS_Gun instead!"), *FString(__FUNCTION__));
	return GetDefault<UAS_Gun>()->GetNumberOfBulletsPerFire();
}
int32 AGATA_BulletTrace::GetPenetrations() const
{
	if (GunAttributeSet)
	{
		return GunAttributeSet->GetPenetrations();
	}

	UE_LOG(LogGameplayAbilityTargetActor, Fatal, TEXT("%s() GunAttributeSet null when trying to read its Penetrations attribute! Will return value from Default Object of UAS_Gun instead!"), *FString(__FUNCTION__));
	return GetDefault<UAS_Gun>()->GetPenetrations();
}
int32 AGATA_BulletTrace::GetRicochets() const
{	
	if (GunAttributeSet)
	{
		return GunAttributeSet->GetRicochets();
	}

	UE_LOG(LogGameplayAbilityTargetActor, Fatal, TEXT("%s() GunAttributeSet null when trying to read its Ricochets attribute! Will return value from Default Object of UAS_Gun instead!"), *FString(__FUNCTION__));
	return GetDefault<UAS_Gun>()->GetRicochets();
}
float AGATA_BulletTrace::GetInitialBulletSpeed() const
{
	if (GunAttributeSet)
	{
		return GunAttributeSet->GetInitialBulletSpeed();
	}

	UE_LOG(LogGameplayAbilityTargetActor, Fatal, TEXT("%s() GunAttributeSet null when trying to read its InitialBulletSpeed attribute! Will return value from Default Object of UAS_Gun instead!"), *FString(__FUNCTION__));
	return GetDefault<UAS_Gun>()->GetInitialBulletSpeed();
}
float AGATA_BulletTrace::GetBulletSpeedFalloff() const
{
	if (GunAttributeSet)
	{
		return GunAttributeSet->GetBulletSpeedFalloff();
	}

	UE_LOG(LogGameplayAbilityTargetActor, Fatal, TEXT("%s() GunAttributeSet null when trying to read its BulletSpeedFalloff attribute! Will return value from Default Object of UAS_Gun instead!"), *FString(__FUNCTION__));
	return GetDefault<UAS_Gun>()->GetBulletSpeedFalloff();
}

void AGATA_BulletTrace::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());


	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle TargetDataHandle;


		const int32 numberOfBullets = GetNumberOfTraces();
		BulletSteps.Empty();
		BulletSteps.Reserve(numberOfBullets);
		BulletSteps.AddDefaulted(numberOfBullets);

		TArray<TArray<FHitResult>> TraceResults;
		PerformTraces(TraceResults, SourceActor);

		for (int32 bulletNumber = 0; bulletNumber < TraceResults.Num(); bulletNumber++)
		{
			TArray<FHitResult>& ThisBulletHitResults = TraceResults[bulletNumber];

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
					const bool bIsNewTrace = !UBFL_HitResultHelpers::AreHitsFromSameTrace(Hit, PreviousHit);
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
				float bulletSpeedOnHit = GetBulletSpeedAtPoint(Hit.ImpactPoint, bulletNumber);
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

void AGATA_BulletTrace::CalculateAimDirection(FVector& OutAimStart, FVector& OutAimDir) const
{
	Super::CalculateAimDirection(OutAimStart, OutAimDir); // call Super so we get the PC's view dir, and then we can add bullet spread ontop of that


	// Calculate new OutAimDir with random bullet spread offset if needed
	float currentBulletSpread = GunAttributeSet->CurrentBulletSpread;
	if (currentBulletSpread > SMALL_NUMBER)
	{
		// Our injected random seed is only unique to each fire. We need a random seed that is also unique to each bullet in the fire, so we will do this by using t
		const int32 fireAndBulletSpecificNetSafeRandomSeed = FireSpecificNetSafeRandomSeed - ((CurrentTraceIndex + 2) * FireSpecificNetSafeRandomSeed);	// Here, the 'number' multiplied to t makes the random pattern noticable after firing 'number' of times. I use the prediction key as that 'number' which i think eliminates the threshold for noticeability entirely. - its confusing to think about but i think it works
		FMath::RandInit(fireAndBulletSpecificNetSafeRandomSeed);
		const FRandomStream RandomStream = FRandomStream(FMath::Rand());

		// Get and apply random offset to OutAimDir using randomStream
		const float coneHalfAngleRadius = FMath::DegreesToRadians(currentBulletSpread * 0.5f);
		OutAimDir = RandomStream.VRandCone(OutAimDir, coneHalfAngleRadius);
	}
}
bool AGATA_BulletTrace::ShouldRicochetOffOf(const FHitResult& Hit) const
{
	if (const UShooterPhysicalMaterial* ShooterPhysMat = Cast<const UShooterPhysicalMaterial>(Hit.PhysMaterial.Get()))
	{
		if (ShooterPhysMat->bRichochetsBullets)
		{
			return true;
		}
	}

	return false;
}



void AGATA_BulletTrace::PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor)
{
	OutHitResults.Empty();


	FCollisionQueryParams Params = FCollisionQueryParams(SCENE_QUERY_STAT(AGATA_BulletTrace));
	Params.AddIgnoredActor(InSourceActor);
	Params.bTraceComplex = true;
	Params.bReturnPhysicalMaterial = true;

	FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();
	FVector TraceEnd;
	AimWithPlayerController(InSourceActor, Params, TraceStart, TraceEnd);		//Effective on server and launching client only

	// ------------------------------------------------------


	// Perform line trace
	LineTraceMulti(OutHitResults, InSourceActor->GetWorld(), TraceStart, TraceEnd, Params, bDebug);

}








/////////////////////////////////////////////////////////////// BEGIN trace events /////////////////////



bool AGATA_BulletTrace::OnInitialTrace(TArray<FHitResult>& OutInitialHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams& TraceParams)
{
	bool RetVal = Super::OnInitialTrace(OutInitialHitResults, World, Start, End, TraceParams);


	// Initialize ThisRicochetBlockingHits
	ThisRicochetBlockingHits.Empty();
	ThisRicochetStartingIndex = 0;
	ThisRicochetTraceDir = UKismetMathLibrary::GetDirectionUnitVector(Start, End);

	// Intialize CurrentBulletSpeed
	CurrentBulletSpeed = GetInitialBulletSpeed();

	// Initialize this bullet's BulletSteps
	BulletSteps[CurrentTraceIndex].Empty();


	// Nerf CurrentBulletSpeed by distance traveled
	{
		float distanceTraveled = 0.f;
		for (const FHitResult& Hit : OutInitialHitResults)
		{
			distanceTraveled += Hit.Distance;
		}

		const float nerfMultiplier = GetBulletSpeedFalloffNerf(GetBulletSpeedFalloff(), distanceTraveled);
		CurrentBulletSpeed *= nerfMultiplier;
	}

	return RetVal;
}
bool AGATA_BulletTrace::OnPenetrate(TArray<FHitResult>& HitResults, TArray<FHitResult>& OutPenetrateHitResults, const UWorld* World, const FVector& PenetrateStart, const FVector& PenetrateEnd, const FCollisionQueryParams& TraceParams)
{
	bool RetVal = Super::OnPenetrate(HitResults, OutPenetrateHitResults, World, PenetrateStart, PenetrateEnd, TraceParams);

	const FHitResult& PenetratedThrough = HitResults.Last();

	// Add what we penetrated through as a blocking hit for ThisRicochetBlockingHits
	ThisRicochetBlockingHits.Emplace(PenetratedThrough);


	// Nerf CurrentBulletSpeed by distance traveled
	{
		float distanceTraveled = 0.f;
		for (const FHitResult& Hit : OutPenetrateHitResults)
		{
			distanceTraveled += Hit.Distance;
		}

		const float nerfMultiplier = GetBulletSpeedFalloffNerf(GetBulletSpeedFalloff(), distanceTraveled);
		CurrentBulletSpeed *= nerfMultiplier;
	}

	return RetVal;
}
bool AGATA_BulletTrace::OnRicochet(TArray<FHitResult>& HitResults, TArray<FHitResult>& OutRicoHitResults, const UWorld* World, const FVector& RicoStart, const FVector& RicoEnd, const FCollisionQueryParams& TraceParams)
{
	bool RetVal = true;

	const FHitResult& RicochetOffOf = HitResults.Last();


	ThisRicochetBlockingHits.Emplace(RicochetOffOf);


	TArray<FBulletStep> ThisRicochetBulletSteps;

	// Fill out ThisRicochetBulletSteps
	{
		// We are ricocheting so BuildTraceSegments about this previous ricochet's blocking hits
		if (ThisRicochetBlockingHits.Num() > 0)
		{
			// We are about to ricochet so calculate Trace Segments for these blocking Hits before we move on to the next ricochet
			TArray<FTraceSegment> ThisRicochetTraceSegments;
			UBFL_CollisionQueryHelpers::BuildTraceSegments(ThisRicochetTraceSegments, ThisRicochetBlockingHits, RicochetOffOf.Location, World, TraceParams, TraceChannel);
			for (const FTraceSegment& TraceSegment : ThisRicochetTraceSegments)
			{
				ThisRicochetBulletSteps.Emplace(TraceSegment);
			}


		}

		FTracePoint RicochetPoint = FTracePoint(RicoStart, RicochetOffOf.PhysMaterial.Get());
		ThisRicochetBulletSteps.Emplace(RicochetPoint);
	}

	BulletSteps[CurrentTraceIndex].Append(ThisRicochetBulletSteps);


	FVector StoppedAtPoint;
	bool bStoppedInSegment = false;
	if (ApplyBulletStepsToBulletSpeed(ThisRicochetBulletSteps, StoppedAtPoint, bStoppedInSegment))
	{
		if (bStoppedInSegment) // only if we stopped inside of a segment
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

		RetVal = false;
	}


	// Nerf CurrentBulletSpeed by distance traveled
	{
		float distanceTraveled = 0.f;
		for (const FHitResult& Hit : OutRicoHitResults)
		{
			distanceTraveled += Hit.Distance;
		}

		const float nerfMultiplier = GetBulletSpeedFalloffNerf(GetBulletSpeedFalloff(), distanceTraveled);
		CurrentBulletSpeed *= nerfMultiplier;
	}


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



	TArray<FBulletStep> ThisRicochetBulletSteps;

	// Fill out ThisRicochetBulletSteps
	{
		// Apply any Trace Segments left to our CurrentBulletSpeed
		if (ThisRicochetBlockingHits.Num() > 0)
		{
			TArray<FTraceSegment> ThisRicochetTraceSegments;
			UBFL_CollisionQueryHelpers::BuildTraceSegments(ThisRicochetTraceSegments, ThisRicochetBlockingHits, World, TraceParams, TraceChannel);
			for (const FTraceSegment& TraceSegment : ThisRicochetTraceSegments)
			{
				ThisRicochetBulletSteps.Emplace(TraceSegment);
			}

		}

	}

	BulletSteps[CurrentTraceIndex].Append(ThisRicochetBulletSteps);


	FVector StoppedAtPoint;
	bool bStoppedInSegment = false;
	if (ApplyBulletStepsToBulletSpeed(ThisRicochetBulletSteps, StoppedAtPoint, bStoppedInSegment))
	{
		if (bStoppedInSegment) // only if we stopped inside of a segment
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
	}




	ThisRicochetBlockingHits.Empty();
	ThisRicochetStartingIndex = 0;
	ThisRicochetTraceDir = FVector::ZeroVector;

}




/////////////////////////////////////////////////////////////// END trace events /////////////////////







bool AGATA_BulletTrace::ApplyBulletStepsToBulletSpeed(const TArray<FBulletStep>& BulletStepsToApply, FVector& OutStoppedAtPoint, bool& OutStoppedInSegment)
{
	// If we were already out of Bullet Speed
	if (CurrentBulletSpeed <= 0)
	{
		// Try to set a valid OutStoppedAtPoint
		if (BulletStepsToApply.IsValidIndex(0))
		{
			const FBulletStep& FirstStep = BulletStepsToApply[0];

			if (const FTraceSegment* TraceSegment = FirstStep.GetTraceSegment())
			{
				OutStoppedAtPoint = TraceSegment->GetStartPoint();
				OutStoppedInSegment = true;
			}
			else if (const FTracePoint* TracePoint = FirstStep.GetRicochetPoint())
			{
				OutStoppedAtPoint = TracePoint->Point;
			}
		}

		CurrentBulletSpeed = 0;
		return true;
	}




	for (const FBulletStep& BulletStep : BulletStepsToApply)
	{
		const float SpeedToTakeAway = BulletStep.GetBulletSpeedToTakeAway();



		// Take away Bullet Speed from this BulletStep
		CurrentBulletSpeed -= BulletStep.GetBulletSpeedToTakeAway();

		// If we ran out of Bullet Speed
		if (CurrentBulletSpeed <= 0)
		{
			if (const FTraceSegment* TraceSegment = BulletStep.GetTraceSegment())
			{
				// The speed we had before we took away
				const float PreLossBulletSpeed = (CurrentBulletSpeed + SpeedToTakeAway); // if this is somehow negative, that means we already were below zero. But this calculation still works on it - it calculates the point that we should've stopped at when we first went below zero. This would never happen but still its kinda cool how it still works if that happens

				// How far we traveled through this Segment
				const float GotThroughnessRatio = (PreLossBulletSpeed / SpeedToTakeAway);
				const float TraveledThroughDistance = GotThroughnessRatio * TraceSegment->GetSegmentDistance();

				// The point which we ran out of speed
				OutStoppedAtPoint = TraceSegment->GetStartPoint() + (TraveledThroughDistance * TraceSegment->GetTraceDir());
				OutStoppedInSegment = true;
			}
			else if (const FTracePoint* TracePoint = BulletStep.GetRicochetPoint())
			{
				OutStoppedAtPoint = TracePoint->Point;
			}

			// We ran out of speed and have a valid OutStoppedAtPoint
			CurrentBulletSpeed = 0;
			return true;
		}
	}




	return false;
}

float AGATA_BulletTrace::GetBulletSpeedAtPoint(const FVector& Point, int32 bulletNumber)
{
	float retVal = GetInitialBulletSpeed();


	float totalDistanceTraveled = 0.f;

	const TArray<FBulletStep>& Steps = BulletSteps[bulletNumber];	// Get the steps from this specific bullet
	for (const FBulletStep& BulletStep : Steps)
	{
		retVal -= BulletStep.GetBulletSpeedToTakeAway();

		if (const FTraceSegment* TraceSegment = BulletStep.GetTraceSegment())	// if we're a TraceSegment
		{
			const float& SegmentDistance = TraceSegment->GetSegmentDistance();

			totalDistanceTraveled += SegmentDistance;

			if (Point.Equals(TraceSegment->GetEndPoint(), KINDA_SMALL_NUMBER + (KINDA_SMALL_NUMBER * 100))) // if the given Point is this segment's EndPoint
			{
				UKismetSystemLibrary::PrintString(this, "Found line!!!", true, false, FLinearColor::Green, 1);
				break;
			}

			const float TraveledDistance = FVector::Distance(TraceSegment->GetStartPoint(), Point);
			const float UntraveledDistance = FVector::Distance(Point, TraceSegment->GetEndPoint());

			if (FMath::IsNearlyEqual(TraveledDistance + UntraveledDistance, SegmentDistance))	// if the Start, End, and Point don't form a triangle, Point is on the segment
			{
				UKismetSystemLibrary::PrintString(this, "Found line!!!", true, false, FLinearColor::Green, 1);

				// We took away the whole Segment's speed even though this point is within the Segment. So add back the part of the Segment that we didn't travel through
				const float TraveledThroughnessRatio = (TraveledDistance / SegmentDistance);
				retVal += BulletStep.GetBulletSpeedToTakeAway() * (1 - TraveledThroughnessRatio);


				totalDistanceTraveled -= UntraveledDistance;

				break;
			}

		}
		else if (const FTracePoint* RicochetPoint = BulletStep.GetRicochetPoint())	// if we're a RicochetPoint
		{
			if (Point.Equals(RicochetPoint->Point, KINDA_SMALL_NUMBER + (KINDA_SMALL_NUMBER * 100)))
			{
				UKismetSystemLibrary::PrintString(this, "Found point!!!", true, false, FLinearColor::Green, 1);
				break;
			}
		}
		else
		{
			UE_LOG(LogGameplayAbilityTargetActor, Warning, TEXT("%s() A BulletStep had no RicochetPoint or TraceSegment.... Something's wrong"), *FString(__FUNCTION__));
		}
	}
	

	// Nerf retVal by distance traveled
	const float nerfMultiplier = GetBulletSpeedFalloffNerf(GetBulletSpeedFalloff(), totalDistanceTraveled);
	retVal *= nerfMultiplier;


	return retVal;
}

float AGATA_BulletTrace::GetBulletSpeedFalloffNerf(const float& bulletSpeedFalloffValue, const float& totalDistanceBulletTraveled)
{
	// bulletSpeedFalloffValue is the multiplier applied against the bullet's speed every 1000cm (32ft) or 10 blocks of our Proto material
	return FMath::Pow(bulletSpeedFalloffValue, (totalDistanceBulletTraveled / 1000));
}
