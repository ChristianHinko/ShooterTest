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
bool UO_Ammo::IsSupportedForNetworking() const
{
	return true;
}
bool UO_Ammo::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = false;

	return bWroteSomething;
}

UO_Ammo::UO_Ammo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, OnClipAmmoChange(MakeShared<FFloatValueChange>())
	, ClipAmmo(0.f, this, FName("ClipAmmo"), OnClipAmmoChange)
{

}
