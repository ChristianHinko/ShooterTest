// Fill out your copyright notice in the Description page of Project Settings.

#include "Utilities/SSNativeGameplayTags.h"



// Ability tags
UE_DEFINE_GAMEPLAY_TAG(Tag_FireAbility,							TEXT("Ability.Fire"))
UE_DEFINE_GAMEPLAY_TAG(Tag_ReloadAbility,						TEXT("Ability.Reload"))
UE_DEFINE_GAMEPLAY_TAG(Tag_ADSAbility,							TEXT("Ability.ADS"))

UE_DEFINE_GAMEPLAY_TAG(Tag_JumpAbility,							TEXT("Ability.Movement.Jump"))
UE_DEFINE_GAMEPLAY_TAG(Tag_JumpStaticAbility,					TEXT("Ability.Movement.JumpStatic"))
UE_DEFINE_GAMEPLAY_TAG(Tag_CrouchAbility,						TEXT("Ability.Movement.Crouch"))
UE_DEFINE_GAMEPLAY_TAG(Tag_RunAbility,							TEXT("Ability.Movement.Run"))

UE_DEFINE_GAMEPLAY_TAG(Tag_InstantInteractAbility,				TEXT("Ability.Interact.InstantInteract"))
UE_DEFINE_GAMEPLAY_TAG(Tag_DurationInteractAbility,				TEXT("Ability.Interact.DurationInteract"))
UE_DEFINE_GAMEPLAY_TAG(Tag_AutoInteractAbility,					TEXT("Ability.Interact.AutoInteract"))

UE_DEFINE_GAMEPLAY_TAG(Tag_ItemSwitchAbility,					TEXT("Ability.Inventory.ItemSwitch"))
UE_DEFINE_GAMEPLAY_TAG(Tag_SwapItemSlotAbility,					TEXT("Ability.Inventory.SwapItemSlot"))


// Ability input tags
UE_DEFINE_GAMEPLAY_TAG(Tag_AbilityInputPrimaryFire,				TEXT("AbilityInput.PrimaryFire"))


// Gameplay Cue tags
UE_DEFINE_GAMEPLAY_TAG(Tag_TestGameplayCue,						TEXT("GameplayCue.Test"))


// Set By Caller tags
UE_DEFINE_GAMEPLAY_TAG(Tag_SetByCallerBackupAmmoDepletion,		TEXT("SetByCaller.BackupAmmoDepletion"))


// Character tags
UE_DEFINE_GAMEPLAY_TAG(Tag_JumpDisabled,						TEXT("Character.JumpDisabled"))
UE_DEFINE_GAMEPLAY_TAG(Tag_CrouchDisabled,						TEXT("Character.CrouchDisabled"))
UE_DEFINE_GAMEPLAY_TAG(Tag_RunDisabled,							TEXT("Character.RunDisabled"))

UE_DEFINE_GAMEPLAY_TAG(Tag_IsJumping,							TEXT("Character.State.IsJumping"))
UE_DEFINE_GAMEPLAY_TAG(Tag_IsCrouching,							TEXT("Character.State.IsCrouching"))
UE_DEFINE_GAMEPLAY_TAG(Tag_IsRunning,							TEXT("Character.State.IsRunning"))

UE_DEFINE_GAMEPLAY_TAG(Tag_HasMaxStamina,						TEXT("Character.State.HasMaxStamina"))

UE_DEFINE_GAMEPLAY_TAG(Tag_IsInteractingDuration,				TEXT("Character.State.IsInteractingDuration"))
UE_DEFINE_GAMEPLAY_TAG(Tag_IsFiringGun,							TEXT("Character.State.IsFiringGun"))
UE_DEFINE_GAMEPLAY_TAG(Tag_IsReloading,							TEXT("Character.State.IsReloading"))
UE_DEFINE_GAMEPLAY_TAG(Tag_IsAimingDownSights,					TEXT("Character.State.IsAimingDownSights"))


// Player tags
UE_DEFINE_GAMEPLAY_TAG(Tag_IsInFirstPerson,						TEXT("Player.State.IsInFirstPerson"))
UE_DEFINE_GAMEPLAY_TAG(Tag_IsInThirdPerson,						TEXT("Player.State.IsInThirdPerson"))


// Inventory tags
UE_DEFINE_GAMEPLAY_TAG(Tag_InventoryLayoutFirst,				TEXT("Inventory.Layout.First"))
UE_DEFINE_GAMEPLAY_TAG(Tag_InventoryLayoutSecond,				TEXT("Inventory.Layout.Second"))
UE_DEFINE_GAMEPLAY_TAG(Tag_InventoryLayoutThird,				TEXT("Inventory.Layout.Third"))
UE_DEFINE_GAMEPLAY_TAG(Tag_InventoryLayoutFourth,				TEXT("Inventory.Layout.Fourth"))
UE_DEFINE_GAMEPLAY_TAG(Tag_InventoryLayoutFifth,				TEXT("Inventory.Layout.Fifth"))
UE_DEFINE_GAMEPLAY_TAG(Tag_InventoryLayoutSixth,				TEXT("Inventory.Layout.Sixth"))
UE_DEFINE_GAMEPLAY_TAG(Tag_InventoryLayoutSeventh,				TEXT("Inventory.Layout.Seventh"))
UE_DEFINE_GAMEPLAY_TAG(Tag_InventoryLayoutEighth,				TEXT("Inventory.Layout.Eighth"))
UE_DEFINE_GAMEPLAY_TAG(Tag_InventoryLayoutNinth,				TEXT("Inventory.Layout.Ninth"))
UE_DEFINE_GAMEPLAY_TAG(Tag_InventoryLayoutTenth,				TEXT("Inventory.Layout.Tenth"))


// Item tags
UE_DEFINE_GAMEPLAY_TAG(Tag_WeaponTypeRifle,						TEXT("Item.ItemType.Weapon.Rifle"))
UE_DEFINE_GAMEPLAY_TAG(Tag_WeaponTypeShotgun,					TEXT("Item.ItemType.Weapon.Shotgun"))
UE_DEFINE_GAMEPLAY_TAG(Tag_WeaponTypePistol,					TEXT("Item.ItemType.Weapon.Pistol"))
UE_DEFINE_GAMEPLAY_TAG(Tag_WeaponTypeFAMAS,						TEXT("Item.ItemType.Weapon.FAMAS"))
