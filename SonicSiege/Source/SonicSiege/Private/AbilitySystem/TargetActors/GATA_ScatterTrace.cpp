// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/GATA_ScatterTrace.h"

#include "GameplayAbility.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"



void AGATA_ScatterTrace::PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor)
{
	bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(InSourceActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGATA_ScatterTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();// InSourceActor->GetActorLocation();
	FVector TraceEnd;
	AimWithPlayerController(InSourceActor, Params, TraceStart, TraceEnd);		//Effective on server and launching client only

	// ------------------------------------------------------

	for (uint8 t = 0; t < numberOfLines; t++)
	{
		int16 randomSeed = OwningAbility->CurrentActivationInfo.GetActivationPredictionKey().Current;

		float randX = UKismetMathLibrary::RandomFloatInRange(0.f - (scatterRadius * 0.5f), 0.f + (scatterRadius * 0.5f));/*UKismetMathLibrary::RandomFloatInRangeFromStream()*/
		float randY = UKismetMathLibrary::RandomFloatInRange(0.f - (scatterRadius * 0.5f), 0.f + (scatterRadius * 0.5f));
		float randZ = UKismetMathLibrary::RandomFloatInRange(0.f - (scatterRadius * 0.5f), 0.f + (scatterRadius * 0.5f));
		FVector RandomVectorOffset = FVector(randX, randY, randZ);

		LineTraceMultiWithFilter(OutHitResults, InSourceActor->GetWorld(), Filter, TraceStart, TraceEnd + RandomVectorOffset, TraceChannel, Params);

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
