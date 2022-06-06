// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/SSObject_ClipAmmo.h"

#include "Net/UnrealNetwork.h"



void USSObject_ClipAmmo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(USSObject_ClipAmmo, ClipAmmo, Params);

}
bool USSObject_ClipAmmo::IsSupportedForNetworking() const
{
	return true;
}
bool USSObject_ClipAmmo::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = false;

	return bWroteSomething;
}

USSObject_ClipAmmo::USSObject_ClipAmmo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ClipAmmo(this, TEXT("ClipAmmo"), 0.f)
{

}
