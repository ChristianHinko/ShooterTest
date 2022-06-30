// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Types/ASSAbilityInputID.h"



/**
 * AbilityInputID enum for ShooterTest
 */
UENUM()
enum ESTAbilityInputID
{
	/** This means the Ability implementor forgot to set an AbilityInputID in their Ability's constructor (``Unset`` is every Ability's default value) */
	Unset,
	/** This means the Ability is triggered without input (probably gameplay code) */
	NoInput,


	Run,
	Jump,
	Crouch,

	Interact,
	DropItem,

	PrimaryFire,
	SecondaryFire,
	Reload,

	SwapToLayout1st,
	SwapToLayout2nd,
	SwapToLayout3rd,
	SwapToLayout4th,
	SwapToLayout5th,
	SwapToPreviousSlot,
	SwapToLayoutForward,
	SwapToLayoutBackward,

	Pause,
	ScoreSheet,


	// MAX
	MAX					UMETA(Hidden)
};
