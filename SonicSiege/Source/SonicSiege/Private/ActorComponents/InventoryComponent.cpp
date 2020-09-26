// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/InventoryComponent.h"



UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void FFASI_Equipment::PreReplicatedRemove(const FFAS_Equipments& InArraySerializer)
{

}
void FFASI_Equipment::PostReplicatedAdd(const FFAS_Equipments& InArraySerializer)
{

}
void FFASI_Equipment::PostReplicatedChange(const FFAS_Equipments& InArraySerializer)
{

}

void FFASI_Weapon::PreReplicatedRemove(const FFAS_Weapons& InArraySerializer)
{

}
void FFASI_Weapon::PostReplicatedAdd(const FFAS_Weapons& InArraySerializer)
{

}
void FFASI_Weapon::PostReplicatedChange(const FFAS_Weapons& InArraySerializer)
{

}
