// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSCharacter_Shooter.h"

#include "Net/UnrealNetwork.h"
#include "Character/SSCharacterMovementComponent_Shooter.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "Subobjects/ActorComponents/SSActorComponent_Interactor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/SSInventoryComponent_Shooter.h"
#include "ArcItemStack.h"
#include "AttributeSets/ASSEAttributeSet_Health.h"
#include "AbilitySystem/AttributeSets/SSAttributeSet_Stamina.h"
#include "Subobjects/ASSActorComponent_AbilitySystemSetup.h"
#include "ArcInventory.h"




const FName ASSCharacter_Shooter::InventoryComponentName = TEXT("InventoryComponent");

ASSCharacter_Shooter::ASSCharacter_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer
		.SetDefaultSubobjectClass<USSCharacterMovementComponent_Shooter>(CharacterMovementComponentName)
		.SetDefaultSubobjectClass<USSInventoryComponent_Shooter>(InventoryComponentName)
	)
{
	// Create Inventory
	InventoryComponent = CreateDefaultSubobject<UArcInventoryComponent>(InventoryComponentName);
	ShooterInventoryComponent = Cast<USSInventoryComponent_Shooter>(InventoryComponent);

	// Create Interactor
	Interactor = CreateDefaultSubobject<USSActorComponent_Interactor>(TEXT("Interactor"));

	// Default to first person
	bFirstPerson = true;
	bUseControllerRotationYaw = true; // let the camera rotation determine our yaw
	GetCharacterMovement()->bOrientRotationToMovement = false; // don't rotate the Character in the movement direction

	// Configure camera sway
	CameraSwayAmount = FVector(0.f, 1.3f, 0.4f);
	AddedCameraSwayDuringADS = FVector(0.f, -1.1f, -0.1f);
}

void ASSCharacter_Shooter::BeginPlay()
{
	Super::BeginPlay();

}


