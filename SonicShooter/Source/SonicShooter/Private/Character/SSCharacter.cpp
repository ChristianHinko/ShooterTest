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
#include "Utilities/CollisionChannels.h"
#include "Interfaces/Interactable.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SSGameState.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Pawn.h"

#include "Kismet/KismetSystemLibrary.h"



DEFINE_LOG_CATEGORY_STATIC(LogCharacter, Log, All); // for some overriden ACharacter functions


void ASSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASSCharacter, bIsRunning, COND_SimulatedOnly);
}

ASSCharacter::ASSCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	SSCharacterMovementComponent = Cast<USSCharacterMovementComponent>(GetMovementComponent());

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set our turn rates for input
	HorizontalSensitivity = 1.f;
	VerticalSensitivity = 1.f;

	// Configure character movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 600.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Mesh defaults
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * -1));
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
	POVMesh->SetRelativeLocation(GetMesh()->GetRelativeLocation() + FVector(-25.f, 0.f, 0.f));
	POVMesh->SetRelativeRotation(GetMesh()->GetRelativeRotation());
	POVMesh->SetRelativeScale3D(GetMesh()->GetRelativeScale3D());
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


	if (GetCharacterMovement())
	{
		GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}

	crouchSpeed = 100.f;

	bToggleRunAlwaysRun = false;
}
//void ASSCharacter::PostInitProperties()
//{
//	Super::PostInitProperties();
//
//
//	// Theses aren't working right yet some reason:
//
//	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * -1));
//
//	POVMesh->SetRelativeLocation(GetMesh()->GetRelativeLocation() + FVector(-25.f, 0.f, 0.f));
//	POVMesh->SetRelativeRotation(GetMesh()->GetRelativeRotation());
//	POVMesh->SetRelativeScale3D(GetMesh()->GetRelativeScale3D());
//}

void ASSCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Set our configuration for this first/third person mode
	SetFirstPerson(bFirstPerson);
}

