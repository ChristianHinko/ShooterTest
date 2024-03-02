// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "STAttributeSet_PlayerState.generated.h"



/**
 *
 */
UCLASS()
class SHOOTERTEST_API USTAttributeSet_PlayerState : public UASSAttributeSet
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ExampleAttribute, Category = "Attributes")
        FGameplayAttributeData ExampleAttribute;
    ATTRIBUTE_ACCESSORS(USTAttributeSet_PlayerState, ExampleAttribute)

protected:
    UFUNCTION()
        virtual void OnRep_ExampleAttribute(const FGameplayAttributeData& OldValue);
};
