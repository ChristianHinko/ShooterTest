// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/UW_Ammo.h"

#include "Inventory/Item/AS_Ammo.h"
#include "Subobjects/O_ClipAmmo.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "Inventory/Item/Gun/ArcItemStack_Gun.h"
#include "Components/TextBlock.h"



UUW_Ammo::UUW_Ammo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttributesToListenFor.Add(UAS_Ammo::GetBackupAmmoAttribute());
}

void UUW_Ammo::OnPlayerASCValid()
{
	Super::OnPlayerASCValid();


	// Get ClipAmmo subobject
	if (const FGAAI_Shooter* ShooterActorInfo = static_cast<const FGAAI_Shooter*>(PlayerASC->AbilityActorInfo.Get()))
	{
		USSArcInventoryComponent_Active* InventoryComponent = ShooterActorInfo->GetInventoryComponent();
		if (IsValid(InventoryComponent))
		{
			const UArcItemStack* ActiveItemStack = InventoryComponent->GetActiveItemStack();
			if (IsValid(ActiveItemStack))
			{
				const UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(ActiveItemStack);
				if (IsValid(GunStack))
				{
					ClipAmmoSubobject = GunStack->GetClipAmmoSubobject();
				}
			}
		}
	}

	if (IsValid(ClipAmmoSubobject))
	{
		ClipAmmoSubobject->OnClipAmmoChange.Get().AddDynamic(this, &UUW_Ammo::OnClipAmmoChange);

		const float& ClipAmmo = ClipAmmoSubobject->ClipAmmo;
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
	FString ClipAmmoString = FString::FromInt(FMath::TruncToInt(CurrentClipAmmo)) + TEXT("/");
	ClipAmmoText->SetText(FText::FromString(ClipAmmoString));

	BackupAmmoText->SetText(FText::AsNumber(FMath::TruncToInt(CurrentBackupAmmo)));
}


void UUW_Ammo::NativeDestruct()
{
	if (ClipAmmoSubobject)
	{
		ClipAmmoSubobject->OnClipAmmoChange.Get().RemoveAll(this);
	}


	Super::NativeDestruct();
}
