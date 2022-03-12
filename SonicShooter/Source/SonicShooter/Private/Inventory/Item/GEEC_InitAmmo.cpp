// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/GEEC_InitAmmo.h"

#include "Inventory/Item/AS_Ammo.h"
#include "Subobjects/O_Ammo.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "Inventory/Item/Gun/ArcItemStack_Gun.h"



////////////////////////////////////////////////
/// UGEEC_InitFAmmoInitializationStaticsAmmo
////////////////////////////////////////////////

struct FAmmoInitializationStatics
{
	// No need to capture these Attributes since we aren't reading from them, but writing to them
	const FGameplayAttribute MaxAmmoAttribute;
	const FGameplayAttribute MaxClipAmmoAttribute;
	const FGameplayAttribute BackupAmmoAttribute;
	
	FAmmoInitializationStatics()
		: MaxAmmoAttribute(UAS_Ammo::GetMaxAmmoAttribute())
		, MaxClipAmmoAttribute(UAS_Ammo::GetMaxClipAmmoAttribute())
		, BackupAmmoAttribute(UAS_Ammo::GetBackupAmmoAttribute())
	{

	}
};

static const FAmmoInitializationStatics& GetAmmoInitializationStatics()
{
	static FAmmoInitializationStatics Statics;
	return Statics;
}



////////////////////////////////////////////////
/// UGEEC_InitAmmo
////////////////////////////////////////////////


UGEEC_InitAmmo::UGEEC_InitAmmo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	const UAS_Ammo* DefaultAttributeSet = GetDefault<UAS_Ammo>();

	// Populate defaults
	MaxAmmo = DefaultAttributeSet->GetMaxAmmo();
	MaxClipAmmo = DefaultAttributeSet->GetMaxClipAmmo();
}

void UGEEC_InitAmmo::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		UE_LOG(LogSSAbilitySystemSetup, Error, TEXT("%s(): TargetAbilitySystemComponent was NULL. Failed to init ammo"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	// Set defaults
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetAmmoInitializationStatics().MaxAmmoAttribute,		EGameplayModOp::Override, MaxAmmo));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetAmmoInitializationStatics().MaxClipAmmoAttribute,	EGameplayModOp::Override, MaxClipAmmo));


	// Calculate defaults
	float ClipAmmo = MaxClipAmmo;
	float BackupAmmo = MaxAmmo - MaxClipAmmo;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetAmmoInitializationStatics().BackupAmmoAttribute,		EGameplayModOp::Override, BackupAmmo));
	
	// Get ammo subobject and initialize ClipAmmo
	if (const FGAAI_Shooter* ShooterActorInfo = static_cast<const FGAAI_Shooter*>(TargetAbilitySystemComponent->AbilityActorInfo.Get()))
	{
		USSArcInventoryComponent_Active* InventoryComponent = ShooterActorInfo->GetInventoryComponent();
		if (IsValid(InventoryComponent))
		{
			const UArcItemStack* ActiveItemStack = InventoryComponent->GetActiveItemStack();
			if (IsValid(ActiveItemStack))
			{
				const UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(ActiveItemStack);
				if (IsValid(GunStack))
				{
					GunStack->GetAmmoSubobject()->ClipAmmo = ClipAmmo;
					GunStack->GetAmmoSubobject()->ClipAmmo.MarkNetDirty(); // we are server-only right now so replicate it
				}
			}
		}
	}

}
