// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/SSNativeGameplayTags.h"



namespace SSNativeGameplayTags
{
	// Ability Tags
	UE_DEFINE_GAMEPLAY_TAG(Ability_Fire,											TEXT("Ability.Fire"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Reload,											TEXT("Ability.Reload"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_ADS,												TEXT("Ability.ADS"))
	
	UE_DEFINE_GAMEPLAY_TAG(Ability_Movement_Jump,									TEXT("Ability.Movement.Jump"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Movement_JumpStatic,								TEXT("Ability.Movement.JumpStatic"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Movement_Crouch,									TEXT("Ability.Movement.Crouch"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Movement_Run,									TEXT("Ability.Movement.Run"))
	
	UE_DEFINE_GAMEPLAY_TAG(Ability_Interact_InstantInteract,						TEXT("Ability.Interact.InstantInteract"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Interact_DurationInteract,						TEXT("Ability.Interact.DurationInteract"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Interact_AutoInteract,							TEXT("Ability.Interact.AutoInteract"))
	
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_ItemHistory_Previous,			TEXT("Ability.Inventory.SwapItem.ItemHistory.Previous"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_Forward,			TEXT("Ability.Inventory.SwapItem.LayoutIndex.Forward"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_Backward,			TEXT("Ability.Inventory.SwapItem.LayoutIndex.Backward"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_1st,				TEXT("Ability.Inventory.SwapItem.LayoutIndex.1st"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_2nd,				TEXT("Ability.Inventory.SwapItem.LayoutIndex.2nd"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_3rd,				TEXT("Ability.Inventory.SwapItem.LayoutIndex.3rd"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_4th,				TEXT("Ability.Inventory.SwapItem.LayoutIndex.4th"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_5th,				TEXT("Ability.Inventory.SwapItem.LayoutIndex.5th"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_6th,				TEXT("Ability.Inventory.SwapItem.LayoutIndex.6th"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_7th,				TEXT("Ability.Inventory.SwapItem.LayoutIndex.7th"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_8th,				TEXT("Ability.Inventory.SwapItem.LayoutIndex.8th"))
	UE_DEFINE_GAMEPLAY_TAG(Ability_Inventory_SwapItem_LayoutIndex_9th,				TEXT("Ability.Inventory.SwapItem.LayoutIndex.9th"))
	
	
	// Gameplay Cue Tags
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Test,										TEXT("GameplayCue.Test"))
	
	
	// Set By Caller Tags
	UE_DEFINE_GAMEPLAY_TAG(SetByCaller_BackupAmmoDepletion,							TEXT("SetByCaller.BackupAmmoDepletion"))
	
	
	// Character Tags
	UE_DEFINE_GAMEPLAY_TAG(Character_JumpDisabled,									TEXT("Character.JumpDisabled"))
	UE_DEFINE_GAMEPLAY_TAG(Character_CrouchDisabled,								TEXT("Character.CrouchDisabled"))
	UE_DEFINE_GAMEPLAY_TAG(Character_RunDisabled,									TEXT("Character.RunDisabled"))
	
	UE_DEFINE_GAMEPLAY_TAG(Character_State_IsJumping,								TEXT("Character.State.IsJumping"))
	UE_DEFINE_GAMEPLAY_TAG(Character_State_IsCrouching,								TEXT("Character.State.IsCrouching"))
	UE_DEFINE_GAMEPLAY_TAG(Character_State_IsRunning,								TEXT("Character.State.IsRunning"))
	
	UE_DEFINE_GAMEPLAY_TAG(Character_State_HasMaxStamina,							TEXT("Character.State.HasMaxStamina"))
	
	UE_DEFINE_GAMEPLAY_TAG(Character_State_IsInteractingDuration,					TEXT("Character.State.IsInteractingDuration"))
	UE_DEFINE_GAMEPLAY_TAG(Character_State_IsFiringGun,								TEXT("Character.State.IsFiringGun"))
	UE_DEFINE_GAMEPLAY_TAG(Character_State_IsReloading,								TEXT("Character.State.IsReloading"))
	UE_DEFINE_GAMEPLAY_TAG(Character_State_IsAimingDownSights,						TEXT("Character.State.IsAimingDownSights"))
	
	
	// Player Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_State_IsInFirstPerson,							TEXT("Player.State.IsInFirstPerson"))
	UE_DEFINE_GAMEPLAY_TAG(Player_State_IsInThirdPerson,							TEXT("Player.State.IsInThirdPerson"))
	
	
	// Inventory Tags
	UE_DEFINE_GAMEPLAY_TAG(Inventory_Layout_1st,									TEXT("Inventory.Layout.1st"))
	UE_DEFINE_GAMEPLAY_TAG(Inventory_Layout_2nd,									TEXT("Inventory.Layout.2nd"))
	UE_DEFINE_GAMEPLAY_TAG(Inventory_Layout_3rd,									TEXT("Inventory.Layout.3rd"))
	UE_DEFINE_GAMEPLAY_TAG(Inventory_Layout_4th,									TEXT("Inventory.Layout.4th"))
	UE_DEFINE_GAMEPLAY_TAG(Inventory_Layout_5th,									TEXT("Inventory.Layout.5th"))
	UE_DEFINE_GAMEPLAY_TAG(Inventory_Layout_6th,									TEXT("Inventory.Layout.6th"))
	UE_DEFINE_GAMEPLAY_TAG(Inventory_Layout_7th,									TEXT("Inventory.Layout.7th"))
	UE_DEFINE_GAMEPLAY_TAG(Inventory_Layout_8th,									TEXT("Inventory.Layout.8th"))
	UE_DEFINE_GAMEPLAY_TAG(Inventory_Layout_9th,									TEXT("Inventory.Layout.9th"))
	
	
	// Item Tags
	UE_DEFINE_GAMEPLAY_TAG(Item_ItemType_Weapon_Rifle,								TEXT("Item.ItemType.Weapon.Rifle"))
	UE_DEFINE_GAMEPLAY_TAG(Item_ItemType_Weapon_Shotgun,							TEXT("Item.ItemType.Weapon.Shotgun"))
	UE_DEFINE_GAMEPLAY_TAG(Item_ItemType_Weapon_Pistol,								TEXT("Item.ItemType.Weapon.Pistol"))
	UE_DEFINE_GAMEPLAY_TAG(Item_ItemType_Weapon_FAMAS,								TEXT("Item.ItemType.Weapon.FAMAS"))
}
