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
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Fire)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Reload)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ADS)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Jump)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_JumpStatic)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Crouch)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Run)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Interact_InstantInteract)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Interact_DurationInteract)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Interact_AutoInteract)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_ItemHistory_Previous)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_Forward)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_Backward)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_1st)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_2nd)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_3rd)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_4th)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_5th)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_6th)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_7th)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_8th)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Inventory_SwapItem_LayoutIndex_9th)


	// Gameplay Cue Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Test)


	// Set By Caller Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_BackupAmmoDepletion)


	// Character Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_JumpDisabled)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_CrouchDisabled)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_RunDisabled)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsJumping)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsCrouching)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsRunning)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_HasMaxStamina)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsInteractingDuration)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsFiringGun)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsReloading)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_IsAimingDownSights)


	// Player Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_IsInFirstPerson)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_IsInThirdPerson)


	// Inventory Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Layout_1st)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Layout_2nd)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Layout_3rd)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Layout_4th)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Layout_5th)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Layout_6th)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Layout_7th)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Layout_8th)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Layout_9th)


	// Item Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Rifle)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Shotgun)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_Pistol)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ItemType_Weapon_FAMAS)
}
