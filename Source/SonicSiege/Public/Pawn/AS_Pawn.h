// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AS_Pawn.generated.h"



/**
 * This attribute set will be on every pawn that uses the ability system (using AbilitySystemPawn) add universal pawn attributes here
 */
UCLASS()
class SONICSIEGE_API UAS_Pawn : public USSAttributeSet
{
	GENERATED_BODY()
	
public:
	// Constructor and default values
	UAS_Pawn();

	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MyPawnAttribute, Category = "Attributes")
		FGameplayAttributeData MyPawnAttribute;
	ATTRIBUTE_ACCESSORS(UAS_Pawn, MyPawnAttribute)

protected:
	//These OnReps exist to make sure the GAS internal representations are synchronized properly during replication
	UFUNCTION()
		virtual void OnRep_MyPawnAttribute(const FGameplayAttributeData& ServerBaseValue);
};
