// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/GEEC_GunDealDamage.h"

#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "AbilitySystem\AttributeSets\AS_Health.h"
#include "AbilitySystem/AttributeSets/AS_Damage.h"

#include "Item/Weapons/AS_Gun.h"
#include "AbilitySystem/SSGameplayEffectTypes.h"


// Declare the attributes to capture and define how we want to capture them from the Source and Target
struct SSDamageStatics
{
	// Source
	DECLARE_ATTRIBUTE_CAPTUREDEF(OutgoingDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BulletSpeedFalloff);
	
	// Target
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingDamage);




	SSDamageStatics()
	{
		// Snapshot happens at time of GESpec creation

		//Source captures
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAS_Damage, OutgoingDamage, Source, true);	// This will be the value to damage the target by
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAS_Gun, BulletSpeedFalloff, Source, true);	// This will be the value to damage the target by

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
	RelevantAttributesToCapture.Add(DamageStatics().BulletSpeedFalloffDef);

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


	FGameplayEffectSpec* MutableSpec = ExecutionParams.GetOwningSpecForPreExecuteMod();
	FGEC_Shooter* Context = static_cast<FGEC_Shooter*>(MutableSpec->GetContext().Get());



	


	// Needed parameter for AttemptCalculateCapturedAttributeMagnitude()
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Lets get the values we need for our damage calculation (ie. source/target attributes, passed in values)
	float RawDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().OutgoingDamageDef, EvaluationParameters, RawDamage);
	float BulletSpeedFalloff = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BulletSpeedFalloffDef, EvaluationParameters, BulletSpeedFalloff);

	// Example for if you want to get a SetByCaller
	//const float totalDistanceBulletTraveled = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("SetByCaller.RicochetsBeforeHit"), true, 0);		// This is not an actual SetByCaller, just an example

	// Lets get our effect context's data
	const float totalDistanceBulletTraveled = Context->GetHitInfo().totalTraveledDistanceBeforeHit;
	const uint8 ricochetsBeforeHit = Context->GetNumRicochetsBeforeHit();

	// Lets start calculating
	float finalDamage = RawDamage;

















	// Set the Target's IncomingDamage meta attribute
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().IncomingDamageProperty, EGameplayModOp::Additive, finalDamage));
}
