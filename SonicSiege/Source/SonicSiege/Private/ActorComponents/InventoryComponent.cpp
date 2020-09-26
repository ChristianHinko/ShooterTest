// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/InventoryComponent.h"

#include "Actor/Weapon/Weapon.h"



void FFASI_Weapon::PreReplicatedRemove(const FFAS_Weapons& InArraySerializer)
{

}
void FFASI_Weapon::PostReplicatedAdd(const FFAS_Weapons& InArraySerializer)
{

}
void FFASI_Weapon::PostReplicatedChange(const FFAS_Weapons& InArraySerializer)
{

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



UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


/////////////////////////////////////////////////////////////////////////// UNTESTED AND NEEDS WORK!!!!! \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
int32 UInventoryComponent::AddWeaponToInventory(AWeapon* Weapon)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		return -1;
	}

	FFASI_Weapon WeaponItem;
	WeaponItem.Weapon = Weapon;

	Weapons.Items.Add(WeaponItem);
	Weapons.MarkArrayDirty();



	// Come up with how to assign right index before returning



	return WeaponItem.index;
}
bool UInventoryComponent::RemoveWeaponFromInventory(AWeapon* Weapon)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		return false;
	}


	for (int32 i = 0; i < Weapons.Items.Num(); ++i)
	{
		if (Weapon == Weapons.Items[i].Weapon)
		{
			Weapons.Items.RemoveAt(i);
			Weapons.MarkArrayDirty();
			return true;
		}
	}

	return false;
}
