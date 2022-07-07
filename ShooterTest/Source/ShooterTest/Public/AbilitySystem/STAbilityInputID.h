// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Types/ASSAbilityInputID.h"



/**
 * Our AbilityInputID enum
 */
UENUM()
enum class ESTAbilityInputID : uint8
{
	Run = static_cast<uint8>(EASSAbilityInputID::MAX),
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


	MAX					UMETA(Hidden)
};
