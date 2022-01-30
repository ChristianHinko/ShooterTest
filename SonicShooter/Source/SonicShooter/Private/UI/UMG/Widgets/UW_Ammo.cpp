// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/UW_Ammo.h"

#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"
#include "UI/UMG/Widgets/UW_ActiveItem.h"
#include "Item/AS_Ammo.h"
#include "Subobjects/O_Ammo.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "Item/Weapons/GunStack.h"
#include "Components/TextBlock.h"



UUW_Ammo::UUW_Ammo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttributesToListenFor.Add(UAS_Ammo::GetBackupAmmoAttribute());
}

void UUW_Ammo::OnPlayerASCValid()
{
	Super::OnPlayerASCValid();


	// Get ammo subobject
	if (const FGAAI_Shooter* ShooterActorInfo = static_cast<const FGAAI_Shooter*>(PlayerASC->AbilityActorInfo.Get()))
	{
		USSArcInventoryComponent_Active* InventoryComponent = ShooterActorInfo->GetInventoryComponent();
		if (IsValid(InventoryComponent))
		{
			const UArcItemStack* ActiveItemStack = InventoryComponent->GetActiveItemStack();
			if (IsValid(ActiveItemStack))
			{
				const UGunStack* GunStack = Cast<UGunStack>(ActiveItemStack);
				if (IsValid(GunStack))
				{
					AmmoSubobject = GunStack->GetAmmoSubobject();
				}
			}
		}
	}

	if (IsValid(AmmoSubobject))
	{
		AmmoSubobject->OnClipAmmoChange.Get().AddDynamic(this, &UUW_Ammo::OnClipAmmoChange);

		const float& ClipAmmo = AmmoSubobject->ClipAmmo;
		OnClipAmmoChange(ClipAmmo, ClipAmmo);
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
	CurrentClipAmmo = NewClipAmmo;
	UpdateAmmoStatus();
}
void UUW_Ammo::SetBackupAmmo(float NewBackupAmmo)
{
	CurrentBackupAmmo = NewBackupAmmo;
	UpdateAmmoStatus();
}

void UUW_Ammo::UpdateAmmoStatus()
{
	FString clipText = FString::FromInt(FMath::TruncToFloat(CurrentClipAmmo)) + "/";
	ClipAmmoText->SetText(FText::FromString(clipText));


	BackupAmmoText->SetText(FText::FromString(FString::FromInt(FMath::TruncToFloat(CurrentBackupAmmo))));
}


void UUW_Ammo::NativeDestruct()
{
	if (AmmoSubobject)
	{
		AmmoSubobject->OnClipAmmoChange.Get().RemoveAll(this);
	}


	Super::NativeDestruct();
}
