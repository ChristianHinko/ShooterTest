// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttributeSets/SSAttributeSet_CharacterMovement.h"

#include "Net/UnrealNetwork.h"

#include "Kismet/KismetSystemLibrary.h"



void USSAttributeSet_CharacterMovement::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_CharacterMovement, WalkSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_CharacterMovement, WalkAcceleration, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_CharacterMovement, RunSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_CharacterMovement, RunAccelaration, Params);
}

//	These are default values BEFORE the default attribute values effect gets applied
USSAttributeSet_CharacterMovement::USSAttributeSet_CharacterMovement(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, WalkSpeed(300.f)
	, WalkAcceleration(2048.f)
	, RunSpeed(600.f)
	, RunAccelaration(4096.f)
{


}



// OnReps:


void USSAttributeSet_CharacterMovement::OnRep_WalkSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_CharacterMovement, WalkSpeed, ServerBaseValue);
}

void USSAttributeSet_CharacterMovement::OnRep_WalkAcceleration(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_CharacterMovement, WalkAcceleration, ServerBaseValue);
}

void USSAttributeSet_CharacterMovement::OnRep_RunSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_CharacterMovement, RunSpeed, ServerBaseValue);
}

void USSAttributeSet_CharacterMovement::OnRep_RunAccelaration(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_CharacterMovement, RunAccelaration, ServerBaseValue);
}
