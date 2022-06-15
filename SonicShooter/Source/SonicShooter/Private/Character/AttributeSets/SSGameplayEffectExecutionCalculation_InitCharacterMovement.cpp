// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttributeSets/SSGameplayEffectExecutionCalculation_InitCharacterMovement.h"

#include "Character/AttributeSets/SSAttributeSet_CharacterMovement.h"



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
/// USSGameplayEffectExecutionCalculation_InitCharacterMovement
///////////////////////////////////////////////


USSGameplayEffectExecutionCalculation_InitCharacterMovement::USSGameplayEffectExecutionCalculation_InitCharacterMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	const USSAttributeSet_CharacterMovement* DefaultAttributeSet = GetDefault<USSAttributeSet_CharacterMovement>(USSAttributeSet_CharacterMovement::StaticClass());

	// Populate defaults for easy BP editing
	WalkSpeed = DefaultAttributeSet->GetWalkSpeed();
	WalkAcceleration = DefaultAttributeSet->GetWalkAcceleration();
	RunSpeed = DefaultAttributeSet->GetRunSpeed();
	RunAccelaration = DefaultAttributeSet->GetRunAccelaration();
}

void USSGameplayEffectExecutionCalculation_InitCharacterMovement::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSSAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init Character Movement"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_CharacterMovement::GetWalkSpeedAttribute(),				EGameplayModOp::Override, WalkSpeed));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_CharacterMovement::GetWalkAccelerationAttribute(),		EGameplayModOp::Override, WalkAcceleration));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_CharacterMovement::GetRunSpeedAttribute(),				EGameplayModOp::Override, RunSpeed));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_CharacterMovement::GetRunAccelarationAttribute(),		EGameplayModOp::Override, RunAccelaration));

}
