// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/STAttributeSet_Ammo.h"

#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"



void USTAttributeSet_Ammo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);


    FDoRepLifetimeParams Params;
    Params.Condition = COND_None;
    Params.RepNotifyCondition = REPNOTIFY_Always;
    Params.bIsPushBased = true;

    DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Ammo, MaxAmmo, Params);
    DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Ammo, BackupAmmo, Params);
    DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Ammo, MaxClipAmmo, Params);

}


void USTAttributeSet_Ammo::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    FGameplayAttribute ModifiedAttribute = Data.EvaluatedData.Attribute;


    //if (ModifiedAttribute == GetBackupAmmoReceiveAttribute())
    //{
    //    const float ammoToAdd = GetBackupAmmoReceive();
    //    SetBackupAmmoReceive(0.f);

    //    const float maxBackupAmmo = GetMaxAmmo() - GetMaxClipAmmo();

    //    SetBackupAmmo(FMath::Clamp(GetBackupAmmo() + ammoToAdd, 0.f, maxBackupAmmo));
    //}
}



void USTAttributeSet_Ammo::OnRep_MaxAmmo(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Ammo, MaxAmmo, OldValue);
}

void USTAttributeSet_Ammo::OnRep_BackupAmmo(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Ammo, BackupAmmo, OldValue);
}

void USTAttributeSet_Ammo::OnRep_MaxClipAmmo(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Ammo, MaxClipAmmo, OldValue);
}
