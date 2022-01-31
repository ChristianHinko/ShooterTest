// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_Stamina.h"

#include "Net/UnrealNetwork.h"



void UO_Stamina::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(UO_Stamina, Stamina, Params);

}

UO_Stamina::UO_Stamina(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, OnStaminaChange(MakeShared<FFloatValueChange>())
	, Stamina(this, FName("Stamina"), OnStaminaChange)
{
	Stamina = 0.f;

}


bool UO_Stamina::IsTickable() const
{
	return false;
}
void UO_Stamina::Tick(float DeltaTime)
{

}
