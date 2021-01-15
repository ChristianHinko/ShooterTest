// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/Weapon.h"

#include "Net/UnrealNetwork.h"
#include "Actor/Weapon/AS_Weapon.h"
#include "AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"



void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AWeapon, FireAbilitySpecHandle);
}


AWeapon::AWeapon()
{

}
void AWeapon::BeginPlay()
{
	Super::BeginPlay();


	BulletTraceTargetActor = GetWorld()->SpawnActor<AGATA_BulletTrace>(BulletTraceTargetActorTSub);
	BulletTraceTargetActor->bDestroyOnConfirmation = false;
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


	if (WeaponAttributeSet && !GetAbilitySystemComponent()->GetSpawnedAttributes().Contains(WeaponAttributeSet))
	{
		GetAbilitySystemComponent()->AddAttributeSetSubobject(WeaponAttributeSet);
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogWeapon, Warning, TEXT("%s() WeaponAttributeSet was either NULL or already added to the actor's ASC. Actor: %s"), *FString(__FUNCTION__), *GetName());
	}
}

bool AWeapon::GrantStartingAbilities()
{
	if (Super::GrantStartingAbilities() == false)
	{
		return false;	// Did not pass predefined checks
	}
	//	We are on authority and have a valid ASC to work with

	FireAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(FireAbilityTSub, this, EAbilityInputID::PrimaryFire/*, GetLevel()*/);

	return true;
}
