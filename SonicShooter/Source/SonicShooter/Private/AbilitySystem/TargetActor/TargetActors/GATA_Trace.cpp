// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/TargetActors/GATA_Trace.h"

#include "GameFramework/PlayerController.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/TargetActor/GATDF_MultiFilter.h"
#include "Character/AbilitySystemCharacter.h"
#include "Pawn/AbilitySystemPawn.h"
#include "Actor/AbilitySystemActor.h"
#include "Utilities/SurfaceTypes.h"
#include "Utilities/LogCategories.h"
#include "Utilities/BlueprintFunctionLibraries/BFL_MaterialHelpers.h"
#include "Utilities/BlueprintFunctionLibraries/BFL_HitResultHelpers.h"

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

	TArray<FHitResult> ThisRicochetBlockingHits;
	TArray<FSectionPenetrationInfo> Penetrations;

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

		if (!ShouldRicochetOffOf(LastHit))
		{
			// Only add to this if we are not ricochetable. (If we were, this array would get reset for the next ricochet hits)
			ThisRicochetBlockingHits.Add(LastHit);
		}


		// Ricochet
		bool bRicocheted = false;
		if (ShouldRicochetOffOf(LastHit))
		{
			if (timesRicocheted < maxRicochets)
			{
				// We are about to ricochet so calculate Penetrations for these blocking Hits before we move on to the next ricochet
				TArray<FSectionPenetrationInfo> ThisRicochetPenetrations;
				BuildPenetrationInfos(ThisRicochetPenetrations, ThisRicochetBlockingHits, LastHit.Location, World, TraceParams);
				Penetrations.Append(ThisRicochetPenetrations);
				ThisRicochetBlockingHits.Empty(); // we are about to begin our next ricochet so reset the blocking Hit Results for next ricochet





				// Calculate ricochet direction
				FVector RicoDir;
				CalculateRicochetDirection(RicoDir, LastHit);

				// Use direction to get the trace end
				FVector RicoStart = LastHit.Location + ((KINDA_SMALL_NUMBER * 100) * RicoDir);			// bump it outwards a bit for reassurance (sometimes works without this if using Chaos)
				FVector RicoEnd = RicoStart + ((GetMaxRange() - LastHit.Distance) * RicoDir);

				// Perform ricochet trace
				TArray<FHitResult> RicoHitResults; // this ricochet's hit results
				World->LineTraceMultiByChannel(RicoHitResults, RicoStart, RicoEnd, TraceChannel, TraceParams);
				


				if (RicoHitResults.Num() > 0)
				{
					OutHitResults.Append(RicoHitResults); // add these results to the end of OutHitResults
					LastHit = OutHitResults.Last(); // update LastHit
					++timesRicocheted;
					bRicocheted = true;
				}
			}



			if (bRicocheted == false)
			{
				// We should've ricocheted but didn't so stop here. (we don't want to proceed to penetration logic on ricochetable surfaces).
				// Possible ways of getting to this point:
				//		1. This ricochet didn't hit anything
				//		2. We ran out of ricochets / speed
				break;
			}
		}

		if (bRicocheted)
		{
			// Continue here because we always want to check whether we should ricochet first before we try to penetrate.
			// For example. If we ricocheted, and then hit another surface that can be ricocheted off of, we want to run ricochet logic on that. If we don't continue here, the penetration logic below would run on that ricochetable surface instead of ricochet logic
			continue;
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

			FCollisionQueryParams PenetrateParams = TraceParams;
			PenetrateParams.bTraceComplex = true; // Use complex collision if the collider has it. We need this because we are starting from inside the geometry and shooting out (this won't work for CTF_UseSimpleAsComplex and Physics Assest colliders so TODO: we will need a case that covers this)
			PenetrateParams.bReturnFaceIndex = true;

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


			
			if (PenetrateHitResults.Num() > 0)
			{
				OutHitResults.Append(PenetrateHitResults); // add these results to the end of OutHitResults
				LastHit = OutHitResults.Last(); // update LastHit
				++timesPenetrated;
				bPenetrated = true;
			}
		}



		if (bRicocheted == false && bPenetrated == false)
		{
			// We weren't able to ricochet nor penetrate, stop here
			break;
		}

	}

	if (ThisRicochetBlockingHits.Num() > 0)
	{
		TArray<FSectionPenetrationInfo> ThisRicochetPenetrations;
		BuildPenetrationInfos(ThisRicochetPenetrations, ThisRicochetBlockingHits, ThisRicochetBlockingHits.Last().TraceEnd, World, TraceParams);
		Penetrations.Append(ThisRicochetPenetrations);
		ThisRicochetBlockingHits.Empty();
	}





