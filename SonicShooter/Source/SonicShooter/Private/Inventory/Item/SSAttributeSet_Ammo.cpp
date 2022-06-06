// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/SSAttributeSet_Ammo.h"

#include "Net/UnrealNetwork.h"
#include "GameplayAbilities/Public/GameplayEffectExtension.h"



void USSAttributeSet_Ammo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Ammo, MaxAmmo, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Ammo, BackupAmmo, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Ammo, MaxClipAmmo, Params);

}

USSAttributeSet_Ammo::USSAttributeSet_Ammo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MaxAmmo(100)
	, MaxClipAmmo(10)
	, BackupAmmo(GetMaxAmmo() - GetMaxClipAmmo())
{

}


void USSAttributeSet_Ammo::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayAttribute ModifiedAttribute = Data.EvaluatedData.Attribute;


	//if (ModifiedAttribute == GetBackupAmmoReceiveAttribute())
	//{
	//	const float ammoToAdd = GetBackupAmmoReceive();
	//	SetBackupAmmoReceive(0.f);

	//	const float maxBackupAmmo = GetMaxAmmo() - GetMaxClipAmmo();

	//	SetBackupAmmo(FMath::Clamp(GetBackupAmmo() + ammoToAdd, 0.f, maxBackupAmmo));
	//}
}




void USSAttributeSet_Ammo::OnRep_MaxAmmo(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Ammo, MaxAmmo, ServerBaseValue);
}

void USSAttributeSet_Ammo::OnRep_BackupAmmo(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Ammo, BackupAmmo, ServerBaseValue);
}

void USSAttributeSet_Ammo::OnRep_MaxClipAmmo(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Ammo, MaxClipAmmo, ServerBaseValue);
}
