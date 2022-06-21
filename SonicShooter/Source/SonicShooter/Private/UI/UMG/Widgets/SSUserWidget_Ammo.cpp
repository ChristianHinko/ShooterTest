// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/SSUserWidget_Ammo.h"

#include "Inventory/Item/SSAttributeSet_Ammo.h"
#include "Subobjects/SSObject_ClipAmmo.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "Components/ArcInventoryComponent_Active.h"
#include "Inventory/Item/Gun/SSItemStack_Gun.h"
#include "Components/TextBlock.h"



USSUserWidget_Ammo::USSUserWidget_Ammo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USSUserWidget_Ammo::OnPlayerASCValid()
{
	Super::OnPlayerASCValid();


	// Get ClipAmmo subobject
	if (const FSSGameplayAbilityActorInfo_Shooter* ShooterActorInfo = static_cast<const FSSGameplayAbilityActorInfo_Shooter*>(PlayerASC->AbilityActorInfo.Get()))
	{
		UArcInventoryComponent_Active* InventoryComponentActive = Cast<UArcInventoryComponent_Active>(ShooterActorInfo->InventoryComponent);
		if (IsValid(InventoryComponentActive))
		{
			const UArcItemStack* ActiveItemStack = InventoryComponentActive->GetActiveItemStack();
			if (IsValid(ActiveItemStack))
			{
				const USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(ActiveItemStack);
				if (IsValid(GunStack))
				{
					ClipAmmoSubobject = GunStack->GetClipAmmoSubobject();
				}
			}
		}
	}

	// Get and bind to updates for ClipAmmo
	if (ClipAmmoSubobject.IsValid())
	{
		const float& ClipAmmo = ClipAmmoSubobject->ClipAmmo;
		OnClipAmmoChange(ClipAmmo, ClipAmmo);

		ClipAmmoSubobject->ClipAmmo.ValueChangeDelegate.AddDynamic(this, &USSUserWidget_Ammo::OnClipAmmoChange);
	}

	// Get and bind to updates for BackupAmmo
	CurrentBackupAmmo = PlayerASC->GetNumericAttribute(USSAttributeSet_Ammo::GetBackupAmmoAttribute());
	UpdateAmmoStatus();
	PlayerASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Ammo::GetBackupAmmoAttribute()).AddWeakLambda(this, [&](const FOnAttributeChangeData& Data)
		{
			CurrentBackupAmmo = Data.NewValue;
			UpdateAmmoStatus();
		}
	);
}

void USSUserWidget_Ammo::OnClipAmmoChange(const float& OldValue, const float& NewValue)
{
	CurrentClipAmmo = NewValue;
	UpdateAmmoStatus();
}

void USSUserWidget_Ammo::UpdateAmmoStatus()
{
	FString ClipAmmoString = FString::FromInt(FMath::TruncToInt(CurrentClipAmmo)) + TEXT("/");
	ClipAmmoText->SetText(FText::FromString(ClipAmmoString));

	BackupAmmoText->SetText(FText::AsNumber(FMath::TruncToInt(CurrentBackupAmmo)));
}


void USSUserWidget_Ammo::NativeDestruct()
{
	if (ClipAmmoSubobject.IsValid())
	{
		ClipAmmoSubobject->ClipAmmo.ValueChangeDelegate.RemoveAll(this);
	}


	Super::NativeDestruct();
}
