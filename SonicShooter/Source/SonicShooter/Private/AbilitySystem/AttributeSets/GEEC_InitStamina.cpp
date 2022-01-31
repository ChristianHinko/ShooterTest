// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/GEEC_InitStamina.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"

#include "Character/SSCharacterMovementComponent.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
#include "Subobjects/O_Stamina.h"



///////////////////////////////////////////////
/// FStaminaInitializationStatics
///////////////////////////////////////////////

struct FStaminaInitializationStatics
{
	// No need to capture these Attributes since we aren't reading from them, but writing to them
	const FGameplayAttribute MaxStaminaAttribute;
	const FGameplayAttribute StaminaDrainAttribute;
	const FGameplayAttribute StaminaGainAttribute;
	const FGameplayAttribute StaminaRegenPauseAttribute;


	FStaminaInitializationStatics()
		: MaxStaminaAttribute(UAS_Stamina::GetMaxStaminaAttribute())
		, StaminaDrainAttribute(UAS_Stamina::GetStaminaDrainAttribute())
		, StaminaGainAttribute(UAS_Stamina::GetStaminaGainAttribute())
		, StaminaRegenPauseAttribute(UAS_Stamina::GetStaminaRegenPauseAttribute())
	{

	}
};

static const FStaminaInitializationStatics& GetStaminaInitializationStatics()
{
	static FStaminaInitializationStatics Statics;
	return Statics;
}



///////////////////////////////////////////////
/// UGEEC_InitStamina
///////////////////////////////////////////////


UGEEC_InitStamina::UGEEC_InitStamina(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	const UAS_Stamina* DefaultAttributeSet = GetDefault<UAS_Stamina>(UAS_Stamina::StaticClass());

	// Populate defaults
	MaxStamina = DefaultAttributeSet->GetMaxStamina();
	StaminaDrain = DefaultAttributeSet->GetStaminaDrain();
	StaminaGain = DefaultAttributeSet->GetStaminaGain();
	StaminaRegenPause = DefaultAttributeSet->GetStaminaRegenPause();
}

void UGEEC_InitStamina::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSSAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init stamina"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetStaminaInitializationStatics().MaxStaminaAttribute,				EGameplayModOp::Override, MaxStamina));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetStaminaInitializationStatics().StaminaDrainAttribute,			EGameplayModOp::Override, StaminaDrain));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetStaminaInitializationStatics().StaminaGainAttribute,				EGameplayModOp::Override, StaminaGain));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetStaminaInitializationStatics().StaminaRegenPauseAttribute,		EGameplayModOp::Override, StaminaRegenPause));





	// Calculate defaults
	float Stamina = MaxStamina;
	// Get stamina subobject and initialize Stamina
	if (const FGAAI_Shooter* ShooterActorInfo = static_cast<const FGAAI_Shooter*>(TargetAbilitySystemComponent->AbilityActorInfo.Get()))
	{
		USSCharacterMovementComponent* SSCMC = ShooterActorInfo->GetSSCharacterMovementComponent();
		if (IsValid(SSCMC))
		{
			SSCMC->StaminaSubobject->Stamina = Stamina;
		}
	}
}
