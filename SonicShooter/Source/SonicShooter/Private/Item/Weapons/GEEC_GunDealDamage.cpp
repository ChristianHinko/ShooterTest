// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/GEEC_GunDealDamage.h"

#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "AbilitySystem\AttributeSets\AS_Health.h"
#include "AbilitySystem/AttributeSets/AS_Damage.h"
#include "Item/AS_Gun.h"


// Declare the attributes to capture and define how we want to capture them from the Source and Target
struct SSDamageStatics
{
	// Source
	DECLARE_ATTRIBUTE_CAPTUREDEF(OutgoingDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageFalloff);
	
	// Target
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingDamage);




	SSDamageStatics()
	{
		// Snapshot happens at time of GESpec creation

		//Source captures
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAS_Damage, OutgoingDamage, Source, true);	// This will be the value to damage the target by
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAS_Gun, DamageFalloff, Source, true);	// This will be the value to damage the target by

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
	// Cache GameplayTags
	BulletTotalTravelDistanceBeforeHitTag = FGameplayTag::RequestGameplayTag("SetByCaller.BulletTotalTravelDistanceBeforeHit");



	//Source
	RelevantAttributesToCapture.Add(DamageStatics().OutgoingDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageFalloffDef);

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


	const FHitResult* Hit = Spec.GetContext().GetHitResult();





	


	// Needed parameter for AttemptCalculateCapturedAttributeMagnitude()
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Lets get the values we need for our damage calculation (ie. source/target attributes, passed in values)
	float RawDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().OutgoingDamageDef, EvaluationParameters, RawDamage);
	float DamageFalloff = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageFalloffDef, EvaluationParameters, DamageFalloff);
	float totalDistanceBulletTraveled = Spec.GetSetByCallerMagnitude(BulletTotalTravelDistanceBeforeHitTag, true, 0);


	float finalDamage = RawDamage;
	// Lets start calculating
	finalDamage = finalDamage * DamageFalloff;	// THIS IS NOT A CORRECT IMPLEMENTATION FOR DAMAGE FALLOFF! JUST HERE TO TEST THINGS OUT!















	// Set the Target's IncomingDamage meta attribute
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().IncomingDamageProperty, EGameplayModOp::Additive, finalDamage));
}
