// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActors/STGameplayAbilityTargetActor_BulletTrace.h"

#include "BlueprintFunctionLibraries/CollisionQuery/GCBlueprintFunctionLibrary_StrengthCollisionQueries.h"
#include "BlueprintFunctionLibraries/Debugging/GCBlueprintFunctionLibrary_DrawDebugHelpersStrengthCollisionQueries.h"
#include "DrawDebugHelpers.h"
#include "Utilities/STCollisionChannels.h"
#include "AbilitySystem/Types/STGameplayAbilityTargetTypes.h"
#include "PhysicalMaterial/STPhysicalMaterial_Shooter.h"
#include "BlueprintFunctionLibraries/GCBlueprintFunctionLibrary_MathHelpers.h"
#include "AbilitySystem/Types/ASSGameplayAbilityTypes.h"
#include "GameFramework/Controller.h"
#include "Abilities/GameplayAbility.h"



ASTGameplayAbilityTargetActor_BulletTrace::ASTGameplayAbilityTargetActor_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bDebug = true;

	MaxRange = 100000.f;
	TraceChannel = COLLISIONCHANNEL_BULLET;
}

void ASTGameplayAbilityTargetActor_BulletTrace::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (!IsConfirmTargetingAllowed())
	{
		return;
	}

	// Our Target Data to broadcast
	FGameplayAbilityTargetDataHandle TargetDataHandle;

	// Do our bullet collision queries
	TArray<FRicochetingPenetrationSceneCastWithExitHitsUsingStrengthResult> BulletResults;
	BulletResults.AddDefaulted(NumOfBullets); // add the predetermined number of bullets

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bReturnPhysicalMaterial = true; // this is needed for our bullet speed nerf calculations and determining whether to ricochet
	CollisionQueryParams.AddIgnoredActor(SourceActor);
	CollisionQueryParams.bTraceComplex = true;

	// Perform each bullet collision query
	for (int32 i = 0; i < NumOfBullets; ++i)
	{
		// Calculate this bullet direction
		FVector BulletDirection = FVector::ZeroVector;
		{
			// Calculate BulletDirection
			if (IsValid(OwningAbility)) // server and launching client only
			{
				if (const FASSGameplayAbilityActorInfo* ASSActorInfo = static_cast<const FASSGameplayAbilityActorInfo*>(OwningAbility->GetCurrentActorInfo()))
				{
					FVector ViewStart;
					FRotator ViewRot;
					ASSActorInfo->Controller->GetPlayerViewPoint(ViewStart, ViewRot);
					FVector ViewDir = ViewRot.Vector();

					BulletDirection = UGCBlueprintFunctionLibrary_MathHelpers::GetLocationAimDirection(GetWorld(), CollisionQueryParams, ViewStart, ViewDir, MaxRange, StartLocation.GetTargetingTransform().GetLocation());
				}
			}

			// Calculate new BulletDirection with random bullet spread offset if needed
			if (CurrentBulletSpread > SMALL_NUMBER)
			{
				// Our injected random seed is only unique to each fire. We need a random seed that is also unique to each bullet in the fire, so we will do this by using t
				const int32 FireAndBulletSpecificNetSafeRandomSeed = FireSpecificNetSafeRandomSeed - ((i + 2) * FireSpecificNetSafeRandomSeed);	// Here, the 'number' multiplied to t makes the random pattern noticable after firing 'number' of times. I use the prediction key as that 'number' which i think eliminates the threshold for noticeability entirely. - its confusing to think about but i think it works
				FMath::RandInit(FireAndBulletSpecificNetSafeRandomSeed);
				const FRandomStream RandomStream = FRandomStream(FMath::Rand());

				// Get and apply random offset to OutAimDir using randomStream
				const float ConeHalfAngleRadius = FMath::DegreesToRadians(CurrentBulletSpread * 0.5f);
				BulletDirection = RandomStream.VRandCone(BulletDirection, ConeHalfAngleRadius);
			}
		}

		// Perform this bullet's scene query
		FCollisionShape CollisionShape = FCollisionShape::MakeSphere(1.f);
		UGCBlueprintFunctionLibrary_StrengthCollisionQueries::RicochetingPenetrationSceneCastWithExitHitsUsingStrength(InitialBulletSpeed, RangeFalloffNerf, SourceActor->GetWorld(), BulletResults[i], StartLocation.GetTargetingTransform().GetLocation(), BulletDirection, MaxRange, FQuat::Identity, TraceChannel, CollisionShape, CollisionQueryParams, FCollisionResponseParams::DefaultResponseParam, MaxRicochets,
			[](const FHitResult& Hit) -> float // GetPerCmPenetrationNerf()
			{
				const USTPhysicalMaterial_Shooter* ShooterPhysMat = Cast<USTPhysicalMaterial_Shooter>(Hit.PhysMaterial);
				if (IsValid(ShooterPhysMat))
				{
					return ShooterPhysMat->PerCmPenetrationSpeedNerf;
				}

				return 0.f;
			},
			[](const FHitResult& Hit) -> float // GetRicochetNerf()
			{
				const USTPhysicalMaterial_Shooter* ShooterPhysMat = Cast<USTPhysicalMaterial_Shooter>(Hit.PhysMaterial);
				if (IsValid(ShooterPhysMat))
				{
					return ShooterPhysMat->RicochetSpeedNerf;
				}

				return 0.f;
			},
			[](const FHitResult& Hit) -> bool // IsHitRicochetable()
			{
				const USTPhysicalMaterial_Shooter* ShooterPhysMat = Cast<USTPhysicalMaterial_Shooter>(Hit.PhysMaterial);
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

			UGCBlueprintFunctionLibrary_DrawDebugHelpersStrengthCollisionQueries::DrawStrengthDebugLine(SourceActor->GetWorld(), BulletResults[i], InitialBulletSpeed, false, DebugLifeTime, 0.f, 0.f, 1.f);
			UGCBlueprintFunctionLibrary_DrawDebugHelpersStrengthCollisionQueries::DrawStrengthDebugText(SourceActor->GetWorld(), BulletResults[i], InitialBulletSpeed, DebugLifeTime);
			UGCBlueprintFunctionLibrary_DrawDebugHelpersStrengthCollisionQueries::DrawCollisionShapeDebug(SourceActor->GetWorld(), BulletResults[i], InitialBulletSpeed, false, DebugLifeTime, 0.f, 0.f);
		}
	}


	// Create and add Target Data to our handle
	for (int32 i = 0; i < BulletResults.Num(); ++i)
	{
		FSTGameplayAbilityTargetData_BulletTraceTargetHit* ThisBulletTargetData = new FSTGameplayAbilityTargetData_BulletTraceTargetHit(); // these are cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr)

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
						FSTActorHitInfo ActorHitInfo = FSTActorHitInfo(Hit.GetActor(), Hit.Strength);
						ThisBulletTargetData->ActorHitInfos.Add(ActorHitInfo);

						if (bDebug)
						{
							// Since we know this hit actor has an ASC, we will display dmg text over its head
#if ENABLE_DRAW_DEBUG
							const float ZOffset = 10.f;

							const FBox ActorBoundingBox = Hit.GetActor()->CalculateComponentsBoundingBoxInLocalSpace(false, true);
							FVector ActorCenter;
							FVector ActorExtents;
							ActorBoundingBox.GetCenterAndExtents(ActorCenter, ActorExtents);
							ActorCenter = ActorCenter + Hit.GetActor()->GetActorLocation(); // since it is relative, add the world position so we get the world location

							FVector StringLocation = ActorCenter;
							StringLocation = StringLocation + FVector(0, 0, ActorExtents.Z + ZOffset);

							const FString DebugString = FString::Printf(TEXT("%.2f dmg"), Hit.Strength);
							DrawDebugString(GetWorld(), StringLocation, DebugString, nullptr, FColor::Red, 5.f, true, 2.f);
#endif // ENABLE_DRAW_DEBUG
							
						}
					}
				}
			}
		}

		TargetDataHandle.Add(ThisBulletTargetData);
	}

	TargetDataReadyDelegate.Broadcast(TargetDataHandle);
}
