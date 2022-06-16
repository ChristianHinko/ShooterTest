// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSAttributeSet_PlayerState.h"

#include "Net/UnrealNetwork.h"



void USSAttributeSet_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_PlayerState, ExampleAttribute, Params);
}

USSAttributeSet_PlayerState::USSAttributeSet_PlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ExampleAttribute(100)
{
}


// OnReps

void USSAttributeSet_PlayerState::OnRep_ExampleAttribute(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_PlayerState, ExampleAttribute, OldValue);
}
