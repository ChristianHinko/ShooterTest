// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/GATA_MultiLineTrace.h"

#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"

//#include "DrawDebugHelpers.h"



AGATA_MultiLineTrace::AGATA_MultiLineTrace()
{
	maxTraces = 1;
}


void AGATA_MultiLineTrace::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (!SourceActor)
	{
		return;
	}

	FGameplayAbilityTargetDataHandle Handle = StartLocation.MakeTargetDataHandleFromHitResults(OwningAbility, PerformMultiTraces/*<ActorClassToCollect>*/(SourceActor));
	TargetDataReadyDelegate.Broadcast(Handle);
}

TArray<FHitResult> AGATA_MultiLineTrace::PerformMultiTraces(AActor* InSourceActor)
{
	bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(InSourceActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGameplayAbilityTargetActor_SingleLineTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();// InSourceActor->GetActorLocation();
	FVector TraceEnd;
	AimWithPlayerController(InSourceActor, Params, TraceStart, TraceEnd);		//Effective on server and launching client only

	// ------------------------------------------------------

	TArray<FHitResult> ReturnHitResults;
	AActor* LastHitActor;
	for (uint8 i = 0; i < maxTraces; i++)
	{
		FHitResult TraceHitResult;
		LineTraceWithFilter(TraceHitResult, InSourceActor->GetWorld(), Filter, TraceStart, TraceEnd, TraceProfile.Name, Params);

		// store the hit actor so we can ignore it next iteration
		if (TraceHitResult.Actor.IsValid())
		{
			Params.ClearIgnoredActors();
			Params.AddIgnoredActor(InSourceActor);
			AActor* HitActor = TraceHitResult.Actor.Get();
			Params.AddIgnoredActor(HitActor);
			LastHitActor = HitActor;
		}
		else
		{
#if ENABLE_DRAW_DEBUG
			if (bDebug)
			{
				float debugLifeTime = 5.f;
				float colorAccumulate = i * (maxTraces > 1 ? (255 / (maxTraces - 1)) : 0);

				DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor(0.f, 0.f + colorAccumulate, 255.f), false, debugLifeTime);
				DrawDebugPoint(GetWorld(), TraceEnd, 10, FColor(0.f, 0.f, 255.f), false, debugLifeTime);
			}
#endif // ENABLE_DRAW_DEBUG
			break;
		}

		if (TraceHitResult.bBlockingHit)
		{
			if (TraceHitResult.Actor->IsA(ActorClassToCollect))
			{
				ReturnHitResults.Add(TraceHitResult);
			}
			else
			{
#if ENABLE_DRAW_DEBUG
				if (bDebug)
				{
					float debugLifeTime = 5.f;
					float colorAccumulate = i * (maxTraces > 1 ? (255 / (maxTraces - 1)) : 0);

					DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor(0.f, 0.f + colorAccumulate, 255.f), false, debugLifeTime);
					DrawDebugPoint(GetWorld(), TraceEnd, 10, FColor(0.f, 0.f, 255.f), false, debugLifeTime);
				}
#endif // ENABLE_DRAW_DEBUG
				break;
			}
		}

#if ENABLE_DRAW_DEBUG
		if (bDebug)
		{
			float debugLifeTime = 5.f;
			float colorAccumulate = i * (maxTraces > 1 ? (255 / (maxTraces - 1)) : 0);

			DrawDebugLine(GetWorld(), TraceStart, TraceHitResult.Location, FColor(0.f, 0.f + colorAccumulate, 255.f), false, debugLifeTime);
			DrawDebugPoint(GetWorld(), TraceHitResult.Location, 10, FColor(0.f + colorAccumulate, 255.f - colorAccumulate, 0.f), false, debugLifeTime);
		}
#endif // ENABLE_DRAW_DEBUG


		TraceStart = TraceHitResult.ImpactPoint;
	}




	//if (AGameplayAbilityWorldReticle* LocalReticleActor = ReticleActor.Get())
	//{
	//	//const bool bHitActor = (ReturnHitResult.bBlockingHit && (ReturnHitResult.Actor != NULL));
	//	const bool bHitActor = (ReturnHitResults.Num() > 0);
	//	const FVector ReticleLocation = (bHitActor && LocalReticleActor->bSnapToTargetedActor) ? ReturnHitResult.Actor->GetActorLocation() : ReturnHitResult.Location;

	//	LocalReticleActor->SetActorLocation(ReticleLocation);
	//	LocalReticleActor->SetIsTargetAnActor(bHitActor);
	//}

	return ReturnHitResults;
}
