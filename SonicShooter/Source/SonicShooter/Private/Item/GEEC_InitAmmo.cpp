// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GEEC_InitAmmo.h"

#include "Item/AS_Ammo.h"



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




UGEEC_InitAmmo::UGEEC_InitAmmo()
{
	const UAS_Ammo* DefaultAmmoAttributeSet = GetDefault<UAS_Ammo>(UAS_Ammo::StaticClass());

	MaxAmmo = DefaultAmmoAttributeSet->GetMaxAmmo();
	MaxClipAmmo = DefaultAmmoAttributeSet->GetMaxClipAmmo();
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
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetAmmoInitializationStatics().MaxAmmoAttribute, EGameplayModOp::Override, MaxAmmo));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetAmmoInitializationStatics().MaxClipAmmoAttribute, EGameplayModOp::Override, MaxClipAmmo));

	// Calculate defaults
	float ClipAmmo = MaxClipAmmo;
	float BackupAmmo = MaxAmmo - MaxClipAmmo;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetAmmoInitializationStatics().BackupAmmoAttribute, EGameplayModOp::Override, BackupAmmo));
	
	// Search for ammo Attribute Set and initialize ClipAmmo. TODO: this is really bad accessing an Ability System Component's Attribute Sets directly - move ClipAmmo somewhere else!
	{
		UAS_Ammo** AmmoAttributeSetPtr = nullptr;
		int32* index = nullptr;
		TargetAbilitySystemComponent->GetSpawnedAttributes_Mutable().FindItemByClass<UAS_Ammo>(AmmoAttributeSetPtr, index, 0);
		if (AmmoAttributeSetPtr)
		{
			UAS_Ammo* AmmoAttributeSet = *AmmoAttributeSetPtr;
			if (IsValid(AmmoAttributeSet))
			{
				AmmoAttributeSet->ClipAmmo = ClipAmmo;
			}
		}
	}

}
