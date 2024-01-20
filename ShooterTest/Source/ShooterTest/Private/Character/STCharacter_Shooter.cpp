// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STCharacter_Shooter.h"

#include "Net/UnrealNetwork.h"
#include "Character/STCharacterMovementComponent_Shooter.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "Subobjects/ActorComponents/STActorComponent_Interactor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/STInventoryProcessor_Shooter.h"
#include "Modular/ArcInventoryComponent_Modular.h"
#include "ArcItemStack.h"
#include "AttributeSets/ASSEAttributeSet_Health.h"
#include "AbilitySystem/AttributeSets/STAttributeSet_Stamina.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputTriggers.h"
#include "Subsystems/ISEngineSubsystem_ObjectReferenceLibrary.h"




const FName ASTCharacter_Shooter::InventoryComponentName = TEXT("InventoryComponent");

ASTCharacter_Shooter::ASTCharacter_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USTCharacterMovementComponent_Shooter>(CharacterMovementComponentName))
{
	// Create Inventory
	InventoryComponent = CreateDefaultSubobject<UArcInventoryComponent_Modular>(InventoryComponentName);

	// Create Interactor
	Interactor = CreateDefaultSubobject<USTActorComponent_Interactor>(TEXT("Interactor"));

	// Default to first person
	bFirstPerson = true;
	bUseControllerRotationYaw = true; // let the camera rotation determine our yaw
	GetCharacterMovement()->bOrientRotationToMovement = false; // don't rotate the Character in the movement direction

	// Configure camera sway
	CameraSwayAmount = FVector(0.f, 1.3f, 0.4f);
	AddedCameraSwayDuringADS = FVector(0.f, -1.1f, -0.1f);
}

void ASTCharacter_Shooter::BeginPlay()
{
	Super::BeginPlay();

	ShooterInventoryProcessor = InventoryComponent->FindFirstProcessor<USTInventoryProcessor_Shooter>();
}


