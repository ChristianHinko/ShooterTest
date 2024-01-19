// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Fragments/STItemFragment_ClipAmmo.h"

#include "Modular/ArcItemStackModular.h"
#include "Net/UnrealNetwork.h"

USTItemFragment_ClipAmmo::USTItemFragment_ClipAmmo()
	: ClipAmmo(this, TEXT("ClipAmmo"), 0)
{
	ClipAmmo.ValueChangeDelegate.AddStatic(&GCPropertyWrapperOnChangePrintString<FGCInt32PropertyWrapper, int32>);
}

USTItemFragment_ClipAmmoInstanced& USTItemFragment_ClipAmmo::GetOrCreateInstancedClipAmmoFragment(UArcItemStackModular* itemStack) const
{
	check(itemStack);

	// Make sure it's not already initialized
	USTItemFragment_ClipAmmoInstanced* instancedFragment = itemStack->FindFirstFragment<USTItemFragment_ClipAmmoInstanced>();
	if (instancedFragment)
	{
		return *instancedFragment;
	}

	// Create instanced fragment
	instancedFragment = itemStack->AddFragment<USTItemFragment_ClipAmmoInstanced>();

	checkf(instancedFragment, TEXT("Failed to add instanced fragment."));
	instancedFragment->FragmentTags = FragmentTags;

	return *instancedFragment;
}

void USTItemFragment_ClipAmmoInstanced::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(USTItemFragment_ClipAmmoInstanced, ClipAmmo, Params);
}

USTItemFragment_ClipAmmoInstanced::USTItemFragment_ClipAmmoInstanced()
	: ClipAmmo(this, TEXT("ClipAmmo"), 0)
{
	ClipAmmo.ValueChangeDelegate.AddStatic(&GCPropertyWrapperOnChangePrintString<FGCInt32PropertyWrapper, int32>);
}
