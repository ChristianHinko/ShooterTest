// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/STUserWidget_Ammo.h"

#include "Inventory/Item/STAttributeSet_Ammo.h"
#include "Inventory\Item\Fragments\STItemFragment_ClipAmmo.h"
#include "AbilitySystem/Types/STGameplayAbilityTypes.h"
#include "Components/TextBlock.h"
#include "Modular/ArcInventoryComponent_Modular.h"
#include "Inventory/AIEInventoryProcessor_Active.h"
#include "Modular/ArcItemStackModular.h"



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
        UArcInventoryComponent_Modular* InventoryComponentModular = Cast<UArcInventoryComponent_Modular>(ShooterActorInfo->InventoryComponent);
        if (IsValid(InventoryComponentModular))
        {
            const UArcInventoryProcessor_Active* InventoryProcessorActive = InventoryComponentModular->FindFirstProcessor<UArcInventoryProcessor_Active>();
            if (IsValid(InventoryProcessorActive))
            {
                UArcItemStackModular* ActiveItemStack = InventoryProcessorActive->GetActiveItemStack();
                if (IsValid(ActiveItemStack))
                {
                    ClipAmmoItemFragment = ActiveItemStack->FindFirstFragment<USTItemFragment_ClipAmmoInstanced>();
                    if (ClipAmmoItemFragment.IsValid())
                    {
                        ClipAmmoItemFragment = ClipAmmoItemFragment;
                    }
                }
            }
        }
    }

    // Get and bind to updates for ClipAmmo
    if (ClipAmmoItemFragment.IsValid())
    {
        const int32& ClipAmmo = ClipAmmoItemFragment->ClipAmmo;
        OnClipAmmoChange(ClipAmmoItemFragment->ClipAmmo, ClipAmmo, ClipAmmo);

        ClipAmmoItemFragment->ClipAmmo.ValueChangeDelegate.AddUObject(this, &USTUserWidget_Ammo::OnClipAmmoChange);
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
    if (ClipAmmoItemFragment.IsValid())
    {
        ClipAmmoItemFragment->ClipAmmo.ValueChangeDelegate.RemoveAll(this);
    }


    Super::NativeDestruct();
}
