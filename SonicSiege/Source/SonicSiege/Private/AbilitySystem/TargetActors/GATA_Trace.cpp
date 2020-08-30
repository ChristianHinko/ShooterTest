// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/GATA_Trace.h"

#include "GameFramework/PlayerController.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/TargetActors/GATDF_MultiFilter.h"
#include "Character/AbilitySystemCharacter.h"
#include "Pawn/AbilitySystemPawn.h"
#include "Actor/AbilitySystemActor.h"
#include "AbilitySystem/SSAbilitySystemBlueprintLibrary.h"

#include "DrawDebugHelpers.h"



AGATA_Trace::AGATA_Trace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	ShouldProduceTargetDataOnServer = true;

	MaxRange = 100000.f;
	bTraceAffectsAimPitch = true;
	TraceChannel = ECollisionChannel::ECC_Visibility;

	MultiFilter.bReverseFilter = true;
	MultiFilter.RequiredActorClasses.Add(AAbilitySystemCharacter::StaticClass());
	MultiFilter.RequiredActorClasses.Add(AAbilitySystemPawn::StaticClass());
	MultiFilter.RequiredActorClasses.Add(AAbilitySystemActor::StaticClass());
}
void AGATA_Trace::PreInitializeComponents()
{
	Super::PreInitializeComponents();


	MultiFilterHandle = USSAbilitySystemBlueprintLibrary::MakeMultiFilterHandle(MultiFilter, SourceActor);
}


void AGATA_Trace::StartTargeting(UGameplayAbility* InAbility)
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

void AGATA_Trace::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		TArray<FHitResult> HitResults;
		PerformTrace(HitResults, SourceActor);
		FGameplayAbilityTargetDataHandle TargetDataHandle = StartLocation.MakeTargetDataHandleFromHitResults(OwningAbility, HitResults);
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}

void AGATA_Trace::AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceEnd, bool bIgnorePitch) const
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

	TArray<FHitResult> HitResults;
	LineTraceMultiWithFilter(HitResults, InSourceActor->GetWorld(), MultiFilterHandle, ViewStart, ViewEnd, TraceChannel, Params);
	FHitResult HitResult = HitResults.Num() ? HitResults.Last() : FHitResult();

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
void AGATA_Trace::DirWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceDir, bool bIgnorePitch) const
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

	TArray<FHitResult> HitResults;
	LineTraceMultiWithFilter(HitResults, InSourceActor->GetWorld(), MultiFilterHandle, ViewStart, ViewEnd, TraceChannel, Params);
	FHitResult HitResult = HitResults.Num() ? HitResults.Last() : FHitResult();

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

	OutTraceDir = AdjustedAimDir;
}

bool AGATA_Trace::ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition)
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

