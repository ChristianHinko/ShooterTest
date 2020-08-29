// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/GATA_BulletTrace.h"

#include "Abilities/GameplayAbility.h"
#include "Utilities/CollisionChannels.h"

#include "DrawDebugHelpers.h"



AGATA_BulletTrace::AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ShouldProduceTargetDataOnServer = true;

	MaxRange = 100000.f;
	bTraceAffectsAimPitch = true;
	TraceChannel = COLLISION_BULLET;
	numberOfLines = 1;
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

	for (uint8 t = 0; t < numberOfLines; t++)
	{
		// create net-safe random seed stream
		const int16 predKey = OwningAbility->GetCurrentActivationInfo().GetActivationPredictionKey().Current;
		const int32 randomSeed = predKey - (t * 100000000000000000);	// use the prediction key as a net safe seed and add a crazy t-based large number so that each bullet has its own randomness per fire (the larger the number multiplied to t, the less likely bullets will follow the same pattern per fire)
		const FRandomStream randomStream = FRandomStream(randomSeed);

		// Get direction player is aiming
		FVector AimDir;
		DirWithPlayerController(InSourceActor, Params, TraceStart, AimDir);		//Effective on server and launching client only

		// add random offset to AimDir
		const float coneHalfAngleRadius = FMath::DegreesToRadians(scatterRadius * 0.5f);
		AimDir = randomStream.VRandCone(AimDir, coneHalfAngleRadius);

		// calculate the end of the trace based off aim dir and max range
		const FVector TraceEnd = TraceStart + (AimDir * MaxRange);


		// perform line trace 
		LineTraceMultiWithFilter(OutHitResults, InSourceActor->GetWorld(), MultiFilterHandle, TraceStart, TraceEnd, TraceChannel, Params);


		FHitResult LastHitResult = OutHitResults.Num() ? OutHitResults.Last() : FHitResult();
		//Default to end of trace line if we don't hit anything.
		if (!LastHitResult.bBlockingHit)
		{
			LastHitResult.Location = TraceEnd;
		}
		//if (AGameplayAbilityWorldReticle* LocalReticleActor = ReticleActor.Get())
		//{
		//	const bool bHitActor = (ReturnHitResult.bBlockingHit && (ReturnHitResult.Actor != NULL));
		//	const FVector ReticleLocation = (bHitActor && LocalReticleActor->bSnapToTargetedActor) ? ReturnHitResult.Actor->GetActorLocation() : ReturnHitResult.Location;

		//	LocalReticleActor->SetActorLocation(ReticleLocation);
		//	LocalReticleActor->SetIsTargetAnActor(bHitActor);
		//}

#if ENABLE_DRAW_DEBUG
		if (bDebug)
		{
			float debugLifeTime = 5.f;

			uint8 hitsNum = OutHitResults.Num();
			if (hitsNum > 0)
			{
				for (uint8 i = 0; i < hitsNum; i++)
				{
					float colorAccumulate = i * (hitsNum > 1 ? (255 / (hitsNum - 1)) : 0);

					FVector FromLocation = i > 0 ? OutHitResults[i - 1].Location : TraceStart;
					FVector ToLocation = OutHitResults[i].Location;

					DrawDebugLine(GetWorld(), FromLocation, ToLocation, FColor(0.f, 0.f + colorAccumulate, 255.f), false, debugLifeTime);
					DrawDebugPoint(GetWorld(), ToLocation, 10, FColor(0.f + (colorAccumulate * 0.5f), 255.f - colorAccumulate, 0.f), false, debugLifeTime);
				}
				if (!OutHitResults.Last().bBlockingHit)
				{
					DrawDebugLine(GetWorld(), OutHitResults.Last().Location, TraceEnd, FColor(0.f, 0.f + 255.f, 255.f), false, debugLifeTime);
				}
			}
			else
			{
				DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor(0.f, 0.f, 255.f), false, debugLifeTime);
			}
		}
#endif // ENABLE_DRAW_DEBUG
	}
}
