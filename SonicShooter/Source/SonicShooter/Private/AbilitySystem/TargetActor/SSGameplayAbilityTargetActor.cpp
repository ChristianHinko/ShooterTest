// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/SSGameplayAbilityTargetActor.h"



ASSGameplayAbilityTargetActor::ASSGameplayAbilityTargetActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void ASSGameplayAbilityTargetActor::FilterHitResults(TArray<FHitResult>& OutHitResults, const FGATDF_MultiFilterHandle FilterHandle, const bool inAllowMultipleHitsPerActor) const
{
	for (int32 i = 0; i < OutHitResults.Num(); ++i)
	{
		const FHitResult Hit = OutHitResults[i];


		if (FilterHandle.MultiFilter.IsValid()) // if valid filter
		{
			const bool bPassesFilter = FilterHandle.FilterPassesForActor(Hit.Actor);
			if (!bPassesFilter)
			{
				OutHitResults.RemoveAt(i);
				--i;
				continue;
			}
		}

		if (!inAllowMultipleHitsPerActor) // if we should remove multiple hits
		{
			// Loop through each hit result and check if the hits infront of it (the hit results less than the pending index) already have its actor.
			// If so, remove the pending hit result because it has the actor that was already hit and is considered a duplicate hit.

			bool removed = false; // if true, we removed a duplicate hit

			// Check if the hit results that we've looped through so far contains a hit result with this actor already
			for (int32 comparisonIndex = 0; comparisonIndex < i; ++comparisonIndex)
			{
				if (Hit.Actor == OutHitResults[comparisonIndex].Actor)
				{
					OutHitResults.RemoveAt(i);
					--i;
					removed = true;
					break;
				}
			}

			if (removed)
			{
				continue;
			}
		}
	}
}