void AGATA_Trace::LineTraceMultiWithFilter(TArray<FHitResult>& OutHitResults, const UWorld* World, const FGATDF_MultiFilterHandle MultiFilterHandle, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel, const FCollisionQueryParams Params, bool debug)
{
	check(World);

	World->LineTraceMultiByChannel(OutHitResults, Start, End, TraceChannel, Params);


	//for (int32 HitIdx = 0; HitIdx < OutHitResults.Num(); ++HitIdx)				// find first hit that passes the filter (if any) then treat is as a blocking hit and output it
	//{
	//	const FHitResult& Hit = OutHitResults[HitIdx];

	//	if (!Hit.Actor.IsValid() || MultiFilterHandle.FilterPassesForActor(Hit.Actor) == false)
	//	{
	//		OutHitResults[HitIdx] = Hit;
	//		OutHitResults[HitIdx].bBlockingHit = true; // treat it as a blocking hit
	//	}
	//}
#if ENABLE_DRAW_DEBUG
	if (debug)
	{
		const float debugLifeTime = 5.f;

		const uint8 hitsNum = OutHitResults.Num();
		if (hitsNum > 0)
		{
			for (uint8 i = 0; i < hitsNum; i++)
			{
				const float colorAccumulate = i * (hitsNum > 1 ? (255 / (hitsNum - 1)) : 0);

				const FVector FromLocation = i > 0 ? OutHitResults[i - 1].Location : Start;
				const FVector ToLocation = OutHitResults[i].Location;

				DrawDebugLine(World, FromLocation, ToLocation, FColor(0.f, 0.f + colorAccumulate, 255.f), false, debugLifeTime);
				DrawDebugPoint(World, ToLocation, 10, FColor(0.f + (colorAccumulate * 0.5f), 255.f - colorAccumulate, 0.f), false, debugLifeTime);
			}
			if (!OutHitResults.Last().bBlockingHit)
			{
				DrawDebugLine(World, OutHitResults.Last().Location, End, FColor(0.f, 0.f + 255.f, 255.f), false, debugLifeTime);
			}
		}
		else
		{
			DrawDebugLine(World, Start, End, FColor(0.f, 0.f, 255.f), false, debugLifeTime);
		}
	}
#endif // ENABLE_DRAW_DEBUG

	for (int32 i = 0; i < OutHitResults.Num(); i++)
	{
		const FHitResult Hit = OutHitResults[i];

		const bool bPassesFilter = MultiFilterHandle.FilterPassesForActor(Hit.Actor);
		if (!bPassesFilter)
		{
			OutHitResults.RemoveAt(i);
			i--;		// put i back in sync after removal		(this can be weird because on first iteration, this will make i == -1 but it gets fixed next iteration)
		}
	}
}

void AGATA_Trace::SweepMultiWithFilter(TArray<FHitResult>& OutHitResults, const UWorld* World, const FGATDF_MultiFilterHandle MultiFilterHandle, const FVector& Start, const FVector& End, const FQuat& Rotation, const FCollisionShape CollisionShape, ECollisionChannel TraceChannel, const FCollisionQueryParams Params, bool debug)
{
	check(World);

	World->SweepMultiByChannel(OutHitResults, Start, End, Rotation, TraceChannel, CollisionShape, Params);


	//for (int32 HitIdx = 0; HitIdx < OutHitResults.Num(); ++HitIdx)				// find first hit that passes the filter (if any) then treat is as a blocking hit and output it
	//{
	//	const FHitResult& Hit = OutHitResults[HitIdx];

	//	if (!Hit.Actor.IsValid() || FilterHandle.FilterPassesForActor(Hit.Actor))
	//	{
	//		OutHitResults[HitIdx] = Hit;
	//		OutHitResults[HitIdx].bBlockingHit = true; // treat it as a blocking hit
	//		break;
	//	}
	//}

	for (int32 i = 0; i < OutHitResults.Num(); i++)
	{
		const FHitResult Hit = OutHitResults[i];

		const bool bPassesFilter = MultiFilterHandle.FilterPassesForActor(Hit.Actor);
		if (!bPassesFilter)
		{
			OutHitResults.RemoveAt(i);
			i--;		// put i back in sync after removal		(this can be weird because on first iteration, this will make i == -1 but it gets fixed next iteration)
		}
	}
}

void AGATA_Trace::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	// very temp - do a mostly hardcoded trace from the source actor
	if (SourceActor)
	{
		TArray<FHitResult> HitResults;
		PerformTrace(HitResults, SourceActor);
		FHitResult HitResult = HitResults.Num() ? HitResults.Last() : FHitResult();	// get last hit
		FVector EndPoint = HitResult.Component.IsValid() ? HitResult.ImpactPoint : HitResult.TraceEnd;

		SetActorLocationAndRotation(EndPoint, SourceActor->GetActorRotation());
	}
}

void AGATA_Trace::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ReticleActor.IsValid())
	{
		ReticleActor.Get()->Destroy();
	}


	Super::EndPlay(EndPlayReason);
}
