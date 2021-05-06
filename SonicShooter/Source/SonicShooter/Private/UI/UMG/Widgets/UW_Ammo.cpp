// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/UW_Ammo.h"
#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"
#include "UI/UMG/Widgets/UW_ActiveItem.h"

#include "Item/AS_Ammo.h"



UUW_Ammo::UUW_Ammo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttributesToListenFor.Add(UAS_Ammo::GetBackupAmmoAttribute());
}

void UUW_Ammo::OnPlayerASCValid()
{
	Super::OnPlayerASCValid();


	ShooterASC = Cast<UASC_Shooter>(PlayerASC);
	if (ShooterASC)
	{
		ShooterASC->OnClipAmmoChange->AddDynamic(this, &UUW_Ammo::OnClipAmmoChange);


		// Search for an Ammo AttributeSet
		for (UAttributeSet* AttributeSet : PlayerASC->GetSpawnedAttributes_Mutable())
		{
			if (UAS_Ammo* AmmoAttributeSet = Cast<UAS_Ammo>(AttributeSet))
			{
				// Call manually for initial value
				float clipAmmo = AmmoAttributeSet->ClipAmmo;
				OnClipAmmoChange(clipAmmo, clipAmmo);
			}
		}
	}

}

void UUW_Ammo::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	const FGameplayAttribute Attribute = Data.Attribute;
	const float NewValue = Data.NewValue;


	if (Attribute == UAS_Ammo::GetBackupAmmoAttribute())
	{
		SetBackupAmmo(NewValue);
	}
}

void UUW_Ammo::OnClipAmmoChange(const float& OldValue, const float& NewValue)
{
	SetClipAmmo(NewValue);
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


void UUW_Ammo::NativeDestruct()
{
	if (ShooterASC)
	{
		ShooterASC->OnClipAmmoChange->RemoveAll(this);
	}


	Super::NativeDestruct();
}
