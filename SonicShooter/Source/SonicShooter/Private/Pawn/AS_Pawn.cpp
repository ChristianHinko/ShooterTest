// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/AS_Pawn.h"

#include "Net/UnrealNetwork.h"



void UAS_Pawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Pawn, MyPawnAttribute, Params);
}

UAS_Pawn::UAS_Pawn()
	: MyPawnAttribute(75)
{

}


void UAS_Pawn::OnRep_MyPawnAttribute(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Pawn, MyPawnAttribute, ServerBaseValue);
}
