// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STCharacter_Shooter.h"

#include "Net/UnrealNetwork.h"
#include "Character/STCharacterMovementComponent_Shooter.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "Subobjects/ActorComponents/STActorComponent_Interactor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/STInventoryComponent_Shooter.h"
#include "ArcItemStack.h"
#include "AttributeSets/ASSEAttributeSet_Health.h"
#include "AbilitySystem/AttributeSets/STAttributeSet_Stamina.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputTriggers.h"
#include "ISEngineSubsystem_InputActions.h"

#include "AbilitySystem/TargetActors/STGameplayAbilityTargetActor_BulletTrace.h"

#include "D:\Program Files\UE_5.0\Engine\Source\Runtime\Engine\Classes\GameFramework\SpringArmComponent.h"


const FName ASTCharacter_Shooter::InventoryComponentName = TEXT("InventoryComponent");

ASTCharacter_Shooter::ASTCharacter_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer
		.SetDefaultSubobjectClass<USTCharacterMovementComponent_Shooter>(CharacterMovementComponentName)
		.SetDefaultSubobjectClass<USTInventoryComponent_Shooter>(InventoryComponentName)
	)
{
	// Create Inventory
	InventoryComponent = CreateDefaultSubobject<UArcInventoryComponent>(InventoryComponentName);
	ShooterInventoryComponent = Cast<USTInventoryComponent_Shooter>(InventoryComponent);

	// Create Interactor
	Interactor = CreateDefaultSubobject<USTActorComponent_Interactor>(TEXT("Interactor"));

	// Default to first person
	bFirstPerson = true;
	bUseControllerRotationYaw = true; // let the camera rotation determine our yaw
	GetCharacterMovement()->bOrientRotationToMovement = false; // don't rotate the Character in the movement direction

	// Configure camera sway
	CameraSwayAmount = FVector(0.f, 1.3f, 0.4f);
	AddedCameraSwayDuringADS = FVector(0.f, -1.1f, -0.1f);

	POVMesh->SetVisibility(false, false); // in the demo it looks bad to show the character since it blocks the screen a lot
	CurrentTime = 0.f;
	CammeraMoveAlongSpeed = 2;
	TargetArmLengthDuringAnimation = 100;
	CameraMoveAlongRotSpeed = 1;
}

void ASTCharacter_Shooter::BeginPlay()
{
	Super::BeginPlay();
	CameraBoomStartingLoc = GetCameraBoom()->GetRelativeLocation();
	AddControllerPitchInput(-1);
}


#include "Kismet/KismetSystemLibrary.h"
#include "AttributeSets/ASSEAttributeSet_Health.h"
#include "Inventory/Item/STAttributeSet_Ammo.h"
#include "Inventory/Item/Gun/STAttributeSet_Gun.h"
#include "Subobjects/STObject_ClipAmmo.h"
#include "Subobjects/STObject_BulletSpread.h"
#include "Subobjects/STObject_Stamina.h"
#include "AbilitySystem/AttributeSets/STAttributeSet_Stamina.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Item\ArcItemDefinition_New.h"
#include "Inventory/Item/Gun/STItemStack_Gun.h"
#include "Character/STCharacterMovementComponent.h"
#include "AbilitySystem/AbilitySystemComponents/STAbilitySystemComponent_Shooter.h"
#include "AbilitySystem/ASSAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/STAttributeSet_Stamina.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "GameFramework/SpringArmComponent.h"
#include "BlueprintFunctionLibraries\GCBlueprintFunctionLibrary_MathHelpers.h"
#include "Camera\PlayerCameraManager.h"
#include "Kismet\GameplayStatics.h"
#include "Camera\CameraActor.h"
#include "GameFramework/HUD.h"
#include "UI\STHUD_Shooter.h"
#include "Blueprint/UserWidget.h"

#include "BlueprintFunctionLibraries\CollisionQuery\GCBlueprintFunctionLibrary_StrengthCollisionQueries.h"