#include "Kismet/KismetSystemLibrary.h"
#include "AttributeSets/ASSEAttributeSet_Health.h"
#include "Inventory/Item/STAttributeSet_Ammo.h"
#include "Inventory/Item/Gun/STAttributeSet_Gun.h"
#include "Subobjects/STObject_Stamina.h"
#include "AbilitySystem/AttributeSets/STAttributeSet_Stamina.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Character/STCharacterMovementComponent.h"
#include "AbilitySystem/AbilitySystemComponents/STAbilitySystemComponent_Shooter.h"
#include "AbilitySystem/ASSAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/STAttributeSet_Stamina.h"
#include "Modular/ArcItemStackModular.h"
#include "Inventory/Item/Fragments/STItemFragment_BulletSpread.h"
#include "Inventory/Item/Fragments/STItemFragment_ClipAmmo.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "GameFramework/SpringArmComponent.h"
void ASTCharacter_Shooter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	//for (int32 i = 0; i < ShooterInventoryProcessor->ActiveItemHistory.Num(); ++i)
	//{
	//	FArcInventoryItemSlotReference current = ShooterInventoryProcessor->ActiveItemHistory[i];

	//	UKismetSystemLibrary::PrintString(this, "["+FString::FromInt(current.SlotId)+"] " + current.SlotTags.GetByIndex(1).ToString(), true, false, FLinearColor::Green);
	//}

	if (ShooterInventoryProcessor.IsValid())
	{
		//UKismetSystemLibrary::PrintString(this, "Current Item Slot: " + FString::FromInt(ShooterInventoryProcessor->GetActiveItemSlot().SlotId), true, false);
		//UKismetSystemLibrary::PrintString(this, "Pending Item Slot: " + FString::FromInt(ShooterInventoryProcessor->PendingItemSlot), true, false);
	}

	if (ShooterInventoryProcessor.IsValid())
	{
		UArcItemStackModular* ActiveItemStack = ShooterInventoryProcessor->GetActiveItemStack();
		if (IsValid(ActiveItemStack))
		{
			USTItemFragment_ClipAmmoInstanced* ClipAmmoItemFragment = ActiveItemStack->FindFirstFragment<USTItemFragment_ClipAmmoInstanced>();
			if (IsValid(ClipAmmoItemFragment))
			{
				const FGCInt32PropertyWrapper& ClipAmmo = ClipAmmoItemFragment->ClipAmmo;
				//UKismetSystemLibrary::PrintString(this, ClipAmmo.GetDebugString(), true, false);

				USTItemFragment_BulletSpreadInstanced* BulletSpreadItemFragment = ActiveItemStack->FindFirstFragment<USTItemFragment_BulletSpreadInstanced>();
				const FGCFloatPropertyWrapper& CurrentBulletSpread = BulletSpreadItemFragment->CurrentBulletSpread;
				//UKismetSystemLibrary::PrintString(this, CurrentBulletSpread.GetDebugString(), true, false);
			}
		}


	}

	if (GetSTCharacterMovementComponent())
	{
		//if (IsValid(GetSTCharacterMovementComponent()->StaminaSubobject))
		//{
		//	const FGCFloatPropertyWrapper& Stamina = GetSTCharacterMovementComponent()->StaminaSubobject->Stamina;
			//UKismetSystemLibrary::PrintString(this, Stamina.GetDebugString(), true, false);

		//}
	}
	if (IsValid(GetAbilitySystemComponent()))
	{
		const float MaxStamina = GetAbilitySystemComponent()->GetNumericAttribute(USTAttributeSet_Stamina::GetMaxStaminaAttribute());
		const float StaminaDrain = GetAbilitySystemComponent()->GetNumericAttribute(USTAttributeSet_Stamina::GetStaminaDrainAttribute());
		const float StaminaGain = GetAbilitySystemComponent()->GetNumericAttribute(USTAttributeSet_Stamina::GetStaminaGainAttribute());
		const float StaminaRegenPause = GetAbilitySystemComponent()->GetNumericAttribute(USTAttributeSet_Stamina::GetStaminaRegenPauseAttribute());

		//UKismetSystemLibrary::PrintString(this, TEXT("MaxStamina: ") + FString::SanitizeFloat(MaxStamina), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaDrain: ") + FString::SanitizeFloat(StaminaDrain), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaGain: ") + FString::SanitizeFloat(StaminaGain), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaRegenPause: ") + FString::SanitizeFloat(StaminaRegenPause), true, false);




		const float MaxAmmo = GetAbilitySystemComponent()->GetNumericAttribute(USTAttributeSet_Ammo::GetMaxAmmoAttribute());
		const float MaxClipAmmo = GetAbilitySystemComponent()->GetNumericAttribute(USTAttributeSet_Ammo::GetMaxClipAmmoAttribute());
		const float BackupAmmo = GetAbilitySystemComponent()->GetNumericAttribute(USTAttributeSet_Ammo::GetBackupAmmoAttribute());

		//UKismetSystemLibrary::PrintString(this, TEXT("MaxAmmo: ") + FString::SanitizeFloat(MaxAmmo), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("MaxClipAmmo: ") + FString::SanitizeFloat(MaxClipAmmo), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("BackupAmmo: ") + FString::SanitizeFloat(BackupAmmo), true, false);



		const float MaxHealth = GetAbilitySystemComponent()->GetNumericAttribute(UASSEAttributeSet_Health::GetMaxHealthAttribute());
		const float Health = GetAbilitySystemComponent()->GetNumericAttribute(UASSEAttributeSet_Health::GetHealthAttribute());

		//UKismetSystemLibrary::PrintString(this, TEXT("MaxHealth: ") + FString::SanitizeFloat(MaxHealth), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("Health: ") + FString::SanitizeFloat(Health), true, false);
	}

	//}

	//	Item history debug OUTDATED (ArcInventory 1.0)
	//UKismetSystemLibrary::PrintString(this, "------------", true, false);
	//if (ShooterInventoryProcessor)
	//{
	//	for (FArcInventoryItemSlotReference slotRef : ShooterInventoryProcessor->ActiveItemHistory)
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

void ASTCharacter_Shooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(PlayerEnhancedInputComponent))
	{
		const UISEngineSubsystem_ObjectReferenceLibrary* InputSetupObjectReferenceLibrary = GEngine->GetEngineSubsystem<UISEngineSubsystem_ObjectReferenceLibrary>();
		if (IsValid(InputSetupObjectReferenceLibrary))
		{
			const UInputAction* InputActionInteract = InputSetupObjectReferenceLibrary->GetInputAction(STNativeGameplayTags::InputAction_Interact);
			if (IsValid(InputActionInteract))
			{
				PlayerEnhancedInputComponent->BindAction(InputActionInteract, ETriggerEvent::Started, this, &ThisClass::OnPressedInteract);
			}
		}
	}
}

void ASTCharacter_Shooter::OnPressedInteract()
{
	Interactor->TryInteract();
}
