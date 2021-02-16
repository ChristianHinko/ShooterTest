// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AS_Ammo.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAS_Ammo : public USSAttributeSet
{
	GENERATED_BODY()

public:
	UAS_Ammo();

	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxAmmo, Category = "Attributes")
		FGameplayAttributeData MaxAmmo;
	ATTRIBUTE_ACCESSORS(UAS_Ammo, MaxAmmo)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BackupAmmo, Category = "Attributes")
		FGameplayAttributeData BackupAmmo;
	ATTRIBUTE_ACCESSORS(UAS_Ammo, BackupAmmo)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxClipSize, Category = "Attributes")
		FGameplayAttributeData MaxClipSize;
	ATTRIBUTE_ACCESSORS(UAS_Ammo, MaxClipSize)

	UPROPERTY(BlueprintReadOnly/*, ReplicatedUsing = OnRep_ClipAmmo*/, Category = "Attributes", meta = (HideFromModifiers))
		FGameplayAttributeData ClipAmmo;
	ATTRIBUTE_ACCESSORS(UAS_Ammo, ClipAmmo)

	//UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (HideFromLevelInfos))
	//	FGameplayAttributeData BackupAmmoReceive;
	//ATTRIBUTE_ACCESSORS(UAS_Ammo, BackupAmmoReceive)

protected:
	virtual void SetSoftAttributeDefaults() override;


	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;



	UFUNCTION()
		virtual void OnRep_MaxAmmo(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BackupAmmo(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_MaxClipSize(const FGameplayAttributeData& ServerBaseValue);

	//UFUNCTION()
	//	virtual void OnRep_ClipAmmo(const FGameplayAttributeData& ServerBaseValue);
};
