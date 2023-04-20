// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/STGameplayEffectExecutionCalculation_InitStamina.h"
#include "AbilitySystem/Types/STGameplayAbilityTypes.h"

#include "Character/STCharacterMovementComponent_Shooter.h"
#include "AbilitySystem/AttributeSets/STAttributeSet_Stamina.h"
#include "Subobjects/STObject_Stamina.h"



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
/// USTGameplayEffectExecutionCalculation_InitStamina
///////////////////////////////////////////////


USTGameplayEffectExecutionCalculation_InitStamina::USTGameplayEffectExecutionCalculation_InitStamina(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USTGameplayEffectExecutionCalculation_InitStamina::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSTAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init stamina"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Stamina::GetMaxStaminaAttribute(),				EGameplayModOp::Override, MaxStamina));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Stamina::GetStaminaDrainAttribute(),			EGameplayModOp::Override, StaminaDrain));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Stamina::GetStaminaGainAttribute(),				EGameplayModOp::Override, StaminaGain));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Stamina::GetStaminaRegenPauseAttribute(),		EGameplayModOp::Override, StaminaRegenPause));





	// Calculate defaults
	float Stamina = MaxStamina;
	// Get stamina subobject and initialize Stamina
	if (const FSTGameplayAbilityActorInfo_Shooter* ShooterActorInfo = static_cast<const FSTGameplayAbilityActorInfo_Shooter*>(TargetAbilitySystemComponent->AbilityActorInfo.Get()))
	{
		USTCharacterMovementComponent_Shooter* CMC = Cast<USTCharacterMovementComponent_Shooter>(ShooterActorInfo->STCharacterMovementComponent);
		if (IsValid(CMC))
		{
			CMC->GetStaminaSubobject()->Stamina = Stamina;
			CMC->GetStaminaSubobject()->Stamina.MarkNetDirty(); // we are server-only right now so replicate it
		}
	}
}
