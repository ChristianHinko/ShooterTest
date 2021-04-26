// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilitySystem\SSGameplayAbilityTargetTypes.h"

#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"

TArray<FActiveGameplayEffectHandle> FGameplayAbilityTargetData_BulletTraceTargetHit::ApplyGameplayEffectSpec(FGameplayEffectSpec& InSpec, FPredictionKey PredictionKey)
{
	TArray<FActiveGameplayEffectHandle>	AppliedHandles;

	if (!ensure(InSpec.GetContext().IsValid() && InSpec.GetContext().GetInstigatorAbilitySystemComponent()))
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
			FGameplayEffectSpec	SpecToApply(InSpec);
			FGameplayEffectContextHandle EffectContext = SpecToApply.GetContext().Duplicate();
			SpecToApply.SetContext(EffectContext);

			/////////////////
			SpecToApply.SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("SetByCaller.BulletTotalTravelDistanceBeforeHit"), bulletTotalTravelDistanceBeforeHit);	// Only line added
			/////////////////

			AddTargetDataToContext(EffectContext, false);

			AppliedHandles.Add(EffectContext.GetInstigatorAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(SpecToApply, TargetComponent, PredictionKey));
		}
	}

	return AppliedHandles;
}

bool FGameplayAbilityTargetData_BulletTraceTargetHit::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	HitResult.NetSerialize(Ar, Map, bOutSuccess);

	return true;
}