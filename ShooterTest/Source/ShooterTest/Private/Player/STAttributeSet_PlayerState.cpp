// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STAttributeSet_PlayerState.h"

#include "Net/UnrealNetwork.h"



void USTAttributeSet_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_PlayerState, ExampleAttribute, Params);
}

USTAttributeSet_PlayerState::USTAttributeSet_PlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ExampleAttribute(100)
{
}


// OnReps

void USTAttributeSet_PlayerState::OnRep_ExampleAttribute(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_PlayerState, ExampleAttribute, OldValue);
}
