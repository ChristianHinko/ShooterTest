// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_ClipAmmo.h"

#include "Net/UnrealNetwork.h"



void UO_ClipAmmo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(UO_ClipAmmo, ClipAmmo, Params);

}
bool UO_ClipAmmo::IsSupportedForNetworking() const
{
	return true;
}
bool UO_ClipAmmo::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = false;

	return bWroteSomething;
}

UO_ClipAmmo::UO_ClipAmmo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ClipAmmo(0.f, this, TEXT("ClipAmmo"))
{

}
