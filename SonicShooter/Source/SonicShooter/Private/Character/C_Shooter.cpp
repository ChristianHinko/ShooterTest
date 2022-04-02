// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_Shooter.h"

#include "Net/UnrealNetwork.h"
#include "Utilities/LogCategories.h"
#include "Utilities/SSNativeGameplayTags.h"
#include "Character/CMC_Shooter.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "Subobjects/ActorComponents/AC_Interactor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/ArcInventoryComponent_Shooter.h"
#include "ArcItemStack.h"
#include "AttributeSets/AS_Health.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
#include "AbilitySystemSetupComponent/AbilitySystemSetupComponent.h"



void AC_Shooter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME_CONDITION(AC_Shooter, InteractInstantAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AC_Shooter, InteractDurationAbilitySpecHandle, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(AC_Shooter, SwapToLastActiveItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AC_Shooter, SwapToNextItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AC_Shooter, SwapToPreviousItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AC_Shooter, SwapToFirstItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AC_Shooter, SwapToSecondItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AC_Shooter, SwapToThirdItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AC_Shooter, SwapToFourthItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AC_Shooter, SwapToFifthItemAbilitySpecHandle, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(AC_Shooter, DropItemAbilitySpecHandle, COND_OwnerOnly);
}

const FName AC_Shooter::InventoryComponentName = TEXT("InventoryComponent");

AC_Shooter::AC_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer
		.SetDefaultSubobjectClass<UCMC_Shooter>(CharacterMovementComponentName)
		.SetDefaultSubobjectClass<UArcInventoryComponent_Shooter>(InventoryComponentName)
	)
{
	// Create Inventory
	InventoryComponent = CreateDefaultSubobject<UArcInventoryComponent>(InventoryComponentName);
	ShooterInventoryComponent = Cast<UArcInventoryComponent_Shooter>(InventoryComponent);

	// Create Interactor
	Interactor = CreateDefaultSubobject<UAC_Interactor>(TEXT("Interactor"));

	// Attribute Sets
	GetAbilitySystemSetupComponent()->StartingAttributeSets.Add(UAS_Stamina::StaticClass());
	GetAbilitySystemSetupComponent()->StartingAttributeSets.Add(UAS_Health::StaticClass());


	// Default to first person
	bFirstPerson = true;
	bUseControllerRotationYaw = true; // let the camera rotation determine our yaw
	GetCharacterMovement()->bOrientRotationToMovement = false; // don't rotate the Character in the movement direction

	// Configure camera sway
	CameraSwayAmount = FVector(0.f, 1.3f, 0.4f);
	AddedCameraSwayDuringADS = FVector(0.f, -1.1f, -0.1f);
}

void AC_Shooter::BeginPlay()
{
	Super::BeginPlay();

}

void AC_Shooter::GiveStartingAbilities()
{
	Super::GiveStartingAbilities();


	InteractInstantAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(InteractInstantAbilityTSub, /*GetLevel()*/1, -1, this));
	InteractDurationAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(InteractDurationAbilityTSub, /*GetLevel()*/1, -1, this));

	SwapToLastActiveItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToLastActiveItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToNextItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToNextItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToPreviousItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToPreviousItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToFirstItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToFirstItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToSecondItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToSecondItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToThirdItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToThirdItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToFourthItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToFourthItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToFifthItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToFifthItemAbilityTSub, /*GetLevel()*/1, -1, this));

	DropItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(DropItemAbilityTSub, /*GetLevel()*/1, -1, this));
}

