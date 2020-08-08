// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Weapon/Weapon.h"
#include "Actor/Item/Weapon/AS_Weapon.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"

AWeapon::AWeapon()
{

}


void AWeapon::CreateAttributeSets()
{
	Super::CreateAttributeSets();


	if (!WeaponAttributeSet)
	{
		WeaponAttributeSet = NewObject<UAS_Weapon>(this, UAS_Weapon::StaticClass(), TEXT("WeaponAttributeSet"));
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogWeapon, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), *FString(__FUNCTION__), *WeaponAttributeSet->GetName());
	}
}
void AWeapon::RegisterAttributeSets()
{
	Super::RegisterAttributeSets();


	if (WeaponAttributeSet && !GetAbilitySystemComponent()->SpawnedAttributes.Contains(WeaponAttributeSet))
	{
		GetAbilitySystemComponent()->AddAttributeSetSubobject(WeaponAttributeSet);
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogWeapon, Warning, TEXT("%s() WeaponAttributeSet was either NULL or already added to the character's ASC. Character: %s"), *FString(__FUNCTION__), *GetName());
	}
}
