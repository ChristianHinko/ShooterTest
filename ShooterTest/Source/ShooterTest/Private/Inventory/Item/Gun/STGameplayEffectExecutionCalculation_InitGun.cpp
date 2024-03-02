// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/STGameplayEffectExecutionCalculation_InitGun.h"

#include "Inventory/Item/Gun/STAttributeSet_Gun.h"
#include "Inventory\Item\Fragments\STItemFragment_BulletSpread.h"
#include "AbilitySystem/Types/STGameplayAbilityTypes.h"
#include "Modular/ArcItemStackModular.h"
#include "Inventory/AIEInventoryProcessor_Active.h"
#include "Modular/ArcInventoryComponent_Modular.h"



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
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetMinBulletSpreadAttribute(),                    EGameplayModOp::Override, MinBulletSpread));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetMovingBulletSpreadAttribute(),                EGameplayModOp::Override, MovingBulletSpread));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetBulletSpreadIncRateAttribute(),                EGameplayModOp::Override, BulletSpreadIncRate));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetFireBulletSpreadAttribute(),                EGameplayModOp::Override, FireBulletSpread));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetBulletSpreadDecSpeedAttribute(),            EGameplayModOp::Override, BulletSpreadDecSpeed));

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetNumberOfBulletsPerFireAttribute(),            EGameplayModOp::Override, NumberOfBulletsPerFire));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetMaxRangeAttribute(),                        EGameplayModOp::Override, MaxRange));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetPenetrationsAttribute(),                    EGameplayModOp::Override, Penetrations));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetRicochetsAttribute(),                        EGameplayModOp::Override, Ricochets));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetInitialBulletSpeedAttribute(),                EGameplayModOp::Override, InitialBulletSpeed));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetBulletSpeedFalloffAttribute(),                EGameplayModOp::Override, BulletSpeedFalloff));

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetbFullAutoAttribute(),                        EGameplayModOp::Override, bFullAuto));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetTimeBetweenShotsAttribute(),                EGameplayModOp::Override, TimeBetweenShots));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetTimeBetweenFiresOverrideAttribute(),        EGameplayModOp::Override, TimeBetweenFiresOverride));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetTimeBetweenBurstsOverrideAttribute(),        EGameplayModOp::Override, TimeBetweenBurstsOverride));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetNumShotsPerBurstAttribute(),                EGameplayModOp::Override, NumShotsPerBurst));
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Gun::GetAmmoCostAttribute(),                        EGameplayModOp::Override, AmmoCost));


    // Calculate defaults
    float CurrentBulletSpread = MinBulletSpread;

    // Get BulletSpread subobject and initialize CurrentBulletSpread
    if (const FSTGameplayAbilityActorInfo_Shooter* ShooterActorInfo = static_cast<const FSTGameplayAbilityActorInfo_Shooter*>(TargetAbilitySystemComponent->AbilityActorInfo.Get()))
    {
        const UArcInventoryComponent_Modular* InventoryComponentModular = Cast<const UArcInventoryComponent_Modular>(ShooterActorInfo->InventoryComponent);
        if (IsValid(InventoryComponentModular))
        {
            const UArcInventoryProcessor_Active* InventoryProcessor_Active = InventoryComponentModular->FindFirstProcessor<UArcInventoryProcessor_Active>();
            if (IsValid(InventoryProcessor_Active))
            {
                UArcItemStackModular* ActiveItemStack = InventoryProcessor_Active->GetActiveItemStack();
                if (IsValid(ActiveItemStack))
                {
                    USTItemFragment_BulletSpreadInstanced* BulletSpreadItemFragment = ActiveItemStack->FindFirstFragment<USTItemFragment_BulletSpreadInstanced>();

                    if (IsValid(BulletSpreadItemFragment))
                    {
                        BulletSpreadItemFragment->CurrentBulletSpread = CurrentBulletSpread;
                        BulletSpreadItemFragment->CurrentBulletSpread.MarkNetDirty(); // we are server-only here so replicate it
                    }
                }
            }
        }
    }
}
