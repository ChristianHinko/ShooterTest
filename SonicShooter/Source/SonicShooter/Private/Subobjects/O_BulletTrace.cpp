// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_BulletTrace.h"

#include "GameFramework/PlayerController.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemSetupExtras/Private/Utilities/ASSELogCategories.h"
#include "Kismet/KismetMathLibrary.h"

#include "DrawDebugHelpers.h"



const float UO_BulletTrace::TraceStartWallAvoidancePadding = .01f;

UO_BulletTrace::UO_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MaxPenetrations(0)
	, MaxRicochets(0)
{
#if 0
	RicochetableSurfaces.Add(SURFACETYPE_METAL);
#endif

}

bool UO_BulletTrace::ShouldRicochetOffOf(const FHitResult& Hit) const
{
	if (const UPhysicalMaterial* HitPhysMaterial = Hit.PhysMaterial.Get())
	{
		const EPhysicalSurface& HitSurfaceType = HitPhysMaterial->SurfaceType;
		if (RicochetableSurfaces.Contains(HitSurfaceType))
		{
			return true;
		}
	}

	return false;
}
FVector UO_BulletTrace::CalculateRicochetDirection(const FHitResult& FromHit) const
{
	const FVector FromDir = (FromHit.Location - FromHit.TraceStart).GetSafeNormal();
	const FVector MirroredDir = FromDir.MirrorByVector(FromHit.ImpactNormal);

	return MirroredDir;
}