void ASTCharacter_Shooter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (BulletTraceLocations.Num() > 0)
	{
		if (CurrentTime == 0)
		{
			AddControllerYawInput(-12);
			POVMesh->SetVisibility(true, true);
			Cast<ASTHUD_Shooter>((Cast<APlayerController>(GetController())->GetHUD()))->HealthWidget->SetVisibility(ESlateVisibility::Hidden);
			Cast<ASTHUD_Shooter>((Cast<APlayerController>(GetController())->GetHUD()))->CurrentActiveItemWidget->SetVisibility(ESlateVisibility::Hidden);
			GetCameraBoom()->TargetArmLength = TargetArmLengthDuringAnimation;

			currentTraceStartIndex = 0;
			currentTraceEndIndex = 1;
			CurrentCameraLoc = BulletTraceLocations[currentTraceStartIndex];
			GetCameraBoom()->SetWorldLocation(CurrentCameraLoc);

			CurrentTime = CurrentTime + DeltaSeconds;
			return;
		}
		const float ErrorTollerance = 1;

		FVector CurrentTraceStart = BulletTraceLocations[currentTraceStartIndex];
		FVector CurrentTraceEnd = BulletTraceLocations[currentTraceEndIndex];
		if (UGCBlueprintFunctionLibrary_MathHelpers::PointLiesOnSegment(CurrentTraceStart, CurrentTraceEnd, CurrentCameraLoc, ErrorTollerance))
		{

			const FVector TraceDir = (CurrentTraceEnd - CurrentTraceStart).GetSafeNormal();

			CurrentCameraLoc = CurrentCameraLoc + (TraceDir * CammeraMoveAlongSpeed * DeltaSeconds);
			GetCameraBoom()->SetWorldLocation(CurrentCameraLoc);


			AddControllerYawInput(-CameraMoveAlongRotSpeed * DeltaSeconds);
		}
		else
		{
			++currentTraceStartIndex;
			++currentTraceEndIndex;

			if (BulletTraceLocations.IsValidIndex(currentTraceEndIndex) == false)
			{
				// We are past the last segment so reset stuff we changed

				Cast<ASTHUD_Shooter>((Cast<APlayerController>(GetController())->GetHUD()))->HealthWidget->SetVisibility(ESlateVisibility::Visible);
				Cast<ASTHUD_Shooter>((Cast<APlayerController>(GetController())->GetHUD()))->CurrentActiveItemWidget->SetVisibility(ESlateVisibility::Visible);
				GetCameraBoom()->SetRelativeLocation(CameraBoomStartingLoc);
				GetCameraBoom()->TargetArmLength = 0;
				BulletTraceLocations.Empty(); // stops playing the animation
				CurrentTime = 0;
				POVMesh->SetVisibility(false, false);
			}
			else
			{
				CurrentTraceStart = BulletTraceLocations[currentTraceStartIndex];
				CurrentTraceEnd = BulletTraceLocations[currentTraceStartIndex];
				CurrentCameraLoc = CurrentTraceStart;

				GetCameraBoom()->SetWorldLocation(CurrentCameraLoc);
			}
		}




		CurrentTime = CurrentTime + DeltaSeconds;
	}












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
			const USTItemStack_Gun* GunStack = Cast<USTItemStack_Gun>(ActiveItemStack);
			if (IsValid(GunStack))
			{
				const FGCFloatPropertyWrapper& ClipAmmo = GunStack->GetClipAmmoSubobject()->ClipAmmo;
				//UKismetSystemLibrary::PrintString(this, ClipAmmo.GetDebugString(), true, false);

				const FGCFloatPropertyWrapper& CurrentBulletSpread = GunStack->GetBulletSpreadSubobject()->CurrentBulletSpread;
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

void ASTCharacter_Shooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(PlayerEnhancedInputComponent))
	{
		const UISEngineSubsystem_InputActions* InputActionsSubsystem = GEngine->GetEngineSubsystem<UISEngineSubsystem_InputActions>();
		if (IsValid(InputActionsSubsystem))
		{
			const UInputAction* InputActionInteract = InputActionsSubsystem->GetInputAction(STNativeGameplayTags::InputAction_Interact);
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
