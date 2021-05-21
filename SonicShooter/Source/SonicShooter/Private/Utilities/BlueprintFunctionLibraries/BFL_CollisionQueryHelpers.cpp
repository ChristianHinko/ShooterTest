// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"

#include "Utilities/SurfaceTypes.h"
#include "Utilities/LogCategories.h"
#include "Kismet/KismetMathLibrary.h"



void UBFL_CollisionQueryHelpers::BuildPenetrationInfos(TArray<FPenetrationInfo>& OutPenetrationInfos, const TArray<FHitResult>& FwdBlockingHits, const FVector& FwdEndLocation, const UWorld* World, const FCollisionQueryParams& TraceParams, const TEnumAsByte<ECollisionChannel> TraceChannel)
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

	if (FwdBlockingHits.Num() <= 0)
	{
		return;
	}

	const FVector FwdStartLocation = FwdBlockingHits[0].TraceStart; // maybe make this a parameter since FwdEndLocation is one


	TArray<FPenetrationHitResult> PenetrationHitResults;

	// Bkwd traces loop. This fills up our PenetrationHitResults
	{
		// Get trace dir from this hit
		const FVector FwdDir = UKismetMathLibrary::GetDirectionUnitVector(FwdStartLocation, FwdEndLocation);
		const FVector BkwdDir = -1 * FwdDir; // get the opposite direction


		FVector BkwdStart = FwdEndLocation + ((KINDA_SMALL_NUMBER * 100) * BkwdDir);
		FVector BkwdEnd = FwdStartLocation + ((KINDA_SMALL_NUMBER * 100) * FwdDir);


		FCollisionQueryParams BkwdParams = TraceParams;
		BkwdParams.bTraceComplex = true; // Use complex collision if the collider has it. We need this because we are starting from inside the geometry and shooting out (this won't work for CTF_UseSimpleAsComplex and Physics Assest colliders so TODO: we will need a case that covers this)
		BkwdParams.bIgnoreTouches = true;


		int32 NextFwdBlockingHitToInsert = FwdBlockingHits.Num() - 1;
		for (FHitResult BkwdHitResult; World->LineTraceSingleByChannel(BkwdHitResult, BkwdStart, BkwdEnd, TraceChannel, BkwdParams); BkwdStart = BkwdHitResult.Location + ((KINDA_SMALL_NUMBER * 100) * BkwdDir))
		{
			// If the trace messed up
			if (BkwdHitResult.Distance == 0)
			{
				// Unsuccessful backwards trace (we didn't travel anywhere but hit something)
				// Likely reason: It's stuck inside a collider that's using simple collision

				// Fallback method...........
				// Try again with this component (collider) ignored
				FCollisionQueryParams FallbackQueryParams = TraceParams;
				FallbackQueryParams.AddIgnoredComponent(BkwdHitResult.GetComponent());

				if (!World->LineTraceSingleByChannel(BkwdHitResult, BkwdStart, BkwdEnd, TraceChannel, FallbackQueryParams))
				{
					// Our fallback didn't hit anything, stop here
					break;
				}
			}


			// Loop to fill PenetrationHitResults
			for (int32 i = NextFwdBlockingHitToInsert; i >= 0; --i)
			{
				const FHitResult FwdBlockingHit = FwdBlockingHits[i];

				// We want to add the after-most hits first (both the Fwd and Bkwd hits)
				const FVector BkwdToFwd = (FwdBlockingHit.ImpactPoint - BkwdHitResult.ImpactPoint);
				const bool bIsAfterFwd = (FVector::DotProduct(BkwdToFwd, FwdDir) <= 0); // if this BkwdHitResult is after FwdBlockingHit
				if (bIsAfterFwd)
				{
					// Add this Bkwd result
					PenetrationHitResults.Insert(FPenetrationHitResult(BkwdHitResult, false), 0);
					break; // break here because we need our next Bkwd hit
				}
				else
				{
					// Add this Fwd result
					PenetrationHitResults.Insert(FPenetrationHitResult(FwdBlockingHit, true), 0);
					--NextFwdBlockingHitToInsert; // make it so next time, we only look at the Fwd Blocking Hits before this one we just inserted
					continue;
				}

			}

		}

		// Loop to finish filling PenetrationHitResults
		for (int32 i = NextFwdBlockingHitToInsert; i >= 0; --i)
		{
			const FHitResult FwdBlockingHit = FwdBlockingHits[i];

			// Add this Fwd result
			PenetrationHitResults.Insert(FPenetrationHitResult(FwdBlockingHit, true), 0);
		}

	}


	TArray<UPhysicalMaterial*> CurrentEntrancePhysMaterials;
	FPenetrationHitResult* PenetrationHitResultToStartAt = nullptr;
	for (FPenetrationHitResult& CurrentPenetrationHitResult : PenetrationHitResults)
	{
		if (CurrentPenetrationHitResult.bIsEntrance)
		{
			// This stack tells us how deep we are and provides us with the phys materials of the entrance hits
			CurrentEntrancePhysMaterials.Push(CurrentPenetrationHitResult.HitResult.PhysMaterial.Get());
		}


		if (CurrentEntrancePhysMaterials.Num() > 0 && PenetrationHitResultToStartAt)	// If true, we should calculate a distance and create a new PenetrationInfo
		{
			FPenetrationInfo PenetrationInfo;
			PenetrationInfo.EntrancePoint = PenetrationHitResultToStartAt->HitResult.ImpactPoint;
			PenetrationInfo.ExitPoint = CurrentPenetrationHitResult.HitResult.ImpactPoint;
			PenetrationInfo.PenetrationDistance = FVector::Distance(PenetrationInfo.EntrancePoint, PenetrationInfo.ExitPoint);
			if (CurrentPenetrationHitResult.bIsEntrance)
			{
				for (int32 i = 0; i < CurrentEntrancePhysMaterials.Num() - 1; ++i)
				{
					PenetrationInfo.PenetratedPhysMaterials.Add(CurrentEntrancePhysMaterials[i]);
				}
			}
			else
			{
				for (int32 i = 0; i < CurrentEntrancePhysMaterials.Num(); ++i)
				{
					PenetrationInfo.PenetratedPhysMaterials.Add(CurrentEntrancePhysMaterials[i]);
				}

				// Remove this Phys Mat from the Phys Mat stack because we are exiting it
				UPhysicalMaterial* PhysMatThatWeAreExiting = CurrentPenetrationHitResult.HitResult.PhysMaterial.Get();
				int32 IndexOfPhysMatThatWeAreExiting = CurrentEntrancePhysMaterials.FindLast(PhysMatThatWeAreExiting); // the inner-most (last) occurrence of this Phys Mat is the one that we are exiting
				if (IndexOfPhysMatThatWeAreExiting != INDEX_NONE)
				{
					CurrentEntrancePhysMaterials.RemoveAt(IndexOfPhysMatThatWeAreExiting); // remove this Phys Mat that we are exiting from the Phys Mat stack
				}
			}

			OutPenetrationInfos.Add(PenetrationInfo);
		}

		// This gives PenetrationHitResultToStartAt its correct value. This is basicly just a "PreviousPenetrationHitResult" variable, but is NULL whenever we don't want to make a FPenetrationInfo (because we are in an empty space)
		if (CurrentEntrancePhysMaterials.Num() > 0)
		{
			PenetrationHitResultToStartAt = &CurrentPenetrationHitResult;
		}
		else
		{
			PenetrationHitResultToStartAt = nullptr;
		}
	}


	if (CurrentEntrancePhysMaterials.Num() > 0)
	{
		check(OutPenetrationInfos.Num() > 0); // i have no idea when this would be false but just in case. also we should UE_LOG this when we log up this function
		

		FPenetrationInfo PenetrationInfo;
		PenetrationInfo.EntrancePoint = OutPenetrationInfos.Last().ExitPoint;
		PenetrationInfo.ExitPoint = FwdEndLocation;
		PenetrationInfo.PenetrationDistance = FVector::Distance(PenetrationInfo.EntrancePoint, PenetrationInfo.ExitPoint);

		for (int32 i = 0; i < CurrentEntrancePhysMaterials.Num(); ++i)
		{
			PenetrationInfo.PenetratedPhysMaterials.Add(CurrentEntrancePhysMaterials[i]);
		}
		CurrentEntrancePhysMaterials.Empty();


		OutPenetrationInfos.Add(PenetrationInfo);
	}

}
