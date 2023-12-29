// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory\Item\Fragments\STItemFragment_ClipAmmo.h"

#include "Net/UnrealNetwork.h"

void USTItemFragment_ClipAmmo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(USTItemFragment_ClipAmmo, ClipAmmo, Params);

}
bool USTItemFragment_ClipAmmo::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = false;

	return bWroteSomething;
}

USTItemFragment_ClipAmmo::USTItemFragment_ClipAmmo()
	: ClipAmmo(this, TEXT("ClipAmmo"), 0)
{
	ClipAmmo.ValueChangeDelegate.AddStatic(&GCPropertyWrapperOnChangePrintString<FGCInt32PropertyWrapper, int32>);
}
