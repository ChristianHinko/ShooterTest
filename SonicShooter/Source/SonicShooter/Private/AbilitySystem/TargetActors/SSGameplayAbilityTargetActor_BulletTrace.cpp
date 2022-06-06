// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/SSGameplayAbilityTargetActor_BulletTrace.h"

#include "BlueprintFunctionLibraries/CollisionQuery/HLBlueprintFunctionLibrary_StrengthCollisionQueries.h"
#include "BlueprintFunctionLibraries/Debugging/HLBlueprintFunctionLibrary_DrawDebugHelpersStrengthCollisionQueries.h"
#include "Utilities/SSCollisionChannels.h"
#include "AbilitySystem/Types/SSGameplayAbilityTargetTypes.h"
#include "PhysicalMaterial/SSPhysicalMaterial_Shooter.h"



ASSGameplayAbilityTargetActor_BulletTrace::ASSGameplayAbilityTargetActor_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TraceChannel = COLLISIONCHANNEL_BULLET;

	CurrentBulletIndex = INDEX_NONE;
	bDebug = true;
}


void ASSGameplayAbilityTargetActor_BulletTrace::ConfirmTargetingAndContinue()
{
	Super::ConfirmTargetingAndContinue();

	// Our Target Data to broadcast
	FGameplayAbilityTargetDataHandle TargetDataHandle;

	// Do our bullet collision queries
	TArray<FRicochetingPenetrationSceneCastWithExitHitsUsingStrengthResult> BulletResults;
	BulletResults.AddDefaulted(NumOfBullets); // add the predetermined number of bullets

	// Perform each bullet collision query
	for (CurrentBulletIndex = 0; CurrentBulletIndex < NumOfBullets; ++CurrentBulletIndex)
	{
		// Perform line trace
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.bReturnPhysicalMaterial = true; // this is needed for our bullet speed nerf calculations and determining whether to ricochet
		CollisionQueryParams.AddIgnoredActor(SourceActor);
		//CollisionQueryParams.bTraceComplex = true;
		FCollisionShape CollisionShape = FCollisionShape::MakeSphere(30.f);
		UHLBlueprintFunctionLibrary_StrengthCollisionQueries::RicochetingPenetrationSceneCastWithExitHitsUsingStrength(InitialBulletSpeed, RangeFalloffNerf, SourceActor->GetWorld(), BulletResults[CurrentBulletIndex], StartLocation.GetTargetingTransform().GetLocation(), GetAimDirectionOfStartLocation(), MaxRange, FQuat::Identity, TraceChannel, CollisionShape, CollisionQueryParams, FCollisionResponseParams::DefaultResponseParam, MaxRicochets,
			[](const FHitResult& Hit) -> float // GetPerCmPenetrationNerf()
			{
				const USSPhysicalMaterial_Shooter* ShooterPhysMat = Cast<USSPhysicalMaterial_Shooter>(Hit.PhysMaterial);
				if (IsValid(ShooterPhysMat))
				{
					return ShooterPhysMat->PerCmPenetrationSpeedNerf;
				}

				return 0.f;
			},
			[](const FHitResult& Hit) -> float // GetRicochetNerf()
			{
				const USSPhysicalMaterial_Shooter* ShooterPhysMat = Cast<USSPhysicalMaterial_Shooter>(Hit.PhysMaterial);
				if (IsValid(ShooterPhysMat))
				{
					return ShooterPhysMat->RicochetSpeedNerf;
				}

				return 0.f;
			},
			[](const FHitResult& Hit) -> bool // IsHitRicochetable()
			{
				const USSPhysicalMaterial_Shooter* ShooterPhysMat = Cast<USSPhysicalMaterial_Shooter>(Hit.PhysMaterial);
				if (IsValid(ShooterPhysMat))
				{
					return ShooterPhysMat->bRicochets;
				}

				return false;
			}
			);

		if (bDebug)
		{
			const float DebugLifeTime = 10.f;

			UHLBlueprintFunctionLibrary_DrawDebugHelpersStrengthCollisionQueries::DrawStrengthDebugLine(SourceActor->GetWorld(), BulletResults[CurrentBulletIndex], InitialBulletSpeed, false, DebugLifeTime, 0.f, 0.f, 1.f);
			UHLBlueprintFunctionLibrary_DrawDebugHelpersStrengthCollisionQueries::DrawStrengthDebugText(SourceActor->GetWorld(), BulletResults[CurrentBulletIndex], InitialBulletSpeed, DebugLifeTime);
			UHLBlueprintFunctionLibrary_DrawDebugHelpersStrengthCollisionQueries::DrawCollisionShapeDebug(SourceActor->GetWorld(), BulletResults[CurrentBulletIndex], InitialBulletSpeed, false, DebugLifeTime, 0.f, 0.f);
		}
	}
	CurrentBulletIndex = INDEX_NONE;


	// Create and add Target Data to our handle
	for (int32 i = 0; i < BulletResults.Num(); ++i)
	{
		FSSGameplayAbilityTargetData_BulletTraceTargetHit* ThisBulletTargetData = new FSSGameplayAbilityTargetData_BulletTraceTargetHit(); // these are cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr)

		const TArray<FPenetrationSceneCastWithExitHitsUsingStrengthResult>& PenetrationSceneCastWithExitHitsUsingStrengthResults = BulletResults[i].PenetrationSceneCastWithExitHitsUsingStrengthResults;

		// Fill target data's BulletTracePoints
		{
			const FRicochetingPenetrationSceneCastWithExitHitsUsingStrengthResult& RicochetingPenetrationSceneCastWithExitHitsUsingStrengthResult = BulletResults[i];

			ThisBulletTargetData->BulletTracePoints.Empty(PenetrationSceneCastWithExitHitsUsingStrengthResults.Num() + 1); // reserve number of scene casts plus the end location

			// Add the start location
			ThisBulletTargetData->BulletTracePoints.Add(RicochetingPenetrationSceneCastWithExitHitsUsingStrengthResult.StrengthSceneCastInfo.StartLocation);
			// Add the rest of the start locations
			for (int32 j = 1; j < PenetrationSceneCastWithExitHitsUsingStrengthResults.Num(); ++j)
			{
				ThisBulletTargetData->BulletTracePoints.Add(PenetrationSceneCastWithExitHitsUsingStrengthResults[j].StrengthSceneCastInfo.StartLocation);
			}
			// And the end location
			ThisBulletTargetData->BulletTracePoints.Add(RicochetingPenetrationSceneCastWithExitHitsUsingStrengthResult.StrengthSceneCastInfo.StopLocation);
		}

		// Add the actor hit infos for this bullet. Making a sort of custom filter to not hit the same actor more than once in the same trace
		for (int32 j = 0; j < PenetrationSceneCastWithExitHitsUsingStrengthResults.Num(); ++j)
		{
			const FPenetrationSceneCastWithExitHitsUsingStrengthResult& PenetrationSceneCastWithExitHitsUsingStrengthResult = PenetrationSceneCastWithExitHitsUsingStrengthResults[j];
			const TArray<FStrengthHitResult>& HitResults = PenetrationSceneCastWithExitHitsUsingStrengthResult.HitResults;

			for (int32 k = 0; k < HitResults.Num(); ++k)
			{
				const FStrengthHitResult& Hit = HitResults[k];
				if (Hit.bIsExitHit)
				{
					continue;
				}

				if (Filter.FilterPassesForActor(Hit.GetActor()))
				{
					bool bHasAlreadyBeenHitByThisSceneCast = false;
					for (int32 l = 0; l < k; ++l)
					{
						if (Hit.GetActor() == HitResults[l].GetActor())
						{
							bHasAlreadyBeenHitByThisSceneCast = true;
							break;
						}
					}

					if (!bHasAlreadyBeenHitByThisSceneCast)
					{
						// This hit won't get filtered, so lets add it to the target data
						FActorHitInfo ActorHitInfo = FActorHitInfo(Hit.GetActor(), Hit.Strength);
						ThisBulletTargetData->ActorHitInfos.Add(ActorHitInfo);
					}
				}
			}
		}

		TargetDataHandle.Add(ThisBulletTargetData);
	}

	TargetDataReadyDelegate.Broadcast(TargetDataHandle);
}

