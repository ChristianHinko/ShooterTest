// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/SSAttributeSet_Gun.h"

#include "Net/UnrealNetwork.h"



void USSAttributeSet_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, MinBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, MovingBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, BulletSpreadIncRate, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, FireBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, BulletSpreadDecSpeed, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, NumberOfBulletsPerFire, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, MaxRange, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, Ricochets, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, Penetrations, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, InitialBulletSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, BulletSpeedFalloff, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, bFullAuto, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, TimeBetweenShots, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, TimeBetweenFiresOverride, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, TimeBetweenBurstsOverride, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, NumShotsPerBurst, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Gun, AmmoCost, Params);
}

USSAttributeSet_Gun::USSAttributeSet_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)

	, MinBulletSpread(10.f)
	, MovingBulletSpread(20.f)
	, BulletSpreadIncRate(70.f)
	, FireBulletSpread(50.f)
	, BulletSpreadDecSpeed(15.f)

	, NumberOfBulletsPerFire(1.f)
	, MaxRange(100000.f)
	, Penetrations(-1)
	, Ricochets(-1)
	, InitialBulletSpeed(20.f)
	, BulletSpeedFalloff(0.02f)

	, bFullAuto(0)
	, TimeBetweenShots(0.1f)
	, TimeBetweenFiresOverride(-1.f)
	, TimeBetweenBurstsOverride(-1.f)
	, NumShotsPerBurst(1)
	, AmmoCost(1.f)
{
}



// OnReps


void USSAttributeSet_Gun::OnRep_MinBulletSpread(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, MinBulletSpread, OldValue);
}

void USSAttributeSet_Gun::OnRep_MovingBulletSpread(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, MovingBulletSpread, OldValue);
}

void USSAttributeSet_Gun::OnRep_BulletSpreadIncRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, BulletSpreadIncRate, OldValue);
}

void USSAttributeSet_Gun::OnRep_FireBulletSpread(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, FireBulletSpread, OldValue);
}

void USSAttributeSet_Gun::OnRep_BulletSpreadDecSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, BulletSpreadDecSpeed, OldValue);
}



void USSAttributeSet_Gun::OnRep_NumberOfBulletsPerFire(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, NumberOfBulletsPerFire, OldValue);
}

void USSAttributeSet_Gun::OnRep_MaxRange(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, MaxRange, OldValue);
}

void USSAttributeSet_Gun::OnRep_Ricochets(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, Ricochets, OldValue);
}

void USSAttributeSet_Gun::OnRep_Penetrations(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, Penetrations, OldValue);
}

void USSAttributeSet_Gun::OnRep_InitialBulletSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, InitialBulletSpeed, OldValue);
}

void USSAttributeSet_Gun::OnRep_BulletSpeedFalloff(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, BulletSpeedFalloff, OldValue);
}



void USSAttributeSet_Gun::OnRep_bFullAuto(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, bFullAuto, OldValue);
}

void USSAttributeSet_Gun::OnRep_TimeBetweenShots(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, TimeBetweenShots, OldValue);
}

void USSAttributeSet_Gun::OnRep_TimeBetweenFiresOverride(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, TimeBetweenFiresOverride, OldValue);
}

void USSAttributeSet_Gun::OnRep_TimeBetweenBurstsOverride(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, TimeBetweenBurstsOverride, OldValue);
}


void USSAttributeSet_Gun::OnRep_NumShotsPerBurst(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, NumShotsPerBurst, OldValue);
}

void USSAttributeSet_Gun::OnRep_AmmoCost(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, AmmoCost, OldValue);
}
