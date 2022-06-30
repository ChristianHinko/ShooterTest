// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"



/**
 * This module's Native Gameplay Tags wrapped in a namespace.
 * 
 * You should include this header in your project's PCH.
 * This is nice so that you can just start typing "STNativeGameplayTags::" and then see the list of all of the module's Gameplay Tags.
 */
namespace STNativeGameplayTags
{
	// Ability Tags
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Fire)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Reload)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ADS)

	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Jump)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_JumpStatic)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Crouch)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Run)

	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Interact_InstantInteract)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Interact_DurationInteract)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Interact_AutoInteract)


	// Gameplay Cue Tags
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Test)


	// Set By Caller Tags
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_BackupAmmoDepletion)


	// Character Tags
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_JumpDisabled)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_CrouchDisabled)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_RunDisabled)

	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsJumping)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsCrouching)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsRunning)

	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_HasMaxStamina)

	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsInteractingDuration)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsFiringGun)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsReloading)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsAimingDownSights)


	// Player Tags
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_IsInFirstPerson)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_IsInThirdPerson)


	// Item Tags
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Rifle)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Shotgun)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Pistol)
	SHOOTERTEST_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Famas)
}
