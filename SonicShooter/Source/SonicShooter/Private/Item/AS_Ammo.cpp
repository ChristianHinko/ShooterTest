// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AS_Ammo.h"

#include "Net/UnrealNetwork.h"
#include "GameplayAbilities/Public/GameplayEffectExtension.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"



void UAS_Ammo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Ammo, MaxAmmo, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Ammo, BackupAmmo, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Ammo, MaxClipAmmo, Params);

	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Ammo, ClipAmmo, Params);
	Params.RepNotifyCondition = REPNOTIFY_Always;


}

UAS_Ammo::UAS_Ammo()
	: MaxAmmo(100)
	, MaxClipAmmo(10)
	, ClipAmmo(GetMaxClipAmmo(), this, FName(TEXT("ClipAmmo")))
	, BackupAmmo(GetMaxAmmo() - ClipAmmo)

{

}


void UAS_Ammo::PostInitProperties()
{
	Super::PostInitProperties();

	if (GetWorld() == nullptr || GetWorld()->IsGameWorld() == false)
	{
		return;
	}
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}
	//---------------------------------------- safe "BeginPlay" logic here ------------------------


	if (FGAAI_Shooter* ShooterActorInfo = static_cast<FGAAI_Shooter*>(GetActorInfo()))
	{
		if (UASC_Shooter* ShooterASC = ShooterActorInfo->GetShooterAbilitySystemComponent())
		{
			ClipAmmo.SetValueChangeDelegate(ShooterASC->OnClipAmmoChange);
		}
	}
}


void UAS_Ammo::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
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




void UAS_Ammo::OnRep_MaxAmmo(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Ammo, MaxAmmo, ServerBaseValue);
}

void UAS_Ammo::OnRep_BackupAmmo(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Ammo, BackupAmmo, ServerBaseValue);
}

void UAS_Ammo::OnRep_MaxClipAmmo(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Ammo, MaxClipAmmo, ServerBaseValue);
}
