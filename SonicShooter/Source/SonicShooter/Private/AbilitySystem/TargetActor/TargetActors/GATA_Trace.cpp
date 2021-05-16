// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/TargetActors/GATA_Trace.h"

#include "GameFramework/PlayerController.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/TargetActor/GATDF_MultiFilter.h"
#include "Character/AbilitySystemCharacter.h"
#include "Pawn/AbilitySystemPawn.h"
#include "Actor/AbilitySystemActor.h"
#include "Utilities/SurfaceTypes.h"
#include "Algo/Reverse.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

#include "Kismet/KismetSystemLibrary.h"


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
int32 AGATA_Trace::GetPenetrations() const
{
	return 0;
}

bool AGATA_Trace::ShouldRicochetOffOf(const FHitResult& Hit) const
{
	if (const UPhysicalMaterial* HitPhysMaterial = Hit.PhysMaterial.Get())
	{
		const EPhysicalSurface HitSurfaceType = HitPhysMaterial->SurfaceType;
		if (RicochetableSurfaces.Contains(HitSurfaceType))
		{
			return true;
		}
	}

	return false;
}
void AGATA_Trace::CalculateRicochetDirection(FVector& RicoDir, const FHitResult& FromHit) const
{
	const FVector FromDir = UKismetMathLibrary::GetDirectionUnitVector(FromHit.TraceStart, FromHit.Location);
	const FVector MirroredDir = FromDir.MirrorByVector(FromHit.ImpactNormal);

	RicoDir = MirroredDir;
}


void AGATA_Trace::LineTraceMulti(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams& Params, const bool inDebug)
{
	OutHitResults.Empty();
	check(World);


	// Ensure we return Physical Material for the ricochet determination
	FCollisionQueryParams TraceParams = Params;
	TraceParams.bReturnPhysicalMaterial = true;

	// Perform initial trace
	TArray<FHitResult> HitResults;
	World->LineTraceMultiByChannel(HitResults, Start, End, TraceChannel, TraceParams);
	OutHitResults.Append(HitResults);

	TArray<FHitResult> FwdBlockingHitResults;
	if (HitResults.Num() > 0 && HitResults.Last().bBlockingHit)
	{
		FwdBlockingHitResults.Add(HitResults.Last());
	}
	// Extra traces loop
	int32 maxRicochets = GetRicochets();
	int32 timesRicocheted = 0;
	int32 maxPenetrations = GetPenetrations();
	int32 timesPenetrated = 0;
	while (true)
	{
		if (OutHitResults.Num() <= 0)
		{
			// Nothing to work with, break here
			break;
		}
		FHitResult LastHit = OutHitResults.Last();
		if (LastHit.bBlockingHit == false)
		{
			// We only ricochet and penetrate for blocking hits
			break;
		}
		
		// Ricochet
		bool bRicocheted = false;
		if (timesRicocheted < maxRicochets)
		{
			if (ShouldRicochetOffOf(LastHit))
			{
				// Calculate ricochet direction
				FVector RicoDir;
				CalculateRicochetDirection(RicoDir, LastHit);

				// Use direction to get the trace end
				FVector RicoStart = LastHit.Location + ((KINDA_SMALL_NUMBER * 100) * RicoDir);			// bump it outwards a bit for reassurance (sometimes works without this if using Chaos)
				FVector RicoEnd = RicoStart + ((GetMaxRange() - LastHit.Distance) * RicoDir);

				// Perform ricochet trace
				TArray<FHitResult> RicoHitResults; // this ricochet's hit results
				const bool bHitBlockingHit = World->LineTraceMultiByChannel(RicoHitResults, RicoStart, RicoEnd, TraceChannel, TraceParams);
				OutHitResults.Append(RicoHitResults); // add these results to the end of OutHitResults
				LastHit = OutHitResults.Last(); // update LastHit
				++timesRicocheted;

				if (RicoHitResults.Num() > 0 && RicoHitResults.Last().bBlockingHit)
				{
					FwdBlockingHitResults.Add(RicoHitResults.Last());
				}
			}
		}

		// Penetrate
		bool bPenetrated = false;
		if (timesPenetrated < maxPenetrations)
		{
			// The direction we traced from
			const FVector FromDir = UKismetMathLibrary::GetDirectionUnitVector(LastHit.TraceStart, LastHit.Location);

			// Use direction to get the trace end
			FVector PenetrateStart = LastHit.Location + ((KINDA_SMALL_NUMBER * 100) * FromDir);			// bump it into itself a bit for reassurance (sometimes works without this if using Chaos)
			FVector PenetrateEnd = PenetrateStart + ((GetMaxRange() - LastHit.Distance) * FromDir);

			// Ensure Trace Complex for this trace
			FCollisionQueryParams PenetrateParams = TraceParams;
			PenetrateParams.bTraceComplex = true; // we need bTraceComplex because we are starting from inside the geometry and shooting out (this won't work for CTF_UseSimpleAsComplex and Physics Assest colliders but we have a fallback method for them)

			// Perform penetrate trace
			TArray<FHitResult> PenetrateHitResults; // this penetration's hit results
			World->LineTraceMultiByChannel(PenetrateHitResults, PenetrateStart, PenetrateEnd, TraceChannel, PenetrateParams);
			


			// Our fallback if the trace messed up (if we hit ourselves instead of going through to the next hit). This happens if we are a CTF_UseSimpleAsComplex or a Physics Asset collider.
			if (PenetrateHitResults.Num() > 0 && PenetrateHitResults.Last().Distance == 0)
			{
				// Try again with this component ignored
				PenetrateParams.AddIgnoredComponent(PenetrateHitResults.Last().GetComponent());
				PenetrateHitResults.Empty();
				World->LineTraceMultiByChannel(PenetrateHitResults, PenetrateStart, PenetrateEnd, TraceChannel, PenetrateParams);
			}


			
			OutHitResults.Append(PenetrateHitResults); // add these results to the end of OutHitResults
			LastHit = OutHitResults.Last(); // update LastHit
			++timesPenetrated;
			bPenetrated = true;

			if (PenetrateHitResults.Num() > 0 && PenetrateHitResults.Last().bBlockingHit)
			{
				FwdBlockingHitResults.Add(PenetrateHitResults.Last());
			}
		}



		if (bRicocheted == false && bPenetrated == false)
		{
			// We weren't able to ricochet nor penetrate, stop here
			break;
		}

	}


	TArray<FBodyPenetrationInfo> Penetrations;
	BuildPenetrationInfos(Penetrations, FwdBlockingHitResults, World, TraceParams);

	for (const FBodyPenetrationInfo& Penetration : Penetrations)
	{
		UKismetSystemLibrary::PrintString(this, Penetration.DebugName + " " + "penetration distance: " + FString::SanitizeFloat(Penetration.PenetrationDistance), true, false, FLinearColor::Green, 10.f);
	}




#if ENABLE_DRAW_DEBUG
	if (inDebug)
	{
		DebugTrace(OutHitResults, World, Start, End, timesRicocheted);
	}
#endif
}

