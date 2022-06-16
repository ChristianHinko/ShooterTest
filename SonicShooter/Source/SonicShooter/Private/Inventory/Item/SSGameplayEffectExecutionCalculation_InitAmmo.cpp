// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/SSGameplayEffectExecutionCalculation_InitAmmo.h"

#include "Inventory/Item/SSAttributeSet_Ammo.h"
#include "Subobjects/SSObject_ClipAmmo.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "Inventory/SSInventoryComponent_Active.h"
#include "Inventory/Item/Gun/SSItemStack_Gun.h"



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
/// USSGameplayEffectExecutionCalculation_InitAmmo
////////////////////////////////////////////////


USSGameplayEffectExecutionCalculation_InitAmmo::USSGameplayEffectExecutionCalculation_InitAmmo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	const USSAttributeSet_Ammo* DefaultAttributeSet = GetDefault<USSAttributeSet_Ammo>();

	// Populate defaults for easy BP editing
	MaxAmmo = DefaultAttributeSet->GetMaxAmmo();
	MaxClipAmmo = DefaultAttributeSet->GetMaxClipAmmo();
}

void USSGameplayEffectExecutionCalculation_InitAmmo::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSSAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init ammo"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_Ammo::GetMaxAmmoAttribute(), EGameplayModOp::Override, MaxAmmo));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_Ammo::GetMaxClipAmmoAttribute(), EGameplayModOp::Override, MaxClipAmmo));


	// Calculate defaults
	float ClipAmmo = MaxClipAmmo;
	float BackupAmmo = MaxAmmo - MaxClipAmmo;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USSAttributeSet_Ammo::GetBackupAmmoAttribute(), EGameplayModOp::Override, BackupAmmo));
	
	// Get ClipAmmo subobject and initialize ClipAmmo
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
					GunStack->GetClipAmmoSubobject()->ClipAmmo = ClipAmmo;
					GunStack->GetClipAmmoSubobject()->ClipAmmo.MarkNetDirty(); // we are server-only right now so replicate it
				}
			}
		}
	}

}
