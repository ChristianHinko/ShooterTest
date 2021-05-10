// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/TargetActors/GATA_Trace.h"

#include "GameFramework/PlayerController.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/TargetActor/GATDF_MultiFilter.h"
#include "Character/AbilitySystemCharacter.h"
#include "Pawn/AbilitySystemPawn.h"
#include "Actor/AbilitySystemActor.h"
#include "Utilities/SurfaceTypes.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"



AGATA_Trace::AGATA_Trace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentTraceIndex = -1;


	MultiFilter.bReverseFilter = true;
	MultiFilter.RequiredActorClasses.Add(AAbilitySystemCharacter::StaticClass());
	MultiFilter.RequiredActorClasses.Add(AAbilitySystemPawn::StaticClass());
	MultiFilter.RequiredActorClasses.Add(AAbilitySystemActor::StaticClass());

	bDebug = true;

	RicochetableSurfaces.Add(SURFACE_METAL);
}


void AGATA_Trace::StartTargeting(UGameplayAbility* InAbility)
{
	Super::StartTargeting(InAbility);


	SourceActor = InAbility->GetCurrentActorInfo()->AvatarActor.Get();

	if (ReticleClass)
	{
		AGameplayAbilityWorldReticle* SpawnedReticleActor = GetWorld()->SpawnActor<AGameplayAbilityWorldReticle>(ReticleClass, GetActorLocation(), GetActorRotation());
		if (SpawnedReticleActor)
		{
			SpawnedReticleActor->InitializeReticle(this, MasterPC, ReticleParams);
			ReticleActor = SpawnedReticleActor;

			// This is to catch cases of playing on a listen server where we are using a replicated reticle actor.
			// (In a client controlled player, this would only run on the client and therefor never replicate. If it runs
			// on a listen server, the reticle actor may replicate. We want consistancy between client/listen server players.
			// Just saying 'make the reticle actor non replicated' isnt a good answer, since we want to mix and match reticle
			// actors and there may be other targeting types that want to replicate the same reticle actor class).
			if (!ShouldProduceTargetDataOnServer)
			{
				SpawnedReticleActor->SetReplicates(false);
			}
		}
	}
}

void AGATA_Trace::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle TargetDataHandle;
		

		TArray<TArray<FHitResult>> TraceResults;
		PerformTraces(TraceResults, SourceActor);

		// Loop through each of our traces
		for (TArray<FHitResult>& HitResults : TraceResults)
		{
			FilterHitResults(HitResults, MultiFilterHandle, bAllowMultipleHitsPerActor);

			// Loop through this trace's hits (that have been filtered)
			for (const FHitResult& HitResult : HitResults)
			{
				/** Note: These are cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr) */
				FGameplayAbilityTargetData_SingleTargetHit* ReturnData = new FGameplayAbilityTargetData_SingleTargetHit();
				ReturnData->HitResult = HitResult;

				TargetDataHandle.Add(ReturnData);
			}
		}


		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}

void AGATA_Trace::PerformTraces(TArray<TArray<FHitResult>>& OutTraceResults, AActor* InSourceActor)
{
	OutTraceResults.Empty();

	const float NumberOfTraces = GetNumberOfTraces();

	CurrentTraceIndex = 0;
	for (CurrentTraceIndex; CurrentTraceIndex < NumberOfTraces; ++CurrentTraceIndex)
	{
		TArray<FHitResult> ThisTraceHitResults;
		PerformTrace(ThisTraceHitResults, InSourceActor);

		OutTraceResults.Add(ThisTraceHitResults);
	}
	CurrentTraceIndex = -1;


}

int32 AGATA_Trace::GetNumberOfTraces() const
{
	return 1;
}
int32 AGATA_Trace::GetRicochets() const
{
	return 0;
}

void AGATA_Trace::CalculateRicochetDirection(FVector& RicoDir, const FHitResult& FromHit) const
{
	const FVector FromDir = UKismetMathLibrary::GetDirectionUnitVector(FromHit.TraceStart, FromHit.Location);
	const FVector MirroredDir = FromDir.MirrorByVector(FromHit.ImpactNormal);

	RicoDir = MirroredDir;
}

bool AGATA_Trace::RicochetLineTrace(TArray<FHitResult>& OutHitResults, const UWorld* World, const FCollisionQueryParams Params)
{
	if (OutHitResults.Num() <= 0)
	{
		return false;
	}
	const FHitResult LastHit = OutHitResults.Last();
	if (LastHit.bBlockingHit == false)
	{
		return false;
	}

	// This ricochet's hit results
	TArray<FHitResult> RicoHitResults;

	// Add the current hit actor on top of the ignored actors
	FCollisionQueryParams RicoParams = Params;

	// Calculate ricochet direction
	FVector RicoDir;
	CalculateRicochetDirection(RicoDir, LastHit);

	// Use direction to get the trace end
	const FVector RicoStart = LastHit.Location;
	const FVector RicoEnd = RicoStart + ((GetMaxRange() - LastHit.Distance) * RicoDir);

	// Perform ricochet
	const bool bHitBlockingHit = World->LineTraceMultiByChannel(RicoHitResults, RicoStart, RicoEnd, TraceChannel, RicoParams);
	OnTraced(RicoHitResults);

	OutHitResults.Append(RicoHitResults);

	if (!bHitBlockingHit)
	{
		return false;
	}
	return true;
}
bool AGATA_Trace::RicochetSweep(TArray<FHitResult>& OutHitResults, const UWorld* World, const FQuat& Rotation, const FCollisionShape CollisionShape, const FCollisionQueryParams Params)
{
	if (OutHitResults.Num() <= 0)
	{
		return false;
	}
	const FHitResult LastHit = OutHitResults.Last();
	if (LastHit.bBlockingHit == false)
	{
		return false;
	}

	// This ricochet's hit results
	TArray<FHitResult> RicoHitResults;

	// Add the current hit actor on top of the ignored actors
	FCollisionQueryParams RicoParams = Params;

	// Calculate ricochet direction
	FVector RicoDir;
	CalculateRicochetDirection(RicoDir, LastHit);

	// Use direction to get the trace end
	const FVector RicoStart = LastHit.Location;
	const FVector RicoEnd = RicoStart + ((GetMaxRange() - LastHit.Distance) * RicoDir);

	// Perform ricochet
	const bool bHitBlockingHit = World->SweepMultiByChannel(RicoHitResults, RicoStart, RicoEnd, Rotation, TraceChannel, CollisionShape, RicoParams);
	OnTraced(RicoHitResults);

	OutHitResults.Append(RicoHitResults);

	if (!bHitBlockingHit)
	{
		return false;
	}
	return true;
}

