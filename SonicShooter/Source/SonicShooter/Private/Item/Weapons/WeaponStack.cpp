// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/WeaponStack.h"

#include "Net/UnrealNetwork.h"



void UWeaponStack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UWeaponStack, BulletTraceTargetActorTSub, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWeaponStack, BulletHitEffectTSub, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWeaponStack, FiringMode, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWeaponStack, FireRate, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWeaponStack, NumBursts, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWeaponStack, AutoShootingRate, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWeaponStack, AmmoCost, COND_OwnerOnly);
}
