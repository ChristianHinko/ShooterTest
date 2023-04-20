// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/STGameplayEffectExecutionCalculation_InitAmmo.h"

#include "Inventory/Item/STAttributeSet_Ammo.h"
#include "Subobjects/STObject_ClipAmmo.h"
#include "AbilitySystem/Types/STGameplayAbilityTypes.h"
#include "Components/ArcInventoryComponent_Active.h"
#include "Inventory/Item/Gun/STItemStack_Gun.h"



////////////////////////////////////////////////
/// FAmmoInitializationStatics
////////////////////////////////////////////////

struct FAmmoInitializationStatics
{
	// No need to capture these Attributes since we aren't reading from them, but writing to them
	
	FAmmoInitializationStatics()
	{
	}
};

static const FAmmoInitializationStatics& GetAmmoInitializationStatics()
{
	static FAmmoInitializationStatics Statics;
	return Statics;
}



////////////////////////////////////////////////
/// USTGameplayEffectExecutionCalculation_InitAmmo
////////////////////////////////////////////////


USTGameplayEffectExecutionCalculation_InitAmmo::USTGameplayEffectExecutionCalculation_InitAmmo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USTGameplayEffectExecutionCalculation_InitAmmo::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSTAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init ammo"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Ammo::GetMaxAmmoAttribute(), EGameplayModOp::Override, MaxAmmo));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Ammo::GetMaxClipAmmoAttribute(), EGameplayModOp::Override, MaxClipAmmo));


	// Calculate defaults
	float ClipAmmo = MaxClipAmmo;
	float BackupAmmo = MaxAmmo - MaxClipAmmo;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USTAttributeSet_Ammo::GetBackupAmmoAttribute(), EGameplayModOp::Override, BackupAmmo));
	
	// Get ClipAmmo subobject and initialize ClipAmmo
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
					GunStack->GetClipAmmoSubobject()->ClipAmmo = ClipAmmo;
					GunStack->GetClipAmmoSubobject()->ClipAmmo.MarkNetDirty(); // we are server-only here so replicate it
				}
			}
		}
	}
}
