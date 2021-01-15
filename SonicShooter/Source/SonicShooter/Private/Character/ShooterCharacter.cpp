// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShooterCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "ActorComponents/InteractorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArcInventoryComponent_Active.h"



void AShooterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AShooterCharacter, InteractInstantAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, InteractDurationAbilitySpecHandle, COND_OwnerOnly);
}

FName AShooterCharacter::InventoryComponentName(TEXT("InventoryComponent"));

AShooterCharacter::AShooterCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UArcInventoryComponent_Active>(InventoryComponentName))
{
	InventoryComponent = CreateDefaultSubobject<UArcInventoryComponent>(InventoryComponentName);

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

