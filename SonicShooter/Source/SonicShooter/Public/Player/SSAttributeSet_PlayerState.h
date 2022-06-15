// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "SSAttributeSet_PlayerState.generated.h"



/**
 *
 */
UCLASS()
class SONICSHOOTER_API USSAttributeSet_PlayerState : public UASSAttributeSet
{
	GENERATED_BODY()

public:
	USSAttributeSet_PlayerState(const FObjectInitializer& ObjectInitializer);


	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ExampleAttribute, Category = "Attributes")
		FGameplayAttributeData ExampleAttribute;
	ATTRIBUTE_ACCESSORS(USSAttributeSet_PlayerState, ExampleAttribute)

protected:
	// OnReps
	UFUNCTION()
		virtual void OnRep_ExampleAttribute(const FGameplayAttributeData& OldValue);
};
