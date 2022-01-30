// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/GunStack.h"

#include "Net/UnrealNetwork.h"
#include "Subobjects/O_Ammo.h"



void UGunStack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UGunStack, BulletTraceTargetActorTSub, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UGunStack, BulletHitEffectTSub, COND_OwnerOnly);
}

UGunStack::UGunStack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AmmoSubobject = CreateDefaultSubobject<UO_Ammo>(TEXT("AmmoSubobject"));

}
