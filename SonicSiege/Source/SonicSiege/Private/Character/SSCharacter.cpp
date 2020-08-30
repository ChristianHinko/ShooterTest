// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/SSCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/SSCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet\KismetMathLibrary.h"
#include "Kismet\KismetSystemLibrary.h"
#include "Utilities/CollisionChannels.h"
#include "Interfaces/Interactable.h"
#include "GameFramework/PlayerController.h"


void ASSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASSCharacter, Inventory, COND_OwnerOnly);
}

ASSCharacter::ASSCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<USSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	SSCharacterMovementComponent = Cast<USSCharacterMovementComponent>(GetMovementComponent());


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set our turn rates for input
	HorizontalSensitivity = 45.f;
	VerticalSensitivity = 45.f;

	// Configure character movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 600.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


	// Mesh defaults
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->bCastHiddenShadow = true;	// we still want the shadow from the normal mesh
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -96.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	// Create POVMesh
	POVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("POVMesh"));
	POVMesh->SetupAttachment(GetCapsuleComponent());
	POVMesh->SetOnlyOwnerSee(true);
	POVMesh->SetCastShadow(false);	// hide the POV mesh shadow because it will probably look weird (we're using the normal mesh's shadow instead)
	POVMesh->SetRelativeLocation(FVector(0.f, 0.f, -96.f));
	POVMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	POVMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	// Create CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->TargetArmLength = 0.f;
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InteractSweepDistance = 100.f;
	InteractSweepRadius = 2.f;
	CurrentInteract = nullptr;
	LastInteract = nullptr;
}

void ASSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//float frameHorizontalMouseRate = 0;
	//float frameVerticalMouseRate = 0;
	//Cast<APlayerController>(GetController())-> GetInputMouseDelta(frameHorizontalMouseRate, frameVerticalMouseRate);
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

	//		GetCameraBoom()->SetRelativeLocation(UKismetMathLibrary::VInterpTo(CurrentCameraLocation, NewCameraLocation, DeltaTime, 10));
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




	//		GetCameraBoom()->SetRelativeLocation(UKismetMathLibrary::VInterpTo(CurrentCameraLocation, NewCameraLocation, DeltaTime, 10));
	//	}



	//}

	if (HasAuthority() || IsLocallyControlled())	// Don't run for simulated proxies
	{
		ScanForInteractables(CurrentInteract, InteractSweepHitResult);
		if (CurrentInteract)
		{
			if (CurrentInteract->bShouldFireSweepEvents)
			{
				if (CurrentInteract != LastInteract)
				{
					CurrentInteract->OnInteractSweepInitialHit(this);
				}
				else
				{
					CurrentInteract->OnInteractSweepConsecutiveHit(this);
				}

				LastInteract = CurrentInteract;
				//CurrentInteract = nullptr;
			}
		}
		else
		{
			if (LastInteract != nullptr)	// If the last frame had something to interact with
			{
				LastInteract->OnInteractSweepEndHitting(this);
				LastInteract = nullptr;
			}
		}
	}
	
	
}

void ASSCharacter::ScanForInteractables(IInteractable*& OutInteractable, FHitResult& OutHit)
{
	if (GetWorld() && GetFollowCamera())
	{
		FVector StartLocation = GetFollowCamera()->GetComponentLocation();
		FVector EndLocation = StartLocation + (GetFollowCamera()->GetForwardVector() * InteractSweepDistance);

		const bool bBlockingHit = GetWorld()->SweepSingleByChannel(OutHit, StartLocation, EndLocation, FQuat::Identity, COLLISION_INTERACT, FCollisionShape::MakeSphere(InteractSweepRadius), FCollisionQueryParams());
		if (bBlockingHit)
		{
			OutInteractable = Cast<IInteractable>(InteractSweepHitResult.GetActor());
			return;
		}
	}
	OutInteractable = nullptr;
}


#pragma region Input
void ASSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//Action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASSCharacter::OnJumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASSCharacter::OnJumpReleased);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASSCharacter::OnInteractPressed);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ASSCharacter::OnInteractReleased);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASSCharacter::OnRunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASSCharacter::OnRunReleased);

	PlayerInputComponent->BindAction("PrimaryFire", IE_Pressed, this, &ASSCharacter::OnPrimaryFirePressed);
	PlayerInputComponent->BindAction("PrimaryFire", IE_Released, this, &ASSCharacter::OnPrimaryFireReleased);

	PlayerInputComponent->BindAction("SecondaryFire", IE_Pressed, this, &ASSCharacter::OnSecondaryFirePressed);
	PlayerInputComponent->BindAction("SecondaryFire", IE_Released, this, &ASSCharacter::OnSecondaryFireReleased);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ASSCharacter::OnReloadPressed);
	PlayerInputComponent->BindAction("Reload", IE_Released, this, &ASSCharacter::OnReloadReleased);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASSCharacter::OnCrouchPressed);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASSCharacter::OnCrouchReleased);

	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ASSCharacter::OnSwitchWeaponPressed);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Released, this, &ASSCharacter::OnSwitchWeaponReleased);

	//Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &ASSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnRightRate", this, &ASSCharacter::HorizontalLook);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASSCharacter::VerticalLook);
}

//Actions
void ASSCharacter::OnJumpPressed()
{
	Jump();
}
void ASSCharacter::OnJumpReleased()
{
	StopJumping();
}

void ASSCharacter::OnInteractPressed()
{
	if (InteractSweepHitResult.bBlockingHit)
	{
		
	}
}
void ASSCharacter::OnInteractReleased()
{

}

void ASSCharacter::OnPrimaryFirePressed()
{

}
void ASSCharacter::OnPrimaryFireReleased()
{

}

void ASSCharacter::OnSecondaryFirePressed()
{

}
void ASSCharacter::OnSecondaryFireReleased()
{

}

void ASSCharacter::OnReloadPressed()
{

}
void ASSCharacter::OnReloadReleased()
{

}

void ASSCharacter::OnCrouchPressed()
{

}
void ASSCharacter::OnCrouchReleased()
{

}

void ASSCharacter::OnSwitchWeaponPressed()
{

}
void ASSCharacter::OnSwitchWeaponReleased()
{

}

void ASSCharacter::OnRunPressed()
{
	SSCharacterMovementComponent->SetWantsToRun(true);
}
void ASSCharacter::OnRunReleased()
{
	SSCharacterMovementComponent->SetWantsToRun(false);
}


//Axis
void ASSCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void ASSCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASSCharacter::HorizontalLook(float Rate)
{
	if (Rate != 0)
	{
		AddControllerYawInput(Rate * HorizontalSensitivity * GetWorld()->GetDeltaSeconds());
	}
}
void ASSCharacter::VerticalLook(float Rate)
{
	if (Rate != 0)
	{
		AddControllerPitchInput(Rate * VerticalSensitivity * GetWorld()->GetDeltaSeconds());
	}
}
#pragma endregion
