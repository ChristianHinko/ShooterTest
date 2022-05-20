// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/GATA_BulletTrace.h"

#include "BlueprintFunctionLibraries/BFL_ShooterHelpers.h"
#include "Utilities/SSCollisionChannels.h"
#include "AbilitySystem/Types/SSGameplayAbilityTargetTypes.h"
#include "PhysicalMaterial/PM_Shooter.h"



AGATA_BulletTrace::AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TraceChannel = COLLISION_BULLET;

	CurrentScanIndex = INDEX_NONE;
	bDebug = true;
}


void AGATA_BulletTrace::ConfirmTargetingAndContinue()
{
	Super::ConfirmTargetingAndContinue();

	// Our Target Data to broadcast
	FGameplayAbilityTargetDataHandle TargetDataHandle;

	// Perform our scans
	TArray<TArray<TArray<FShooterHitResult>>> SceneCastHitResults;
	SceneCastHitResults.AddDefaulted(NumOfScans); // add the predetermined number of scans
	TArray<FSceneCastInfo> SceneCastInfos;
	SceneCastInfos.AddDefaulted(NumOfScans); // add the predetermined number of scans

	// Perform scans
	for (CurrentScanIndex = 0; CurrentScanIndex < NumOfScans; ++CurrentScanIndex)
	{
		// Perform line trace
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.bReturnPhysicalMaterial = true; // this is needed for our bullet speed nerf calculations and determining whether to ricochet
		CollisionQueryParams.AddIgnoredActor(SourceActor);
		//CollisionQueryParams.bTraceComplex = true;
		float BulletSpeed = InitialBulletSpeed;
		UBFL_ShooterHelpers::RicochetingPenetrationSceneCastWithExitHitsUsingSpeed(BulletSpeed, RangeFalloffNerf, SourceActor->GetWorld(), SceneCastHitResults[CurrentScanIndex], SceneCastInfos[CurrentScanIndex], StartLocation.GetTargetingTransform().GetLocation(), GetAimDirectionOfStartLocation(), MaxRange, FQuat::Identity, TraceChannel, FCollisionShape(), CollisionQueryParams, MaxRicochets,
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
			},
			[](const FHitResult& Hit) -> bool // IsHitRicochetable()
			{
				const UPM_Shooter* ShooterPhysMat = Cast<UPM_Shooter>(Hit.PhysMaterial);
				if (IsValid(ShooterPhysMat))
				{
					return ShooterPhysMat->bRicochets;
				}

				return false;
			}
		);

		if (bDebug)
		{

		}
	}
	CurrentScanIndex = INDEX_NONE;


	// Create and add Target Data to our handle
	for (int32 i = 0; i < SceneCastHitResults.Num(); ++i)
	{
		FGATD_BulletTraceTargetHit* ThisScanTargetData = new FGATD_BulletTraceTargetHit(); // these are cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr)

		const TArray<TArray<FShooterHitResult>>& ShooterHits = SceneCastHitResults[i];
		const FSceneCastInfo& SceneCastInfo = SceneCastInfos[i];

		// Fill target data's BulletTracePoints
		{
			ThisScanTargetData->BulletTracePoints.Reserve(ShooterHits.Num() + 2);

			ThisScanTargetData->BulletTracePoints.Add(SceneCastInfo.StartLocation);
			for (const TArray<FShooterHitResult>& Hits : ShooterHits)
			{
				if (Hits.Num() <= 0)
				{
					continue;
				}

				ThisScanTargetData->BulletTracePoints.Add(Hits.Last().Location);
			}
			ThisScanTargetData->BulletTracePoints.Add(SceneCastInfo.EndLocation);
		}

		// Add the actor hit infos for this scan. Making a sort of custom filter to not hit the same actor more than once in the same trace
		for (const TArray<FShooterHitResult>& Hits : ShooterHits)
		{
			for (int32 j = 0; j < Hits.Num(); ++j)
			{
				const FShooterHitResult& Hit = Hits[j];

				if (Hit.bIsExitHit)
				{
					continue;
				}

				if (Filter.FilterPassesForActor(Hit.GetActor()))
				{
					bool bHasAlreadyBeenHitByThisSceneCast = false;
					for (int32 k = 0; k < j; ++k)
					{
						if (Hit.GetActor() == Hits[k].GetActor())
						{
							bHasAlreadyBeenHitByThisSceneCast = true;
							break;
						}
					}

					if (!bHasAlreadyBeenHitByThisSceneCast)
					{
						// This hit won't get filtered, so lets add it to the target data
						FActorHitInfo ActorHitInfo = FActorHitInfo(Hit.GetActor(), Hit.Speed);
						ThisScanTargetData->ActorHitInfos.Add(ActorHitInfo);
					}
				}
			}

			
		}

		TargetDataHandle.Add(ThisScanTargetData);
	}

	TargetDataReadyDelegate.Broadcast(TargetDataHandle);
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
