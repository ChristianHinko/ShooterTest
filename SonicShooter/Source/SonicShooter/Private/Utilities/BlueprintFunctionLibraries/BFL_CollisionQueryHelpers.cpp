// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/BlueprintFunctionLibraries/BFL_CollisionQueryHelpers.h"

#include "Utilities/LogCategories.h"
#include "Kismet/KismetMathLibrary.h"
#include "Algo/Reverse.h"



void UBFL_CollisionQueryHelpers::BuildPenetrationInfos(TArray<FPenetrationInfo>& OutPenetrationInfos, const TArray<FHitResult>& FwdBlockingHits, const UWorld* World, const FCollisionQueryParams& TraceParams, const TEnumAsByte<ECollisionChannel> TraceChannel)
{
	OutPenetrationInfos.Empty();

	if (FwdBlockingHits.Num() <= 0)
	{
		UE_LOG(LogBlueprintFunctionLibrary, Warning, TEXT("%s(): Wasn't given any FwdBlockingHits to build any penetration info of. Returned and did nothing"), *FString(__FUNCTION__));
		return;
	}



	// This is the furthest possible FwdEndLocation for the given FwdBlockingHits
	FVector FurthestPossibleEnd;

	// Calculate the FurthestPossibleEnd point out of these FwdBlockingHits
	{
		const FVector TracedDir = UKismetMathLibrary::GetDirectionUnitVector(FwdBlockingHits[0].TraceStart, FwdBlockingHits[0].TraceEnd);
		
		float currentFurthestPossibleSize = 0.f;
		for (const FHitResult& Hit : FwdBlockingHits)
		{
			if (Hit.Component.IsValid() == false)
			{
				continue;
			}

			// The Impact Point plus the bounding diameter
			const FVector ThisHitFurthestPossibleEnd = Hit.ImpactPoint + (TracedDir * (Hit.Component.Get()->Bounds.SphereRadius * 2));

			// If this ThisHitFurthestPossibleEnd is further than our current FurthestPossibleEnd then update FurthestPossibleEnd
			const float thisHitFurthestPossibleSize = (ThisHitFurthestPossibleEnd - FwdBlockingHits[0].TraceStart).SizeSquared();
			if (thisHitFurthestPossibleSize > currentFurthestPossibleSize)
			{
				FurthestPossibleEnd = ThisHitFurthestPossibleEnd;
				currentFurthestPossibleSize = thisHitFurthestPossibleSize;
			}

		}

		// Bump out a little because the BuildPenetrationInfos() will bump us in a little
		FurthestPossibleEnd += (TracedDir * ((KINDA_SMALL_NUMBER * 100) * 2));
	}


	// Use this FurthestPossibleEnd as a Bkwd trace start location
	BuildPenetrationInfos(OutPenetrationInfos, FwdBlockingHits, FurthestPossibleEnd, World, TraceParams, TraceChannel);
}

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
		UE_LOG(LogBlueprintFunctionLibrary, Warning, TEXT("%s(): Wasn't given any FwdBlockingHits to build any penetration info of. Returned and did nothing"), *FString(__FUNCTION__));
		return;
	}
	OutPenetrationInfos.Reserve(FwdBlockingHits.Num() * 2);		// We know most of the time we will have at least double the elements from FwdBlockingHits (most of the time)


	const FVector FwdStartLocation = FwdBlockingHits[0].TraceStart; // maybe make this a parameter since FwdEndLocation is one


	TArray<UPhysicalMaterial*> CurrentEntrancePhysMaterials;		// These don't point to a specific instance of a phys material in the game (not possible). They just point to the type.

	// TODO: document
	{
		FCollisionQueryParams BkwdParams = TraceParams;
		BkwdParams.bIgnoreTouches = true; // we only care about blocking hits

		
		for (int32 i = -1; i < FwdBlockingHits.Num(); ++i)
		{
			//const FHitResult& ThisFwdBlockingHit = FwdBlockingHits[i];

			FVector BkwdStart;
			if (FwdBlockingHits.IsValidIndex(i + 1))
			{
				BkwdStart = FwdBlockingHits[i + 1].Location;
			}
			else
			{
				BkwdStart = FwdEndLocation;
			}
			FVector BkwdEnd;
			if (i == -1)
			{
				BkwdEnd = FwdStartLocation;
			}
			else
			{
				BkwdEnd = FwdBlockingHits[i].ImpactPoint; // NOTE: this would be weird for collision sweeps
			}



			if (i != -1)
			{
				// This stack tells us how deep we are and provides us with the phys materials of the entrance hits
				CurrentEntrancePhysMaterials.Push(FwdBlockingHits[i].PhysMaterial.Get());
			}


			TArray<FHitResult> BkwdHitResults;
			LineTracePenetrateBetweenPoints(BkwdHitResults, World, BkwdStart, BkwdEnd, TraceChannel, BkwdParams);
			Algo::Reverse<TArray<FHitResult>>(BkwdHitResults);


			{
				FPenetrationInfo PenetrationInfo; // the Penetration Info we will make for this distance we just traced
				PenetrationInfo.EntrancePoint = (i == -1) ? BkwdEnd : FwdBlockingHits[i].ImpactPoint;
				PenetrationInfo.ExitPoint = (BkwdHitResults.Num() > 0) ? BkwdHitResults[0].ImpactPoint : BkwdStart;
				PenetrationInfo.PenetrationDistance = FVector::Distance(PenetrationInfo.EntrancePoint, PenetrationInfo.ExitPoint);
				PenetrationInfo.PenetratedPhysMaterials = CurrentEntrancePhysMaterials;

				OutPenetrationInfos.Emplace(PenetrationInfo);
			}

			for (const FHitResult& BkwdHit : BkwdHitResults)
			{

				// Remove this Phys Mat from the Phys Mat stack because we are exiting it
				UPhysicalMaterial* PhysMatThatWeAreExiting = BkwdHit.PhysMaterial.Get();
				int32 IndexOfPhysMatThatWeAreExiting = CurrentEntrancePhysMaterials.FindLast(PhysMatThatWeAreExiting); // the inner-most (last) occurrence of this Phys Mat is the one that we are exiting
				if (IndexOfPhysMatThatWeAreExiting != INDEX_NONE)
				{
					CurrentEntrancePhysMaterials.RemoveAt(IndexOfPhysMatThatWeAreExiting); // remove this Phys Mat that we are exiting from the Phys Mat stack
				}
				else
				{
					// We've just realized that we have been inside of something from the start (because we just exited something that we've never entered).
					// Add this something to all of the Penetrations we have made so far
					for (FPenetrationInfo& PenetrationInfoToAddTo : OutPenetrationInfos)
					{
						PenetrationInfoToAddTo.PenetratedPhysMaterials.Insert(PhysMatThatWeAreExiting, 0); // insert at the bottom
					}
				}


				FPenetrationInfo PenetrationInfo; // the Penetration Info we will make for this distance we just traced
				PenetrationInfo.EntrancePoint = BkwdHit.ImpactPoint;
				PenetrationInfo.ExitPoint = BkwdHit.TraceStart;
				PenetrationInfo.PenetrationDistance = FVector::Distance(PenetrationInfo.EntrancePoint, PenetrationInfo.ExitPoint);
				PenetrationInfo.PenetratedPhysMaterials = CurrentEntrancePhysMaterials;


				OutPenetrationInfos.Emplace(PenetrationInfo);



			}


		}

	}



}

