// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/SSGameplayEffectExecutionCalculation_InitStamina.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"

#include "Character/SSCharacterMovementComponent_Shooter.h"
#include "AbilitySystem/AttributeSets/SSAttributeSet_Stamina.h"
#include "Subobjects/SSObject_Stamina.h"



///////////////////////////////////////////////
/// FStaminaInitializationStatics
///////////////////////////////////////////////

struct FStaminaInitializationStatics
{
	// No need to capture these Attributes since we aren't reading from them, but writing to them

	FStaminaInitializationStatics()
	{
	}
};

static const FStaminaInitializationStatics& GetStaminaInitializationStatics()
{
	static FStaminaInitializationStatics Statics;
	return Statics;
}



///////////////////////////////////////////////
/// USSGameplayEffectExecutionCalculation_InitStamina
///////////////////////////////////////////////


USSGameplayEffectExecutionCalculation_InitStamina::USSGameplayEffectExecutionCalculation_InitStamina(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	const USSAttributeSet_Stamina* DefaultAttributeSet = GetDefault<USSAttributeSet_Stamina>(USSAttributeSet_Stamina::StaticClass());

	// Populate defaults for easy BP editing
	MaxStamina = DefaultAttributeSet->GetMaxStamina();
	StaminaDrain = DefaultAttributeSet->GetStaminaDrain();
	StaminaGain = DefaultAttributeSet->GetStaminaGain();
	StaminaRegenPause = DefaultAttributeSet->GetStaminaRegenPause();
}

void USSGameplayEffectExecutionCalculation_InitStamina::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSSAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init stamina"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_Stamina::GetMaxStaminaAttribute(),				EGameplayModOp::Override, MaxStamina));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_Stamina::GetStaminaDrainAttribute(),			EGameplayModOp::Override, StaminaDrain));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_Stamina::GetStaminaGainAttribute(),				EGameplayModOp::Override, StaminaGain));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_Stamina::GetStaminaRegenPauseAttribute(),		EGameplayModOp::Override, StaminaRegenPause));





	// Calculate defaults
	float Stamina = MaxStamina;
	// Get stamina subobject and initialize Stamina
	if (const FSSGameplayAbilityActorInfo_Shooter* ShooterActorInfo = static_cast<const FSSGameplayAbilityActorInfo_Shooter*>(TargetAbilitySystemComponent->AbilityActorInfo.Get()))
	{
		USSCharacterMovementComponent_Shooter* CMC = Cast<USSCharacterMovementComponent_Shooter>(ShooterActorInfo->GetSSCharacterMovementComponent());
		if (IsValid(CMC))
		{
			CMC->GetStaminaSubobject()->Stamina = Stamina;
			CMC->GetStaminaSubobject()->Stamina.MarkNetDirty(); // we are server-only right now so replicate it
		}
	}
}
