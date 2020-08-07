// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AS_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class SONICSIEGE_API UAS_Weapon : public USSAttributeSet
{
	GENERATED_BODY()

public:
	UAS_Weapon();

	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentAmmo, Category = "Attributes")
		FGameplayAttributeData CurrentAmmo;
	ATTRIBUTE_ACCESSORS(UAS_Weapon, CurrentAmmo)

protected:
	UFUNCTION()
		virtual void OnRep_CurrentAmmo(const FGameplayAttributeData& ServerBaseValue);
};
