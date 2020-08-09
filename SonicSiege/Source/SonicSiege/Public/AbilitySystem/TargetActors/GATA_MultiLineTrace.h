// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"

#include "DrawDebugHelpers.h"

#include "GATA_MultiLineTrace.generated.h"



/**
 * This target actor will collect all desired actors (specified by ActorClassToCollect) by using multiple line traces (maximum value
 * specified by maxTraces) and end when it hits a non-ActorClassToCollect
 * 
 * This doesn't take into account collision profiles yet
 */
UCLASS()
class SONICSIEGE_API AGATA_MultiLineTrace : public AGameplayAbilityTargetActor_Trace
{
	GENERATED_BODY()

public:
	AGATA_MultiLineTrace();


	uint8 maxTraces;

	TSubclassOf<AActor> ActorClassToCollect;

protected:
	//BEGIN AGameplayAbilityTargetActor_Trace Interface
	virtual void ConfirmTargetingAndContinue() override;
	//virtual FHitResult PerformTrace(AActor* InSourceActor) override;
	//END AGameplayAbilityTargetActor_Trace Interface

	TArray<FHitResult> PerformMultiTraces(AActor* InSourceActor);
#pragma region old templated multitrace funciton
//	template <class ActorClassToCollect = AActor>
//	TArray<FHitResult> PerformMultiTraces(AActor* InSourceActor)
//	{
//		bool bTraceComplex = false;
//		TArray<AActor*> ActorsToIgnore;
//
//		ActorsToIgnore.Add(InSourceActor);
//
//		FCollisionQueryParams Params(SCENE_QUERY_STAT(AGameplayAbilityTargetActor_SingleLineTrace), bTraceComplex);
//		Params.bReturnPhysicalMaterial = true;
//		Params.AddIgnoredActors(ActorsToIgnore);
//
//		FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();// InSourceActor->GetActorLocation();
//		FVector TraceEnd;
//		AimWithPlayerController(InSourceActor, Params, TraceStart, TraceEnd);		//Effective on server and launching client only
//
//		// ------------------------------------------------------
//
//		TArray<FHitResult> ReturnHitResults;
//		AActor* LastHitActor;
//		for (uint8 i = 0; i < maxTraces; i++)
//		{
//			FHitResult TraceHitResult;
//			LineTraceWithFilter(TraceHitResult, InSourceActor->GetWorld(), Filter, TraceStart, TraceEnd, TraceProfile.Name, Params);
//
//			// store the hit actor so we can ignore it next iteration
//			if (TraceHitResult.Actor.IsValid())
//			{
//				Params.ClearIgnoredActors();
//				Params.AddIgnoredActor(InSourceActor);
//				AActor* HitActor = TraceHitResult.Actor.Get();
//				Params.AddIgnoredActor(HitActor);
//				LastHitActor = HitActor;
//			}
//			else
//			{
//#if ENABLE_DRAW_DEBUG
//				if (bDebug)
//				{
//					float debugLifeTime = 5.f;
//
//					DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor(0.f, 0.f + (i * (255 / (maxTraces - 1))), 255.f), false, debugLifeTime);
//					DrawDebugPoint(GetWorld(), TraceEnd, 10, FColor(0.f, 0.f, 255.f), false, debugLifeTime);
//				}
//#endif // ENABLE_DRAW_DEBUG
//				break;
//			}
//
//			if (TraceHitResult.bBlockingHit)
//			{
//				if (Cast<ActorClassToCollect>(TraceHitResult.Actor))		// this is where to add actor checks
//				{
//					ReturnHitResults.Add(TraceHitResult);
//				}
//				else
//				{
//					break;
//				}
//			}
//
//#if ENABLE_DRAW_DEBUG
//			if (bDebug)
//			{
//				float debugLifeTime = 5.f;
//
//				DrawDebugLine(GetWorld(), TraceStart, TraceHitResult.Location, FColor(0.f, 0.f + (i * (255 / (maxTraces - 1))), 255.f), false, debugLifeTime);
//				DrawDebugPoint(GetWorld(), TraceHitResult.Location, 10, FColor(0.f + (i * (255 / (maxTraces - 1))), 255.f - (i * (255 / (maxTraces - 1))), 0.f), false, debugLifeTime);
//			}
//#endif // ENABLE_DRAW_DEBUG
//
//
//			TraceStart = TraceHitResult.ImpactPoint;
//		}
//
//
//
//
//		//if (AGameplayAbilityWorldReticle* LocalReticleActor = ReticleActor.Get())
//		//{
//		//	//const bool bHitActor = (ReturnHitResult.bBlockingHit && (ReturnHitResult.Actor != NULL));
//		//	const bool bHitActor = (ReturnHitResults.Num() > 0);
//		//	const FVector ReticleLocation = (bHitActor && LocalReticleActor->bSnapToTargetedActor) ? ReturnHitResult.Actor->GetActorLocation() : ReturnHitResult.Location;
//
//		//	LocalReticleActor->SetActorLocation(ReticleLocation);
//		//	LocalReticleActor->SetIsTargetAnActor(bHitActor);
//		//}
//
//		return ReturnHitResults;
//	}  
#pragma endregion

};
