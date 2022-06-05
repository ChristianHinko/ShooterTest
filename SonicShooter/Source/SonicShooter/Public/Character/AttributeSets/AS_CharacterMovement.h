// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AS_CharacterMovement.generated.h"



/**
 * This attribute set will be on every character. Add universal character attributes here - but avoid doing so if you can, try to make Attributes into modular Attribute Sets
 */
UCLASS()
class SONICSHOOTER_API UAS_CharacterMovement : public UASSAttributeSet
{
	GENERATED_BODY()

public:
	// Constructor and default values
	UAS_CharacterMovement(const FObjectInitializer& ObjectInitializer);


	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WalkSpeed, Category = "MovementAttributes")
		FGameplayAttributeData WalkSpeed;
	ATTRIBUTE_ACCESSORS(UAS_CharacterMovement, WalkSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WalkAcceleration, Category = "MovementAttributes")
		FGameplayAttributeData WalkAcceleration;
	ATTRIBUTE_ACCESSORS(UAS_CharacterMovement, WalkAcceleration)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RunSpeed, Category = "MovementAttributes")
		FGameplayAttributeData RunSpeed;
	ATTRIBUTE_ACCESSORS(UAS_CharacterMovement, RunSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RunAccelaration, Category = "MovementAttributes")
		FGameplayAttributeData RunAccelaration;
	ATTRIBUTE_ACCESSORS(UAS_CharacterMovement, RunAccelaration)


protected:
	// These OnReps exist to make sure the GAS internal representations are synchronized properly during replication
	UFUNCTION()
		virtual void OnRep_WalkSpeed(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_WalkAcceleration(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_RunSpeed(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_RunAccelaration(const FGameplayAttributeData& ServerBaseValue);
};