#include "Kismet/KismetSystemLibrary.h"
#include "AttributeSets/AS_Health.h"
#include "Inventory/Item/AS_Ammo.h"
#include "Inventory/Item/Gun/AS_Gun.h"
#include "Subobjects/O_ClipAmmo.h"
#include "Subobjects/O_BulletSpread.h"
#include "Subobjects/O_Stamina.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Item\ArcItemDefinition_New.h"
#include "Inventory/Item/Gun/ArcItemStack_Gun.h"
#include "Character/SSCharacterMovementComponent.h"
#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"
#include "AbilitySystem/ASSAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "GameFramework/SpringArmComponent.h"
void AC_Shooter::Tick(float DeltaSeconds)
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
			const UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(ActiveItemStack);
			if (IsValid(GunStack))
			{
				const FFloatPropertyWrapper& ClipAmmo = GunStack->GetClipAmmoSubobject()->ClipAmmo;
				//UKismetSystemLibrary::PrintString(this, ClipAmmo.GetDebugString(), true, false);

				const FFloatPropertyWrapper& CurrentBulletSpread = GunStack->GetBulletSpreadSubobject()->CurrentBulletSpread;
				//UKismetSystemLibrary::PrintString(this, CurrentBulletSpread.GetDebugString(), true, false);
			}
		}


	}

	if (GetSSCharacterMovementComponent())
	{
		//if (IsValid(GetSSCharacterMovementComponent()->StaminaSubobject))
		//{
		//	const FFloatPropertyWrapper& Stamina = GetSSCharacterMovementComponent()->StaminaSubobject->Stamina;
			//UKismetSystemLibrary::PrintString(this, Stamina.GetDebugString(), true, false);

		//}
	}
	if (IsValid(GetAbilitySystemComponent()))
	{
		const float MaxStamina = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Stamina::GetMaxStaminaAttribute());
		const float StaminaDrain = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Stamina::GetStaminaDrainAttribute());
		const float StaminaGain = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Stamina::GetStaminaGainAttribute());
		const float StaminaRegenPause = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Stamina::GetStaminaRegenPauseAttribute());

		//UKismetSystemLibrary::PrintString(this, TEXT("MaxStamina: ") + FString::SanitizeFloat(MaxStamina), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaDrain: ") + FString::SanitizeFloat(StaminaDrain), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaGain: ") + FString::SanitizeFloat(StaminaGain), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaRegenPause: ") + FString::SanitizeFloat(StaminaRegenPause), true, false);




		const float MaxAmmo = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Ammo::GetMaxAmmoAttribute());
		const float MaxClipAmmo = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Ammo::GetMaxClipAmmoAttribute());
		const float BackupAmmo = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Ammo::GetBackupAmmoAttribute());

		//UKismetSystemLibrary::PrintString(this, TEXT("MaxAmmo: ") + FString::SanitizeFloat(MaxAmmo), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("MaxClipAmmo: ") + FString::SanitizeFloat(MaxClipAmmo), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("BackupAmmo: ") + FString::SanitizeFloat(BackupAmmo), true, false);
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


void AC_Shooter::OnInteractPressed()
{
	Interactor->TryInteract();
}

void AC_Shooter::OnPrimaryFirePressed()
{
	if (GetAbilitySystemComponent())
	{
		TArray<FGameplayAbilitySpec*> Specs; // our found specs
		GetAbilitySystemComponent()->GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag_AbilityInputPrimaryFire.GetTag().GetSingleTagContainer(), Specs);

		for (FGameplayAbilitySpec* Spec : Specs)
		{
			// Our spec handle to activate
			FGameplayAbilitySpecHandle Handle = Spec->Handle;

			GetAbilitySystemComponent()->TryActivateAbility(Handle);
		}
	}
}

void AC_Shooter::OnReloadPressed()
{
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->TryActivateAbilitiesByTag(Tag_ReloadAbility.GetTag().GetSingleTagContainer());
	}
}

void AC_Shooter::OnSwitchWeaponPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToLastActiveItemAbilitySpecHandle);
}
void AC_Shooter::OnFirstItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToFirstItemAbilitySpecHandle);
}
void AC_Shooter::OnSecondItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToSecondItemAbilitySpecHandle);
}
void AC_Shooter::OnThirdItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToThirdItemAbilitySpecHandle);
}
void AC_Shooter::OnFourthItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToFourthItemAbilitySpecHandle);
}
void AC_Shooter::OnFifthItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToFifthItemAbilitySpecHandle);
}
void AC_Shooter::OnNextItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToNextItemAbilitySpecHandle);
}
void AC_Shooter::OnPreviousItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToPreviousItemAbilitySpecHandle);
}

void AC_Shooter::OnPausePressed()
{
	Super::OnPausePressed();
}

void AC_Shooter::OnScoreSheetPressed()
{
	Super::OnScoreSheetPressed();
}

void AC_Shooter::OnDropItemPressed()
{
	FArcInventoryItemSlotReference ActiveItem = ShooterInventoryComponent->GetActiveItemSlot();
	if (ShooterInventoryComponent->IsValidActiveItemSlot(ActiveItem.SlotId))
	{
		ShooterInventoryComponent->PendingItemDrop = ShooterInventoryComponent->GetActiveItemSlot();
		GetAbilitySystemComponent()->TryActivateAbility(DropItemAbilitySpecHandle, true);
	}
}
