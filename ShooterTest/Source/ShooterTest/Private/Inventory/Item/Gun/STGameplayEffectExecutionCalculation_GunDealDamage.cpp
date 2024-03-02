// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/STGameplayEffectExecutionCalculation_GunDealDamage.h"

#include "AttributeSets/ASSEAttributeSet_Health.h"
#include "AbilitySystem/Types/STGameplayEffectTypes.h"



struct FDamageStatics
{
    FGameplayEffectAttributeCaptureDefinition IncomingDamageDef;

    FDamageStatics()
    {
        IncomingDamageDef = FGameplayEffectAttributeCaptureDefinition(UASSEAttributeSet_Health::GetIncomingDamageAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);
    }
};

static const FDamageStatics& GetDamageStatics()
{
    static FDamageStatics Statics;
    return Statics;
}









USTGameplayEffectExecutionCalculation_GunDealDamage::USTGameplayEffectExecutionCalculation_GunDealDamage()
{
    RelevantAttributesToCapture.Add(GetDamageStatics().IncomingDamageDef);
}

void USTGameplayEffectExecutionCalculation_GunDealDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();
    UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();

    if (!IsValid(SourceAbilitySystemComponent) || !IsValid(TargetAbilitySystemComponent))
    {
        return;
    }


    AActor* SourceActor = SourceAbilitySystemComponent->GetAvatarActor();
    AActor* TargetActor = TargetAbilitySystemComponent->GetAvatarActor();

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    FGameplayTagContainer AssetTags;
    Spec.GetAllAssetTags(AssetTags);

    // Gather the tags from the source and target as that can affect how the damage might be calulated
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();


    FGameplayEffectSpec* MutableSpec = ExecutionParams.GetOwningSpecForPreExecuteMod();
    FSTGameplayEffectContext_Shooter* Context = static_cast<FSTGameplayEffectContext_Shooter*>(MutableSpec->GetContext().Get());



    // Needed parameter for AttemptCalculateCapturedAttributeMagnitude()
    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;








    //// Lets get the values we need for our damage calculation (ie. source/target attributes, passed in values)
    //float RawDamage = 0.0f;
    //ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().OutgoingDamageDef, EvaluationParameters, RawDamage);

    //// Example for if you want to get a SetByCaller
    //const float totalDistanceBulletTraveled = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("SetByCaller.RicochetsBeforeHit"), true, 0);        // This is not an actual SetByCaller, just an example

    // Lets get our effect context's data
    const float BulletSpeedAtImpact = Context->GetHitInfo().BulletSpeedAtImpact;

    // Lets start calculating
    float DamageToApply = BulletSpeedAtImpact;

















    // Set the Target's IncomingDamage meta attribute
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageStatics().IncomingDamageDef.AttributeToCapture, EGameplayModOp::Additive, DamageToApply));
}
