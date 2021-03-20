// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h"

#include "Abilities/GameplayAbility.h"
#include "Utilities/CollisionChannels.h"
#include "AbilitySystem/SSGameplayAbilityTargetTypes.h"


AGATA_BulletTrace::AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TraceChannel = COLLISION_BULLET;
	NumberOfBullets = 1;
	BulletSpread = 0.f;
}

void AGATA_BulletTrace::ConfirmTargetingAndContinue()
{
	// Same as super, but we make our own target data handle since we want to use our bullet trace one
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		TArray<FHitResult> HitResults;
		PerformTrace(HitResults, SourceActor);
		FGameplayAbilityTargetDataHandle TargetDataHandle;
		
		// For loop code copied from FGameplayAbilityTargetingLocationInfo::MakeTargetDataHandleFromHitResults. Not using that function to make target data handle because it uses FGameplayAbilityTargetData_SingleTargetHit and not our custom target data struct FGameplayAbilityTargetData_BulletTraceTargetHit
		for (int32 i = 0; i < HitResults.Num(); i++)
		{
			/** Note: These are cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr) */
			FGameplayAbilityTargetData_BulletTraceTargetHit* ReturnData = new FGameplayAbilityTargetData_BulletTraceTargetHit();
			ReturnData->HitResult = HitResults[i];
			TargetDataHandle.Add(ReturnData);
		}

		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}

void AGATA_BulletTrace::PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor)
{
	const bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(InSourceActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGATA_BulletTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	const FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();

	// ------------------------------------------------------

	for (uint8 t = 0; t < NumberOfBullets; ++t)
	{
		// Get direction player is aiming
		FVector AimDir;
		DirWithPlayerController(InSourceActor, Params, TraceStart, AimDir);		//Effective on server and launching client only

		// Calculate new AimDir with random bullet spread offset if needed
		if (BulletSpread > SMALL_NUMBER)
		{
			// Our injected random seed is only unique to each fire. We need a random seed that is also unique to each bullet in the fire, so we will do this by using t
			const int32 fireAndBulletSpecificNetSafeRandomSeed = FireSpecificNetSafeRandomSeed - ((t + 2) * FireSpecificNetSafeRandomSeed);	// Here, the 'number' multiplied to t makes the random pattern noticable after firing 'number' of times. I use the prediction key as that 'number' which i think eliminates the threshold for noticeability entirely. - its confusing to think about but i think it works
			FMath::RandInit(fireAndBulletSpecificNetSafeRandomSeed);
			const FRandomStream RandomStream = FRandomStream(FMath::Rand());

			// Add random offset to AimDir using randomStream
			const float coneHalfAngleRadius = FMath::DegreesToRadians(BulletSpread * 0.5f);
			AimDir = RandomStream.VRandCone(AimDir, coneHalfAngleRadius);
		}

		// Calculate the end of the trace based off aim dir and max range
		const FVector TraceEnd = TraceStart + (AimDir * MaxRange);

		// Perform line trace 
		TArray<FHitResult> ShotHitResults;
		LineTraceMultiWithFilter(ShotHitResults, InSourceActor->GetWorld(), TraceStart, TraceEnd, Params, bDebug);
		

		// Add this bullet's hit results to the final hit results
		OutHitResults.Append(ShotHitResults);
	}
}