void AGATA_Trace::LineTraceMultiWithRicochets(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams Params, const bool inDebug)
{
	check(World);

	// Initial trace (non ricochets)
	TArray<FHitResult> HitResults;
	World->LineTraceMultiByChannel(HitResults, Start, End, TraceChannel, Params);
	OnTraced(HitResults);

	OutHitResults.Append(HitResults);

	// ricochets
	uint8 r = 0; // outside for bDebug to use maybe try to change this idk
	for (r; r < GetRicochets(); ++r)
	{
		const bool bShouldContinue = RicochetLineTrace(OutHitResults, World, Params);

		if (bShouldContinue == false)
		{
			break;
		}
	}



#if ENABLE_DRAW_DEBUG
	if (inDebug)
	{
		DebugTrace(OutHitResults, World, Start, End, r);
	}
#endif
}

void AGATA_Trace::SweepMultiWithRicochets(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FQuat& Rotation, const FCollisionShape CollisionShape, const FCollisionQueryParams Params, const bool inDebug)
{
	check(World);

	TArray<FHitResult> HitResults;
	World->SweepMultiByChannel(OutHitResults, Start, End, Rotation, TraceChannel, CollisionShape, Params);
	OnTraced(HitResults);

	OutHitResults.Append(HitResults);

	// ricochets
	uint8 r = 0; // outside for bDebug to use maybe try to change this idk
	for (r; r < GetRicochets(); ++r)
	{
		const bool bShouldContinue = RicochetSweep(OutHitResults, World, Rotation, CollisionShape, Params);

		if (bShouldContinue == false)
		{
			break;
		}
	}



#if ENABLE_DRAW_DEBUG
	if (inDebug)
	{
		DebugTrace(OutHitResults, World, Start, End, r);
	}
#endif
}

//#if ENABLE_DRAW_DEBUG
void AGATA_Trace::DebugTrace(const TArray<FHitResult>& HitResults, const UWorld* World, const FVector& Start, const FVector& End, const int32 timesRicocheted) const
{
#if ENABLE_DRAW_DEBUG
	TArray<FHitResult> DebugHitResults = HitResults;
	FilterHitResults(DebugHitResults, FGATDF_MultiFilterHandle(), bAllowMultipleHitsPerActor); // removes multiple hits if needed (but doesn't filter actors because we have different colors for whether it filters or not)


	const float debugLifeTime = 5.f;
	const FColor TraceColor = FColor::Blue;
	const FColor PassesFilterColor = FColor::Red;

	const uint8 hitsNum = DebugHitResults.Num();
	if (hitsNum > 0)
	{
		for (int32 i = 0; i < DebugHitResults.Num(); ++i)
		{
			const FHitResult Hit = DebugHitResults[i];
			const FVector FromLocation = Hit.TraceStart;
			const FVector ToLocation = Hit.Location;

			DrawDebugLine(World, FromLocation, ToLocation, TraceColor, false, debugLifeTime);

			const bool bPassesFilter = MultiFilterHandle.FilterPassesForActor(Hit.Actor);
			if (bPassesFilter)
			{
				DrawDebugPoint(World, Hit.ImpactPoint, 10, PassesFilterColor, false, debugLifeTime);
			}
			else
			{
				DrawDebugPoint(World, Hit.ImpactPoint, 10, TraceColor, false, debugLifeTime);
			}
		}
		if (DebugHitResults.Last().bBlockingHit == false)
		{
			DrawDebugLine(World, DebugHitResults.Last().Location, DebugHitResults.Last().TraceEnd, TraceColor, false, debugLifeTime);		// after the we've drawn a line to all hit results, draw from last hit result to the trace end
		}
		else if (GetRicochets() - timesRicocheted > 0)
		{
			const FVector TracedDir = UKismetMathLibrary::GetDirectionUnitVector(DebugHitResults.Last().TraceStart, DebugHitResults.Last().TraceEnd);
			const FVector MirroredDir = TracedDir.MirrorByVector(DebugHitResults.Last().ImpactNormal);

			const FVector RicoStart = DebugHitResults.Last().Location;
			const FVector RicoEnd = RicoStart + ((GetMaxRange() - DebugHitResults.Last().Distance) * MirroredDir);

			DrawDebugLine(World, RicoStart, RicoEnd, TraceColor, false, debugLifeTime);
		}
	}
	else // if we've traced in thin air
	{
		DrawDebugLine(World, Start, End, TraceColor, false, debugLifeTime);
	}
#endif // ENABLE_DRAW_DEBUG
}
//#endif // ENABLE_DRAW_DEBUG


void AGATA_Trace::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ReticleActor.IsValid())
	{
		ReticleActor.Get()->Destroy();
	}


	Super::EndPlay(EndPlayReason);
}
