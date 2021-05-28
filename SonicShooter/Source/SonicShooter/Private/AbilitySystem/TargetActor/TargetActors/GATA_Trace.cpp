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

#include "Utilities\BlueprintFunctionLibraries\BFL_CollisionQueryHelpers.h"
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

	RicochetableSurfaces.Add(SURFACETYPE_METAL);
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


	float currentMaxRange = GetMaxRange();

	// Ensure we return Physical Material for the ricochet determination
	FCollisionQueryParams TraceParams = Params;
	TraceParams.bReturnPhysicalMaterial = true;

	// Perform initial trace
	TArray<FHitResult> InitialHitResults;
	World->LineTraceMultiByChannel(InitialHitResults, Start, End, TraceChannel, TraceParams);
	if (InitialHitResults.Num() > 0)
	{
		currentMaxRange -= InitialHitResults.Last().Distance;
		OutHitResults.Append(InitialHitResults);
	}
	else
	{
		// Our caller may depend on us returning at least one Hit Result so it can get TraceStart and TraceEnd.
		// Make an empty Hit Result containing this info (this will just end up getting filtered)
		FHitResult TraceInfo;
		TraceInfo.TraceStart = Start;
		TraceInfo.TraceEnd = End;

		OutHitResults.Emplace(TraceInfo);
	}

	const bool bShouldStop = !OnInitialTrace(OutHitResults.Last(), World, TraceParams);
	if (!bShouldStop)
	{
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
			if (ShouldRicochetOffOf(LastHit))
			{
				if (timesRicocheted < maxRicochets)
				{
					// Calculate ricochet direction
					FVector RicoDir;
					CalculateRicochetDirection(RicoDir, LastHit);

					// Use direction to get the trace end
					FVector RicoStart = LastHit.Location + ((KINDA_SMALL_NUMBER * 100) * RicoDir);			// bump it outwards a bit for reassurance (sometimes works without this if using Chaos)
					FVector RicoEnd = RicoStart + (currentMaxRange * RicoDir);




					TArray<FHitResult> RicoHitResults;
					const bool bBreakOutEarly = !OnRicochet(LastHit, RicoHitResults, World, RicoStart, RicoEnd, TraceParams);




					if (RicoHitResults.Num() > 0)
					{
						currentMaxRange -= RicoHitResults.Last().Distance;
						OutHitResults.Append(RicoHitResults); // add these results to the end of OutHitResults
						LastHit = OutHitResults.Last(); // update LastHit
						++timesRicocheted;
						bRicocheted = true;
					}
					else // this ricochet didn't hit anything
					{
						// Our caller may depend on us returning at least one Hit Result so it can get TraceStart and TraceEnd.
						// Make an empty Hit Result containing this info (this will just end up getting filtered)
						FHitResult TraceInfo;
						TraceInfo.TraceStart = RicoStart;
						TraceInfo.TraceEnd = RicoEnd;

						OutHitResults.Emplace(TraceInfo);
					}

					if (bBreakOutEarly)
					{
						break;
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
				FVector PenetrateEnd = PenetrateStart + (currentMaxRange * FromDir);




				TArray<FHitResult> PenetrateHitResults;
				const bool bBreakOutEarly = !OnPenetrate(LastHit, PenetrateHitResults, World, PenetrateStart, PenetrateEnd, TraceParams);




				if (PenetrateHitResults.Num() > 0)
				{
					currentMaxRange -= PenetrateHitResults.Last().Distance;
					OutHitResults.Append(PenetrateHitResults); // add these results to the end of OutHitResults
					LastHit = OutHitResults.Last(); // update LastHit
					++timesPenetrated;
					bPenetrated = true;
				}
				else // this penetration didn't hit anything
				{
					// Our caller may depend on us returning at least one Hit Result so it can get TraceStart and TraceEnd.
					// Make an empty Hit Result containing this info (this will just end up getting filtered)
					FHitResult TraceInfo;
					TraceInfo.TraceStart = PenetrateStart;
					TraceInfo.TraceEnd = PenetrateEnd;

					OutHitResults.Emplace(TraceInfo);
				}

				if (bBreakOutEarly)
				{
					break;
				}

			}



			if (bRicocheted == false && bPenetrated == false)
			{
				// We weren't able to ricochet nor penetrate, stop here
				break;
			}

		}

		// If we didn't hit anything (ei. we traced into thin air)
		if (OutHitResults.Num() <= 0)
		{
			// Our caller may depend on us returning at least one Hit Result so it can get TraceStart and TraceEnd.
			// Make an empty Hit Result containing this info (this will just end up getting filtered)
			FHitResult TraceInfo;
			TraceInfo.TraceStart = Start;
			TraceInfo.TraceEnd = End;

			OutHitResults.Emplace(TraceInfo);
		}
	}

	OnPostTraces(OutHitResults.Last(), World, TraceParams);





#if ENABLE_DRAW_DEBUG
	if (inDebug)
	{
		DebugHitResults(OutHitResults, World);
	}
#endif
}

