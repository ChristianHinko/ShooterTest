// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttributeSets/GEEC_InitCharacterMovement.h"

#include "Character/AttributeSets/AS_CharacterMovement.h"



///////////////////////////////////////////////
/// FCharacterMovementInitializationStatics
///////////////////////////////////////////////

struct FCharacterMovementInitializationStatics
{
	// No need to capture these Attributes since we aren't reading from them, but writing to them
	const FGameplayAttribute WalkSpeedAttribute;
	const FGameplayAttribute WalkAccelerationAttribute;
	const FGameplayAttribute RunSpeedAttribute;
	const FGameplayAttribute RunAccelarationAttribute;


	FCharacterMovementInitializationStatics()
		: WalkSpeedAttribute(UAS_CharacterMovement::GetWalkSpeedAttribute())
		, WalkAccelerationAttribute(UAS_CharacterMovement::GetWalkAccelerationAttribute())
		, RunSpeedAttribute(UAS_CharacterMovement::GetRunSpeedAttribute())
		, RunAccelarationAttribute(UAS_CharacterMovement::GetRunAccelarationAttribute())
	{

	}
};

static const FCharacterMovementInitializationStatics& GetCharacterMovementInitializationStatics()
{
	static FCharacterMovementInitializationStatics Statics;
	return Statics;
}



///////////////////////////////////////////////
/// UGEEC_InitCharacterMovement
///////////////////////////////////////////////


UGEEC_InitCharacterMovement::UGEEC_InitCharacterMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	const UAS_CharacterMovement* DefaultAttributeSet = GetDefault<UAS_CharacterMovement>(UAS_CharacterMovement::StaticClass());

	// Populate defaults
	WalkSpeed = DefaultAttributeSet->GetWalkSpeed();
	WalkAcceleration = DefaultAttributeSet->GetWalkAcceleration();
	RunSpeed = DefaultAttributeSet->GetRunSpeed();
	RunAccelaration = DefaultAttributeSet->GetRunAccelaration();
}

void UGEEC_InitCharacterMovement::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSSAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init Character Movement"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetCharacterMovementInitializationStatics().WalkSpeedAttribute,					EGameplayModOp::Override, WalkSpeed));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetCharacterMovementInitializationStatics().WalkAccelerationAttribute,			EGameplayModOp::Override, WalkAcceleration));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetCharacterMovementInitializationStatics().RunSpeedAttribute,					EGameplayModOp::Override, RunSpeed));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetCharacterMovementInitializationStatics().RunAccelarationAttribute,			EGameplayModOp::Override, RunAccelaration));

}