void UO_BulletTrace::ScanWithLineTraces(TArray<FHitResult>& OutHitResults, const FVector& ScanStart, const FVector& ScanDirection, const float MaxRange, const UWorld* World, const ECollisionChannel TraceChannel, FCollisionQueryParams CollisionQueryParams)
{
	FVector CurrentTracingDirection = ScanDirection;
	float CurrentTracingMaxRange = MaxRange; // keep track of the max range as we go through our traces
	bool bCurrentTraceHitBlockingHit = false;

	FVector StartingTraceEnd = ScanStart + (CurrentTracingMaxRange * CurrentTracingDirection);

	CollisionQueryParams.bReturnPhysicalMaterial = true; // ensure we return the Physical Material for ricochet determination
	CollisionQueryParams.bTraceComplex = true; // trace complex is required for penetrations. We need this for when we are starting from inside the geometry and shooting out (this won't work for CTF_UseSimpleAsComplex and Physics Assest colliders so TODO: we will need a case that covers this)

	// Perform the first trace and give the HitResults to our output parameter
	bCurrentTraceHitBlockingHit = World->LineTraceMultiByChannel(OutHitResults, ScanStart, StartingTraceEnd, TraceChannel, CollisionQueryParams);


	if (bCurrentTraceHitBlockingHit && ShouldContinueTracingAfterFirstTrace(OutHitResults, World, CurrentTracingDirection, CollisionQueryParams))
	{
		// Perform the rest of the traces (penetrations and ricochets)
		int32 TimesRicocheted = 0;
		int32 TimesPenetrated = 0;
		while (bCurrentTraceHitBlockingHit)
		{
			// Update our traces' max range
			CurrentTracingMaxRange -= OutHitResults.Last().Distance;

			// Perform next trace (ricochet or penetration)
			TArray<FHitResult> TraceHitResults;
			FVector TraceStart;
			FVector TraceEnd;

			if (ShouldRicochetOffOf(OutHitResults.Last()))
			{
				if (TimesRicocheted >= MaxRicochets && MaxRicochets != -1)
				{
					// We've reached MaxRicochets
					break;
				}

				if (!ShouldContinueTracingAfterRicochetHit(OutHitResults, TraceHitResults, World, CurrentTracingDirection, CollisionQueryParams)) // TODO: get rid of passing in RicochetTraceHitResults as a parameter (it is empty at this point anyways)
				{
					// We have been stopped by this ricochet hit
					break;
				}

				++TimesRicocheted;

				// Calculate ricochet direction
				CurrentTracingDirection = CalculateRicochetDirection(OutHitResults.Last());

				// Use the direction to get the trace end
				TraceStart = OutHitResults.Last().Location + (CurrentTracingDirection * TraceStartWallAvoidancePadding);
				TraceEnd = TraceStart + (CurrentTracingMaxRange * CurrentTracingDirection);

				// Perform ricochet trace
				bCurrentTraceHitBlockingHit = World->LineTraceMultiByChannel(TraceHitResults, TraceStart, TraceEnd, TraceChannel, CollisionQueryParams);
				OutHitResults.Append(TraceHitResults);
			}
			else
			{
				if (TimesPenetrated >= MaxPenetrations && MaxPenetrations != -1)
				{
					// We've reached MaxPenetrations
					break;
				}

				++TimesPenetrated;

				// Use the direction to get the trace end
				TraceStart = OutHitResults.Last().Location + (CurrentTracingDirection * TraceStartWallAvoidancePadding);
				TraceEnd = TraceStart + (CurrentTracingMaxRange * CurrentTracingDirection);

				// Perform the penetration trace and fill out PenetrationTraceHitResults with the HitResults
				{
					bCurrentTraceHitBlockingHit = World->LineTraceMultiByChannel(TraceHitResults, TraceStart, TraceEnd, TraceChannel, CollisionQueryParams);

					// Edge case: if we hit ourselves instead of going through to the next hit. This happens if we are a CTF_UseSimpleAsComplex or a Physics Asset collider.
					if (TraceHitResults.Num() > 0 && TraceHitResults.Last().Distance == 0)
					{
						// Our fallback if the trace messed up. Try again with this component ignored
						CollisionQueryParams.AddIgnoredComponent(TraceHitResults.Last().GetComponent());
						bCurrentTraceHitBlockingHit = World->LineTraceMultiByChannel(TraceHitResults, TraceStart, TraceEnd, TraceChannel, CollisionQueryParams);
					}
				}

				OutHitResults.Append(TraceHitResults);

				if (!ShouldContinueTracingAfterPenetrationTrace(OutHitResults, TraceHitResults, World, CurrentTracingDirection, CollisionQueryParams))
				{
					// We have been stopped in this penetration
					break;
				}
			}

			if (TraceHitResults.Num() <= 0)
			{
				// Our caller may depend on us returning at least one Hit Result so it can get TraceStart and TraceEnd.
				// Make an empty Hit Result containing this info (this will just end up getting filtered)
				FHitResult TraceInfo;
				TraceInfo.TraceStart = TraceStart;
				TraceInfo.TraceEnd = TraceEnd;

				OutHitResults.Add(TraceInfo);
			}
		}
	}

	if (OutHitResults.Num() <= 0) // first trace didn't hit anything (i.e. we've traced into thin air)
	{
		// Our caller may depend on us returning at least one Hit Result so it can get TraceStart and TraceEnd.
		// Make an empty Hit Result containing this info (this will just end up getting filtered)
		FHitResult TraceInfo;
		TraceInfo.TraceStart = ScanStart;
		TraceInfo.TraceEnd = StartingTraceEnd;

		OutHitResults.Add(TraceInfo);
	}

	OnFinishedScanWithLineTraces(OutHitResults, World, CurrentTracingDirection, CollisionQueryParams);
}

bool UO_BulletTrace::ShouldContinueTracingAfterFirstTrace(TArray<FHitResult>& FirstTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams)
{
	return true;
}
bool UO_BulletTrace::ShouldContinueTracingAfterPenetrationTrace(TArray<FHitResult>& ScanHitResults, TArray<FHitResult>& PenetrationTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams)
{
	return true;
}
bool UO_BulletTrace::ShouldContinueTracingAfterRicochetHit(TArray<FHitResult>& ScanHitResults, TArray<FHitResult>& RicochetTraceHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams)
{
	return true;
}
void UO_BulletTrace::OnFinishedScanWithLineTraces(TArray<FHitResult>& ScanHitResults, const UWorld* World, const FVector& CurrentTracingDirection, const FCollisionQueryParams& QueryParams)
{

}
