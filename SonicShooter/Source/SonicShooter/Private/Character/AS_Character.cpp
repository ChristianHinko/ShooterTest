// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AS_Character.h"

#include "Net/UnrealNetwork.h"
#include "GameplayAbilities/Public/GameplayEffectExtension.h"

#include "Kismet/KismetSystemLibrary.h"



void UAS_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Character, WalkSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Character, WalkAcceleration, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Character, RunSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Character, RunAccelaration, Params);
}

//	These are default values BEFORE the default attribute values effect gets applied
UAS_Character::UAS_Character()
	: WalkSpeed(300.f),
	WalkAcceleration(2048.f),
	RunSpeed(600.f),
	RunAccelaration(4096.f)
{
	SetSoftAttributeDefaults();
	

}

void UAS_Character::SetSoftAttributeDefaults()
{
	Super::SetSoftAttributeDefaults();



}

bool UAS_Character::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	Super::PreGameplayEffectExecute(Data);

	const FGameplayAttribute AttributeToModify = Data.EvaluatedData.Attribute;
	

	return true;
}
void UAS_Character::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute ModifiedAttribute = Data.EvaluatedData.Attribute;



}



// OnReps:


void UAS_Character::OnRep_WalkSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, WalkSpeed, ServerBaseValue);
}

void UAS_Character::OnRep_WalkAcceleration(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, WalkAcceleration, ServerBaseValue);
}

void UAS_Character::OnRep_RunSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, RunSpeed, ServerBaseValue);
}

void UAS_Character::OnRep_RunAccelaration(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, RunAccelaration, ServerBaseValue);
}
