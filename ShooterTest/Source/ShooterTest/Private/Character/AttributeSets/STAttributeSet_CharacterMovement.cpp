// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttributeSets/STAttributeSet_CharacterMovement.h"

#include "Net/UnrealNetwork.h"

#include "Kismet/KismetSystemLibrary.h"



void USTAttributeSet_CharacterMovement::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_CharacterMovement, WalkSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_CharacterMovement, WalkAcceleration, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_CharacterMovement, RunSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_CharacterMovement, RunAccelaration, Params);
}

//	These are default values BEFORE the default attribute values effect gets applied
USTAttributeSet_CharacterMovement::USTAttributeSet_CharacterMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, WalkSpeed(300.f)
	, WalkAcceleration(2048.f)
	, RunSpeed(600.f)
	, RunAccelaration(4096.f)
{
}



// OnReps

void USTAttributeSet_CharacterMovement::OnRep_WalkSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_CharacterMovement, WalkSpeed, OldValue);
}

void USTAttributeSet_CharacterMovement::OnRep_WalkAcceleration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_CharacterMovement, WalkAcceleration, OldValue);
}

void USTAttributeSet_CharacterMovement::OnRep_RunSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_CharacterMovement, RunSpeed, OldValue);
}

void USTAttributeSet_CharacterMovement::OnRep_RunAccelaration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_CharacterMovement, RunAccelaration, OldValue);
}