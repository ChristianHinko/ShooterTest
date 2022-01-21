// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/GEEC_GunInitialization.h"

#include "Item/Weapons/AS_Gun.h"



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
		: MinBulletSpreadAttribute(UAS_Gun::GetMinBulletSpreadAttribute())
		, MovingBulletSpreadAttribute(UAS_Gun::GetMovingBulletSpreadAttribute())
		, BulletSpreadIncRateAttribute(UAS_Gun::GetBulletSpreadIncRateAttribute())
		, FireBulletSpreadAttribute(UAS_Gun::GetFireBulletSpreadAttribute())
		, BulletSpreadDecSpeedAttribute(UAS_Gun::GetBulletSpreadDecSpeedAttribute())

		, NumberOfBulletsPerFireAttribute(UAS_Gun::GetNumberOfBulletsPerFireAttribute())
		, MaxRangeAttribute(UAS_Gun::GetMaxRangeAttribute())
		, PenetrationsAttribute(UAS_Gun::GetPenetrationsAttribute())
		, RicochetsAttribute(UAS_Gun::GetRicochetsAttribute())
		, InitialBulletSpeedAttribute(UAS_Gun::GetInitialBulletSpeedAttribute())
		, BulletSpeedFalloffAttribute(UAS_Gun::GetBulletSpeedFalloffAttribute())

		, bFullAutoAttribute(UAS_Gun::GetbFullAutoAttribute())
		, TimeBetweenShotsAttribute(UAS_Gun::GetTimeBetweenShotsAttribute())
		, TimeBetweenFiresOverrideAttribute(UAS_Gun::GetTimeBetweenFiresOverrideAttribute())
		, TimeBetweenBurstsOverrideAttribute(UAS_Gun::GetTimeBetweenBurstsOverrideAttribute())
		, NumShotsPerBurstAttribute(UAS_Gun::GetNumShotsPerBurstAttribute())
		, AmmoCostAttribute(UAS_Gun::GetAmmoCostAttribute())
	{

	}
};

static const FGunInitializationStatics& GetGunInitializationStatics()
{
	static FGunInitializationStatics Statics;
	return Statics;
}




UGEEC_GunInitialization::UGEEC_GunInitialization()
{
	const UAS_Gun* DefaultGunAttributeSet = GetDefault<UAS_Gun>(UAS_Gun::StaticClass());

	
	MinBulletSpread = DefaultGunAttributeSet->GetMinBulletSpread();
	MovingBulletSpread = DefaultGunAttributeSet->GetMovingBulletSpread();
	BulletSpreadIncRate = DefaultGunAttributeSet->GetBulletSpreadIncRate();
	FireBulletSpread = DefaultGunAttributeSet->GetFireBulletSpread();
	BulletSpreadDecSpeed = DefaultGunAttributeSet->GetBulletSpreadDecSpeed();

	NumberOfBulletsPerFire = DefaultGunAttributeSet->GetNumberOfBulletsPerFire();
	MaxRange = DefaultGunAttributeSet->GetMaxRange();
	Penetrations = DefaultGunAttributeSet->GetPenetrations();
	Ricochets = DefaultGunAttributeSet->GetRicochets();
	InitialBulletSpeed = DefaultGunAttributeSet->GetInitialBulletSpeed();
	BulletSpeedFalloff = DefaultGunAttributeSet->GetBulletSpeedFalloff();

	bFullAuto = DefaultGunAttributeSet->GetbFullAuto();
	TimeBetweenShots = DefaultGunAttributeSet->GetTimeBetweenShots();
	TimeBetweenFiresOverride = DefaultGunAttributeSet->GetTimeBetweenFiresOverride();
	TimeBetweenBurstsOverride = DefaultGunAttributeSet->GetTimeBetweenBurstsOverride();
	NumShotsPerBurst = DefaultGunAttributeSet->GetNumShotsPerBurst();
	AmmoCost = DefaultGunAttributeSet->GetAmmoCost();
}

void UGEEC_GunInitialization::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().MinBulletSpreadAttribute, EGameplayModOp::Override, MinBulletSpread));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().MovingBulletSpreadAttribute, EGameplayModOp::Override, MovingBulletSpread));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().BulletSpreadIncRateAttribute, EGameplayModOp::Override, BulletSpreadIncRate));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().FireBulletSpreadAttribute, EGameplayModOp::Override, FireBulletSpread));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().BulletSpreadDecSpeedAttribute, EGameplayModOp::Override, BulletSpreadDecSpeed));

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().NumberOfBulletsPerFireAttribute, EGameplayModOp::Override, NumberOfBulletsPerFire));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().MaxRangeAttribute, EGameplayModOp::Override, MaxRange));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().PenetrationsAttribute, EGameplayModOp::Override, Penetrations));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().RicochetsAttribute, EGameplayModOp::Override, Ricochets));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().InitialBulletSpeedAttribute, EGameplayModOp::Override, InitialBulletSpeed));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().BulletSpeedFalloffAttribute, EGameplayModOp::Override, BulletSpeedFalloff));

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().bFullAutoAttribute, EGameplayModOp::Override, bFullAuto));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().TimeBetweenShotsAttribute, EGameplayModOp::Override, TimeBetweenShots));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().TimeBetweenFiresOverrideAttribute, EGameplayModOp::Override, TimeBetweenFiresOverride));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().TimeBetweenBurstsOverrideAttribute, EGameplayModOp::Override, TimeBetweenBurstsOverride));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().NumShotsPerBurstAttribute, EGameplayModOp::Override, NumShotsPerBurst));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetGunInitializationStatics().AmmoCostAttribute, EGameplayModOp::Override, AmmoCost));
	

	// Calculate defaults
	float CurrentBulletSpread = MinBulletSpread;

	// Search for gun Attribute Set and initialize CurrentBulletSpread. TODO: this is really bad accessing an Ability System Component's Attribute Sets directly - move CurrentBulletSpread somewhere else!
	{
		UAS_Gun** GunAttributeSetPtr = nullptr;
		int32* index = nullptr;
		TargetAbilitySystemComponent->GetSpawnedAttributes_Mutable().FindItemByClass<UAS_Gun>(GunAttributeSetPtr, index, 0);
		if (GunAttributeSetPtr)
		{
			UAS_Gun* GunAttributeSet = *GunAttributeSetPtr;
			if (IsValid(GunAttributeSet))
			{
				GunAttributeSet->CurrentBulletSpread = CurrentBulletSpread;
			}
		}
	}

}