#if ENABLE_DRAW_DEBUG
	if (inDebug)
	{
		for (const FSectionPenetrationInfo& Penetration : Penetrations)
		{
			UKismetSystemLibrary::PrintString(this, Penetration.DebugName + "    " + "penetration distance: " + FString::SanitizeFloat(Penetration.PenetrationDistance), true, false, FLinearColor::Green, 10.f);
		}
		DebugTrace(OutHitResults, World, Start, End, timesRicocheted);
	}
#endif
}

void AGATA_Trace::BuildPenetrationInfos(TArray<FSectionPenetrationInfo>& OutPenetrationInfos, const TArray<FHitResult>& FwdBlockingHits, const FVector& FwdEndLocation, const UWorld* World, const FCollisionQueryParams& TraceParams)  const
{
	OutPenetrationInfos.Empty();

	/**
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
	 *
	 *		We can simplify this concept by visualizing it in 2d
	 */


	TArray<FHitResult> BkwdBlockingHits;	// For loop will create this BkwdBlockingHits arr
	FVector BkwdStart;
	for (int32 i = FwdBlockingHits.Num() - 1; i >= 0; --i)
	{
		const FHitResult FwdHit = FwdBlockingHits[i];

		// Get trace dir from this hit
		const FVector FwdDir = UKismetMathLibrary::GetDirectionUnitVector(FwdHit.TraceStart, FwdHit.Location);
		const FVector BkwdDir = -1 * FwdDir; // get the opposite direction

		FVector BkwdEnd;
		if (i == FwdBlockingHits.Num() - 1)
		{
			BkwdStart = FwdEndLocation + ((KINDA_SMALL_NUMBER * 100) * BkwdDir);
		}
		BkwdEnd = FwdHit.Location + ((KINDA_SMALL_NUMBER * 100) * FwdDir);


		






		FCollisionQueryParams BkwdParams = TraceParams;
		BkwdParams.bTraceComplex = true; // Use complex collision if the collider has it. We need this because we are starting from inside the geometry and shooting out (this won't work for CTF_UseSimpleAsComplex and Physics Assest colliders so TODO: we will need a case that covers this)
		BkwdParams.bReturnFaceIndex = true;
		BkwdParams.bIgnoreTouches = true;


		// Perform backwards trace
		FHitResult BkwdHitResult;
		const bool bFirstTraceHit = World->LineTraceSingleByChannel(BkwdHitResult, BkwdStart, BkwdEnd, TraceChannel, BkwdParams);
		if (!bFirstTraceHit)
		{
			continue;	// we've either reached the end or we just didn't hit anything because we started inside the geometry
		}


		if (bFirstTraceHit && BkwdHitResult.Distance != 0)	// This is a correct and successful backwards trace
		{
			BkwdBlockingHits.Insert(BkwdHitResult, 0);
			BkwdStart = BkwdHitResult.Location + ((KINDA_SMALL_NUMBER * 100) * BkwdDir);
			continue;
		}



		// Unsuccessful backwards trace (we didn't travel anywhere but hit something)
		// Likely reason: It's stuck inside a collider that's using simple collision
		
		// Fallback method...........
		// Try again with this component (collider) ignored
		BkwdParams.AddIgnoredComponent(BkwdHitResult.GetComponent());
		bool bFallbackTraceHit = World->LineTraceSingleByChannel(BkwdHitResult, BkwdStart, BkwdEnd, TraceChannel, BkwdParams);
		if (bFallbackTraceHit)
		{
			BkwdBlockingHits.Insert(BkwdHitResult, 0);
			BkwdStart = BkwdHitResult.Location + ((KINDA_SMALL_NUMBER * 100) * BkwdDir);
		}
	}




	// Lets finaly build our OutPenetrationInfos
	/*
	*	We will make use of sections to be specific enough to know what parts of a mesh should be penetrated in certain ways.
	*	A section has a material associated with it and that material stores the physical material so this is how we can know how to
	*	penetrate that part of the mesh. Since we don't have pointers to sections to work with, we will use the section index associated with
	*	a pointer to the primitive component that has that section. This fixes the problem of having reoccuring section indexes in the case where
	*	there are multible primative components. To differentiate between them we can use the primative component pointer.
	*
	*	(As an update, I did find that you could just get the section index's pointer, but I left it this way for now since I was unsure if that makes it less genaric or not since I noticed there was a cast to UStaticMesh in order to retrieve the pointer)
	*/
	for (int32 i = 0; i < FwdBlockingHits.Num(); ++i)
	{
		// Get detaled information about the wall/object we hit going forward at index [i]
		UPrimitiveComponent* PrimitiveComponentPenetrated = nullptr;
		int32 sectionIndexPenetrated = -1;
		UBFL_HitResultHelpers::GetSectionLevelHitInfo(FwdBlockingHits[i], PrimitiveComponentPenetrated, sectionIndexPenetrated);
		
		// ------ Create this section's penetration info from what we know so far ------
		FSectionPenetrationInfo PenetrationInfo;
		PenetrationInfo.PenetratedSectionIndex = sectionIndexPenetrated;
		PenetrationInfo.PenetratedPhysicsMaterial = FwdBlockingHits[i].PhysMaterial.Get();
		PenetrationInfo.EntrancePoint = FwdBlockingHits[i].ImpactPoint;
		PenetrationInfo.DebugName = "Actor: " + FwdBlockingHits[i].Actor.Get()->GetActorLabel() + "    Component: " + PrimitiveComponentPenetrated->GetName();
		// ------------------------------------------------------------------------------




		// Now time to find the other side of this Fwd Hit's section


		// Loop through every Bkwd Blocking Hit until we find the same section that belongs to the same primative component
		bool bPaired = false;
		for (int32 j = 0; j < BkwdBlockingHits.Num(); ++j)
		{
			// Get detaled information about the wall/object we hit going backward at index [i]
			UPrimitiveComponent* TestAgainstPrimitiveComponent = nullptr;
			int32 testAgainstSectionIndex = -1;
			UBFL_HitResultHelpers::GetSectionLevelHitInfo(BkwdBlockingHits[j], TestAgainstPrimitiveComponent, testAgainstSectionIndex);

			if (PrimitiveComponentPenetrated == TestAgainstPrimitiveComponent && sectionIndexPenetrated == testAgainstSectionIndex)
			{
				// We found the other side of the specific section we are penetrating
				PenetrationInfo.ExitPoint = BkwdBlockingHits[j].Location;
				PenetrationInfo.PenetrationDistance = FVector::Distance(PenetrationInfo.EntrancePoint, PenetrationInfo.ExitPoint);
				OutPenetrationInfos.Add(PenetrationInfo);
				BkwdBlockingHits.RemoveAt(j); // we've just paired this index of BkwdBlockingHits with us so remove it so other FwdBlockingHits don't try to pair themselves with it
				bPaired = true;
				break;
			}
		}
		if (bPaired)
		{
			// This Fwd Blocking Hit has been paired up with a Bkwd Blocking Hit, continue to the next one
			continue;
		}

		// If we end up here, that means this Fwd Blocking Hit was not able to be paired with any BkwdBlockingHits


		// Just give the distance between this Fwd Blocking Hit and the FwdEndLocation because we probably began the Bkwd trace starting from the inside the geometry
		PenetrationInfo.PenetrationDistance = FVector::Distance(FwdBlockingHits[i].Location, FwdEndLocation);
		OutPenetrationInfos.Add(PenetrationInfo);

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
