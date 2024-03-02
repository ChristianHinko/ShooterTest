// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/Item/Fragments/STItemFragment_ClipAmmo.h"

#include "Net/UnrealNetwork.h"

USTItemFragment_ClipAmmoInstanced::USTItemFragment_ClipAmmoInstanced()
    : ClipAmmo(this, TEXT("ClipAmmo"), 0)
{
    ClipAmmo.ValueChangeDelegate.AddStatic(&GCPropertyWrapperOnChangePrintString<FGCInt32PropertyWrapper, int32>);
}

void USTItemFragment_ClipAmmoInstanced::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    FDoRepLifetimeParams params;
    params.Condition = COND_None;
    params.RepNotifyCondition = REPNOTIFY_OnChanged;
    params.bIsPushBased = true;

    DOREPLIFETIME_WITH_PARAMS_FAST(USTItemFragment_ClipAmmoInstanced, ClipAmmo, params);
}