void ASSGameplayAbilityTargetActor_BulletTrace::CalculateAimDirection(FVector& OutAimStart, FVector& OutAimDir) const
{
	Super::CalculateAimDirection(OutAimStart, OutAimDir); // call Super so we get the PC's view dir, and then we can add bullet spread ontop of that


	// Calculate new OutAimDir with random bullet spread offset if needed
	if (CurrentBulletSpread > SMALL_NUMBER)
	{
		// Our injected random seed is only unique to each fire. We need a random seed that is also unique to each bullet in the fire, so we will do this by using t
		const int32 FireAndBulletSpecificNetSafeRandomSeed = FireSpecificNetSafeRandomSeed - ((CurrentBulletIndex + 2) * FireSpecificNetSafeRandomSeed);	// Here, the 'number' multiplied to t makes the random pattern noticable after firing 'number' of times. I use the prediction key as that 'number' which i think eliminates the threshold for noticeability entirely. - its confusing to think about but i think it works
		FMath::RandInit(FireAndBulletSpecificNetSafeRandomSeed);
		const FRandomStream RandomStream = FRandomStream(FMath::Rand());

		// Get and apply random offset to OutAimDir using randomStream
		const float ConeHalfAngleRadius = FMath::DegreesToRadians(CurrentBulletSpread * 0.5f);
		OutAimDir = RandomStream.VRandCone(OutAimDir, ConeHalfAngleRadius);
	}
}
