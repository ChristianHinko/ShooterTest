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
	if (GunAttributeSet)
	{
		return GunAttributeSet->GetRicochets();
	}

	UE_LOG(LogGameplayAbilityTargetActor, Error, TEXT("%s() GunAttributeSet null when trying to read its Ricochets attribute! Will return default value from Super instead!"), *FString(__FUNCTION__));
	return Super::GetRicochets();
}
int32 AGATA_BulletTrace::GetPenetrations() const
{
	return 10;
}
float AGATA_BulletTrace::GetInitialTraceSpeed() const
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

				ThisBulletTargetData->ActorHitInfos.Emplace(Hit.GetActor(), ricochetAwareDistance, -1);




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

	// Intialize CurrentTraceSpeed
	CurrentTraceSpeed = GetInitialTraceSpeed();

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

	// We are ricocheting so Build Penetration Info about this previous ricochet's blocking hits
	if (ThisRicochetBlockingHits.Num() > 0)
	{
		// We are about to ricochet so calculate Penetrations for these blocking Hits before we move on to the next ricochet
		TArray<FPenetrationInfo> ThisRicochetPenetrations;
		UBFL_CollisionQueryHelpers::BuildPenetrationInfos(ThisRicochetPenetrations, ThisRicochetBlockingHits, RicochetOffOf.Location, World, TraceParams, TraceChannel);

		FVector StoppedAtPoint;
		if (ApplyPenetrationInfosToTraceSpeed(ThisRicochetPenetrations, StoppedAtPoint))
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

					// Add TraceInfo so we have where the penetration ended
					FHitResult TraceInfo;
					TraceInfo.TraceStart = Hit.TraceStart;
					TraceInfo.TraceEnd = StoppedAtPoint;
					HitResults.Emplace(TraceInfo);

					break;
				}
			}

			RetVal = false;
		}
	}


	// Take away ricochet speed reduction using RicochetOffOf's physical materials
	if (const UShooterPhysicalMaterial* ShooterPhysMat = Cast<UShooterPhysicalMaterial>(RicochetOffOf.PhysMaterial.Get()))
	{
		CurrentTraceSpeed -= (ShooterPhysMat->BulletRicochetSpeedReduction);

		// If we ran out of Trace Speed from this ricochet
		if (CurrentTraceSpeed <= 0)
		{
			CurrentTraceSpeed = 0;
			RetVal = false;
		}
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


	// Apply any penetrations left to our CurrentTraceSpeed
	if (ThisRicochetBlockingHits.Num() > 0)
	{
		TArray<FPenetrationInfo> ThisRicochetPenetrations;
		UBFL_CollisionQueryHelpers::BuildPenetrationInfos(ThisRicochetPenetrations, ThisRicochetBlockingHits, World, TraceParams, TraceChannel);

		FVector StoppedAtPoint;
		if (ApplyPenetrationInfosToTraceSpeed(ThisRicochetPenetrations, StoppedAtPoint))
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

					// Add TraceInfo so we have where the penetration ended
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

bool AGATA_BulletTrace::ApplyPenetrationInfosToTraceSpeed(const TArray<FPenetrationInfo>& PenetrationInfos, FVector& OutStoppedAtPoint)
{
	// If we were already out of Trace Speed
	if (CurrentTraceSpeed <= 0)
	{
		// Try to set a valid OutStoppedAtPoint
		if (PenetrationInfos.IsValidIndex(0))
		{
			OutStoppedAtPoint = PenetrationInfos[0].GetEntrancePoint();
		}

		CurrentTraceSpeed = 0;
		return true;
	}


	// For each penetration
	for (const FPenetrationInfo& Penetration : PenetrationInfos)
	{
		const float& PenetrationDistance = Penetration.GetPenetrationDistance();

		// For each Phys Mat in this Penetration
		const TArray<UPhysicalMaterial*>& PhysMats = Penetration.PenetratedPhysMaterials;
		for (const UPhysicalMaterial* PhysMat : PhysMats)
		{
			// If this is a ShooterPhysicalMaterial, it has Trace Speed loss data
			if (const UShooterPhysicalMaterial* ShooterPhysMat = Cast<UShooterPhysicalMaterial>(PhysMat))
			{
				// Take away Trace Speed from this Phys Mat
				const float SpeedLossPerCentimeter = (ShooterPhysMat->BulletPenetrationSpeedReduction / 100);
				const float SpeedToTakeAway = (PenetrationDistance * SpeedLossPerCentimeter);
				CurrentTraceSpeed -= SpeedToTakeAway;
				
				// If we ran out of Trace Speed
				if (CurrentTraceSpeed <= 0)
				{
					// The speed we had before we took away
					const float PreLossTraceSpeed = (CurrentTraceSpeed + SpeedToTakeAway); // if this is somehow negative, that means we already were below zero. But this calculation still works on it - it calculates the point that we should've stopped at when we first went below zero. This would never happen but still its kinda cool how it still works if that happens
					
					// How far we traveled through this Penetration
					const float GotThroughnessRatio = (PreLossTraceSpeed / SpeedToTakeAway);
					const float TraveledThroughDistance = GotThroughnessRatio * PenetrationDistance;

					// The point which we ran out of speed
					OutStoppedAtPoint = Penetration.GetEntrancePoint() + (TraveledThroughDistance * Penetration.GetPenetrationDir());


					// We ran out of speed and have a valid OutStoppedAtPoint
					CurrentTraceSpeed = 0;
					return true;
				}
			}
		}

	}

	return false;
}