#include "Kismet/KismetSystemLibrary.h"
#include "AttributeSets/ASSEAttributeSet_Health.h"
#include "Inventory/Item/SSAttributeSet_Ammo.h"
#include "Inventory/Item/Gun/SSAttributeSet_Gun.h"
#include "Subobjects/SSObject_ClipAmmo.h"
#include "Subobjects/SSObject_BulletSpread.h"
#include "Subobjects/SSObject_Stamina.h"
#include "AbilitySystem/AttributeSets/SSAttributeSet_Stamina.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Item\ArcItemDefinition_New.h"
#include "Inventory/Item/Gun/SSItemStack_Gun.h"
#include "Character/SSCharacterMovementComponent.h"
#include "AbilitySystem/AbilitySystemComponents/SSAbilitySystemComponent_Shooter.h"
#include "AbilitySystem/ASSAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/SSAttributeSet_Stamina.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "GameFramework/SpringArmComponent.h"
void ASSCharacter_Shooter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	//for (int32 i = 0; i < ShooterInventoryComponent->ActiveItemHistory.Num(); ++i)
	//{
	//	FArcInventoryItemSlotReference current = ShooterInventoryComponent->ActiveItemHistory[i];

	//	UKismetSystemLibrary::PrintString(this, "["+FString::FromInt(current.SlotId)+"] " + current.SlotTags.GetByIndex(1).ToString(), true, false, FLinearColor::Green);
	//}

	if (ShooterInventoryComponent.IsValid())
	{
		//UKismetSystemLibrary::PrintString(this, "Current Item Slot: " + FString::FromInt(ShooterInventoryComponent->GetActiveItemSlot().SlotId), true, false);
		//UKismetSystemLibrary::PrintString(this, "Pending Item Slot: " + FString::FromInt(ShooterInventoryComponent->PendingItemSlot), true, false);
	}

	if (ShooterInventoryComponent.IsValid())
	{
		const UArcItemStack* ActiveItemStack = ShooterInventoryComponent->GetActiveItemStack();
		if (IsValid(ActiveItemStack))
		{
			const USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(ActiveItemStack);
			if (IsValid(GunStack))
			{
				const FPWFloatPropertyWrapper& ClipAmmo = GunStack->GetClipAmmoSubobject()->ClipAmmo;
				//UKismetSystemLibrary::PrintString(this, ClipAmmo.GetDebugString(), true, false);

				const FPWFloatPropertyWrapper& CurrentBulletSpread = GunStack->GetBulletSpreadSubobject()->CurrentBulletSpread;
				//UKismetSystemLibrary::PrintString(this, CurrentBulletSpread.GetDebugString(), true, false);
			}
		}


	}

	if (GetSSCharacterMovementComponent())
	{
		//if (IsValid(GetSSCharacterMovementComponent()->StaminaSubobject))
		//{
		//	const FPWFloatPropertyWrapper& Stamina = GetSSCharacterMovementComponent()->StaminaSubobject->Stamina;
			//UKismetSystemLibrary::PrintString(this, Stamina.GetDebugString(), true, false);

		//}
	}
	if (IsValid(GetAbilitySystemComponent()))
	{
		const float MaxStamina = GetAbilitySystemComponent()->GetNumericAttribute(USSAttributeSet_Stamina::GetMaxStaminaAttribute());
		const float StaminaDrain = GetAbilitySystemComponent()->GetNumericAttribute(USSAttributeSet_Stamina::GetStaminaDrainAttribute());
		const float StaminaGain = GetAbilitySystemComponent()->GetNumericAttribute(USSAttributeSet_Stamina::GetStaminaGainAttribute());
		const float StaminaRegenPause = GetAbilitySystemComponent()->GetNumericAttribute(USSAttributeSet_Stamina::GetStaminaRegenPauseAttribute());

		//UKismetSystemLibrary::PrintString(this, TEXT("MaxStamina: ") + FString::SanitizeFloat(MaxStamina), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaDrain: ") + FString::SanitizeFloat(StaminaDrain), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaGain: ") + FString::SanitizeFloat(StaminaGain), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaRegenPause: ") + FString::SanitizeFloat(StaminaRegenPause), true, false);




		const float MaxAmmo = GetAbilitySystemComponent()->GetNumericAttribute(USSAttributeSet_Ammo::GetMaxAmmoAttribute());
		const float MaxClipAmmo = GetAbilitySystemComponent()->GetNumericAttribute(USSAttributeSet_Ammo::GetMaxClipAmmoAttribute());
		const float BackupAmmo = GetAbilitySystemComponent()->GetNumericAttribute(USSAttributeSet_Ammo::GetBackupAmmoAttribute());

		//UKismetSystemLibrary::PrintString(this, TEXT("MaxAmmo: ") + FString::SanitizeFloat(MaxAmmo), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("MaxClipAmmo: ") + FString::SanitizeFloat(MaxClipAmmo), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("BackupAmmo: ") + FString::SanitizeFloat(BackupAmmo), true, false);



		const float MaxHealth = GetAbilitySystemComponent()->GetNumericAttribute(UASSEAttributeSet_Health::GetMaxHealthAttribute());
		const float Health = GetAbilitySystemComponent()->GetNumericAttribute(UASSEAttributeSet_Health::GetHealthAttribute());

		//UKismetSystemLibrary::PrintString(this, TEXT("MaxHealth: ") + FString::SanitizeFloat(MaxHealth), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("Health: ") + FString::SanitizeFloat(Health), true, false);
	}

	//}

	//	Item history debug
	//UKismetSystemLibrary::PrintString(this, "------------", true, false);
	//if (ShooterInventoryComponent)
	//{
	//	for (FArcInventoryItemSlotReference slotRef : ShooterInventoryComponent->ActiveItemHistory)
	//	{
	//		UKismetSystemLibrary::PrintString(this, UArcItemBPFunctionLibrary::GetItemFromSlot(slotRef)->GetItemDefinition().GetDefaultObject()->GetFName().ToString(), true, false);

	//	}
	//}
	//UKismetSystemLibrary::PrintString(this, "-----------", true, false);


	

	//float frameHorizontalMouseRate = 0;
	//float frameVerticalMouseRate = 0;
	//Cast<APlayerController>(GetController())->GetInputMouseDelta(frameHorizontalMouseRate, frameVerticalMouseRate);
	//

	//// Weapon sway
	//if (POVMesh/* && AbilitySystem && !AbilitySystem->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("WeaponState.ADS")))*/)
	//{
	//	FVector CameraSocketLocation = POVMesh->GetSocketTransform(TEXT("CameraBoneSocket"), ERelativeTransformSpace::RTS_ParentBoneSpace).GetLocation();
	//	FVector FrameMouseRate = FVector(0, -frameHorizontalMouseRate, -frameVerticalMouseRate);
	//	FVector NewCameraLocation = CameraSocketLocation - (FrameMouseRate * CameraSwayAmount);
	//	if (GetCameraBoom())
	//	{
	//		FVector CurrentCameraLocation = FVector(GetCameraBoom()->GetRelativeTransform().GetLocation());

	//		GetCameraBoom()->SetRelativeLocation(UKismetMathLibrary::VInterpTo(CurrentCameraLocation, NewCameraLocation, DeltaSeconds, 10));
	//	}

	//	
	//}
	//else
	//{
	//	FVector CameraSocketLocation = POVMesh->GetSocketTransform(TEXT("CameraBoneSocket"), ERelativeTransformSpace::RTS_ParentBoneSpace).GetLocation();
	//	FVector NewCameraLocation = FVector(0, 0, 0);
	//	if (GetCameraBoom())
	//	{
	//		FVector CurrentCameraLocation = FVector(GetCameraBoom()->GetRelativeTransform().GetLocation());

	//		float yaw = CurrentCameraLocation.Y - frameHorizontalMouseRate;
	//		float pitch = CurrentCameraLocation.Z - frameVerticalMouseRate;
	//		FVector Sway = FVector(CurrentCameraLocation.X, yaw, pitch);

	//		FVector ADSCameraSwayAmount = CameraSwayAmount + AddedCameraSwayDuringADS;

	//		NewCameraLocation = CameraSocketLocation - (Sway * ADSCameraSwayAmount);




	//		GetCameraBoom()->SetRelativeLocation(UKismetMathLibrary::VInterpTo(CurrentCameraLocation, NewCameraLocation, DeltaSeconds, 10));
	//	}




	//}
}


