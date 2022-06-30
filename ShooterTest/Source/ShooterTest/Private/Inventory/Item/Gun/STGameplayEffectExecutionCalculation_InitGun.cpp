// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/STGameplayEffectExecutionCalculation_InitGun.h"

#include "Inventory/Item/Gun/STAttributeSet_Gun.h"
#include "Subobjects/STObject_BulletSpread.h"
#include "AbilitySystem/Types/STGameplayAbilityTypes.h"
#include "Components/ArcInventoryComponent_Active.h"
#include "Inventory/Item/Gun/STItemStack_Gun.h"



struct FGunInitializationStatics
{
	// No need to capture these Attributes since we aren't reading from them, but writing to them

	FGunInitializationStatics()
	{
	}
};

static const FGunInitializationStatics& GetGunInitializationStatics()
{
	static FGunInitializationStatics Statics;
	return Statics;
}




USTGameplayEffectExecutionCalculation_InitGun::USTGameplayEffectExecutionCalculation_InitGun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Populate defaults for easy BP editing
	const USTAttributeSet_Gun* DefaultAttributeSet = GetDefault<USTAttributeSet_Gun>(USTAttributeSet_Gun::StaticClass());

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

void USTGameplayEffectExecutionCalculation_InitGun::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSTAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init gun"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetMinBulletSpreadAttribute(),					EGameplayModOp::Override, MinBulletSpread));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetMovingBulletSpreadAttribute(),				EGameplayModOp::Override, MovingBulletSpread));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetBulletSpreadIncRateAttribute(),				EGameplayModOp::Override, BulletSpreadIncRate));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetFireBulletSpreadAttribute(),				EGameplayModOp::Override, FireBulletSpread));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetBulletSpreadDecSpeedAttribute(),			EGameplayModOp::Override, BulletSpreadDecSpeed));

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetNumberOfBulletsPerFireAttribute(),			EGameplayModOp::Override, NumberOfBulletsPerFire));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetMaxRangeAttribute(),						EGameplayModOp::Override, MaxRange));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetPenetrationsAttribute(),					EGameplayModOp::Override, Penetrations));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetRicochetsAttribute(),						EGameplayModOp::Override, Ricochets));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetInitialBulletSpeedAttribute(),				EGameplayModOp::Override, InitialBulletSpeed));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetBulletSpeedFalloffAttribute(),				EGameplayModOp::Override, BulletSpeedFalloff));

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetbFullAutoAttribute(),						EGameplayModOp::Override, bFullAuto));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetTimeBetweenShotsAttribute(),				EGameplayModOp::Override, TimeBetweenShots));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetTimeBetweenFiresOverrideAttribute(),		EGameplayModOp::Override, TimeBetweenFiresOverride));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetTimeBetweenBurstsOverrideAttribute(),		EGameplayModOp::Override, TimeBetweenBurstsOverride));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetNumShotsPerBurstAttribute(),				EGameplayModOp::Override, NumShotsPerBurst));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetAmmoCostAttribute(),						EGameplayModOp::Override, AmmoCost));
	

	// Calculate defaults
	float CurrentBulletSpread = MinBulletSpread;

	// Get BulletSpread subobject and initialize CurrentBulletSpread
	if (const FSTGameplayAbilityActorInfo_Shooter* ShooterActorInfo = static_cast<const FSTGameplayAbilityActorInfo_Shooter*>(TargetAbilitySystemComponent->AbilityActorInfo.Get()))
	{
		UArcInventoryComponent_Active* InventoryComponentActive = Cast<UArcInventoryComponent_Active>(ShooterActorInfo->InventoryComponent);
		if (IsValid(InventoryComponentActive))
		{
			const UArcItemStack* ActiveItemStack = InventoryComponentActive->GetActiveItemStack();
			if (IsValid(ActiveItemStack))
			{
				const USTItemStack_Gun* GunStack = Cast<USTItemStack_Gun>(ActiveItemStack);
				if (IsValid(GunStack))
				{
					GunStack->GetBulletSpreadSubobject()->CurrentBulletSpread = CurrentBulletSpread;
					GunStack->GetBulletSpreadSubobject()->CurrentBulletSpread.MarkNetDirty(); // we are server-only here so replicate it
				}
			}
		}
	}
}
