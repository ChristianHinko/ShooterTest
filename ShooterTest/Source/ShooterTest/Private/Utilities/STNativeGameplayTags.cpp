// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/STNativeGameplayTags.h"



namespace STNativeGameplayTags
{
	// Input Actions
	UE_DEFINE_GAMEPLAY_TAG(InputAction_Run,											TEXT("InputAction.Run"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_Jump,										TEXT("InputAction.Jump"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_Crouch,										TEXT("InputAction.Crouch"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_Interact,									TEXT("InputAction.Interact"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_PrimaryFire,									TEXT("InputAction.PrimaryFire"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_SecondaryFire,								TEXT("InputAction.SecondaryFire"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_Reload,										TEXT("InputAction.Reload"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_SwapToLayout1st,								TEXT("InputAction.SwapToLayout1st"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_SwapToLayout2nd,								TEXT("InputAction.SwapToLayout2nd"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_SwapToLayout3rd,								TEXT("InputAction.SwapToLayout3rd"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_SwapToLayout4th,								TEXT("InputAction.SwapToLayout4th"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_SwapToLayout5th,								TEXT("InputAction.SwapToLayout5th"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_SwapToPreviousSlot,							TEXT("InputAction.SwapToPreviousSlot"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_SwapToLayoutForward,							TEXT("InputAction.SwapToLayoutForward"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_SwapToLayoutBackward,						TEXT("InputAction.SwapToLayoutBackward"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_DropItem,									TEXT("InputAction.DropItem"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_Pause,										TEXT("InputAction.Pause"))
	UE_DEFINE_GAMEPLAY_TAG(InputAction_ScoreSheet,									TEXT("InputAction.ScoreSheet"))

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


	// Item Tags
	UE_DEFINE_GAMEPLAY_TAG(Item_ItemType_Weapon_Rifle,								TEXT("Item.ItemType.Weapon.Rifle"))
	UE_DEFINE_GAMEPLAY_TAG(Item_ItemType_Weapon_Shotgun,							TEXT("Item.ItemType.Weapon.Shotgun"))
	UE_DEFINE_GAMEPLAY_TAG(Item_ItemType_Weapon_Pistol,								TEXT("Item.ItemType.Weapon.Pistol"))
	UE_DEFINE_GAMEPLAY_TAG(Item_ItemType_Weapon_Famas,								TEXT("Item.ItemType.Weapon.Famas"))
}
