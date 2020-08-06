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
class SONICSIEGE_API UAS_Character : public USSAttributeSet
{
	GENERATED_BODY()
	
public:
	// Constructor and default values
	UAS_Character();

	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MyCharacterAttribute, Category = "Attributes")
		FGameplayAttributeData MyCharacterAttribute;
	ATTRIBUTE_ACCESSORS(UAS_Character, MyCharacterAttribute)

protected:
	//These OnReps exist to make sure the GAS internal representations are synchronized properly during replication
	UFUNCTION()
		virtual void OnRep_MyCharacterAttribute(const FGameplayAttributeData& ServerBaseValue);
};
