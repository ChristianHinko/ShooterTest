// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/GATA_MultiLineTrace.h"

#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"

#include "DrawDebugHelpers.h"



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


	TArray<FHitResult> HitResults;

	for (uint8 i = 0; i < maxTraces; i++)
	{
		FHitResult TraceHitResult;
		TraceHitResult = PerformTrace(SourceActor);
#if ENABLE_DRAW_DEBUG
		if (bDebug)
		{
			float debugLifeTime = 5.f;

			DrawDebugLine(GetWorld(), StartLocation.GetTargetingTransform().GetLocation(), TraceHitResult.Location, FColor(0.f, 255.f, 0.f + (i * 150)), false, debugLifeTime);
			DrawDebugPoint(GetWorld(), TraceHitResult.Location, 10, FColor(0.f + (i * 90), 255.f - (i * 90), 0.f), false, debugLifeTime);
		}
#endif // ENABLE_DRAW_DEBUG

		// store the hit actor so we can ignore it next iteration
		if (TraceHitResult.Actor.IsValid())
		{
			LastHitActor = TraceHitResult.Actor.Get();
		}
		else
		{
			break;
		}

		if (TraceHitResult.bBlockingHit)
		{
			if (Cast<AActor/*ACharacter*/>(TraceHitResult.Actor))
			{
				HitResults.Add(TraceHitResult);
			}
			else
			{
				break;
			}
		}
		else
		{
			continue;
		}


		StartLocation.LiteralTransform = FTransform(TraceHitResult.ImpactPoint);
	}


	FGameplayAbilityTargetDataHandle Handle = StartLocation.MakeTargetDataHandleFromHitResults(OwningAbility, HitResults);
	TargetDataReadyDelegate.Broadcast(Handle);
}

FHitResult AGATA_MultiLineTrace::PerformTrace(AActor* InSourceActor)
{
	bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(InSourceActor);
	ActorsToIgnore.Add(LastHitActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGameplayAbilityTargetActor_SingleLineTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();// InSourceActor->GetActorLocation();
	FVector TraceEnd;
	AimWithPlayerController(InSourceActor, Params, TraceStart, TraceEnd);		//Effective on server and launching client only

	// ------------------------------------------------------

	FHitResult ReturnHitResult;
	LineTraceWithFilter(ReturnHitResult, InSourceActor->GetWorld(), Filter, TraceStart, TraceEnd, TraceProfile.Name, Params);
	//Default to end of trace line if we don't hit anything.
	if (!ReturnHitResult.bBlockingHit)
	{
		ReturnHitResult.Location = TraceEnd;
	}
	if (AGameplayAbilityWorldReticle* LocalReticleActor = ReticleActor.Get())
	{
		const bool bHitActor = (ReturnHitResult.bBlockingHit && (ReturnHitResult.Actor != NULL));
		const FVector ReticleLocation = (bHitActor && LocalReticleActor->bSnapToTargetedActor) ? ReturnHitResult.Actor->GetActorLocation() : ReturnHitResult.Location;

		LocalReticleActor->SetActorLocation(ReticleLocation);
		LocalReticleActor->SetIsTargetAnActor(bHitActor);
	}

	return ReturnHitResult;
}