void AGATA_Trace::BuildPenetrationInfos(TArray<FBodyPenetrationInfo>& OutPenetrationInfos, const TArray<FHitResult>& FwdBlockingHits, const UWorld* World, const FCollisionQueryParams& TraceParams)  const
{
	/**
	 *
	 *						GENERAL GOAL
	 *
	 * 
	 *			OutPenetrationInfos[0]	OutPenetrationInfos[1]
	 *				|-------|				|-------|
	 * 
	 * 
	 *				_________				_________
	 *				|		|				|		|
	 *	------------O-------|---------------O-------|---------------> // forward traces
	 *				|		|				|		|
	 *	<-----------|-------O---------------|-------O---------------- // backwards traces
	 *				|		|				|		|
	 *				|		|				|		|
	 *				|		|				|		|
	 *				|		|				|		|
	 *				_________				_________
	 */

	
	FHitResult PreviousBkwdHit;
	for (int32 i = FwdBlockingHits.Num() - 1; i >= 0; --i)
	{
		const FHitResult FwdHit = FwdBlockingHits[i];

		// Get trace dir from this hit
		const FVector FwdDir = UKismetMathLibrary::GetDirectionUnitVector(FwdHit.TraceStart, FwdHit.Location);
		const FVector BkwdDir = -1 * FwdDir; // get the opposite direction

		FVector RevStart;
		FVector RevEnd;
		if (i == FwdBlockingHits.Num() - 1)
		{
			RevStart = FwdHit.TraceEnd + ((KINDA_SMALL_NUMBER * 100) * BkwdDir);
		}
		else
		{
			RevStart = PreviousBkwdHit.Location + ((KINDA_SMALL_NUMBER * 100) * BkwdDir);
		}
		RevEnd = FwdHit.Location + ((KINDA_SMALL_NUMBER * 100) * FwdDir);


		// Ensure Trace Complex for this trace
		FCollisionQueryParams RevParams = TraceParams;
		RevParams.bTraceComplex = true; // we need bTraceComplex because we are starting from inside the geometry and shooting out (this won't work for CTF_UseSimpleAsComplex and Physics Assest colliders so TODO: we will need a case that covers this)
		RevParams.bIgnoreTouches = true;

		// Perform reverse trace
		FHitResult BkwdHitResult; // this reverse trace's hit result
		const bool bHit = World->LineTraceSingleByChannel(BkwdHitResult, RevStart, RevEnd, TraceChannel, RevParams);

		// The fallback method for weird cases (may have been a non complex collision)
		bool bFallbackHit = false;
		if (bHit && BkwdHitResult.Distance == 0)
		{
			// Try again with this component ignored
			RevParams.AddIgnoredComponent(BkwdHitResult.GetComponent());
			bFallbackHit = World->LineTraceSingleByChannel(BkwdHitResult, RevStart, RevEnd, TraceChannel, RevParams);
		}

		// If the reverse trace didn't hit anything
		if (!bHit && !bFallbackHit)
		{
			// Just continue
			continue;
		}


		UPhysicalMaterial* FwdPhysMaterial = FwdBlockingHits[i].PhysMaterial.Get();
		UPhysicalMaterial* BkwdPhysMaterial = BkwdHitResult.PhysMaterial.Get();




		// ---------- Create this body's penetration info ----------
		FBodyPenetrationInfo BodyPenetrationInfo = FBodyPenetrationInfo();
		BodyPenetrationInfo.PhysMaterial = BkwdPhysMaterial;
		BodyPenetrationInfo.DebugName = BkwdHitResult.Actor.Get()->GetActorLabel();
		// ---------------------------------------------------------


		// If this is true, the left side of BkwdPhysMaterial's geometry is to the RIGHT of the left side of FwdPhysMaterial's geometry. This is the easy case
		if (FwdPhysMaterial == BkwdPhysMaterial)
		{
			// We found our correct fwd
			BodyPenetrationInfo.PenetrationDistance = FVector::Distance(BkwdHitResult.Location, FwdBlockingHits[i].Location);
			OutPenetrationInfos.Insert(BodyPenetrationInfo, 0);			// insert at the first index (instead of adding to the end) because we are looping backwards

			PreviousBkwdHit = BkwdHitResult;
			continue;
		}

		// (FwdPhysMaterial == BkwdPhysMaterial) was false, so that means the left side of BkwdPhysMaterial's geometry is to the LEFT of the left side of FwdPhysMaterial's geometry. This is the more complex case
		TArray<FHitResult> FwdBlockingHitsReversed = FwdBlockingHits;
		Algo::Reverse(FwdBlockingHitsReversed);


		// Lets pop the whole stack and compare
		while (FwdBlockingHitsReversed.Num() > 0)
		{
			FHitResult PoppedFwdHitResult = FwdBlockingHitsReversed.Pop();	// This might be our guy....
			if (PoppedFwdHitResult.PhysMaterial.Get() == BkwdPhysMaterial)
			{
				// We found our correct fwd
				BodyPenetrationInfo.PenetrationDistance = FVector::Distance(BkwdHitResult.Location, PoppedFwdHitResult.Location);
				OutPenetrationInfos.Add(BodyPenetrationInfo);	// We just add to the end in this case since the left side of BkwdPhysMaterial's geometry is to the LEFT of the left side of FwdPhysMaterial's geometry

				PreviousBkwdHit = BkwdHitResult;
				break;
			}
		}


	}
}

