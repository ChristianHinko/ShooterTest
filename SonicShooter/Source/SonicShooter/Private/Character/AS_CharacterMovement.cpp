// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AS_CharacterMovement.h"

#include "Net/UnrealNetwork.h"
#include "GameplayAbilities/Public/GameplayEffectExtension.h"

#include "Kismet/KismetSystemLibrary.h"



void UAS_CharacterMovement::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_CharacterMovement, WalkSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_CharacterMovement, WalkAcceleration, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_CharacterMovement, RunSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_CharacterMovement, RunAccelaration, Params);
}

//	These are default values BEFORE the default attribute values effect gets applied
UAS_CharacterMovement::UAS_CharacterMovement()
	: WalkSpeed(300.f),
	WalkAcceleration(2048.f),
	RunSpeed(600.f),
	RunAccelaration(4096.f)
{
	SetSoftAttributeDefaults();


}

void UAS_CharacterMovement::SetSoftAttributeDefaults()
{
	Super::SetSoftAttributeDefaults();



}

bool UAS_CharacterMovement::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	Super::PreGameplayEffectExecute(Data);

	const FGameplayAttribute AttributeToModify = Data.EvaluatedData.Attribute;


	return true;
}
void UAS_CharacterMovement::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute ModifiedAttribute = Data.EvaluatedData.Attribute;



}



// OnReps:


void UAS_CharacterMovement::OnRep_WalkSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_CharacterMovement, WalkSpeed, ServerBaseValue);
}

void UAS_CharacterMovement::OnRep_WalkAcceleration(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_CharacterMovement, WalkAcceleration, ServerBaseValue);
}

void UAS_CharacterMovement::OnRep_RunSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_CharacterMovement, RunSpeed, ServerBaseValue);
}

void UAS_CharacterMovement::OnRep_RunAccelaration(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_CharacterMovement, RunAccelaration, ServerBaseValue);
}
