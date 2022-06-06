// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/SSGameplayEffectExecutionCalculation_InitGun.h"

#include "Inventory/Item/Gun/SSAttributeSet_Gun.h"
#include "Subobjects/SSObject_BulletSpread.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "Inventory/SSInventoryComponent_Active.h"
#include "Inventory/Item/Gun/SSItemStack_Gun.h"



struct FGunInitializationStatics
{
	// No need to capture these Attributes since we aren't reading from them, but writing to them
	const FGameplayAttribute MinBulletSpreadAttribute;
	const FGameplayAttribute MovingBulletSpreadAttribute;
	const FGameplayAttribute BulletSpreadIncRateAttribute;
	const FGameplayAttribute FireBulletSpreadAttribute;
	const FGameplayAttribute BulletSpreadDecSpeedAttribute;

	const FGameplayAttribute NumberOfBulletsPerFireAttribute;
	const FGameplayAttribute MaxRangeAttribute;
	const FGameplayAttribute PenetrationsAttribute;
	const FGameplayAttribute RicochetsAttribute;
	const FGameplayAttribute InitialBulletSpeedAttribute;
	const FGameplayAttribute BulletSpeedFalloffAttribute;

	const FGameplayAttribute bFullAutoAttribute;
	const FGameplayAttribute TimeBetweenShotsAttribute;
	const FGameplayAttribute TimeBetweenFiresOverrideAttribute;
	const FGameplayAttribute TimeBetweenBurstsOverrideAttribute;
	const FGameplayAttribute NumShotsPerBurstAttribute;
	const FGameplayAttribute AmmoCostAttribute;


	FGunInitializationStatics()
		: MinBulletSpreadAttribute(USSAttributeSet_Gun::GetMinBulletSpreadAttribute())
		, MovingBulletSpreadAttribute(USSAttributeSet_Gun::GetMovingBulletSpreadAttribute())
		, BulletSpreadIncRateAttribute(USSAttributeSet_Gun::GetBulletSpreadIncRateAttribute())
		, FireBulletSpreadAttribute(USSAttributeSet_Gun::GetFireBulletSpreadAttribute())
		, BulletSpreadDecSpeedAttribute(USSAttributeSet_Gun::GetBulletSpreadDecSpeedAttribute())

		, NumberOfBulletsPerFireAttribute(USSAttributeSet_Gun::GetNumberOfBulletsPerFireAttribute())
		, MaxRangeAttribute(USSAttributeSet_Gun::GetMaxRangeAttribute())
		, PenetrationsAttribute(USSAttributeSet_Gun::GetPenetrationsAttribute())
		, RicochetsAttribute(USSAttributeSet_Gun::GetRicochetsAttribute())
		, InitialBulletSpeedAttribute(USSAttributeSet_Gun::GetInitialBulletSpeedAttribute())
		, BulletSpeedFalloffAttribute(USSAttributeSet_Gun::GetBulletSpeedFalloffAttribute())

		, bFullAutoAttribute(USSAttributeSet_Gun::GetbFullAutoAttribute())
		, TimeBetweenShotsAttribute(USSAttributeSet_Gun::GetTimeBetweenShotsAttribute())
		, TimeBetweenFiresOverrideAttribute(USSAttributeSet_Gun::GetTimeBetweenFiresOverrideAttribute())
		, TimeBetweenBurstsOverrideAttribute(USSAttributeSet_Gun::GetTimeBetweenBurstsOverrideAttribute())
		, NumShotsPerBurstAttribute(USSAttributeSet_Gun::GetNumShotsPerBurstAttribute())
		, AmmoCostAttribute(USSAttributeSet_Gun::GetAmmoCostAttribute())
	{

	}
};

static const FGunInitializationStatics& GetGunInitializationStatics()
{
	static FGunInitializationStatics Statics;
	return Statics;
}




