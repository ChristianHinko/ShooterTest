// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttributeSets/STGameplayEffectExecutionCalculation_InitCharacterMovement.h"

#include "Character/AttributeSets/STAttributeSet_CharacterMovement.h"



///////////////////////////////////////////////
/// FCharacterMovementInitializationStatics
///////////////////////////////////////////////

struct FCharacterMovementInitializationStatics
{
	// No need to capture these Attributes since we aren't reading from them, but writing to them

	FCharacterMovementInitializationStatics()
	{
	}
};

static const FCharacterMovementInitializationStatics& GetCharacterMovementInitializationStatics()
{
	static FCharacterMovementInitializationStatics Statics;
	return Statics;
}



///////////////////////////////////////////////
/// USTGameplayEffectExecutionCalculation_InitCharacterMovement
///////////////////////////////////////////////


USTGameplayEffectExecutionCalculation_InitCharacterMovement::USTGameplayEffectExecutionCalculation_InitCharacterMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USTGameplayEffectExecutionCalculation_InitCharacterMovement::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSTAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init Character Movement"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_CharacterMovement::GetWalkSpeedAttribute(),				EGameplayModOp::Override, WalkSpeed));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_CharacterMovement::GetWalkAccelerationAttribute(),		EGameplayModOp::Override, WalkAcceleration));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_CharacterMovement::GetRunSpeedAttribute(),				EGameplayModOp::Override, RunSpeed));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_CharacterMovement::GetRunAccelarationAttribute(),		EGameplayModOp::Override, RunAccelaration));

}
