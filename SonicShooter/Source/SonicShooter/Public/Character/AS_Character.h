// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AS_Character.generated.h"



/**
 * This attribute set will be on every character that uses the ability system (using AbilitySystemCharacter)
 * add universal character attributes here.
 */
UCLASS()
class SONICSHOOTER_API UAS_Character : public USSAttributeSet
{
	GENERATED_BODY()
	
public:
	// Constructor and default values
	UAS_Character();

#pragma region Gameplay Tags
	
#pragma endregion

	
	// Attributes
#pragma region Movement Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WalkSpeed, Category = "Attributes|Movement")
		FGameplayAttributeData WalkSpeed;
	ATTRIBUTE_ACCESSORS(UAS_Character, WalkSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WalkAcceleration, Category = "Attributes|Movement")
		FGameplayAttributeData WalkAcceleration;
	ATTRIBUTE_ACCESSORS(UAS_Character, WalkAcceleration)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RunSpeed, Category = "Attributes|Movement")
		FGameplayAttributeData RunSpeed;
	ATTRIBUTE_ACCESSORS(UAS_Character, RunSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RunAccelaration, Category = "Attributes|Movement")
		FGameplayAttributeData RunAccelaration;
	ATTRIBUTE_ACCESSORS(UAS_Character, RunAccelaration)
#pragma endregion


protected:
	virtual void SetSoftAttributeDefaults() override;


	//	Server only. Handle applying any modifications to incomming effects (ie. subtracting incomming damage using a shield attribute)
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	//	Server only. Handle using 'meta' attributes for modifying 'persistant' attributes. Such as Damage modifying Health
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	//These OnReps exist to make sure the GAS internal representations are synchronized properly during replication
	UFUNCTION()
		virtual void OnRep_WalkSpeed(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_WalkAcceleration(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_RunSpeed(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_RunAccelaration(const FGameplayAttributeData& ServerBaseValue);
};
