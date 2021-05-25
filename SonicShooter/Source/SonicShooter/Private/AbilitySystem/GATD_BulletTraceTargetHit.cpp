// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem\GATD_BulletTraceTargetHit.h"

#include "AbilitySystem\GEC_Shooter.h"
#include "Utilities/LogCategories.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"



FGATD_BulletTraceTargetHit::FGATD_BulletTraceTargetHit()
{

}


TArray<FActiveGameplayEffectHandle> FGATD_BulletTraceTargetHit::ApplyGameplayEffectSpec(FGameplayEffectSpec& Spec, FPredictionKey PredictionKey)
{
	TArray<FActiveGameplayEffectHandle>	AppliedHandles;

	if (!ensure(Spec.GetContext().IsValid() && Spec.GetContext().GetInstigatorAbilitySystemComponent()))
	{
		return AppliedHandles;
	}

	TArray<TWeakObjectPtr<AActor> > Actors = GetActors();

	AppliedHandles.Reserve(Actors.Num());

	for (TWeakObjectPtr<AActor>& TargetActor : Actors)
	{
		UAbilitySystemComponent* TargetComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor.Get());

		if (TargetComponent)
		{
			// We have to make a new effect spec and context here, because otherwise the targeting info gets accumulated and things take damage multiple times
			FGameplayEffectSpec	SpecToApply(Spec);
			FGameplayEffectContextHandle EffectContext = SpecToApply.GetContext().Duplicate();
			SpecToApply.SetContext(EffectContext);

			AddTargetDataToContext(EffectContext, false);


			AppliedHandles.Add(EffectContext.GetInstigatorAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(SpecToApply, TargetComponent, PredictionKey));
		}
	}

	return AppliedHandles;
}

void FGATD_BulletTraceTargetHit::AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray) const
{
	if (FGEC_Shooter* SSContext = static_cast<FGEC_Shooter*>(Context.Get()))
	{
		//SSContext->SetBulletTotalTravelDistanceBeforeHit(BulletTotalTravelDistanceBeforeHit);	// COME BACK TO THIS AND HAVE NEW SOLUTION!!!!!!!!!!!!!!!!!!!!!!!!
		SSContext->SetBulletTracePoints(BulletTracePoints);
	}
	else
	{
		UE_LOG(LogGameplayAbilityTargetData, Warning, TEXT("%s() Cast to FSSGameplayEffectContext failed. Bullet specific target data info will not be in our GEEC"), *FString(__FUNCTION__));
	}
}


bool FGATD_BulletTraceTargetHit::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	uint8 RepBits;
	if (Ar.IsSaving())
	{
		// We are a writer, lets find some optimizations and pack them into RepBits


	}

	// Pack/unpack our RepBits into/outof the Archive
	Ar.SerializeBits(&RepBits, 0);
	if (Ar.IsLoading())
	{
		// We are a reader, lets unpack our optimization bools from RepBits

	}

	bOutSuccess &= SafeNetSerializeTArray_WithNetSerialize<31>(Ar, BulletTracePoints, Map);
	bOutSuccess &= SafeNetSerializeTArray_WithNetSerialize<31>(Ar, ActorHitInfos, Map);

	




	bOutSuccess = true;
	return true;
}
