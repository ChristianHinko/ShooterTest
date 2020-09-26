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
	FFASI_Weapon WeaponItem;
	WeaponItem.Weapon = Weapon;

	Weapons.Items.Add(WeaponItem);
	Weapons.MarkArrayDirty();



	// Come up with how to assign right index before returning



	return WeaponItem.index;
}
bool UInventoryComponent::RemoveWeaponFromInventory(AWeapon* Weapon)
{
	bool retVal = false;

	for (int32 i = 0; i < Weapons.Items.Num(); ++i)
	{
		if (Weapon == Weapons.Items[i].Weapon)
		{
			// The reason we aren't just returning true right here is because this allows it to remove multiple of the same references in the array if there are any
			Weapons.Items.RemoveAt(i);
			retVal = true;
		}
	}

	// If we removed something, mark the array dirty
	if (retVal == true)
	{
		Weapons.MarkArrayDirty();
	}

	return retVal;
}
