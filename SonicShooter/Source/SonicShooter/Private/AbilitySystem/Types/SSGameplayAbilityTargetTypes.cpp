// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Types/SSGameplayAbilityTargetTypes.h"

#include "Utilities/LogCategories.h"



FSSGameplayAbilityTargetData::FSSGameplayAbilityTargetData()
{

}



////////////////////////////////////////////////////////////////
/// FGATD_BulletTraceTargetHit
////////////////////////////////////////////////////////////////


#include "AbilitySystem/Types/SSGameplayEffectTypes.h"
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

	AppliedHandles.Reserve(ActorHitInfos.Num());	// Modified: We will use our ActorHitInfos to loop through, since that is the actual array, instead of just using GetActors

	for (int32 i = 0; i < ActorHitInfos.Num(); i++)
	{
		UAbilitySystemComponent* TargetComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorHitInfos[i].HitActor.Get());

		if (TargetComponent)
		{
			// We have to make a new effect spec and context here, because otherwise the targeting info gets accumulated and things take damage multiple times
			FGameplayEffectSpec	SpecToApply(Spec);
			FGameplayEffectContextHandle EffectContext = SpecToApply.GetContext().Duplicate();
			SpecToApply.SetContext(EffectContext);

			AddTargetDataToContext(EffectContext, false, i);


			AppliedHandles.Add(EffectContext.GetInstigatorAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(SpecToApply, TargetComponent, PredictionKey));
		}
	}

	return AppliedHandles;
}

void FGATD_BulletTraceTargetHit::AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray) const
{
	UE_LOG(LogGameplayAbilityTargetData, Fatal, TEXT("%s() This should not be called for this specific GATD. Use our custom overload instead (passes in index)"), ANSI_TO_TCHAR(__FUNCTION__));
}

void FGATD_BulletTraceTargetHit::AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray, int32 HitInfosIndex) const
{
	if (FGEC_Shooter* SSContext = static_cast<FGEC_Shooter*>(Context.Get()))
	{
		SSContext->SetHitInfo(ActorHitInfos[HitInfosIndex]);
		SSContext->SetBulletTracePoints(BulletTracePoints);
	}
	else
	{
		UE_LOG(LogGameplayAbilityTargetData, Warning, TEXT("%s() Cast to FSSGameplayEffectContext failed. Bullet specific target data info will not be in our GEEC"), ANSI_TO_TCHAR(__FUNCTION__));
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
