// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AS_ExampleAbilitySystemCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAS_ExampleAbilitySystemCharacter : public USSAttributeSet
{
	GENERATED_BODY()

public:
	UAS_ExampleAbilitySystemCharacter();

	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ExampleAttribute, Category = "Attributes")
		FGameplayAttributeData ExampleAttribute;
	ATTRIBUTE_ACCESSORS(UAS_ExampleAbilitySystemCharacter, ExampleAttribute)

protected:
	UFUNCTION()
		virtual void OnRep_ExampleAttribute(const FGameplayAttributeData& ServerBaseValue);
};