void ASSCharacter::BeginPlay()
{
	Super::BeginPlay();

	CrouchTickFunction.Target = this;
	CrouchTickFunction.RegisterTickFunction(GetLevel());
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

#pragma region Jump
void ASSCharacter::Jump()
{
	if (SSCharacterMovementComponent)
	{
		if (bPressedJump == false) // if changed
		{
			Super::Jump(); // set to true

			SSCharacterMovementComponent->timestampWantsToJump = GetWorld()->GetTimeSeconds();
		}

	}
}

void ASSCharacter::StopJumping()
{
	if (SSCharacterMovementComponent)
	{
		if (bPressedJump == true) // if changed
		{
			Super::StopJumping(); // set to false

			SSCharacterMovementComponent->timestampWantsToJump = -1 * GetWorld()->GetTimeSeconds();
		}
	}
}

bool ASSCharacter::CanJumpInternal_Implementation() const
{
	//return Super::CanJumpInternal_Implementation(); // the super makes it return false when crouched - we don't want this

	//// Ensure the character isn't currently crouched.
	//bool bCanJump = !bIsCrouched;
	bool bCanJump = true;

	// Ensure that the CharacterMovement state is valid
	bCanJump &= GetCharacterMovement()->CanAttemptJump();

	if (bCanJump)
	{
		// Ensure JumpHoldTime and JumpCount are valid.
		if (!bWasJumping || GetJumpMaxHoldTime() <= 0.0f)
		{
			if (JumpCurrentCount == 0 && GetCharacterMovement()->IsFalling())
			{
				bCanJump = JumpCurrentCount + 1 < JumpMaxCount;
			}
			else
			{
				bCanJump = JumpCurrentCount < JumpMaxCount;
			}
		}
		else
		{
			// Only consider JumpKeyHoldTime as long as:
			// A) The jump limit hasn't been met OR
			// B) The jump limit has been met AND we were already jumping
			const bool bJumpKeyHeld = (bPressedJump && JumpKeyHoldTime < GetJumpMaxHoldTime());
			bCanJump = bJumpKeyHeld &&
				((JumpCurrentCount < JumpMaxCount) || (bWasJumping && JumpCurrentCount == JumpMaxCount));
		}
	}

	return bCanJump;
}

void ASSCharacter::CheckJumpInput(float DeltaTime)
{
	SSCharacterMovementComponent->CheckJumpInput(DeltaTime);
}

void ASSCharacter::ClearJumpInput(float DeltaTime)
{
	SSCharacterMovementComponent->ClearJumpInput(DeltaTime);
}

#pragma endregion


void ASSCharacter::OnRep_IsRunning()
{
	if (SSCharacterMovementComponent)
	{
		if (bIsRunning)
		{
			SSCharacterMovementComponent->SetWantsToRun(true);
			SSCharacterMovementComponent->Run();
		}
		else
		{
			SSCharacterMovementComponent->SetWantsToRun(false);
			SSCharacterMovementComponent->UnRun();
		}
		SSCharacterMovementComponent->bNetworkUpdateReceived = true;
	}
}

#pragma region Crouch
void ASSCharacter::Crouch(bool bClientSimulation)
{
	//Super::Crouch(bClientSimulation);

	if (SSCharacterMovementComponent)
	{
		if (SSCharacterMovementComponent->CanEverCrouch())
		{
			if (SSCharacterMovementComponent->bWantsToCrouch == false) // if changed
			{
				SSCharacterMovementComponent->bWantsToCrouch = true;
				SSCharacterMovementComponent->timestampWantsToCrouch = GetWorld()->GetTimeSeconds();
			}
		}
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		else
		{
			UE_LOG(LogCharacter, Log, TEXT("%s is trying to crouch, but crouching is disabled on this character! (check CharacterMovement NavAgentSettings)"), *GetName());
		}
#endif
	}
}
void ASSCharacter::UnCrouch(bool bClientSimulation)
{
	if (SSCharacterMovementComponent)
	{
		if (SSCharacterMovementComponent->bWantsToCrouch == true) // if changed
		{
			Super::UnCrouch(bClientSimulation); // set to false

			SSCharacterMovementComponent->timestampWantsToCrouch = -1 * GetWorld()->GetTimeSeconds();
		}
	}
}

bool ASSCharacter::CanCrouch() const // this function isn't being used anymore
{
	//Super::CanCrouch();	// We are taking away the check for if bIsCrouched is false becus

	return GetCharacterMovement() && GetCharacterMovement()->CanEverCrouch() && GetRootComponent() && !GetRootComponent()->IsSimulatingPhysics();
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

	const ASSCharacter* DefaultSSChar = GetDefault<ASSCharacter>(GetClass());

	// Do the same for our POVMesh
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

	// Do this for the camera too (we don't want the camera teleporting to another Z position)
	if (CameraBoom && DefaultSSChar->CameraBoom)
	{
		// The crouch teleports our camera down. We want to do smoothing so we bump it back up here
		FVector& CameraBoomRelativeLocation = CameraBoom->GetRelativeLocation_DirectMutable();
		CameraBoomRelativeLocation.Z += HeightAdjust;

		// Store where our camera should be. This is our goal that we will smooth to
		crouchToHeight = DefaultSSChar->CameraBoom->GetRelativeLocation().Z - HeightAdjust;
	}

	// Call BP event
	K2_OnStartCrouch(HeightAdjust, ScaledHeightAdjust);


	CrouchTickFunction.SetTickFunctionEnable(true);
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

	const ASSCharacter* DefaultSSChar = GetDefault<ASSCharacter>(GetClass());

	// Do the same for our POVMesh
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

	// Do this for the camera too (we don't want the camera teleporting to another Z position)
	if (CameraBoom && DefaultSSChar->CameraBoom)
	{
		// The uncrouch teleports our camera back up. We want to do smoothing so we bump it back down here
		FVector& CameraBoomRelativeLocation = CameraBoom->GetRelativeLocation_DirectMutable();
		CameraBoomRelativeLocation.Z -= HeightAdjust;

		// Store where our camera should be. This is our goal that we will smooth to
		crouchToHeight = DefaultSSChar->CameraBoom->GetRelativeLocation().Z;
	}


	// Call BP event
	K2_OnEndCrouch(HeightAdjust, ScaledHeightAdjust);


	CrouchTickFunction.SetTickFunctionEnable(true);
}

void ASSCharacter::RecalculateBaseEyeHeight()
{
	if (SSCharacterMovementComponent->IsCrouching() == false)
	{
		if (Super::StaticClass() == ACharacter::StaticClass())
		{
			ACharacter::Super::RecalculateBaseEyeHeight(); // skip ACharacter's implementation
		}
		else
		{
			Super::RecalculateBaseEyeHeight();
		}

	}
	else
	{
		BaseEyeHeight = CrouchedEyeHeight;
	}
}

void FCrouchTickFunction::ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
{
	if (Target && !Target->IsPendingKillOrUnreachable())
	{
		Target->CrouchTick(DeltaTime);
	}
}
void ASSCharacter::CrouchTick(float DeltaTime)
{
	const FVector CameraBoomLoc = CameraBoom->GetRelativeLocation();
	const float crouchFromHeight = CameraBoomLoc.Z;

	float interpedHeight;
	if (SSCharacterMovementComponent->GetToggleCrouchEnabled()) // toggle crouch feels better with a linear interp
	{
		interpedHeight = FMath::FInterpConstantTo(crouchFromHeight, crouchToHeight, DeltaTime, crouchSpeed);

		if (interpedHeight == crouchToHeight)
		{
			// We've reached our goal, make this our last tick
			CrouchTickFunction.SetTickFunctionEnable(false);
		}
	}
	else // hold to crouch feels better with a smooth interp
	{
		interpedHeight = FMath::FInterpTo(crouchFromHeight, crouchToHeight, DeltaTime, crouchSpeed / 10);

		if (FMath::IsNearlyEqual(interpedHeight, crouchToHeight, KINDA_SMALL_NUMBER * 100))
		{
			// We've nearly reached our goal, set our official height and make this our last tick
			interpedHeight = crouchToHeight;
			CrouchTickFunction.SetTickFunctionEnable(false);
		} 
	}

	CameraBoom->SetRelativeLocation(FVector(CameraBoomLoc.X, CameraBoomLoc.Y, interpedHeight));


	//UKismetSystemLibrary::PrintString(this, "crouch ticking;                      " + CameraBoom->GetRelativeLocation().ToString(), true, false);
}
#pragma endregion

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
	//PlayerInputComponent->BindAction("Reload", IE_Released, this, &ASSCharacter::OnReloadReleased);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASSCharacter::OnCrouchPressed);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASSCharacter::OnCrouchReleased);

	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ASSCharacter::OnSwitchWeaponPressed);
	//PlayerInputComponent->BindAction("SwitchWeapon", IE_Released, this, &ASSCharacter::OnSwitchWeaponReleased);


	PlayerInputComponent->BindAction("Item0", IE_Pressed, this, &ASSCharacter::OnItem0Pressed);
	//PlayerInputComponent->BindAction("Item0", IE_Released, this, &ASSCharacter::OnItem0Released);

	PlayerInputComponent->BindAction("Item1", IE_Pressed, this, &ASSCharacter::OnItem1Pressed);
	//PlayerInputComponent->BindAction("Item1", IE_Released, this, &ASSCharacter::OnItem1Released);

	PlayerInputComponent->BindAction("Item2", IE_Pressed, this, &ASSCharacter::OnItem2Pressed);
	//PlayerInputComponent->BindAction("Item2", IE_Released, this, &ASSCharacter::OnItem2Released);

	PlayerInputComponent->BindAction("Item3", IE_Pressed, this, &ASSCharacter::OnItem3Pressed);
	//PlayerInputComponent->BindAction("Item3", IE_Released, this, &ASSCharacter::OnItem3Released);

	PlayerInputComponent->BindAction("Item4", IE_Pressed, this, &ASSCharacter::OnItem4Pressed);
	//PlayerInputComponent->BindAction("Item4", IE_Released, this, &ASSCharacter::OnItem4Released);



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
//void ASSCharacter::OnReloadReleased()
//{
//
//}

