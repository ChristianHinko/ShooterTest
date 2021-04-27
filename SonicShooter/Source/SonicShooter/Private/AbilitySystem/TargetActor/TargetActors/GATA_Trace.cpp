// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/TargetActors/GATA_Trace.h"

#include "GameFramework/PlayerController.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/TargetActor/GATDF_MultiFilter.h"
#include "Character/AbilitySystemCharacter.h"
#include "Pawn/AbilitySystemPawn.h"
#include "Actor/AbilitySystemActor.h"
#include "AbilitySystem/SSAbilitySystemBlueprintLibrary.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"



AGATA_Trace::AGATA_Trace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	ShouldProduceTargetDataOnServer = true;

	MultiFilter.bReverseFilter = true;
	MultiFilter.RequiredActorClasses.Add(AAbilitySystemCharacter::StaticClass());
	MultiFilter.RequiredActorClasses.Add(AAbilitySystemPawn::StaticClass());
	MultiFilter.RequiredActorClasses.Add(AAbilitySystemActor::StaticClass());

	bDebug = true;
}
void AGATA_Trace::PreInitializeComponents()
{
	Super::PreInitializeComponents();


	MultiFilterHandle = USSAbilitySystemBlueprintLibrary::MakeMultiFilterHandle(MultiFilter/*, SourceActor*/);
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
		TArray<FHitResult> HitResults;
		PerformTrace(HitResults, SourceActor);

		FilterHitResults(HitResults, MultiFilterHandle, bAllowMultipleHitsPerActor);

		FGameplayAbilityTargetDataHandle TargetDataHandle = StartLocation.MakeTargetDataHandleFromHitResults(OwningAbility, HitResults);
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}

int32 AGATA_Trace::GetRicochets() const
{
	return 0;
}

bool AGATA_Trace::RicochetLineTrace(TArray<FHitResult>& OutHitResults, const UWorld* World, const FCollisionQueryParams Params) const
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

	TArray<FHitResult> RicoHitResults;

	FCollisionQueryParams RicoParams = Params;
	RicoParams.AddIgnoredActor(LastHit.GetActor());


	const FVector TracedDir = UKismetMathLibrary::GetDirectionUnitVector(LastHit.TraceStart, LastHit.TraceEnd);
	const FVector MirroredDir = TracedDir.MirrorByVector(LastHit.ImpactNormal);

	const FVector RicoStart = LastHit.Location;
	const FVector RicoEnd = RicoStart + ((GetMaxRange() - LastHit.Distance) * MirroredDir);


	if (World->LineTraceMultiByChannel(RicoHitResults, RicoStart, RicoEnd, TraceChannel, RicoParams) == false)
	{
		return false;
	}
	OutHitResults.Append(RicoHitResults);
	return true;
}
bool AGATA_Trace::RicochetSweep(TArray<FHitResult>& OutHitResults, const UWorld* World, const FQuat& Rotation, const FCollisionShape CollisionShape, const FCollisionQueryParams Params) const
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

	TArray<FHitResult> RicoHitResults;

	FCollisionQueryParams RicoParams = Params;
	RicoParams.AddIgnoredActor(LastHit.GetActor());


	const FVector TracedDir = UKismetMathLibrary::GetDirectionUnitVector(LastHit.TraceStart, LastHit.TraceEnd);
	const FVector MirroredDir = TracedDir.MirrorByVector(LastHit.ImpactNormal);

	const FVector RicoStart = LastHit.Location;
	const FVector RicoEnd = RicoStart + ((GetMaxRange() - LastHit.Distance) * MirroredDir);


	if (World->SweepMultiByChannel(RicoHitResults, RicoStart, RicoEnd, Rotation, TraceChannel, CollisionShape, RicoParams) == false)
	{
		return false;
	}

	OutHitResults.Append(RicoHitResults);
	return true;
}

void AGATA_Trace::LineTraceMultiWithRicochets(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FCollisionQueryParams Params, const bool inDebug) const
{
	check(World);

	World->LineTraceMultiByChannel(OutHitResults, Start, End, TraceChannel, Params);

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
#endif // ENABLE_DRAW_DEBUG
}

void AGATA_Trace::SweepMultiWithRicochets(TArray<FHitResult>& OutHitResults, const UWorld* World, const FVector& Start, const FVector& End, const FQuat& Rotation, const FCollisionShape CollisionShape, const FCollisionQueryParams Params, const bool inDebug) const
{
	check(World);

	World->SweepMultiByChannel(OutHitResults, Start, End, Rotation, TraceChannel, CollisionShape, Params);

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
#endif // ENABLE_DRAW_DEBUG
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


void AGATA_Trace::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	// very temp - do a mostly hardcoded trace from the source actor
	if (SourceActor)
	{
		TArray<FHitResult> HitResults;
		PerformTrace(HitResults, SourceActor);
		const FHitResult HitResult = HitResults.Num() ? HitResults.Last() : FHitResult();		// get last hit
		const FVector EndPoint = HitResult.Component.IsValid() ? HitResult.ImpactPoint : HitResult.TraceEnd;

		SetActorLocationAndRotation(EndPoint, SourceActor->GetActorRotation());
	}
}

void AGATA_Trace::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ReticleActor.IsValid())
	{
		ReticleActor.Get()->Destroy();
	}


	Super::EndPlay(EndPlayReason);
}
