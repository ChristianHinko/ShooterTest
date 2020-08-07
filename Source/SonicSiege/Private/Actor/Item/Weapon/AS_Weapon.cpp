// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Weapon/AS_Weapon.h"

#include "Net/UnrealNetwork.h"



void UAS_Weapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Weapon, CurrentAmmo, COND_None, REPNOTIFY_Always);
}

UAS_Weapon::UAS_Weapon()
	: CurrentAmmo(0)
{

}


void UAS_Weapon::OnRep_CurrentAmmo(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Weapon, CurrentAmmo, ServerBaseValue);
}