void ASSCharacter::OnCrouchPressed()
{
	if (SSCharacterMovementComponent->GetToggleCrouchEnabled())
	{
		if (SSCharacterMovementComponent->bWantsToCrouch == true)
		{
			UnCrouch();
		}
		else
		{
			Crouch();
		}
	}
	else
	{
		Crouch();
	}
}
void ASSCharacter::OnCrouchReleased()
{
	if (SSCharacterMovementComponent->GetToggleCrouchEnabled() == false)
	{
		UnCrouch();
	}
}

void ASSCharacter::OnSwitchWeaponPressed()
{

}
//void ASSCharacter::OnSwitchWeaponReleased()
//{
//
//}

void ASSCharacter::OnItem0Pressed()
{
}

//void ASSCharacter::OnItem0Released()
//{
//}

void ASSCharacter::OnItem1Pressed()
{
}

//void ASSCharacter::OnItem1Released()
//{
//}

void ASSCharacter::OnItem2Pressed()
{
}

//void ASSCharacter::OnItem2Released()
//{
//}

void ASSCharacter::OnItem3Pressed()
{
}

//void ASSCharacter::OnItem3Released()
//{
//}

void ASSCharacter::OnItem4Pressed()
{
}

//void ASSCharacter::OnItem4Released()
//{
//}

