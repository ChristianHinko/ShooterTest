// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h"

#include "Abilities/GameplayAbility.h"
#include "Utilities/CollisionChannels.h"



AGATA_BulletTrace::AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ShouldProduceTargetDataOnServer = true;

	MaxRange = 100000.f;
	bTraceAffectsAimPitch = true;
	TraceChannel = COLLISION_BULLET;
	numberOfBullets = 1;
	bulletSpread = 0.f;
}


void AGATA_BulletTrace::PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor)
{
	const bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(InSourceActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGATA_BulletTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	const FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();

	// ------------------------------------------------------

	for (uint8 t = 0; t < numberOfBullets; t++)
	{
		// Get direction player is aiming
		FVector AimDir;
		DirWithPlayerController(InSourceActor, Params, TraceStart, AimDir);		//Effective on server and launching client only

		// Calculate new AimDir with random bullet spread offset if needed
		if (bulletSpread > SMALL_NUMBER)
		{
			// Our injected random seed is only unique to each fire. We need a random seed that is also unique to each bullet in the fire, so we will do this by using t
			const int32 fireAndBulletNetSafeRandomSeed = fireNetSafeRandomSeed - ((t + 2) * fireNetSafeRandomSeed);	// Here, the 'number' multiplied to t makes the random pattern noticable after firing 'number' of times. I use the prediction key as that 'number' which i think eliminates the threshold for noticeability entirely. - its confusing to think about but i think it works
			const FRandomStream randomStream = FRandomStream(fireAndBulletNetSafeRandomSeed);

			// Add random offset to AimDir using randomStream
			const float coneHalfAngleRadius = FMath::DegreesToRadians(bulletSpread * 0.5f);
			AimDir = randomStream.VRandCone(AimDir, coneHalfAngleRadius);
		}

		// Calculate the end of the trace based off aim dir and max range
		const FVector TraceEnd = TraceStart + (AimDir * MaxRange);

		// Perform line trace 
		TArray<FHitResult> ThisBulletsHitResults;
		LineTraceMultiWithFilter(ThisBulletsHitResults, InSourceActor->GetWorld(), MultiFilterHandle, TraceStart, TraceEnd, TraceChannel, Params, bAllowMultipleHitsPerActor, bDebug);
		
		// Add this bullet's hit results to the final hit results
		OutHitResults.Append(ThisBulletsHitResults);
	}
}
