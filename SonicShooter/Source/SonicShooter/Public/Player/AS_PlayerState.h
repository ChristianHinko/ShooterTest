// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AS_PlayerState.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAS_PlayerState : public USSAttributeSet
{
	GENERATED_BODY()
	
public:
	// Constructor and default values
	UAS_PlayerState();

	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ExampleAttribute, Category = "Attributes")
		FGameplayAttributeData ExampleAttribute;
	ATTRIBUTE_ACCESSORS(UAS_PlayerState, ExampleAttribute)

protected:
	//These OnReps exist to make sure the GAS internal representations are synchronized properly during replication
	UFUNCTION()
		virtual void OnRep_ExampleAttribute(const FGameplayAttributeData& ServerBaseValue);
};
