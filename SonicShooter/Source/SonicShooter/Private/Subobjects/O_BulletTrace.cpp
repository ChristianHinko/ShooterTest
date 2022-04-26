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
	FVector CurrentBulletDirection = InScanDirection; // this copy is for keeping track of the tracing direction as we ricochet
	float CurrentBulletMaxRange = InMaxRange; // this copy is for keeping track of the max range as we go through our traces

	// Configure our TraceCollisionQueryParams
	FCollisionQueryParams BulletCollisionQueryParams = InCollisionQueryParams;
	BulletCollisionQueryParams.bReturnPhysicalMaterial = true; // ensure we return the Physical Material for ricochet determination


	// Lets start
	int32 RicochetNumber = -1;
	TArray<FHitResult> BulletHitResults;
	FVector BulletStart	= InScanStart;
	FVector BulletEnd	= InScanStart + (CurrentBulletDirection * CurrentBulletMaxRange);
	bool bRicocheted = false;
	do
	{
		bRicocheted = false;

		UBFL_CollisionQueryHelpers::DoubleSidedLineTraceMultiByChannelWithPenetrations(InWorld, BulletHitResults, BulletStart, BulletEnd, InTraceChannel, BulletCollisionQueryParams,
			[&bRicocheted, &RicochetNumber](const FHitResult& HitResult)
			{
				if (UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(HitResult.PhysMaterial))
				{
					// See if we ricocheted
					if (ShooterPhysMat->bRichochetsBullets)
					{
						bRicocheted = true;
						++RicochetNumber;
						return true;
					}
				}

				return false;
			}
		);

		if (BulletHitResults.Num() <= 0)
		{
			break; // we Bulleted into thin air
		}


		// Lets add our findings to the return value
		OutHitResults.Append(BulletHitResults);

		// If we ricocheted, we want to prepare for the next trace
		if (bRicocheted)
		{
			CurrentBulletDirection = CurrentBulletDirection.MirrorByVector(OutHitResults.Last().ImpactNormal);
			BulletStart = OutHitResults.Last().Location + (CurrentBulletDirection * TraceStartWallAvoidancePadding);
			BulletEnd = CurrentBulletDirection * CurrentBulletMaxRange;
		}

	} while (bRicocheted && RicochetNumber < MaxRicochets);
}