void UBFL_CollisionQueryHelpers::LineTracePenetrateBetweenPoints(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const ECollisionChannel TraceChannel, const FCollisionQueryParams& Params)
{
	OutHitResults.Empty();




	FCollisionQueryParams PenParams = Params;
	PenParams.bTraceComplex = true; // Use complex collision if the collider has it. We need this because we are starting from inside the geometry and shooting out (this won't work for CTF_UseSimpleAsComplex and Physics Assest colliders so TODO: we will need a case that covers this)


	// Get trace dir from this hit
	const FVector FwdDir = UKismetMathLibrary::GetDirectionUnitVector(Start, End);
	const FVector BkwdDir = -1 * FwdDir; // get the opposite direction


	FVector PenStart = Start + ((KINDA_SMALL_NUMBER * 100) * FwdDir);
	FVector PenEnd = End + ((KINDA_SMALL_NUMBER * 100) * BkwdDir);


	// Penetrate traces loop
	for (FHitResult PenHitResult; World->LineTraceSingleByChannel(PenHitResult, PenStart, PenEnd, TraceChannel, PenParams); PenStart = PenHitResult.Location + ((KINDA_SMALL_NUMBER * 100) * FwdDir))
	{
		if (PenHitResult.Distance == 0)	// If the trace messed up
		{
			// Unsuccessful backwards trace (we didn't travel anywhere but hit something)
			// Likely reason: It's stuck inside a collider that's using simple collision


			// Fallback method...........
			// Try again with this component (collider) ignored so we can move on
			uint8 amtOfFallbackTracesToTry = 5;
			if (amtOfFallbackTracesToTry > 0)
			{
				bool bFallbackMethodReachedBkwdEnd = false;
				FCollisionQueryParams FallbackQueryParams = Params;
				for (uint8 j = 0; j < amtOfFallbackTracesToTry; j++)
				{
					FallbackQueryParams.AddIgnoredComponent(PenHitResult.GetComponent());	// ignore our last trace's blocking hit
					if (!World->LineTraceSingleByChannel(PenHitResult, PenStart, PenEnd, TraceChannel, FallbackQueryParams))
					{
						//	We want to stop doing fallback traces since we are at the end of our bkwd trace now (the beginning of our fwd traces)
						//	We will also tell the outer loop to break as well by setting this bool
						bFallbackMethodReachedBkwdEnd = true;
						break;
					}
					// If we did hit something.....

					if (PenHitResult.Distance == 0)	// if the distance is still 0, we will keep trying again until loop ends
					{
						continue;
					}
					else
					{
						break;
					}
				}


				if (bFallbackMethodReachedBkwdEnd)
				{
					break;		// Fallback method broke the loop since it reached BkwdEnd
				}
			}
		}





		OutHitResults.Emplace(PenHitResult);


	}

}
