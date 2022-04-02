// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/AS_Gun.h"

#include "Net/UnrealNetwork.h"



void UAS_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, MinBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, MovingBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, BulletSpreadIncRate, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, FireBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, BulletSpreadDecSpeed, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, NumberOfBulletsPerFire, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, MaxRange, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, Ricochets, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, Penetrations, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, InitialBulletSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, BulletSpeedFalloff, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, bFullAuto, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, TimeBetweenShots, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, TimeBetweenFiresOverride, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, TimeBetweenBurstsOverride, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, NumShotsPerBurst, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, AmmoCost, Params);
}

UAS_Gun::UAS_Gun()
	: MinBulletSpread(10.f)
	, MovingBulletSpread(20.f)
	, BulletSpreadIncRate(70.f)
	, FireBulletSpread(50.f)
	, BulletSpreadDecSpeed(15.f)

	, NumberOfBulletsPerFire(1.f)
	, MaxRange(100000.f)
	, Penetrations(-1)
	, Ricochets(-1)
	, InitialBulletSpeed(20.f)
	, BulletSpeedFalloff(.9f)

	, bFullAuto(0)
	, TimeBetweenShots(0.1f)
	, TimeBetweenFiresOverride(-1.f)
	, TimeBetweenBurstsOverride(-1.f)
	, NumShotsPerBurst(1)
	, AmmoCost(1.f)
{

}



// OnReps:


void UAS_Gun::OnRep_MinBulletSpread(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, MinBulletSpread, ServerBaseValue);
}

void UAS_Gun::OnRep_MovingBulletSpread(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, MovingBulletSpread, ServerBaseValue);
}

void UAS_Gun::OnRep_BulletSpreadIncRate(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpreadIncRate, ServerBaseValue);
}

void UAS_Gun::OnRep_FireBulletSpread(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, FireBulletSpread, ServerBaseValue);
}

void UAS_Gun::OnRep_BulletSpreadDecSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpreadDecSpeed, ServerBaseValue);
}



void UAS_Gun::OnRep_NumberOfBulletsPerFire(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, NumberOfBulletsPerFire, ServerBaseValue);
}

void UAS_Gun::OnRep_MaxRange(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, MaxRange, ServerBaseValue);
}

void UAS_Gun::OnRep_Ricochets(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, Ricochets, ServerBaseValue);
}

void UAS_Gun::OnRep_Penetrations(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, Penetrations, ServerBaseValue);
}

void UAS_Gun::OnRep_InitialBulletSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, InitialBulletSpeed, ServerBaseValue);
}

void UAS_Gun::OnRep_BulletSpeedFalloff(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpeedFalloff, ServerBaseValue);
}



void UAS_Gun::OnRep_bFullAuto(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, bFullAuto, ServerBaseValue);
}

void UAS_Gun::OnRep_TimeBetweenShots(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, TimeBetweenShots, ServerBaseValue);
}

void UAS_Gun::OnRep_TimeBetweenFiresOverride(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, TimeBetweenFiresOverride, ServerBaseValue);
}

void UAS_Gun::OnRep_TimeBetweenBurstsOverride(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, TimeBetweenBurstsOverride, ServerBaseValue);
}


void UAS_Gun::OnRep_NumShotsPerBurst(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, NumShotsPerBurst, ServerBaseValue);
}

void UAS_Gun::OnRep_AmmoCost(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, AmmoCost, ServerBaseValue);
}