void ASSCharacter_Shooter::OnPressedInteract()
{
	Interactor->TryInteract();
}

void ASSCharacter_Shooter::OnPressedPrimaryFire()
{
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Fire.GetTag().GetSingleTagContainer());
	}
}

void ASSCharacter_Shooter::OnPressedReload()
{
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Reload.GetTag().GetSingleTagContainer());
	}
}

void ASSCharacter_Shooter::OnPressedSwapToPreviousSlot()
{
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Inventory_SwapItem_ItemHistory_Previous.GetTag().GetSingleTagContainer());
}
void ASSCharacter_Shooter::OnPressedSwapToLayout1st()
{
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Inventory_SwapItem_LayoutIndex_1st.GetTag().GetSingleTagContainer());
}
void ASSCharacter_Shooter::OnPressedSwapToLayout2nd()
{
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Inventory_SwapItem_LayoutIndex_2nd.GetTag().GetSingleTagContainer());
}
void ASSCharacter_Shooter::OnPressedSwapToLayout3rd()
{
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Inventory_SwapItem_LayoutIndex_3rd.GetTag().GetSingleTagContainer());
}
void ASSCharacter_Shooter::OnPressedSwapToLayout4th()
{
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Inventory_SwapItem_LayoutIndex_4th.GetTag().GetSingleTagContainer());
}
void ASSCharacter_Shooter::OnPressedSwapToLayout5th()
{
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Inventory_SwapItem_LayoutIndex_5th.GetTag().GetSingleTagContainer());
}
void ASSCharacter_Shooter::OnPressedSwapToLayoutForward()
{
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Inventory_SwapItem_LayoutIndex_Forward.GetTag().GetSingleTagContainer());
}
void ASSCharacter_Shooter::OnPressedSwapToLayoutBackward()
{
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Inventory_SwapItem_LayoutIndex_Backward.GetTag().GetSingleTagContainer());
}

void ASSCharacter_Shooter::OnPressedPause()
{
	Super::OnPressedPause();
}

void ASSCharacter_Shooter::OnPressedScoreSheet()
{
	Super::OnPressedScoreSheet();
}

void ASSCharacter_Shooter::OnPressedDropItem()
{
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(FArcInvDropItemAbilityTag.GetTag().GetSingleTagContainer(), true);
}
