// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AS_Actor.generated.h"



/**
 * This attribute set will be on every actor that uses the ability system (using AbilitySystemActor) add universal actor attributes here
 */
UCLASS()
class SONICSHOOTER_API UAS_Actor : public USSAttributeSet
{
	GENERATED_BODY()

public:
	// Constructor and default values
	UAS_Actor();

	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MyActorAttribute, Category = "Attributes")
		FGameplayAttributeData MyActorAttribute;
	ATTRIBUTE_ACCESSORS(UAS_Actor, MyActorAttribute)

protected:
	//These OnReps exist to make sure the GAS internal representations are synchronized properly during replication
	UFUNCTION()
		virtual void OnRep_MyActorAttribute(const FGameplayAttributeData& ServerBaseValue);
};
