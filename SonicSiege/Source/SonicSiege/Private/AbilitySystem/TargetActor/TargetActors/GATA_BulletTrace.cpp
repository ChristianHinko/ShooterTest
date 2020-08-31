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
}


void AGATA_BulletTrace::PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor)
{
	const bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(InSourceActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGATA_BulletTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	const FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();// InSourceActor->GetActorLocation();

	// ------------------------------------------------------

	for (uint8 t = 0; t < numberOfBullets; t++)
	{
		// create net-safe random seed stream
		const int16 predKey = OwningAbility->GetCurrentActivationInfo().GetActivationPredictionKey().Current;
		const int32 randomSeed = predKey - (t * 100000000000000000);	// use the prediction key as a net safe seed and add a crazy t-based large number so that each bullet has its own randomness per fire (the larger the number multiplied to t, the less likely bullets will follow the same pattern per fire)
		const FRandomStream randomStream = FRandomStream(randomSeed);

		// Get direction player is aiming
		FVector AimDir;
		DirWithPlayerController(InSourceActor, Params, TraceStart, AimDir);		//Effective on server and launching client only

		// add random offset to AimDir
		const float coneHalfAngleRadius = FMath::DegreesToRadians(bulletSpread * 0.5f);
		AimDir = randomStream.VRandCone(AimDir, coneHalfAngleRadius);

		// calculate the end of the trace based off aim dir and max range
		const FVector TraceEnd = TraceStart + (AimDir * MaxRange);


		// perform line trace 
		LineTraceMultiWithFilter(OutHitResults, InSourceActor->GetWorld(), MultiFilterHandle, TraceStart, TraceEnd, TraceChannel, Params, bDebug);
	}
}