void ASSCharacter::OnRunPressed()
{
	if (SSCharacterMovementComponent->GetToggleRunEnabled())
	{
		if (SSCharacterMovementComponent->GetWantsToRun() == true)
		{
			if (bToggleRunAlwaysRun == false)
			{
				SSCharacterMovementComponent->SetWantsToRun(false);
			}
		}
		else
		{
			SSCharacterMovementComponent->SetWantsToRun(true);
		}
	}
	else
	{
		SSCharacterMovementComponent->SetWantsToRun(true);
	}
}
void ASSCharacter::OnRunReleased()
{
	if (SSCharacterMovementComponent->GetToggleRunEnabled() == false)
	{
		SSCharacterMovementComponent->SetWantsToRun(false);
	}
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

void ASSCharacter::HorizontalLook(float Rate) // TODO: add slight smoothing in courtesy of players with low polling rates on high refresh rate displays
{
	if (Rate != 0)
	{
		AddControllerYawInput(Rate * HorizontalSensitivity * 0.5/* * GetWorld()->GetDeltaSeconds()*/); // delta seconds is not needed here for some reason. Idk why but it does the opposite of the expected effect
	}
}
void ASSCharacter::VerticalLook(float Rate) // TODO: add slight smoothing in courtesy of players with low polling rates on high refresh rate displays
{
	if (Rate != 0)
	{
		AddControllerPitchInput(Rate * VerticalSensitivity * 0.5/* * GetWorld()->GetDeltaSeconds()*/); // delta seconds is not needed here for some reason. Idk why but it does the opposite of the expected effect
	}
}
#pragma endregion

#pragma region Helpers
APawn* ASSCharacter::GetNearestPawn()
{
	APawn* RetVal = nullptr;
	if (UGameplayStatics::GetGameState(this))
	{
		float closestPawnDistance = MAX_FLT;
		TArray<APlayerState*> PlayerStates = UGameplayStatics::GetGameState(this)->PlayerArray;
		for (int i = 0; i < PlayerStates.Num(); i++)
		{
			if (PlayerStates.IsValidIndex(i) && PlayerStates[i])
			{
				APawn* CurrentPawn = PlayerStates[i]->GetPawn();
				if (CurrentPawn != this)
				{
					float distanceToCurrentPlayer = GetDistanceTo(CurrentPawn);
					if (distanceToCurrentPlayer < closestPawnDistance)
					{
						RetVal = CurrentPawn;
						closestPawnDistance = distanceToCurrentPlayer;
					}
				}
			}
		}
	}

	return RetVal;
}
#pragma endregion

void ASSCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CrouchTickFunction.UnRegisterTickFunction();
	CrouchTickFunction.Target = nullptr;
}
