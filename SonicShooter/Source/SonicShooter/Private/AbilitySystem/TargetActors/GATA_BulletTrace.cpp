// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/GATA_BulletTrace.h"

#include "Subobjects/O_BulletTrace.h"

#include "Abilities/GameplayAbility.h"
#include "Utilities/SSCollisionChannels.h"
#include "AbilitySystem/Types/SSGameplayAbilityTargetTypes.h"
#include "AbilitySystemComponent.h"
#include "BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"
#include "PhysicalMaterial/PM_Shooter.h"
#include "BlueprintFunctionLibraries/BFL_HitResultHelpers.h"
#include "BlueprintFunctionLibraries/BFL_MathHelpers.h"

#include "Kismet/KismetSystemLibrary.h"



AGATA_BulletTrace::AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TraceChannel = COLLISION_BULLET;

	CurrentScanIndex = INDEX_NONE;
	bDebug = true;

	BulletTraceSubobject = CreateDefaultSubobject<UO_BulletTrace>(TEXT("BulletTraceSubobject"));
}


void AGATA_BulletTrace::ConfirmTargetingAndContinue()
{
	Super::ConfirmTargetingAndContinue();


	// Our Target Data to broadcast
	FGameplayAbilityTargetDataHandle TargetDataHandle;

	// Perform our scans
	TArray<FScanResult> ScanResults;

	// Reserve the predetermined number of scans
	ScanResults.Reserve(NumOfScans);

	// Perform scans
	for (CurrentScanIndex = 0; CurrentScanIndex < NumOfScans; ++CurrentScanIndex)
	{
		const float RangeFalloffNerf = .02f;

		// Perform line trace
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.bReturnPhysicalMaterial = true; // this is needed for our bullet speed nerf calculations and determining whether to ricochet
		CollisionQueryParams.AddIgnoredActor(SourceActor);
		//CollisionQueryParams.bTraceComplex = true;
		FScanResult ScanResult;
		BulletTraceSubobject->ScanWithLineTracesUsingSpeed(ScanResult, StartLocation.GetTargetingTransform().GetLocation(), GetAimDirectionOfStartLocation(), MaxRange, SourceActor->GetWorld(), TraceChannel, CollisionQueryParams, MaxPenetrations, MaxRicochets, InitialBulletSpeed, RangeFalloffNerf,
			[](const FHitResult& Hit) -> bool // ShouldRicochetOffOf()
			{
				const UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(Hit.PhysMaterial);
				if (IsValid(ShooterPhysMat))
				{
					return ShooterPhysMat->bRicochets;
				}

				return false;
			},
			[](const FHitResult& Hit) -> float // GetPenetrationSpeedNerf()
			{
				const UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(Hit.PhysMaterial);
				if (IsValid(ShooterPhysMat))
				{
					return ShooterPhysMat->PenetrationSpeedNerf;
				}

				return 0.f;
			},
			[](const FHitResult& Hit) -> float // GetRicochetSpeedNerf()
			{
				const UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(Hit.PhysMaterial);
				if (IsValid(ShooterPhysMat))
				{
					return ShooterPhysMat->RicochetSpeedNerf;
				}

				return 0.f;
			}
		);

		if (bDebug)
		{
			ScanResult.DebugScan(SourceActor->GetWorld());
		}
		ScanResults.Add(ScanResult);
	}
	CurrentScanIndex = INDEX_NONE;






	for (int32 i = 0; i < ScanResults.Num(); ++i)
	{
		FGATD_BulletTraceTargetHit* ThisScanTargetData = new FGATD_BulletTraceTargetHit(); // these are cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr)

		const FScanResult& ScanResult = ScanResults[i];

		// Fill target data's BulletTracePoints
		{
			ThisScanTargetData->BulletTracePoints.Reserve(ScanResult.BulletHits.Num() + 2);

			ThisScanTargetData->BulletTracePoints.Add(ScanResult.BulletStart);
			for (FHitResult Hit : ScanResult.BulletHits)
			{
				ThisScanTargetData->BulletTracePoints.Add(Hit.Location);
			}
			ThisScanTargetData->BulletTracePoints.Add(ScanResult.BulletEnd);
		}

		// Add the actor hit infos for this scan. Making a sort of custom filter to not hit the same actor more than once in the same trace
		for (int32 j = 0; j < ScanResult.BulletHits.Num(); ++j)
		{
			const FBulletHit& BulletHit = ScanResult.BulletHits[j];

			if (BulletHit.bIsExitHit)
			{
				continue;
			}

			if (Filter.FilterPassesForActor(BulletHit.GetActor()))
			{
				bool bHasAlreadyBeenHitBySameTrace = false;
				for (int32 k = 0; k < j; ++k)
				{
					if (BulletHit.RicochetNumber != ScanResult.BulletHits[k].RicochetNumber) // allow it to be hit again if it's a different trace (e.g. ricochet number 0 vs 1)
					{
						continue;
					}

					if (BulletHit.GetActor() == ScanResult.BulletHits[k].GetActor())
					{
						bHasAlreadyBeenHitBySameTrace = true;
						break;
					}
				}

				if (!bHasAlreadyBeenHitBySameTrace)
				{
					// This hit won't get filtered, so lets add it to the target data
					FActorHitInfo ActorHitInfo = FActorHitInfo(BulletHit.GetActor(), BulletHit.Speed);
					ThisScanTargetData->ActorHitInfos.Add(ActorHitInfo);
				}
			}
		}

		TargetDataHandle.Add(ThisScanTargetData);
	}

	TargetDataReadyDelegate.Broadcast(TargetDataHandle);
}

bool AGATA_BulletTrace::ShouldRicochetOffOf(const FHitResult& Hit) const
{
	const UPM_Shooter* ShooterPhysMat = Cast<const UPM_Shooter>(Hit.PhysMaterial.Get());
	if (IsValid(ShooterPhysMat))
	{
		if (ShooterPhysMat->bRicochets)
		{
			return true;
		}
	}

	return false;
}

void AGATA_BulletTrace::CalculateAimDirection(FVector& OutAimStart, FVector& OutAimDir) const
{
	Super::CalculateAimDirection(OutAimStart, OutAimDir); // call Super so we get the PC's view dir, and then we can add bullet spread ontop of that


	// Calculate new OutAimDir with random bullet spread offset if needed
	if (CurrentBulletSpread > SMALL_NUMBER)
	{
		// Our injected random seed is only unique to each fire. We need a random seed that is also unique to each bullet in the fire, so we will do this by using t
		const int32 FireAndBulletSpecificNetSafeRandomSeed = FireSpecificNetSafeRandomSeed - ((CurrentScanIndex + 2) * FireSpecificNetSafeRandomSeed);	// Here, the 'number' multiplied to t makes the random pattern noticable after firing 'number' of times. I use the prediction key as that 'number' which i think eliminates the threshold for noticeability entirely. - its confusing to think about but i think it works
		FMath::RandInit(FireAndBulletSpecificNetSafeRandomSeed);
		const FRandomStream RandomStream = FRandomStream(FMath::Rand());

		// Get and apply random offset to OutAimDir using randomStream
		const float ConeHalfAngleRadius = FMath::DegreesToRadians(CurrentBulletSpread * 0.5f);
		OutAimDir = RandomStream.VRandCone(OutAimDir, ConeHalfAngleRadius);
	}
}
