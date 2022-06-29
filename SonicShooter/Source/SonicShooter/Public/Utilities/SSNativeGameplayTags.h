// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"



/**
 * This module's Native Gameplay Tags wrapped in a namespace.
 * 
 * You should include this header in your project's PCH.
 * This is nice so that you can just start typing "SSNativeGameplayTags::" and then see the list of all of the module's Gameplay Tags.
 */
namespace SSNativeGameplayTags
{
	// Ability Tags
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Fire)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Reload)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ADS)

	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Jump)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_JumpStatic)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Crouch)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Run)

	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Interact_InstantInteract)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Interact_DurationInteract)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Interact_AutoInteract)


	// Gameplay Cue Tags
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Test)


	// Set By Caller Tags
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_BackupAmmoDepletion)


	// Character Tags
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_JumpDisabled)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_CrouchDisabled)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_RunDisabled)

	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsJumping)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsCrouching)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsRunning)

	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_HasMaxStamina)

	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsInteractingDuration)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsFiringGun)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsReloading)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsAimingDownSights)


	// Player Tags
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_IsInFirstPerson)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_IsInThirdPerson)


	// Item Tags
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Rifle)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Shotgun)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Pistol)
	SONICSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Famas)
}