void AGATA_Trace::SweepMultiWithRicochets(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FQuat& Rotation, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params, const bool inDebug)
{
	check(World);


	FCollisionQueryParams TraceParams = Params;
	TraceParams.bReturnPhysicalMaterial = true;

	TArray<FHitResult> HitResults;
	World->SweepMultiByChannel(OutHitResults, Start, End, Rotation, TraceChannel, CollisionShape, TraceParams);

	OutHitResults.Append(HitResults);

	// ricochets
	uint8 r = 0; // outside for bDebug to use maybe try to change this idk
	for (r; r < GetRicochets(); ++r)
	{
		if (OutHitResults.Num() <= 0)
		{
			break;
		}
		const FHitResult LastHit = OutHitResults.Last();
		if (LastHit.bBlockingHit == false)
		{
			break;
		}
		const EPhysicalSurface LastSurface = LastHit.PhysMaterial.Get()->SurfaceType;
		if (RicochetableSurfaces.Contains(LastSurface) == false)
		{
			// This surface isn't ricochetable
			break;
		}


		// Add the current hit actor on top of the ignored actors
		FCollisionQueryParams RicoParams = TraceParams;

		// Calculate ricochet direction
		FVector RicoDir;
		CalculateRicochetDirection(RicoDir, LastHit);

		// Use direction to get the trace end
		const FVector RicoStart = LastHit.Location + (KINDA_SMALL_NUMBER * RicoDir);
		const FVector RicoEnd = RicoStart + ((GetMaxRange() - LastHit.Distance) * RicoDir);

		// Perform ricochet sweep
		TArray<FHitResult> RicoHitResults; // this ricochet's hit results
		const bool bHitBlockingHit = World->SweepMultiByChannel(RicoHitResults, RicoStart, RicoEnd, Rotation, TraceChannel, CollisionShape, RicoParams);

		OutHitResults.Append(RicoHitResults);

		if (!bHitBlockingHit)
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
		else if (GetRicochets() - timesRicocheted > 0 && timesRicocheted > 0)
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
