// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/FAMAS/GEEC_FAMASInitialization.h"

#include "AbilitySystem/Types/SSGameplayEffectTypes.h"
#include "Item/AS_Ammo.h"



struct FFAMASInitializationStatics
{
	FGameplayEffectAttributeCaptureDefinition MaxAmmoDef;
	FGameplayEffectAttributeCaptureDefinition MaxClipAmmoDef;

	const FGameplayAttribute BackupAmmoAttribute; // no need to capture this one since we aren't reading it, but we are writing to it so we can do a cheap cache.
	

	FFAMASInitializationStatics()
		: BackupAmmoAttribute(UAS_Ammo::GetBackupAmmoAttribute())
	{
		// We are snapshotting so that we don't risk reading attribute values modified via blueprint (in case some careless developer tries to use blueprint mod magnitudes on this)
		MaxAmmoDef = FGameplayEffectAttributeCaptureDefinition(UAS_Ammo::GetMaxAmmoAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
		MaxClipAmmoDef = FGameplayEffectAttributeCaptureDefinition(UAS_Ammo::GetMaxClipAmmoAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
	}
};

static const FFAMASInitializationStatics& GetFAMASInitializationStatics()
{
	static FFAMASInitializationStatics Statics;
	return Statics;
}









UGEEC_FAMASInitialization::UGEEC_FAMASInitialization()
{
	RelevantAttributesToCapture.Add(GetFAMASInitializationStatics().MaxAmmoDef);
	RelevantAttributesToCapture.Add(GetFAMASInitializationStatics().MaxClipAmmoDef);
}

void UGEEC_FAMASInitialization::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
	{
		return;
	}


	float ClipAmmo = 0.f;
	float BackupAmmo = 0.f;




	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetFAMASInitializationStatics().BackupAmmoAttribute, EGameplayModOp::Override, BackupAmmo));
}
