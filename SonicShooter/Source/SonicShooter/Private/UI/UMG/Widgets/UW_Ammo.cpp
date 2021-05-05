// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/UW_Ammo.h"
#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"
#include "Item/AS_Ammo.h"

#include "Item/AS_Ammo.h"



UUW_Ammo::UUW_Ammo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//AttributesToListenFor.Add(UAS_Ammo::GetClipAmmoAttribute());
	AttributesToListenFor.Add(UAS_Ammo::GetBackupAmmoAttribute());
}

void UUW_Ammo::OnPlayerASCValid()
{
	Super::OnPlayerASCValid();



	if (UASC_Shooter* ShooterASC = Cast<UASC_Shooter>(PlayerASC))
	{
		for (UAttributeSet* AttributeSet : PlayerASC->GetSpawnedAttributes_Mutable())
		{
			if (UAS_Ammo* AmmoAttributeSet = Cast<UAS_Ammo>(AttributeSet))
			{
				ShooterASC->OnClipAmmoChange->AddDynamic(this, &UUW_Ammo::OnClipAmmoChange);

				// Call for initial value
				float clipAmmo = AmmoAttributeSet->ClipAmmo.GetValue();
				OnClipAmmoChange(clipAmmo, clipAmmo);
			}
		}	
	}

}

void UUW_Ammo::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	const FGameplayAttribute Attribute = Data.Attribute;
	const float NewValue = Data.NewValue;


	//if (Attribute == UAS_Ammo::GetClipAmmoAttribute())
	//{
	//	SetClipAmmo(NewValue);
	//}

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
