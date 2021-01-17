// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShooterCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "ActorComponents/InteractorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/SSArcInventoryComponent_Active.h"



void AShooterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AShooterCharacter, InteractInstantAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, InteractDurationAbilitySpecHandle, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToLastActiveItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToNextItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToPreviousItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToItem0AbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToItem1AbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToItem2AbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToItem3AbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToItem4AbilitySpecHandle, COND_OwnerOnly);
}

FName AShooterCharacter::InventoryComponentName(TEXT("InventoryComponent"));

AShooterCharacter::AShooterCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USSArcInventoryComponent_Active>(InventoryComponentName))
{
	InventoryComponent = CreateDefaultSubobject<UArcInventoryComponent>(InventoryComponentName);
	SSInventoryComponentActive = Cast<USSArcInventoryComponent_Active>(InventoryComponent);






	Interactor = CreateDefaultSubobject<UInteractorComponent>(TEXT("Interactor"));

	CameraSwayAmount = FVector(0, 1.3f, .4f);
	AddedCameraSwayDuringADS = FVector(0, -1.1f, -.1f);
}

bool AShooterCharacter::GrantStartingAbilities()
{
	if (Super::GrantStartingAbilities() == false)
	{
		return false;	// Did not pass predefined checks
	}
	//	We are on authority and have a valid ASC to work with

	InteractInstantAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(InteractInstantAbilityTSub, this, EAbilityInputID::Interact/*, GetLevel()*/);
	InteractDurationAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(InteractDurationAbilityTSub, this, EAbilityInputID::Interact/*, GetLevel()*/);

	SwapToLastActiveItemAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToLastActiveItemAbilityTSub, this, EAbilityInputID::SwitchWeapon/*, GetLevel()*/);
	SwapToNextItemAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToNextItemAbilityTSub, this, EAbilityInputID::NextItem/*, GetLevel()*/);
	SwapToPreviousItemAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToPreviousItemAbilityTSub, this, EAbilityInputID::PreviousItem/*, GetLevel()*/);
	SwapToItem0AbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToItem0AbilityTSub, this, EAbilityInputID::Item0/*, GetLevel()*/);
	SwapToItem1AbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToItem1AbilityTSub, this, EAbilityInputID::Item1/*, GetLevel()*/);
	SwapToItem2AbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToItem2AbilityTSub, this, EAbilityInputID::Item2/*, GetLevel()*/);
	SwapToItem3AbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToItem3AbilityTSub, this, EAbilityInputID::Item3/*, GetLevel()*/);
	SwapToItem4AbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToItem4AbilityTSub, this, EAbilityInputID::Item4/*, GetLevel()*/);

	return true;
}

//#include "Kismet/KismetSystemLibrary.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "GameFramework/SpringArmComponent.h"
void AShooterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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


void AShooterCharacter::OnInteractPressed()
{
	Interactor->TryInteract();
}

void AShooterCharacter::OnPrimaryFirePressed()
{
	//if (GetAbilitySystemComponent())
	//{
	//	GetAbilitySystemComponent()->TryActivateAbility(CurrentWeapon->FireAbilitySpecHandle);		for when we add inventory system
	//}
}

void AShooterCharacter::OnSwitchWeaponPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToLastActiveItemAbilitySpecHandle);
}
void AShooterCharacter::OnItem0Pressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToItem0AbilitySpecHandle);
}
void AShooterCharacter::OnItem1Pressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToItem1AbilitySpecHandle);
}
void AShooterCharacter::OnItem2Pressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToItem2AbilitySpecHandle);
}
void AShooterCharacter::OnItem3Pressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToItem3AbilitySpecHandle);
}
void AShooterCharacter::OnItem4Pressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToItem4AbilitySpecHandle);
}
void AShooterCharacter::OnNextItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToNextItemAbilitySpecHandle);
}
void AShooterCharacter::OnPreviousItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToPreviousItemAbilitySpecHandle);
}

void AShooterCharacter::OnPausePressed()
{
}

void AShooterCharacter::OnScoreSheetPressed()
{
}


