// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/STObject_ClipAmmo.h"

#include "Net/UnrealNetwork.h"



void USTObject_ClipAmmo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(USTObject_ClipAmmo, ClipAmmo, Params);

}
bool USTObject_ClipAmmo::IsSupportedForNetworking() const
{
	return true;
}
bool USTObject_ClipAmmo::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = false;

	return bWroteSomething;
}

USTObject_ClipAmmo::USTObject_ClipAmmo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ClipAmmo(this, TEXT("ClipAmmo"), 0)
{

}
