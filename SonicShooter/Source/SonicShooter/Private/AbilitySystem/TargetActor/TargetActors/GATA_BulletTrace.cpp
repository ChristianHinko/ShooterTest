// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h"

#include "Abilities/GameplayAbility.h"
#include "Utilities/CollisionChannels.h"
#include "AbilitySystem/SSGameplayAbilityTargetTypes.h"


AGATA_BulletTrace::AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TraceChannel = COLLISION_BULLET;
	NumberOfBullets = 1;
	BulletSpread = 0.f;
}

void AGATA_BulletTrace::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle TargetDataHandle;


		for (currentBulletNumber = 0; currentBulletNumber < NumberOfBullets; ++currentBulletNumber)
		{
			TArray<FHitResult> ThisBulletHitResults;
			PerformTrace(ThisBulletHitResults, SourceActor);


			// Manually filter the hit results (copied code from AGATA_Trace::FilterHitResults()) because we need access to filtered out hit results.
			// And build our target data for non-filtered hit results
			{
				float thisHitTotalDistance = 0.f; // for calculating ReturnData->totalDistanceTraveled (the distance of the non-filterd hit including distances of the previous filtered out traces)

				for (int32 i = 0; i < ThisBulletHitResults.Num(); ++i)
				{
					const FHitResult Hit = ThisBulletHitResults[i];
					thisHitTotalDistance += Hit.Distance;


					if (MultiFilterHandle.MultiFilter.IsValid()) // if valid filter
					{
						const bool bPassesFilter = MultiFilterHandle.FilterPassesForActor(Hit.Actor);
						if (!bPassesFilter)
						{
							ThisBulletHitResults.RemoveAt(i);
							--i;
							continue;
						}
					}

					if (!bAllowMultipleHitsPerActor) // if we should remove multiple hits
					{
						// Loop through each hit result and check if the hits infront of it (the hit results less than the pending index) already have its actor.
						// If so, remove the pending hit result because it has the actor that was already hit and is considered a duplicate hit.

						bool removed = false; // if true, we removed a duplicate hit

						// Check if the hit results that we've looped through so far contains a hit result with this actor already
						for (int32 comparisonIndex = 0; comparisonIndex < i; ++comparisonIndex)
						{
							if (Hit.Actor == ThisBulletHitResults[comparisonIndex].Actor)
							{
								ThisBulletHitResults.RemoveAt(i);
								--i;
								removed = true;
								break;
							}
						}

						if (removed)
						{
							continue;
						}
					}

					
					// If we got here, we are an unfiltered hit (ie. we hit a player), make target data for us:



					/** Note: These are cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr) */
					FGameplayAbilityTargetData_BulletTraceTargetHit* ReturnData = new FGameplayAbilityTargetData_BulletTraceTargetHit();

					ReturnData->HitResult = Hit;
					ReturnData->totalDistanceTraveled = thisHitTotalDistance;
					thisHitTotalDistance = 0.f; // reset back to zero for the next bullet

					TargetDataHandle.Add(ReturnData);
				}
			}




		} // end bullet number loop
		


		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}

void AGATA_BulletTrace::PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor)
{
	OutHitResults.Empty();


	const bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(InSourceActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGATA_BulletTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	const FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();

	// ------------------------------------------------------


	// Get direction player is aiming
	FVector AimDir;
	DirWithPlayerController(InSourceActor, Params, TraceStart, AimDir);		//Effective on server and launching client only

	// Calculate new AimDir with random bullet spread offset if needed
	if (BulletSpread > SMALL_NUMBER)
	{
		// Our injected random seed is only unique to each fire. We need a random seed that is also unique to each bullet in the fire, so we will do this by using t
		const int32 fireAndBulletSpecificNetSafeRandomSeed = FireSpecificNetSafeRandomSeed - ((currentBulletNumber + 2) * FireSpecificNetSafeRandomSeed);	// Here, the 'number' multiplied to t makes the random pattern noticable after firing 'number' of times. I use the prediction key as that 'number' which i think eliminates the threshold for noticeability entirely. - its confusing to think about but i think it works
		FMath::RandInit(fireAndBulletSpecificNetSafeRandomSeed);
		const FRandomStream RandomStream = FRandomStream(FMath::Rand());

		// Add random offset to AimDir using randomStream
		const float coneHalfAngleRadius = FMath::DegreesToRadians(BulletSpread * 0.5f);
		AimDir = RandomStream.VRandCone(AimDir, coneHalfAngleRadius);
	}

	// Calculate the end of the trace based off aim dir and max range
	const FVector TraceEnd = TraceStart + (AimDir * MaxRange);

	// Perform line trace 
	LineTraceMulti(OutHitResults, InSourceActor->GetWorld(), TraceStart, TraceEnd, Params, bDebug);
}
