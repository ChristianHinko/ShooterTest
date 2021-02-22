// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AS_Ammo.h"

#include "Net/UnrealNetwork.h"
#include "GameplayAbilities/Public/GameplayEffectExtension.h"



void UAS_Ammo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Ammo, MaxAmmo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Ammo, BackupAmmo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Ammo, MaxClipSize, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UAS_Ammo, ClipAmmo, COND_None, REPNOTIFY_Always);
}

UAS_Ammo::UAS_Ammo()
	: MaxAmmo(100),
	MaxClipSize(10)

{
	SetSoftAttributeDefaults();



}

void UAS_Ammo::SetSoftAttributeDefaults()
{
	Super::SetSoftAttributeDefaults();


	ClipAmmo = GetMaxClipSize();
	BackupAmmo = GetMaxAmmo() - GetClipAmmo();
}


void UAS_Ammo::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayAttribute ModifiedAttribute = Data.EvaluatedData.Attribute;


	//if (ModifiedAttribute == GetBackupAmmoReceiveAttribute())
	//{
	//	const float ammoToAdd = GetBackupAmmoReceive();
	//	SetBackupAmmoReceive(0.f);

	//	const float maxBackupAmmo = GetMaxAmmo() - GetMaxClipSize();

	//	SetBackupAmmo(FMath::Clamp(GetBackupAmmo() + ammoToAdd, 0.f, maxBackupAmmo));
	//}
}




void UAS_Ammo::OnRep_MaxAmmo(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Ammo, MaxAmmo, ServerBaseValue);
}

void UAS_Ammo::OnRep_BackupAmmo(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Ammo, BackupAmmo, ServerBaseValue);
}

void UAS_Ammo::OnRep_MaxClipSize(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Ammo, MaxClipSize, ServerBaseValue);
}

//void UAS_Ammo::OnRep_ClipAmmo(const FGameplayAttributeData& ServerBaseValue)
//{
//	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Ammo, ClipAmmo, ServerBaseValue);
//}
