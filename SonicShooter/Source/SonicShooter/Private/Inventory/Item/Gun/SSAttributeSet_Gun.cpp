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



// OnReps:


void USSAttributeSet_Gun::OnRep_MinBulletSpread(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, MinBulletSpread, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_MovingBulletSpread(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, MovingBulletSpread, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_BulletSpreadIncRate(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, BulletSpreadIncRate, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_FireBulletSpread(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, FireBulletSpread, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_BulletSpreadDecSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, BulletSpreadDecSpeed, ServerBaseValue);
}



void USSAttributeSet_Gun::OnRep_NumberOfBulletsPerFire(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, NumberOfBulletsPerFire, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_MaxRange(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, MaxRange, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_Ricochets(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, Ricochets, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_Penetrations(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, Penetrations, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_InitialBulletSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, InitialBulletSpeed, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_BulletSpeedFalloff(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, BulletSpeedFalloff, ServerBaseValue);
}



void USSAttributeSet_Gun::OnRep_bFullAuto(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, bFullAuto, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_TimeBetweenShots(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, TimeBetweenShots, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_TimeBetweenFiresOverride(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, TimeBetweenFiresOverride, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_TimeBetweenBurstsOverride(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, TimeBetweenBurstsOverride, ServerBaseValue);
}


void USSAttributeSet_Gun::OnRep_NumShotsPerBurst(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, NumShotsPerBurst, ServerBaseValue);
}

void USSAttributeSet_Gun::OnRep_AmmoCost(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Gun, AmmoCost, ServerBaseValue);
}
