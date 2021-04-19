// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AS_Actor.h"

#include "Net/UnrealNetwork.h"



void UAS_Actor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Actor, MyActorAttribute, Params);
}

UAS_Actor::UAS_Actor()
	: MyActorAttribute(75)
{

}


void UAS_Actor::OnRep_MyActorAttribute(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Actor, MyActorAttribute, ServerBaseValue);
}
