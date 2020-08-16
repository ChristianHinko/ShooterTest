// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/GATA_MultiTrace.h"

#include "GameFramework/PlayerController.h"
#include "Abilities/GameplayAbility.h"

#include "DrawDebugHelpers.h"



// --------------------------------------------------------------------------------------------------------------------------------------------------------
//
//	AGATA_MultiTrace
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------

AGATA_MultiTrace::AGATA_MultiTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	MaxRange = 999999.0f;
	bTraceAffectsAimPitch = true;

	TraceChannel = ECollisionChannel::ECC_Visibility;
}

void AGATA_MultiTrace::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ReticleActor.IsValid())
	{
		ReticleActor.Get()->Destroy();
	}

	Super::EndPlay(EndPlayReason);
}

void AGATA_MultiTrace::LineTraceWithFilter(FHitResult& OutHitResult, const UWorld* World, const FGameplayTargetDataFilterHandle FilterHandle, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel, const FCollisionQueryParams Params)
{
	check(World);

	TArray<FHitResult> HitResults;
	World->LineTraceMultiByChannel(HitResults, Start, End, TraceChannel, Params);

	OutHitResult.TraceStart = Start;
	OutHitResult.TraceEnd = End;

	for (int32 HitIdx = 0; HitIdx < HitResults.Num(); ++HitIdx)				// find first hit that passes the filter (if any) then treat is as a blocking hit and output it
	{
		const FHitResult& Hit = HitResults[HitIdx];

		if (!Hit.Actor.IsValid() || FilterHandle.FilterPassesForActor(Hit.Actor))
		{
			OutHitResult = Hit;
			OutHitResult.bBlockingHit = true; // treat it as a blocking hit
			return;
		}
	}
}

void AGATA_MultiTrace::SweepWithFilter(FHitResult& OutHitResult, const UWorld* World, const FGameplayTargetDataFilterHandle FilterHandle, const FVector& Start, const FVector& End, const FQuat& Rotation, const FCollisionShape CollisionShape, ECollisionChannel TraceChannel, const FCollisionQueryParams Params)
{
	check(World);

	TArray<FHitResult> HitResults;
	World->SweepMultiByChannel(HitResults, Start, End, Rotation, TraceChannel, CollisionShape, Params);

	OutHitResult.TraceStart = Start;
	OutHitResult.TraceEnd = End;

	for (int32 HitIdx = 0; HitIdx < HitResults.Num(); ++HitIdx)
	{
		const FHitResult& Hit = HitResults[HitIdx];

		if (!Hit.Actor.IsValid() || FilterHandle.FilterPassesForActor(Hit.Actor))
		{
			OutHitResult = Hit;
			OutHitResult.bBlockingHit = true; // treat it as a blocking hit
			return;
		}
	}
}

void AGATA_MultiTrace::AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceEnd, bool bIgnorePitch) const
{
	if (!OwningAbility) // Server and launching client only
	{
		return;
	}

	APlayerController* PC = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();
	check(PC);

	FVector ViewStart;
	FRotator ViewRot;
	PC->GetPlayerViewPoint(ViewStart, ViewRot);

	const FVector ViewDir = ViewRot.Vector();
	FVector ViewEnd = ViewStart + (ViewDir * MaxRange);

	ClipCameraRayToAbilityRange(ViewStart, ViewDir, TraceStart, MaxRange, ViewEnd);

	FHitResult HitResult;
	LineTraceWithFilter(HitResult, InSourceActor->GetWorld(), Filter, ViewStart, ViewEnd, TraceChannel, Params);

	const bool bUseTraceResult = HitResult.bBlockingHit && (FVector::DistSquared(TraceStart, HitResult.Location) <= (MaxRange * MaxRange));

	const FVector AdjustedEnd = (bUseTraceResult) ? HitResult.Location : ViewEnd;

	FVector AdjustedAimDir = (AdjustedEnd - TraceStart).GetSafeNormal();
	if (AdjustedAimDir.IsZero())
	{
		AdjustedAimDir = ViewDir;
	}

	if (!bTraceAffectsAimPitch && bUseTraceResult)
	{
		FVector OriginalAimDir = (ViewEnd - TraceStart).GetSafeNormal();

		if (!OriginalAimDir.IsZero())
		{
			// Convert to angles and use original pitch
			const FRotator OriginalAimRot = OriginalAimDir.Rotation();

			FRotator AdjustedAimRot = AdjustedAimDir.Rotation();
			AdjustedAimRot.Pitch = OriginalAimRot.Pitch;

			AdjustedAimDir = AdjustedAimRot.Vector();
		}
	}

	OutTraceEnd = TraceStart + (AdjustedAimDir * MaxRange);
}

bool AGATA_MultiTrace::ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition)
{
	FVector CameraToCenter = AbilityCenter - CameraLocation;
	float DotToCenter = FVector::DotProduct(CameraToCenter, CameraDirection);
	if (DotToCenter >= 0)		//If this fails, we're pointed away from the center, but we might be inside the sphere and able to find a good exit point.
	{
		float DistanceSquared = CameraToCenter.SizeSquared() - (DotToCenter * DotToCenter);
		float RadiusSquared = (AbilityRange * AbilityRange);
		if (DistanceSquared <= RadiusSquared)
		{
			float DistanceFromCamera = FMath::Sqrt(RadiusSquared - DistanceSquared);
			float DistanceAlongRay = DotToCenter + DistanceFromCamera;						//Subtracting instead of adding will get the other intersection point
			ClippedPosition = CameraLocation + (DistanceAlongRay * CameraDirection);		//Cam aim point clipped to range sphere
			return true;
		}
	}
	return false;
}

