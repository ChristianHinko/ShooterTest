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

void UO_BulletTrace::ScanWithLineTraces(TArray<FHitResult>& OutHitResults, const FVector& InScanStart, const FVector& InScanDirection, const float InMaxRange, const UWorld* InWorld, const ECollisionChannel InTraceChannel, const FCollisionQueryParams& InCollisionQueryParams)
{
	FVector CurrentTracingDirection = InScanDirection; // this copy is for keeping track of the tracing direction as we ricochet
	float CurrentTracingMaxRange = InMaxRange; // this copy is for keeping track of the max range as we go through our traces

	// Configure our TraceCollisionQueryParams
	FCollisionQueryParams TraceCollisionQueryParams = InCollisionQueryParams;
	TraceCollisionQueryParams.bReturnPhysicalMaterial = true; // ensure we return the Physical Material for ricochet determination


	// Lets start
	int32 RicochetNumber = -1;
	TArray<FHitResult> TraceHitResults;
	FVector TraceStart	= InScanStart;
	FVector TraceEnd	= InScanStart + (CurrentTracingDirection * CurrentTracingMaxRange);
	bool bRicocheted = false;
	do
	{
		bRicocheted = false;

		UBFL_CollisionQueryHelpers::LineTraceMultiByChannelWithPenetrations(InWorld, TraceHitResults, TraceStart, TraceEnd, InTraceChannel, TraceCollisionQueryParams);
		if (TraceHitResults.Num() <= 0)
		{
			break; // we traced into thin air
		}

		// See if we ricocheted
		for (int32 i = 0; i < TraceHitResults.Num(); ++i)
		{
			if (UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(TraceHitResults[i].PhysMaterial))
			{
				if (ShooterPhysMat->bRichochetsBullets)
				{
					bRicocheted = true;
					++RicochetNumber;


					// Remove all Hit Results after the ricochet hit
					if (TraceHitResults.IsValidIndex(i + 1))
					{
						TraceHitResults.RemoveAt(i + 1, TraceHitResults.Num() - i - 1);
					}

					break;
				}
			}
		}


		// Lets add our findings to the return value
		OutHitResults.Append(TraceHitResults);

		// If we ricocheted, we want to prepare for the next trace
		if (bRicocheted)
		{
			CurrentTracingDirection = CurrentTracingDirection.MirrorByVector(OutHitResults.Last().ImpactNormal);
			TraceStart = OutHitResults.Last().Location + (CurrentTracingDirection * TraceStartWallAvoidancePadding);
			TraceEnd = CurrentTracingDirection * CurrentTracingMaxRange;
		}

	} while (bRicocheted && RicochetNumber < MaxRicochets);
}
