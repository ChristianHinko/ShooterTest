// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAbilitySystemComponent.h"

#include "SSAbilitySystemComponent.generated.h"



UENUM()
enum EAbilityInputID
{
	// 0
	// This means the ability implementor forgot to set an AbilityInputId in their ability's constructor ("Unset" is every ability's default value)
	Unset,
	// 1
	// This means the ability is triggered without input (probably gameplay code)
	NoInput,

	// 2
	Run,
	// 3
	Jump,
	// 4
	Crouch,
	// 5
	Interact,
	// 6
	PrimaryFire,
	// 7
	SecondaryFire,
	// 8
	Reload,
	// 9
	Item0,
	// 10
	Item1,
	// 11
	Item2,
	// 12
	Item3,
	// 13
	Item4,
	// 14
	SwitchWeapon,
	// 15
	NextItem,
	// 16
	PreviousItem,
	// 17
	DropItem,
	// 18
	Pause,
	// 19
	ScoreSheet,


	// MAX
	MAX					UMETA(Hidden) // show a Max value since this isn't an enum class
};

/**
 * Our custom Ability System Component
 */
UCLASS()
class SONICSHOOTER_API USSAbilitySystemComponent : public UASSAbilitySystemComponent
{
	GENERATED_BODY()

public:
	USSAbilitySystemComponent();


};