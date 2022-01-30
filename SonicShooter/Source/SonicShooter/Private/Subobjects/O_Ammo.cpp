// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_Ammo.h"

#include "Net/UnrealNetwork.h"



void UO_Ammo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(UO_Ammo, ClipAmmo, Params);

}

UO_Ammo::UO_Ammo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ClipAmmo(0.f/*GetMaxClipAmmo()*/, this, FName("ClipAmmo"))
	, OnClipAmmoChange(MakeShared<FFloatValueChange>())
{
	ClipAmmo.SetValueChangeDelegate(OnClipAmmoChange);

}