bool AGATA_Trace::OnInitialTrace(const FHitResult& InitialBlockingHit, const UWorld* World, const FCollisionQueryParams& TraceParams)
{
	if (InitialBlockingHit.bBlockingHit == false)
	{
		return false;
	}

	return true;
}
bool AGATA_Trace::OnPenetrate(const FHitResult& PenetratedThrough, TArray<FHitResult>& OutPenetrateHitResults, const UWorld* World, const FVector& PenetrateStart, const FVector& PenetrateEnd, const FCollisionQueryParams& TraceParams)
{
	OutPenetrateHitResults.Empty();


	FCollisionQueryParams PenetrateParams = TraceParams;
	PenetrateParams.bTraceComplex = true; // Use complex collision if the collider has it. We need this because we are starting from inside the geometry and shooting out (this won't work for CTF_UseSimpleAsComplex and Physics Assest colliders so TODO: we will need a case that covers this)

	// Perform penetrate trace
	World->LineTraceMultiByChannel(OutPenetrateHitResults, PenetrateStart, PenetrateEnd, TraceChannel, PenetrateParams);



	// Our fallback if the trace messed up (if we hit ourselves instead of going through to the next hit). This happens if we are a CTF_UseSimpleAsComplex or a Physics Asset collider.
	if (OutPenetrateHitResults.Num() > 0 && OutPenetrateHitResults.Last().Distance == 0)
	{
		// Try again with this component ignored
		PenetrateParams.AddIgnoredComponent(OutPenetrateHitResults.Last().GetComponent());
		OutPenetrateHitResults.Empty();
		World->LineTraceMultiByChannel(OutPenetrateHitResults, PenetrateStart, PenetrateEnd, TraceChannel, PenetrateParams);
	}


	return true;
}
bool AGATA_Trace::OnRicochet(const FHitResult& RicochetOffOf, TArray<FHitResult>& OutRicoHitResults, const UWorld* World, const FVector& RicoStart, const FVector& RicoEnd, const FCollisionQueryParams& TraceParams)
{
	OutRicoHitResults.Empty();



	FCollisionQueryParams RicoParams = TraceParams;
	RicoParams.bTraceComplex = true; // ricochet doesn't need Trace Complex but because we are mixed in with penetration logic (which uses Trace Complex), we have to consider it

	// Perform ricochet trace
	World->LineTraceMultiByChannel(OutRicoHitResults, RicoStart, RicoEnd, TraceChannel, RicoParams);


	return true;
}
void AGATA_Trace::OnPostTraces(const FHitResult& LastBlockingHit, const UWorld* World, const FCollisionQueryParams& TraceParams)
{
	
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
		DebugTrace(OutHitResults, World, Start, End/*, r*/);
	}
#endif
}

