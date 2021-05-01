// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TargetActor/SSGameplayAbilityTargetActor.h"

#include "Abilities/GameplayAbility.h"



ASSGameplayAbilityTargetActor::ASSGameplayAbilityTargetActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAllowMultipleHitsPerActor = false;


	TraceChannel = ECollisionChannel::ECC_Visibility;


	bUsePlayerViewPointAsStartLocation = true;

	bTraceAffectsAimPitch = true;



}


void ASSGameplayAbilityTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);


	if (bUsePlayerViewPointAsStartLocation)
	{
		StartLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;

		FVector ViewStart;
		FVector ViewDir;
		CalculateAimDirection(ViewStart, ViewDir);

		StartLocation.LiteralTransform.SetLocation(ViewStart);
	}
}

float ASSGameplayAbilityTargetActor::GetMaxRange() const
{
	return 100000.f;
}

void ASSGameplayAbilityTargetActor::FilterHitResults(TArray<FHitResult>& OutHitResults, const FGATDF_MultiFilterHandle FilterHandle, const bool inAllowMultipleHitsPerActor) const
{
	for (int32 i = 0; i < OutHitResults.Num(); ++i)
	{
		if (FilterHitResult(OutHitResults, i, FilterHandle, inAllowMultipleHitsPerActor))
		{
			// This index was filtered
		}
	}
}
bool ASSGameplayAbilityTargetActor::FilterHitResult(TArray<FHitResult>& OutHitResults, const int32 index, const FGATDF_MultiFilterHandle FilterHandle, const bool inAllowMultipleHitsPerActor) const
{
	const FHitResult Hit = OutHitResults[index];


	if (FilterHandle.MultiFilter.IsValid()) // if valid filter
	{
		const bool bPassesFilter = FilterHandle.FilterPassesForActor(Hit.Actor);
		if (!bPassesFilter)
		{
			OutHitResults.RemoveAt(index);
			return true;
		}
	}

	if (!inAllowMultipleHitsPerActor) // if we should remove multiple hits
	{
		// Loop through each hit result and check if the hits infront of it (the hit results less than the pending index) already have its actor.
		// If so, remove the pending hit result because it has the actor that was already hit and is considered a duplicate hit.

		bool removed = false; // if true, we removed a duplicate hit

		// Check if the hit results that we've looped through so far contains a hit result with this actor already
		for (int32 comparisonIndex = 0; comparisonIndex < index; ++comparisonIndex)
		{
			if (Hit.Actor == OutHitResults[comparisonIndex].Actor)
			{
				OutHitResults.RemoveAt(index);
				removed = true;
				break;
			}
		}

		if (removed)
		{
			return true;
		}
	}

	// This index was filtered
	return false;
}

void ASSGameplayAbilityTargetActor::AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceEnd) const
{
	FVector TraceDir;
	DirWithPlayerController(InSourceActor, Params, TraceStart, TraceDir);

	OutTraceEnd = TraceStart + (TraceDir * GetMaxRange());
}
void ASSGameplayAbilityTargetActor::DirWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceDir) const
{
	FVector ViewStart;
	FVector ViewDir;
	CalculateAimDirection(ViewStart, ViewDir);
	FVector ViewEnd = ViewStart + (ViewDir * GetMaxRange());

	ClipCameraRayToAbilityRange(ViewStart, ViewDir, TraceStart, GetMaxRange(), ViewEnd);

	// If the TraceStart is nearly equal to the ViewStart, skip the useless camera trace and just return the aim direction
	if ((TraceStart - ViewStart).IsNearlyZero(KINDA_SMALL_NUMBER))
	{
		// As an optimization, skip the extra trace and return here
		OutTraceDir = (ViewEnd - TraceStart).GetSafeNormal();
		return;
	}

	// Line trace from the TraceStart to the the point that player is looking at so we can calculate the direction
	TArray<FHitResult> HitResults;
	InSourceActor->GetWorld()->LineTraceMultiByChannel(HitResults, ViewStart, ViewEnd, TraceChannel, Params);
	FHitResult HitResult = HitResults.Num() ? HitResults[0] : FHitResult();

	const bool bUseTraceResult = /*HitResult.bBlockingHit && */(FVector::DistSquared(TraceStart, HitResult.Location) <= (GetMaxRange() * GetMaxRange()));

	const FVector AdjustedEnd = (bUseTraceResult) ? HitResult.Location : ViewEnd;

	FVector AdjustedAimDir = (AdjustedEnd - TraceStart).GetSafeNormal();
	if (AdjustedAimDir.IsZero())
	{
		AdjustedAimDir = ViewDir;
	}

	if (!bTraceAffectsAimPitch && bUseTraceResult)
	{
		FVector OriginalAimDir = (ViewEnd - TraceStart).GetSafeNormal();

		if (!OriginalAimDir.IsZero())
		{
			// Convert to angles and use original pitch
			const FRotator OriginalAimRot = OriginalAimDir.Rotation();

			FRotator AdjustedAimRot = AdjustedAimDir.Rotation();
			AdjustedAimRot.Pitch = OriginalAimRot.Pitch;

			AdjustedAimDir = AdjustedAimRot.Vector();
		}
	}

	OutTraceDir = AdjustedAimDir;
}

void ASSGameplayAbilityTargetActor::CalculateAimDirection(FVector& ViewStart, FVector& ViewDir) const
{
	if (!OwningAbility) // Server and launching client only
	{
		return;
	}


	const APlayerController* PC = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();
	check(PC);

	FRotator ViewRot;
	PC->GetPlayerViewPoint(ViewStart, ViewRot);

	ViewDir = ViewRot.Vector();
}

bool ASSGameplayAbilityTargetActor::ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition)
{
	const FVector CameraToCenter = AbilityCenter - CameraLocation;
	const float DotToCenter = FVector::DotProduct(CameraToCenter, CameraDirection);
	if (DotToCenter >= 0)		//If this fails, we're pointed away from the center, but we might be inside the sphere and able to find a good exit point.
	{
		const float DistanceSquared = CameraToCenter.SizeSquared() - (DotToCenter * DotToCenter);
		const float RadiusSquared = (AbilityRange * AbilityRange);
		if (DistanceSquared <= RadiusSquared)
		{
			const float DistanceFromCamera = FMath::Sqrt(RadiusSquared - DistanceSquared);
			const float DistanceAlongRay = DotToCenter + DistanceFromCamera;					//Subtracting instead of adding will get the other intersection point
			ClippedPosition = CameraLocation + (DistanceAlongRay * CameraDirection);			//Cam aim point clipped to range sphere
			return true;
		}
	}
	return false;
}