USSGameplayEffectExecutionCalculation_InitGun::USSGameplayEffectExecutionCalculation_InitGun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Populate defaults for easy BP editing
	const USSAttributeSet_Gun* DefaultAttributeSet = GetDefault<USSAttributeSet_Gun>(USSAttributeSet_Gun::StaticClass());

	MinBulletSpread = DefaultAttributeSet->GetMinBulletSpread();
	MovingBulletSpread = DefaultAttributeSet->GetMovingBulletSpread();
	BulletSpreadIncRate = DefaultAttributeSet->GetBulletSpreadIncRate();
	FireBulletSpread = DefaultAttributeSet->GetFireBulletSpread();
	BulletSpreadDecSpeed = DefaultAttributeSet->GetBulletSpreadDecSpeed();

	NumberOfBulletsPerFire = DefaultAttributeSet->GetNumberOfBulletsPerFire();
	MaxRange = DefaultAttributeSet->GetMaxRange();
	Penetrations = DefaultAttributeSet->GetPenetrations();
	Ricochets = DefaultAttributeSet->GetRicochets();
	InitialBulletSpeed = DefaultAttributeSet->GetInitialBulletSpeed();
	BulletSpeedFalloff = DefaultAttributeSet->GetBulletSpeedFalloff();

	bFullAuto = DefaultAttributeSet->GetbFullAuto();
	TimeBetweenShots = DefaultAttributeSet->GetTimeBetweenShots();
	TimeBetweenFiresOverride = DefaultAttributeSet->GetTimeBetweenFiresOverride();
	TimeBetweenBurstsOverride = DefaultAttributeSet->GetTimeBetweenBurstsOverride();
	NumShotsPerBurst = DefaultAttributeSet->GetNumShotsPerBurst();
	AmmoCost = DefaultAttributeSet->GetAmmoCost();
}

void USSGameplayEffectExecutionCalculation_InitGun::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSSAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init gun"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().MinBulletSpreadAttribute,				EGameplayModOp::Override, MinBulletSpread));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().MovingBulletSpreadAttribute,			EGameplayModOp::Override, MovingBulletSpread));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().BulletSpreadIncRateAttribute,			EGameplayModOp::Override, BulletSpreadIncRate));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().FireBulletSpreadAttribute,			EGameplayModOp::Override, FireBulletSpread));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().BulletSpreadDecSpeedAttribute,		EGameplayModOp::Override, BulletSpreadDecSpeed));

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().NumberOfBulletsPerFireAttribute,		EGameplayModOp::Override, NumberOfBulletsPerFire));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().MaxRangeAttribute,					EGameplayModOp::Override, MaxRange));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().PenetrationsAttribute,				EGameplayModOp::Override, Penetrations));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().RicochetsAttribute,					EGameplayModOp::Override, Ricochets));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().InitialBulletSpeedAttribute,			EGameplayModOp::Override, InitialBulletSpeed));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().BulletSpeedFalloffAttribute,			EGameplayModOp::Override, BulletSpeedFalloff));

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().bFullAutoAttribute,					EGameplayModOp::Override, bFullAuto));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().TimeBetweenShotsAttribute,			EGameplayModOp::Override, TimeBetweenShots));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().TimeBetweenFiresOverrideAttribute,	EGameplayModOp::Override, TimeBetweenFiresOverride));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().TimeBetweenBurstsOverrideAttribute,	EGameplayModOp::Override, TimeBetweenBurstsOverride));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().NumShotsPerBurstAttribute,			EGameplayModOp::Override, NumShotsPerBurst));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().AmmoCostAttribute,					EGameplayModOp::Override, AmmoCost));
	

	// Calculate defaults
	float CurrentBulletSpread = MinBulletSpread;

	// Get BulletSpread subobject and initialize CurrentBulletSpread
	if (const FSSGameplayAbilityActorInfo_Shooter* ShooterActorInfo = static_cast<const FSSGameplayAbilityActorInfo_Shooter*>(TargetAbilitySystemComponent->AbilityActorInfo.Get()))
	{
		USSInventoryComponent_Active* InventoryComponent = ShooterActorInfo->GetInventoryComponent();
		if (IsValid(InventoryComponent))
		{
			const UArcItemStack* ActiveItemStack = InventoryComponent->GetActiveItemStack();
			if (IsValid(ActiveItemStack))
			{
				const USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(ActiveItemStack);
				if (IsValid(GunStack))
				{
					GunStack->GetBulletSpreadSubobject()->CurrentBulletSpread = CurrentBulletSpread;
					GunStack->GetBulletSpreadSubobject()->CurrentBulletSpread.MarkNetDirty(); // we are server-only right now so replicate it
				}
			}
		}
	}

}