//#if ENABLE_DRAW_DEBUG
void AGATA_Trace::DebugHitResults(const TArray<FHitResult>& HitResults, const UWorld* World) const
{
#if ENABLE_DRAW_DEBUG
	TArray<FHitResult> DebugHitResults = HitResults;
	FilterHitResults(DebugHitResults, FGATDF_MultiFilterHandle(), bAllowMultipleHitsPerActor); // removes multiple hits if needed (but doesn't filter actors because we have different colors for whether it filters or not)


	const float debugLifeTime = 5.f;
	const FColor TraceColor = FColor::Blue;
	const FColor PassesFilterColor = FColor::Red;

	if (DebugHitResults.Num() > 0)
	{
		for (int32 i = 0; i < DebugHitResults.Num(); ++i)
		{
			const FHitResult& Hit = DebugHitResults[i];

			FVector FromLocation = Hit.TraceStart;
			FVector ToLocation = Hit.Location;
			if (Hit.Location == FVector::ZeroVector) // if invalid Location (this is only to support empty Hit Results that hold TraceStart and TraceEnd locations and this is weird but i don't care about this function enough to fix it)
			{
				ToLocation = Hit.TraceEnd; // to get a line that makes sense, just draw to TraceEnd
			}

			DrawDebugLine(World, FromLocation, ToLocation, TraceColor, false, debugLifeTime);
			
			if (Hit.Location != FVector::ZeroVector) // if Location is valid
			{
				const bool bPassesFilter = MultiFilterHandle.FilterPassesForActor(Hit.GetActor());
				if (bPassesFilter)
				{
					DrawDebugPoint(World, Hit.ImpactPoint, 10, PassesFilterColor, false, debugLifeTime);
				}
				else
				{
					DrawDebugPoint(World, Hit.ImpactPoint, 10, TraceColor, false, debugLifeTime);
				}
			}
		}
	}
#endif // ENABLE_DRAW_DEBUG
}

void AGATA_Trace::DebugTrace(const TArray<FHitResult>& HitResults, const UWorld* World, const FVector& Start, const FVector& End) const
{
#if ENABLE_DRAW_DEBUG
	DebugHitResults(HitResults, World);


	TArray<FHitResult> DebugHitResults = HitResults;
	FilterHitResults(DebugHitResults, FGATDF_MultiFilterHandle(), bAllowMultipleHitsPerActor); // removes multiple hits if needed (but doesn't filter actors because we have different colors for whether it filters or not)


	const float debugLifeTime = 5.f;
	const FColor TraceColor = FColor::Blue;
	const FColor PassesFilterColor = FColor::Red;

	if (DebugHitResults.Num() > 0)
	{
		if (DebugHitResults.Last().bBlockingHit == false)
		{
			// If our last hit was an overlap, draw out one last Trace End to show that it went through
			DrawDebugLine(World, DebugHitResults.Last().Location, DebugHitResults.Last().TraceEnd, TraceColor, false, debugLifeTime);		// after the we've drawn a line to all hit results, draw from last hit result to the trace end
		}
	}
	else // if we've traced in thin air
	{
		// Draw the line that didn't hit anything
		DrawDebugLine(World, Start, End, TraceColor, false, debugLifeTime);
	}

#endif // ENABLE_DRAW_DEBUG
}

void AGATA_Trace::DebugTrace(const TArray<FHitResult>& HitResults, const UWorld* World, const FVector& Start, const FVector& End, const FVector& ExtraTraceEnd) const
{
#if ENABLE_DRAW_DEBUG
	DebugTrace(HitResults, World, Start, End);


	TArray<FHitResult> DebugHitResults = HitResults;
	FilterHitResults(DebugHitResults, FGATDF_MultiFilterHandle(), bAllowMultipleHitsPerActor); // removes multiple hits if needed (but doesn't filter actors because we have different colors for whether it filters or not)


	const float debugLifeTime = 5.f;
	const FColor TraceColor = FColor::Blue;
	const FColor PassesFilterColor = FColor::Red;

	if (DebugHitResults.Num() > 0)
	{
		if (DebugHitResults.Last().bBlockingHit)
		{
			if ((ExtraTraceEnd - DebugHitResults.Last().Location).IsNearlyZero() == false) // only draw this extra trace if it is different then the last trace
			{
				DrawDebugLine(World, DebugHitResults.Last().Location, ExtraTraceEnd, TraceColor, false, debugLifeTime);
			}
		}
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