void AGATA_MultiTrace::StartTargeting(UGameplayAbility* InAbility)
{
	Super::StartTargeting(InAbility);
	SourceActor = InAbility->GetCurrentActorInfo()->AvatarActor.Get();

	if (ReticleClass)
	{
		AGameplayAbilityWorldReticle* SpawnedReticleActor = GetWorld()->SpawnActor<AGameplayAbilityWorldReticle>(ReticleClass, GetActorLocation(), GetActorRotation());
		if (SpawnedReticleActor)
		{
			SpawnedReticleActor->InitializeReticle(this, MasterPC, ReticleParams);
			ReticleActor = SpawnedReticleActor;

			// This is to catch cases of playing on a listen server where we are using a replicated reticle actor.
			// (In a client controlled player, this would only run on the client and therefor never replicate. If it runs
			// on a listen server, the reticle actor may replicate. We want consistancy between client/listen server players.
			// Just saying 'make the reticle actor non replicated' isnt a good answer, since we want to mix and match reticle
			// actors and there may be other targeting types that want to replicate the same reticle actor class).
			if (!ShouldProduceTargetDataOnServer)
			{
				SpawnedReticleActor->SetReplicates(false);
			}
		}
	}
}

void AGATA_MultiTrace::Tick(float DeltaSeconds)
{
	// very temp - do a mostly hardcoded trace from the source actor
	if (SourceActor)
	{
		TArray<FHitResult> HitResults;
		PerformMultiLineTraces(HitResults, SourceActor);

		FVector EndPoint = HitResults.Last().Component.IsValid() ? HitResults.Last().ImpactPoint : HitResults.Last().TraceEnd;

#if ENABLE_DRAW_DEBUG
		if (bDebug)
		{
			DrawDebugLine(GetWorld(), SourceActor->GetActorLocation(), EndPoint, FColor::Green, false);
			DrawDebugSphere(GetWorld(), EndPoint, 16, 10, FColor::Green, false);
		}
#endif // ENABLE_DRAW_DEBUG

		SetActorLocationAndRotation(EndPoint, SourceActor->GetActorRotation());
	}
}

void AGATA_MultiTrace::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		TArray<FHitResult> HitResults;
		PerformMultiLineTraces(HitResults, SourceActor);

		FGameplayAbilityTargetDataHandle Handle = StartLocation.MakeTargetDataHandleFromHitResults(OwningAbility, HitResults);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

FGameplayAbilityTargetDataHandle AGATA_MultiTrace::MakeTargetData(const FHitResult& HitResult) const
{
	/** Note: This will be cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr) */
	return StartLocation.MakeTargetDataHandleFromHitResult(OwningAbility, HitResult);
}

void AGATA_MultiTrace::PerformMultiLineTraces(TArray<FHitResult>& OutHitResults, AActor* InSourceActor)
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

	AActor* LastHitActor;
	for (uint8 i = 0; i < maxTraces; i++)
	{
		FHitResult TraceHitResult;
		LineTraceWithFilter(TraceHitResult, InSourceActor->GetWorld(), Filter, TraceStart, TraceEnd, TraceChannel, Params);

		// store the hit actor so we can ignore it next iteration
		if (TraceHitResult.Actor.IsValid())
		{
			Params.ClearIgnoredActors();
			Params.AddIgnoredActor(InSourceActor);
			AActor* HitActor = TraceHitResult.Actor.Get();
			Params.AddIgnoredActor(HitActor);
			LastHitActor = HitActor;
		}
		else	// this means we line traced in thin air and hit nothing, break to end unnecesary traces
		{
#if ENABLE_DRAW_DEBUG
			if (bDebug)
			{
				float debugLifeTime = 5.f;
				float colorAccumulate = i * (maxTraces > 1 ? (255 / (maxTraces - 1)) : 0);

				DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor(0.f, 0.f + colorAccumulate, 255.f), false, debugLifeTime);
			}
#endif // ENABLE_DRAW_DEBUG
			break;
		}

		if (TraceHitResult.bBlockingHit)
		{
			if (TraceHitResult.Actor->IsA(ActorClassToCollect))
			{
				OutHitResults.Add(TraceHitResult);
			}
			else
			{
#if ENABLE_DRAW_DEBUG
				if (bDebug)
				{
					float debugLifeTime = 5.f;
					float colorAccumulate = i * (maxTraces > 1 ? (255 / (maxTraces - 1)) : 0);

					DrawDebugLine(GetWorld(), TraceStart, TraceHitResult.Location, FColor(0.f, 0.f + colorAccumulate, 255.f), false, debugLifeTime);
					DrawDebugPoint(GetWorld(), TraceHitResult.Location, 10, FColor(0.f, 0.f, 255.f), false, debugLifeTime);
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
			DrawDebugPoint(GetWorld(), TraceHitResult.Location, 10, FColor(0.f + (colorAccumulate * 0.5f), 255.f - colorAccumulate, 0.f), false, debugLifeTime);
		}
#endif // ENABLE_DRAW_DEBUG


		TraceStart = TraceHitResult.ImpactPoint;
	}




	//if (AGameplayAbilityWorldReticle* LocalReticleActor = ReticleActor.Get())
	//{
	//	//const bool bHitActor = (ReturnHitResult.bBlockingHit && (ReturnHitResult.Actor != NULL));
	//	const bool bHitActor = (OutHitResults.Num() > 0);
	//	const FVector ReticleLocation = (bHitActor && LocalReticleActor->bSnapToTargetedActor) ? ReturnHitResult.Actor->GetActorLocation() : ReturnHitResult.Location;

	//	LocalReticleActor->SetActorLocation(ReticleLocation);
	//	LocalReticleActor->SetIsTargetAnActor(bHitActor);
	//}
}
void AGATA_MultiTrace::PerformMultiSweeps(TArray<FHitResult>& OutHitResults, AActor* InSourceActor)
{

}
