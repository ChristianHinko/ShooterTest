// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/UW_Ammo.h"

#include "Item/AS_Ammo.h"



UUW_Ammo::UUW_Ammo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttributesToListenFor.Add(UAS_Ammo::GetClipAmmoAttribute());
	AttributesToListenFor.Add(UAS_Ammo::GetBackupAmmoAttribute());
}


void UUW_Ammo::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	const FGameplayAttribute Attribute = Data.Attribute;
	const float NewValue = Data.NewValue;


	if (Attribute == UAS_Ammo::GetClipAmmoAttribute())
	{
		SetClipAmmo(NewValue);
	}

	if (Attribute == UAS_Ammo::GetBackupAmmoAttribute())
	{
		SetBackupAmmo(NewValue);
	}
}

void UUW_Ammo::SetClipAmmo(float NewClipAmmo)
{
	ClipAmmo = NewClipAmmo;
	UpdateAmmoStatus();
}

void UUW_Ammo::SetBackupAmmo(float NewBackupAmmo)
{
	BackupAmmo = NewBackupAmmo;
	UpdateAmmoStatus();
}
