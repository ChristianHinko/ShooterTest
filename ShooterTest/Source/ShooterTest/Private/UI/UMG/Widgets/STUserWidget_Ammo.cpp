// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/STUserWidget_Ammo.h"

#include "Inventory/Item/STAttributeSet_Ammo.h"
#include "Subobjects/STObject_ClipAmmo.h"
#include "AbilitySystem/Types/STGameplayAbilityTypes.h"
#include "Components/ArcInventoryComponent_Active.h"
#include "Inventory/Item/Gun/STItemStack_Gun.h"
#include "Components/TextBlock.h"



USTUserWidget_Ammo::USTUserWidget_Ammo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void USTUserWidget_Ammo::OnPlayerASCValid()
{
	Super::OnPlayerASCValid();


	// Get ClipAmmo subobject
	if (const FSTGameplayAbilityActorInfo_Shooter* ShooterActorInfo = static_cast<const FSTGameplayAbilityActorInfo_Shooter*>(PlayerASC->AbilityActorInfo.Get()))
	{
		UArcInventoryComponent_Active* InventoryComponentActive = Cast<UArcInventoryComponent_Active>(ShooterActorInfo->InventoryComponent);
		if (IsValid(InventoryComponentActive))
		{
			const UArcItemStack* ActiveItemStack = InventoryComponentActive->GetActiveItemStack();
			if (IsValid(ActiveItemStack))
			{
				const USTItemStack_Gun* GunStack = Cast<USTItemStack_Gun>(ActiveItemStack);
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
		const int32& ClipAmmo = ClipAmmoSubobject->ClipAmmo;
		OnClipAmmoChange(ClipAmmoSubobject->ClipAmmo, ClipAmmo, ClipAmmo);

		ClipAmmoSubobject->ClipAmmo.ValueChangeDelegate.AddUObject(this, &USTUserWidget_Ammo::OnClipAmmoChange);
	}

	// Get and bind to updates for BackupAmmo
	CurrentBackupAmmo = PlayerASC->GetNumericAttribute(USTAttributeSet_Ammo::GetBackupAmmoAttribute());
	UpdateAmmoStatus();
	PlayerASC->GetGameplayAttributeValueChangeDelegate(USTAttributeSet_Ammo::GetBackupAmmoAttribute()).AddWeakLambda(this, [&](const FOnAttributeChangeData& Data)
		{
			CurrentBackupAmmo = Data.NewValue;
			UpdateAmmoStatus();
		}
	);
}

void USTUserWidget_Ammo::OnClipAmmoChange(FGCInt32PropertyWrapper& PropertyWrapper, const int32& InOldValue, const int32& InNewValue)
{
	CurrentClipAmmo = InNewValue;
	UpdateAmmoStatus();
}

void USTUserWidget_Ammo::UpdateAmmoStatus()
{
	FString ClipAmmoString = FString::FromInt(CurrentClipAmmo) + TEXT("/");
	ClipAmmoText->SetText(FText::FromString(ClipAmmoString));

	BackupAmmoText->SetText(FText::AsNumber(FMath::TruncToInt(CurrentBackupAmmo)));
}


void USTUserWidget_Ammo::NativeDestruct()
{
	if (ClipAmmoSubobject.IsValid())
	{
		ClipAmmoSubobject->ClipAmmo.ValueChangeDelegate.RemoveAll(this);
	}


	Super::NativeDestruct();
}
