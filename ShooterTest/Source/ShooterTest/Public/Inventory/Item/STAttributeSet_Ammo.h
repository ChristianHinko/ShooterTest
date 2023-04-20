// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "STAttributeSet_Ammo.generated.h"



/**
 * 
 */
UCLASS()
class SHOOTERTEST_API USTAttributeSet_Ammo : public UASSAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxAmmo, Category = "Attributes")
		FGameplayAttributeData MaxAmmo;
	ATTRIBUTE_ACCESSORS(USTAttributeSet_Ammo, MaxAmmo)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxClipAmmo, Category = "Attributes")
		FGameplayAttributeData MaxClipAmmo;
	ATTRIBUTE_ACCESSORS(USTAttributeSet_Ammo, MaxClipAmmo)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BackupAmmo, Category = "Attributes")
		FGameplayAttributeData BackupAmmo;
	ATTRIBUTE_ACCESSORS(USTAttributeSet_Ammo, BackupAmmo)

	//UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (HideFromLevelInfos))
	//	FGameplayAttributeData BackupAmmoReceive;
	//ATTRIBUTE_ACCESSORS(USTAttributeSet_Ammo, BackupAmmoReceive)

protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	UFUNCTION()
		virtual void OnRep_MaxAmmo(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_BackupAmmo(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MaxClipAmmo(const FGameplayAttributeData& OldValue);
};
