// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/SSCharacter.h"

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



ASSCharacter::ASSCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
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
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -96.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	// Create POVMesh
	POVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("POVMesh"));
	POVMesh->SetupAttachment(GetCapsuleComponent());
	POVMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
	POVMesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	POVMesh->SetCollisionProfileName(TEXT("CharacterMesh"));
	POVMesh->SetGenerateOverlapEvents(false);
	POVMesh->SetCanEverAffectNavigation(false);
	POVMesh->SetRelativeLocation(FVector(0.f, 0.f, -96.f));
	POVMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	POVMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	POVMesh->AlwaysLoadOnServer = false; // the server shouldn't care about this mesh
	// Configure the POVMesh for first person (these apply regardless of third/first person because switching between the two will only set visibility and not change these settings)
	POVMesh->SetOwnerNoSee(false);
	POVMesh->SetOnlyOwnerSee(true);
	POVMesh->SetCastShadow(false);	// hide the POV mesh shadow because it will probably look weird (we're using the normal mesh's shadow instead)

	// Create CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Set default arm length for third person mode
	thirdPersonCameraArmLength = 300.f;

	// Default to first person
	bFirstPerson = true;
}
void ASSCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Set our configuration for this first/third person mode
	SetFirstPerson(bFirstPerson);
}

void ASSCharacter::SetFirstPerson(bool newFirstPerson)
{
	if (newFirstPerson == true)
	{
		bUseControllerRotationYaw = true; // let the camera rotation determine our yaw
		GetCharacterMovement()->bOrientRotationToMovement = false; // don't rotate the character in the movement direction

		// First person, so hide mesh but still see the shadow
		GetMesh()->SetOwnerNoSee(true);
		GetMesh()->bCastHiddenShadow = true; // We still want the shadow from the normal mesh (this casts shadow even when hidden)

		// First person, so show POV mesh
		POVMesh->SetVisibility(true/*, true*/);

		// Configure CameraBoom arm length for first person
		CameraBoom->TargetArmLength = 0.f;
	}
	else
	{
		bUseControllerRotationYaw = false; // don't rotate when the controller rotates. Let that just affect the camera.
		GetCharacterMovement()->bOrientRotationToMovement = true; // make the character face the direction that he is moving

		// Third person, so let player see mesh
		GetMesh()->SetOwnerNoSee(false);
		GetMesh()->bCastHiddenShadow = false; // now if this mesh is hidden, don't show its shadow

		// Third person, so hide POV mesh
		POVMesh->SetVisibility(false/*, true*/);

		// Configure CameraBoom arm length for third person
		GetCameraBoom()->TargetArmLength = thirdPersonCameraArmLength;
	}

	bFirstPerson = newFirstPerson;
}

void ASSCharacter::OnStartCrouch(float HeightAdjust, float ScaledHeightAdjust)
{
	//Super::OnStartCrouch(HeightAdjust, ScaledHeightAdjust);

	RecalculateBaseEyeHeight();


	// From Super
	const ACharacter* DefaultChar = GetDefault<ACharacter>(GetClass());
	if (GetMesh() && DefaultChar->GetMesh())
	{
		FVector& MeshRelativeLocation = GetMesh()->GetRelativeLocation_DirectMutable();
		MeshRelativeLocation.Z = DefaultChar->GetMesh()->GetRelativeLocation().Z + HeightAdjust;
		BaseTranslationOffset.Z = MeshRelativeLocation.Z;
	}
	else
	{
		BaseTranslationOffset.Z = DefaultChar->GetBaseTranslationOffset().Z + HeightAdjust;
	}

	// Do the same for our POVMesh
	const ASSCharacter* DefaultSSChar = GetDefault<ASSCharacter>(GetClass());
	if (POVMesh && DefaultSSChar->POVMesh)
	{
		FVector& MeshRelativeLocation = POVMesh->GetRelativeLocation_DirectMutable();
		MeshRelativeLocation.Z = DefaultSSChar->POVMesh->GetRelativeLocation().Z + HeightAdjust;
		BaseTranslationOffset.Z = MeshRelativeLocation.Z;
	}
	else
	{
		BaseTranslationOffset.Z = DefaultSSChar->GetBaseTranslationOffset().Z + HeightAdjust;
	}


	// Call BP event
	K2_OnStartCrouch(HeightAdjust, ScaledHeightAdjust);
}

void ASSCharacter::OnEndCrouch(float HeightAdjust, float ScaledHeightAdjust)
{
	//Super::OnEndCrouch(HeightAdjust, ScaledHeightAdjust);

	RecalculateBaseEyeHeight();


	// From Super
	const ACharacter* DefaultChar = GetDefault<ACharacter>(GetClass());
	if (GetMesh() && DefaultChar->GetMesh())
	{
		FVector& MeshRelativeLocation = GetMesh()->GetRelativeLocation_DirectMutable();
		MeshRelativeLocation.Z = DefaultChar->GetMesh()->GetRelativeLocation().Z;
		BaseTranslationOffset.Z = MeshRelativeLocation.Z;
	}
	else
	{
		BaseTranslationOffset.Z = DefaultChar->GetBaseTranslationOffset().Z;
	}

	// Do the same for our POVMesh
	const ASSCharacter* DefaultSSChar = GetDefault<ASSCharacter>(GetClass());
	if (POVMesh && DefaultSSChar->POVMesh)
	{
		FVector& MeshRelativeLocation = POVMesh->GetRelativeLocation_DirectMutable();
		MeshRelativeLocation.Z = DefaultSSChar->POVMesh->GetRelativeLocation().Z;
		BaseTranslationOffset.Z = MeshRelativeLocation.Z;
	}
	else
	{
		BaseTranslationOffset.Z = DefaultSSChar->GetBaseTranslationOffset().Z;
	}


	// Call BP event
	K2_OnEndCrouch(HeightAdjust, ScaledHeightAdjust);
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
	forwardInputAxis = Value;
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
	rightInputAxis = Value;
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
