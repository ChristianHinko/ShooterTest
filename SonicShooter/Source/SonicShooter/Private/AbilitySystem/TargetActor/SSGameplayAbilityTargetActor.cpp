// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/SSGameplayAbilityTargetActor.h"

#include "Abilities/GameplayAbility.h"



ASSGameplayAbilityTargetActor::ASSGameplayAbilityTargetActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void ASSGameplayAbilityTargetActor::FilterHitResults(TArray<FHitResult>& OutHitResults, const FGATDF_MultiFilterHandle FilterHandle, const bool inAllowMultipleHitsPerActor) const
{
	for (int32 i = 0; i < OutHitResults.Num(); ++i)
	{
		const FHitResult Hit = OutHitResults[i];


		if (FilterHandle.MultiFilter.IsValid()) // if valid filter
		{
			const bool bPassesFilter = FilterHandle.FilterPassesForActor(Hit.Actor);
			if (!bPassesFilter)
			{
				OutHitResults.RemoveAt(i);
				--i;
				continue;
			}
		}

		if (!inAllowMultipleHitsPerActor) // if we should remove multiple hits
		{
			// Loop through each hit result and check if the hits infront of it (the hit results less than the pending index) already have its actor.
			// If so, remove the pending hit result because it has the actor that was already hit and is considered a duplicate hit.

			bool removed = false; // if true, we removed a duplicate hit

			// Check if the hit results that we've looped through so far contains a hit result with this actor already
			for (int32 comparisonIndex = 0; comparisonIndex < i; ++comparisonIndex)
			{
				if (Hit.Actor == OutHitResults[comparisonIndex].Actor)
				{
					OutHitResults.RemoveAt(i);
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
	}
}

void ASSGameplayAbilityTargetActor::AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceEnd) const
{
	FVector TraceDir;
	DirWithPlayerController(InSourceActor, Params, TraceStart, TraceDir);

	OutTraceEnd = TraceStart + (TraceDir * MaxRange);
}
void ASSGameplayAbilityTargetActor::DirWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceDir) const
{
	if (!OwningAbility) // Server and launching client only
	{
		return;
	}

	const APlayerController* PC = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();
	check(PC);

	FVector ViewStart;
	FRotator ViewRot;
	PC->GetPlayerViewPoint(ViewStart, ViewRot);

	const FVector ViewDir = ViewRot.Vector();
	FVector ViewEnd = ViewStart + (ViewDir * MaxRange);

	ClipCameraRayToAbilityRange(ViewStart, ViewDir, TraceStart, MaxRange, ViewEnd);

	TArray<FHitResult> HitResults;
	InSourceActor->GetWorld()->LineTraceMultiByChannel(HitResults, ViewStart, ViewEnd, TraceChannel, Params);
	FHitResult HitResult = HitResults.Num() ? HitResults[0] : FHitResult();

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

bool ASSGameplayAbilityTargetActor::ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition)
{
	const FVector CameraToCenter = AbilityCenter - CameraLocation;
	const float DotToCenter = FVector::DotProduct(CameraToCenter, CameraDirection);
	if (DotToCenter >= 0)		//If this fails, we're pointed away from the center, but we might be inside the sphere and able to find a good exit point.
	{
		const float DistanceSquared = CameraToCenter.SizeSquared() - (DotToCenter * DotToCenter);
		const float RadiusSquared = (AbilityRange * AbilityRange);
		if (DistanceSquared <= RadiusSquared)
		{
			const float DistanceFromCamera = FMath::Sqrt(RadiusSquared - DistanceSquared);
			const float DistanceAlongRay = DotToCenter + DistanceFromCamera;					//Subtracting instead of adding will get the other intersection point
			ClippedPosition = CameraLocation + (DistanceAlongRay * CameraDirection);			//Cam aim point clipped to range sphere
			return true;
		}
	}
	return false;
}
