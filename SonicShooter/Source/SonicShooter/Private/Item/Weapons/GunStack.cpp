// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/GunStack.h"

#include "Net/UnrealNetwork.h"



void UGunStack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UGunStack, BulletTraceTargetActorTSub, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UGunStack, BulletHitEffectTSub, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UGunStack, FiringMode, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UGunStack, FireRate, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UGunStack, NumBursts, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UGunStack, AutoShootingRate, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UGunStack, AmmoCost, COND_OwnerOnly);
}
