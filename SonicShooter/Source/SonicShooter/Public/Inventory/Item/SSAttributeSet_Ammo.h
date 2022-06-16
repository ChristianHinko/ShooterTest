// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "SSAttributeSet_Ammo.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSAttributeSet_Ammo : public UASSAttributeSet
{
	GENERATED_BODY()

public:
	USSAttributeSet_Ammo(const FObjectInitializer& ObjectInitializer);


	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxAmmo, Category = "Attributes")
		FGameplayAttributeData MaxAmmo;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Ammo, MaxAmmo)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxClipAmmo, Category = "Attributes")
		FGameplayAttributeData MaxClipAmmo;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Ammo, MaxClipAmmo)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BackupAmmo, Category = "Attributes")
		FGameplayAttributeData BackupAmmo;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_Ammo, BackupAmmo)

	//UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (HideFromLevelInfos))
	//	FGameplayAttributeData BackupAmmoReceive;
	//ATTRIBUTE_ACCESSORS(USSAttributeSet_Ammo, BackupAmmoReceive)

protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	// OnReps
	UFUNCTION()
		virtual void OnRep_MaxAmmo(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_BackupAmmo(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MaxClipAmmo(const FGameplayAttributeData& OldValue);

};
