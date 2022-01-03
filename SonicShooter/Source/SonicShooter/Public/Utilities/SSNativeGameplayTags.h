// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"



// Ability tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_FireAbility)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_ReloadAbility)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_ADSAbility)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_JumpAbility)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_JumpStaticAbility)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_CrouchAbility)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_RunAbility)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InstantInteractAbility)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_DurationInteractAbility)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_AutoInteractAbility)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_ItemSwitchAbility)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_SwapItemSlotAbility)


// Ability input tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_AbilityInputPrimaryFire)


// Gameplay Cue tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_TestGameplayCue)


// Set By Caller tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_SetByCallerBackupAmmoDepletion)


// Character tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_JumpDisabled)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_CrouchDisabled)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_RunDisabled)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_IsJumping)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_IsCrouching)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_IsRunning)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_HasMaxStamina)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_IsInteractingDuration)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_IsFiringGun)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_IsReloading)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_IsAimingDownSights)


// Player tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_IsInFirstPerson)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_IsInThirdPerson)


// Inventory tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryEquipmentSlot)

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryLayoutFirst)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryLayoutSecond)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryLayoutThird)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryLayoutFourth)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryLayoutFifth)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryLayoutSixth)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryLayoutSeventh)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryLayoutEighth)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryLayoutNinth)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_InventoryLayoutTenth)


// Item tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_WeaponTypeRifle)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_WeaponTypeShotgun)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_WeaponTypePistol)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_WeaponTypeFAMAS)
