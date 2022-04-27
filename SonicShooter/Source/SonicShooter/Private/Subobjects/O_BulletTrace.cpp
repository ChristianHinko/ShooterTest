// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_BulletTrace.h"

#include "PhysicalMaterial/PM_Shooter.h"
#include "BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"

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

}

void UO_BulletTrace::ScanWithLineTraces(TArray<FHitResult>& OutHitResults, FVector ScanStart, FVector ScanDirection, float DistanceToTravel, const UWorld* InWorld, const ECollisionChannel InTraceChannel, const FCollisionQueryParams& InCollisionQueryParams, const TFunction<bool(const FHitResult&)>& ShouldRicochetOffOf)
{
	// The first iteration of this loop is the initial trace and the rest of the iterations are ricochet traces
	for (int32 RicochetNumber = 0; RicochetNumber <= MaxRicochets; ++RicochetNumber)
	{
		TArray<FHitResult> TraceHitResults;
		const FVector TraceEnd = ScanStart + (ScanDirection * DistanceToTravel);

		// Penetration line trace that stops at a user defined ricochetable surface
		const bool bHitRicochetableSurface = UBFL_CollisionQueryHelpers::DoubleSidedLineTraceMultiByChannelWithPenetrations(InWorld, TraceHitResults, ScanStart, TraceEnd, InTraceChannel, InCollisionQueryParams, ShouldRicochetOffOf);
		OutHitResults.Append(TraceHitResults);

		if (!bHitRicochetableSurface)
		{
			break;
		}
		
		// Take away the distance traveled of this trace from our CurrentBulletMaxRange
		DistanceToTravel -= OutHitResults.Last().Distance; // since we stopped at a ricochet, the last hit is our ricochet hit
		if (DistanceToTravel <= 0.f)
		{
			break;
		}

		// Reflect our ScanDirection off of the ricochetable surface and calculate ScanStart for next ricochet
		ScanDirection = ScanDirection.MirrorByVector(OutHitResults.Last().ImpactNormal);
		ScanStart = OutHitResults.Last().Location + (ScanDirection * TraceStartWallAvoidancePadding);
	}
}
