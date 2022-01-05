// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Wrappers/PropertyWrappers.h"

#include "AS_Ammo.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAS_Ammo : public UASSAttributeSet
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

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxClipAmmo, Category = "Attributes")
		FGameplayAttributeData MaxClipAmmo;
	ATTRIBUTE_ACCESSORS(UAS_Ammo, MaxClipAmmo)

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Attributes", meta = (HideFromModifiers))
		FFloatPropertyWrapper ClipAmmo;

	//UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (HideFromLevelInfos))
	//	FGameplayAttributeData BackupAmmoReceive;
	//ATTRIBUTE_ACCESSORS(UAS_Ammo, BackupAmmoReceive)

protected:
	virtual void PostInitProperties() override;


	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;



	UFUNCTION()
		virtual void OnRep_MaxAmmo(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_BackupAmmo(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_MaxClipAmmo(const FGameplayAttributeData& ServerBaseValue);

};
