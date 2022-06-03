// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AS_PlayerState.h"

#include "Net/UnrealNetwork.h"



void UAS_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_PlayerState, ExampleAttribute, Params);
}

UAS_PlayerState::UAS_PlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ExampleAttribute(100)
{

}


void UAS_PlayerState::OnRep_ExampleAttribute(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_PlayerState, ExampleAttribute, ServerBaseValue);
}
