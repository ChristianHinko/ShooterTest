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

void UO_BulletTrace::ScanWithLineTraces(TArray<FHitResult>& OutHitResults, const FVector& InScanStart, FVector ScanDirection, float DistanceToTravel, const UWorld* InWorld, const ECollisionChannel InTraceChannel, const FCollisionQueryParams& InCollisionQueryParams, const TFunction<bool(const FHitResult&)>& ShouldRicochetOffOf)
{
	// Configure our TraceCollisionQueryParams
	FCollisionQueryParams BulletCollisionQueryParams = InCollisionQueryParams;
	BulletCollisionQueryParams.bReturnPhysicalMaterial = true; // ensure we return the Physical Material for ricochet determination


	// Initial Trace
	FVector BulletEnd = InScanStart + (ScanDirection * DistanceToTravel);
	// Penetration line trace that stops at a user defined ricochetable surface
	bool bHitRicochetableSurface = UBFL_CollisionQueryHelpers::DoubleSidedLineTraceMultiByChannelWithPenetrations(InWorld, OutHitResults, InScanStart, BulletEnd, InTraceChannel, BulletCollisionQueryParams, ShouldRicochetOffOf);
	if (!bHitRicochetableSurface)
	{
		return;
	}
	DistanceToTravel -= OutHitResults.Last().Distance;


	// Ricochets
	for (int32 RicochetNumber = 1; RicochetNumber <= MaxRicochets; ++RicochetNumber)
	{
		// Reflect our ScanDirection off of the ricochetable surface
		ScanDirection = ScanDirection.MirrorByVector(OutHitResults.Last().ImpactNormal);

		FVector RicochetTraceStart = OutHitResults.Last().Location + (ScanDirection * TraceStartWallAvoidancePadding);
		FVector RicochetTraceEnd = RicochetTraceStart + (ScanDirection * DistanceToTravel);


		// Penetration line trace that stops at a user defined ricochetable surface
		TArray<FHitResult> RicochetTraceHitResults;
		bHitRicochetableSurface = UBFL_CollisionQueryHelpers::DoubleSidedLineTraceMultiByChannelWithPenetrations(InWorld, RicochetTraceHitResults, RicochetTraceStart, RicochetTraceEnd, InTraceChannel, BulletCollisionQueryParams, ShouldRicochetOffOf);
		OutHitResults.Append(RicochetTraceHitResults);
			
		if (!bHitRicochetableSurface)
		{
			break;
		}
		
		DistanceToTravel -= OutHitResults.Last().Distance; // since we stopped at a ricochet, the last hit is our ricochet hit. Take away the distance traveled of this trace from our CurrentBulletMaxRange
		if (DistanceToTravel <= 0.f)
		{
			break;
		}
	}
}
