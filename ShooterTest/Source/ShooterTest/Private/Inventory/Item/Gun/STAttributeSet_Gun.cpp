// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/STAttributeSet_Gun.h"

#include "Net/UnrealNetwork.h"



void USTAttributeSet_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, MinBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, MovingBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, BulletSpreadIncRate, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, FireBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, BulletSpreadDecSpeed, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, NumberOfBulletsPerFire, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, MaxRange, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, Ricochets, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, Penetrations, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, InitialBulletSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, BulletSpeedFalloff, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, bFullAuto, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, TimeBetweenShots, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, TimeBetweenFiresOverride, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, TimeBetweenBurstsOverride, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, NumShotsPerBurst, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Gun, AmmoCost, Params);
}


void USTAttributeSet_Gun::OnRep_MinBulletSpread(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, MinBulletSpread, OldValue);
}

void USTAttributeSet_Gun::OnRep_MovingBulletSpread(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, MovingBulletSpread, OldValue);
}

void USTAttributeSet_Gun::OnRep_BulletSpreadIncRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, BulletSpreadIncRate, OldValue);
}

void USTAttributeSet_Gun::OnRep_FireBulletSpread(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, FireBulletSpread, OldValue);
}

void USTAttributeSet_Gun::OnRep_BulletSpreadDecSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, BulletSpreadDecSpeed, OldValue);
}



void USTAttributeSet_Gun::OnRep_NumberOfBulletsPerFire(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, NumberOfBulletsPerFire, OldValue);
}

void USTAttributeSet_Gun::OnRep_MaxRange(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, MaxRange, OldValue);
}

void USTAttributeSet_Gun::OnRep_Ricochets(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, Ricochets, OldValue);
}

void USTAttributeSet_Gun::OnRep_Penetrations(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, Penetrations, OldValue);
}

void USTAttributeSet_Gun::OnRep_InitialBulletSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, InitialBulletSpeed, OldValue);
}

void USTAttributeSet_Gun::OnRep_BulletSpeedFalloff(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, BulletSpeedFalloff, OldValue);
}



void USTAttributeSet_Gun::OnRep_bFullAuto(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, bFullAuto, OldValue);
}

void USTAttributeSet_Gun::OnRep_TimeBetweenShots(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, TimeBetweenShots, OldValue);
}

void USTAttributeSet_Gun::OnRep_TimeBetweenFiresOverride(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, TimeBetweenFiresOverride, OldValue);
}

void USTAttributeSet_Gun::OnRep_TimeBetweenBurstsOverride(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, TimeBetweenBurstsOverride, OldValue);
}


void USTAttributeSet_Gun::OnRep_NumShotsPerBurst(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, NumShotsPerBurst, OldValue);
}

void USTAttributeSet_Gun::OnRep_AmmoCost(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Gun, AmmoCost, OldValue);
}
