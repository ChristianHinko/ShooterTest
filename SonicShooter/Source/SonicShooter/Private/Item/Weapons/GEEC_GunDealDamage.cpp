// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/GEEC_GunDealDamage.h"

#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "AbilitySystem\AttributeSets\AS_Health.h"
#include "AbilitySystem/AttributeSets/AS_Damage.h"


// Declare the attributes to capture and define how we want to capture them from the Source and Target
struct SSDamageStatics
{
	// Source
	DECLARE_ATTRIBUTE_CAPTUREDEF(OutgoingDamage);
	
	// Target
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingDamage);




	SSDamageStatics()
	{
		// Snapshot happens at time of GESpec creation

		//Source captures
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAS_Damage, OutgoingDamage, Source, true);	// This will be the value to damage the target by

		//Target captures
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAS_Health, IncomingDamage, Target, false);	// This is the attribute we will change on the target
	}
};

static const SSDamageStatics& DamageStatics()
{
	static SSDamageStatics DStatics;
	return DStatics;
}

UGEEC_GunDealDamage::UGEEC_GunDealDamage()
{
	//Source
	RelevantAttributesToCapture.Add(DamageStatics().OutgoingDamageDef);

	//Target
	RelevantAttributesToCapture.Add(DamageStatics().IncomingDamageDef);
}

// Need to make this get the OutgoingDamage attribute from a damage attribute set on the source
void UGEEC_GunDealDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	if (!SourceAbilitySystemComponent || !TargetAbilitySystemComponent)
	{
		return;
	}


	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayTagContainer AssetTags;
	Spec.GetAllAssetTags(AssetTags);

	// Gather the tags from the source and target as that can affect how the damage might be calulated
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();












	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	float RawDamage = 0.0f;		// Raw because we havn't done any post process stuff yet (ie. crit multiplier, enemy armor)
	// This recalculation will not run PreAttributeChange() clamps, so if there were any clamps in that, do it here too (or find a better way idk)
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().OutgoingDamageDef, EvaluationParameters, RawDamage);

	// Set the Target's IncomingDamage meta attribute
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().IncomingDamageProperty, EGameplayModOp::Additive, RawDamage));





	////Grab the weapon Stats. (Kaos's way)
	//const FKaosBaseWeaponStats* WeaponStats = Weapon ? Weapon->GetWeaponStats() : nullptr;

	//if (InRange(HitResultDistance, 0.f, WeaponStats->RangeMid))
	//{
	//	CalculatedDamage = UKismetMathLibrary::MapRangeClamped(HitResultDistance, WeaponStats->RangePB, WeaponStats->RangeMid, WeaponStats->DamagePB, WeaponStats->DamageMid);

	//}
	//else if (InRange(HitResultDistance, WeaponStats->RangeMid, WeaponStats->RangeLong))
	//{
	//	CalculatedDamage = UKismetMathLibrary::MapRangeClamped(HitResultDistance, WeaponStats->RangeMid, WeaponStats->RangeLong, WeaponStats->DamageMid, WeaponStats->DamageLong);
	//}
	//else
	//{
	//	CalculatedDamage = WeaponStats->DamageMaxRange;
	//}

	////If it was a head shot or DiceCritChance > 0 and roll is in range, then apply CritDamageMultiplier.
	//if (bIsHeadshot || (WeaponStats->DiceCritChance > 0 && FMath::FRandRange(0, 100) <= WeaponStats->DiceCritChance))
	//{
	//	Context->bIsCriticalHit = true;
	//	Context->bIsDiceCritical = !bIsHeadshot;
	//	float CritMulti = 1.f;
	//	ExecutionParams.AttemptCalculateCapturedAttributeMagnitudeWithBase(KaosDamageCalcStatics().CritMultiplierDef, EvaluationParameters, WeaponStats->CritDamageMultiplier, CritMulti);
	//	CalculatedDamage *= CritMulti;
	//}
}
