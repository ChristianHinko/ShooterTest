// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/STCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Subobjects/ActorComponents/GSActorComponent_PawnExtension.h"
#include "Character/AttributeSets/STAttributeSet_CharacterMovement.h"
#include "Subobjects/ASSActorComponent_AbilitySystemSetup.h"

#include "Kismet/KismetSystemLibrary.h"



DEFINE_LOG_CATEGORY_STATIC(LogCharacter, Log, All); // for some overriden ACharacter functions


void ASTCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME_CONDITION(ASTCharacter, bIsRunning, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ASTCharacter, RemoteViewYaw, COND_SkipOwner); // we also do a custom condition for this in PreReplication() (but we aren't using COND_Custom because we still want to COND_SkipOwner)
}


const FName ASTCharacter::POVMeshComponentName = TEXT("POVMesh");

ASTCharacter::ASTCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USTCharacterMovementComponent>(CharacterMovementComponentName))
{
	GSPawnExtensionComponent = CreateDefaultSubobject<UGSActorComponent_PawnExtension>(TEXT("GSPawnExtensionComponent"));

	STCharacterMovementComponent = Cast<USTCharacterMovementComponent>(GetMovementComponent());

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// Set our turn rates for input
	HorizontalSensitivity = 1.f;
	VerticalSensitivity = 1.f;

	// Configure character movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 600.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Mesh defaults
	if (GetMesh())
	{
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * -1));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	}

	// Create POVMesh
	POVMesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(POVMeshComponentName);
	if (POVMesh)
	{
		POVMesh->SetupAttachment(GetCapsuleComponent());
		POVMesh->AlwaysLoadOnClient = true;
		POVMesh->AlwaysLoadOnServer = false; // the server shouldn't care about this mesh
		POVMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		POVMesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		POVMesh->SetCollisionProfileName(MeshCollisionProfileName);
		POVMesh->SetGenerateOverlapEvents(false);
		POVMesh->SetCanEverAffectNavigation(false);

		if (GetMesh())
		{
			POVMesh->SetRelativeLocation(GetMesh()->GetRelativeLocation());
			POVMesh->SetRelativeRotation(GetMesh()->GetRelativeRotation());
			POVMesh->SetRelativeScale3D(GetMesh()->GetRelativeScale3D());
		}
		// Configure the POVMesh for first person (these apply regardless of third/first person because switching between the two will only set SetOwnerNoSee() and not change these settings)
		POVMesh->SetOnlyOwnerSee(true);
		POVMesh->SetCastShadow(false);	// hide the POV mesh shadow because it will probably look weird (we're using the normal mesh's shadow instead)
	}

	// Create CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// Set default arm length for third person mode
	ThirdPersonCameraArmLength = 300.f;

	// Default to third person
	bFirstPerson = false;
	bUseControllerRotationYaw = false; // don't rotate when the Controller rotates - let that just affect the camera
	GetCharacterMovement()->bOrientRotationToMovement = true; // make the Character face the direction that he is moving


	// Crouching
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	CrouchSpeed = 100.f;

	bToggleRunAlwaysRun = false;
}
void ASTCharacter::PostInitProperties()
{
	Super::PostInitProperties();

	// Set our configuration for this first/third person mode
	SetFirstPerson(bFirstPerson);
}
#if WITH_EDITOR
void ASTCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);


	if (GetMesh())
	{
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * -1));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	}

	if (POVMesh)
	{
		if (GetMesh())
		{
			POVMesh->SetRelativeLocation(GetMesh()->GetRelativeLocation());
			POVMesh->SetRelativeRotation(GetMesh()->GetRelativeRotation());
			POVMesh->SetRelativeScale3D(GetMesh()->GetRelativeScale3D());
		}

	}


	// Set our configuration for this first/third person mode
	SetFirstPerson(bFirstPerson);

}
#endif

void ASTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
	CrouchTickFunction.Target = this;
	CrouchTickFunction.RegisterTickFunction(GetLevel());
}

void ASTCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);


	if (GetLocalRole() == ROLE_Authority && GetController())
	{
		SetRemoteViewYaw(GetController()->GetControlRotation().Yaw);
	}

	// Custom RemoteViewYaw replication condition - only replicate if we aren't using bUseControllerRotationYaw
	DOREPLIFETIME_ACTIVE_OVERRIDE(ASTCharacter, RemoteViewYaw, (bUseControllerRotationYaw == false));

}


void ASTCharacter::SetFirstPerson(bool newFirstPerson)
{
	bFirstPerson = newFirstPerson;


	// Camera boom
	if (bFirstPerson == true)
	{
		// Configure CameraBoom arm length for first person
		CameraBoom->TargetArmLength = 0.f;
	}
	else
	{
		// Configure CameraBoom arm length for third person
		CameraBoom->TargetArmLength = ThirdPersonCameraArmLength;
	}

	// Meshes
	if (GetMesh())
	{
		if (POVMesh)
		{
			if (bFirstPerson == true)
			{
				// First person, so hide mesh but still see the shadow
				GetMesh()->SetOwnerNoSee(true);
				GetMesh()->bCastHiddenShadow = true; // we still want the shadow from the normal mesh (this casts shadow even when hidden)

				// First person, so show POV mesh
				POVMesh->SetOwnerNoSee(false);
			}
			else
			{
				// Third person, so let player see mesh
				GetMesh()->SetOwnerNoSee(false);
				GetMesh()->bCastHiddenShadow = false; // now if this mesh is hidden, don't show its shadow

				// Third person, so hide POV mesh
				POVMesh->SetOwnerNoSee(true);
			}
		}
		else
		{
			// We don't have POVMesh
			GetMesh()->SetOwnerNoSee(false);
			GetMesh()->bCastHiddenShadow = false;
		}
	}

}

void ASTCharacter::SetRemoteViewYaw(float NewRemoteViewYaw)
{
	// Compress yaw to 1 byte
	NewRemoteViewYaw = FRotator::ClampAxis(NewRemoteViewYaw);
	RemoteViewYaw = (uint8)(NewRemoteViewYaw * 255.f / 360.f);
}
FRotator ASTCharacter::GetBaseAimRotation() const
{
	FRotator POVRot = Super::GetBaseAimRotation();
	

	if (Controller != nullptr && !InFreeCam())
	{
		return POVRot;
	}

	
	if (bUseControllerRotationYaw)
	{
		// Our capsule rotation's Yaw perfectly represents our aim rotation's Yaw so just use that because it is more smoothly replicated (and RemoteViewYaw doesn't replicate if this is the case)
		POVRot.Yaw = GetActorRotation().Yaw;
	}
	else
	{
		// Use a replicated view yaw. NOTE: we may need to modify the Super to not do "FMath::IsNearlyZero(POVRot.Pitch)". Idk really what that is for but it may mess things up when we are rotated
		POVRot.Yaw = RemoteViewYaw;
		POVRot.Yaw = POVRot.Yaw * 360.0f / 255.0f;
	}


	return POVRot;
}

//BEGIN Jump overriding
void ASTCharacter::Jump()
{
	if (STCharacterMovementComponent.IsValid())
	{
		if (bPressedJump == false) // if changed
		{
			Super::Jump(); // set to true

			STCharacterMovementComponent->TimestampWantsToJump = GetWorld()->GetTimeSeconds();
		}

	}
}

void ASTCharacter::StopJumping()
{
	if (STCharacterMovementComponent.IsValid())
	{
		if (bPressedJump == true) // if changed
		{
			Super::StopJumping(); // set to false

			STCharacterMovementComponent->TimestampWantsToJump = -1 * GetWorld()->GetTimeSeconds();
		}
	}
}

bool ASTCharacter::CanJumpInternal_Implementation() const
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

void ASTCharacter::CheckJumpInput(float DeltaTime)
{
	STCharacterMovementComponent->CheckJumpInput(DeltaTime);
}

void ASTCharacter::ClearJumpInput(float DeltaTime)
{
	STCharacterMovementComponent->ClearJumpInput(DeltaTime);
}
//END Jump overriding


void ASTCharacter::OnRep_IsRunning()
{
	if (STCharacterMovementComponent.IsValid())
	{
		if (bIsRunning)
		{
			STCharacterMovementComponent->SetWantsToRun(true);
			STCharacterMovementComponent->Run();
		}
		else
		{
			STCharacterMovementComponent->SetWantsToRun(false);
			STCharacterMovementComponent->UnRun();
		}
		STCharacterMovementComponent->bNetworkUpdateReceived = true;
	}
}

//BEGIN Crouch overriding
void ASTCharacter::Crouch(bool bClientSimulation)
{
	//Super::Crouch(bClientSimulation);

	if (STCharacterMovementComponent.IsValid())
	{
		if (STCharacterMovementComponent->CanEverCrouch())
		{
			if (STCharacterMovementComponent->bWantsToCrouch == false) // if changed
			{
				STCharacterMovementComponent->bWantsToCrouch = true;
				STCharacterMovementComponent->TimestampWantsToCrouch = GetWorld()->GetTimeSeconds();
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
void ASTCharacter::UnCrouch(bool bClientSimulation)
{
	if (STCharacterMovementComponent.IsValid())
	{
		if (STCharacterMovementComponent->bWantsToCrouch == true) // if changed
		{
			Super::UnCrouch(bClientSimulation); // set to false

			STCharacterMovementComponent->TimestampWantsToCrouch = -1 * GetWorld()->GetTimeSeconds();
		}
	}
}

bool ASTCharacter::CanCrouch() const // this function isn't being used anymore
{
	//Super::CanCrouch();	// We are taking away the check for if bIsCrouched is false becus

	return GetCharacterMovement() && GetCharacterMovement()->CanEverCrouch() && GetRootComponent() && !GetRootComponent()->IsSimulatingPhysics();
}

void ASTCharacter::OnStartCrouch(float HeightAdjust, float ScaledHeightAdjust)
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

	const ASTCharacter* DefaultSTChar = GetDefault<ASTCharacter>(GetClass());

	// Do the same for our POVMesh
	if (POVMesh && DefaultSTChar->POVMesh)
	{
		FVector& MeshRelativeLocation = POVMesh->GetRelativeLocation_DirectMutable();
		MeshRelativeLocation.Z = DefaultSTChar->POVMesh->GetRelativeLocation().Z + HeightAdjust;
		BaseTranslationOffset.Z = MeshRelativeLocation.Z;
	}
	else
	{
		BaseTranslationOffset.Z = DefaultSTChar->GetBaseTranslationOffset().Z + HeightAdjust;
	}

	// Do this for the camera too (we don't want the camera teleporting to another Z position)
	if (CameraBoom && DefaultSTChar->CameraBoom)
	{
		// The crouch teleports our camera down. We want to do smoothing so we bump it back up here
		FVector& CameraBoomRelativeLocation = CameraBoom->GetRelativeLocation_DirectMutable();
		CameraBoomRelativeLocation.Z += HeightAdjust;

		// Store where our camera should be. This is our goal that we will smooth to
		CrouchToHeight = DefaultSTChar->CameraBoom->GetRelativeLocation().Z - HeightAdjust;
	}

	// Call BP event
	K2_OnStartCrouch(HeightAdjust, ScaledHeightAdjust);


	CrouchTickFunction.SetTickFunctionEnable(true);
}
void ASTCharacter::OnEndCrouch(float HeightAdjust, float ScaledHeightAdjust)
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

	const ASTCharacter* DefaultSTChar = GetDefault<ASTCharacter>(GetClass());

	// Do the same for our POVMesh
	if (POVMesh && DefaultSTChar->POVMesh)
	{
		FVector& MeshRelativeLocation = POVMesh->GetRelativeLocation_DirectMutable();
		MeshRelativeLocation.Z = DefaultSTChar->POVMesh->GetRelativeLocation().Z;
		BaseTranslationOffset.Z = MeshRelativeLocation.Z;
	}
	else
	{
		BaseTranslationOffset.Z = DefaultSTChar->GetBaseTranslationOffset().Z;
	}

	// Do this for the camera too (we don't want the camera teleporting to another Z position)
	if (CameraBoom && DefaultSTChar->CameraBoom)
	{
		// The uncrouch teleports our camera back up. We want to do smoothing so we bump it back down here
		FVector& CameraBoomRelativeLocation = CameraBoom->GetRelativeLocation_DirectMutable();
		CameraBoomRelativeLocation.Z -= HeightAdjust;

		// Store where our camera should be. This is our goal that we will smooth to
		CrouchToHeight = DefaultSTChar->CameraBoom->GetRelativeLocation().Z;
	}


	// Call BP event
	K2_OnEndCrouch(HeightAdjust, ScaledHeightAdjust);


	CrouchTickFunction.SetTickFunctionEnable(true);
}

void ASTCharacter::RecalculateBaseEyeHeight()
{
	if (STCharacterMovementComponent->IsCrouching() == false)
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
	if (Target.IsValid())
	{
		Target->CrouchTick(DeltaTime);
	}
}
void ASTCharacter::CrouchTick(float DeltaTime)
{
	const FVector CameraBoomLoc = CameraBoom->GetRelativeLocation();
	const float CrouchFromHeight = CameraBoomLoc.Z;

	float InterpedHeight;
	if (STCharacterMovementComponent->GetToggleCrouchEnabled()) // toggle crouch feels better with a linear interp
	{
		InterpedHeight = FMath::FInterpConstantTo(CrouchFromHeight, CrouchToHeight, DeltaTime, CrouchSpeed);

		if (InterpedHeight == CrouchToHeight)
		{
			// We've reached our goal, make this our last tick
			CrouchTickFunction.SetTickFunctionEnable(false);
		}
	}
	else // hold to crouch feels better with a smooth interp
	{
		InterpedHeight = FMath::FInterpTo(CrouchFromHeight, CrouchToHeight, DeltaTime, CrouchSpeed / 10);

		if (FMath::IsNearlyEqual(InterpedHeight, CrouchToHeight, KINDA_SMALL_NUMBER * 100))
		{
			// We've nearly reached our goal, set our official height and make this our last tick
			InterpedHeight = CrouchToHeight;
			CrouchTickFunction.SetTickFunctionEnable(false);
		}
	}

	CameraBoom->SetRelativeLocation(FVector(CameraBoomLoc.X, CameraBoomLoc.Y, InterpedHeight));


	//UKismetSystemLibrary::PrintString(this, "crouch ticking;                      " + CameraBoom->GetRelativeLocation().ToString(), true, false);
}
//END Crouch overriding

//void ASTCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	// Add slight smoothing in courtesy of players with low polling rates on high refresh rate displays
//	{
//		// This is the most common polling rate, 1/125 is 8ms so this adds 8ms of input lag.
//		// If we are getting 250fps but our mouse is only 125hz, this will simulate a 250hz mouse but with 8ms of input lag.
//		// If we do have a 250hz mouse anyways, we can't detect it so it ends up adding 8ms of lag anyways.
//		float targetPollingRate = 125;
//
//		if (CurrentYawInput != 0)
//		{
//			float previousYawInput = CurrentYawInput;
//			CurrentYawInput = FMath::FInterpTo(CurrentYawInput, 0.f, DeltaTime, targetPollingRate);
//			float SmoothedYaw = previousYawInput - CurrentYawInput;
//
//			AddControllerYawInput(SmoothedYaw * HorizontalSensitivity * 0.5);
//		}
//
//		if (CurrentPitchInput != 0)
//		{
//			float previousPitchInput = CurrentPitchInput;
//			CurrentPitchInput = FMath::FInterpTo(CurrentPitchInput, 0.f, DeltaTime, targetPollingRate);
//			float SmoothedPitch = previousPitchInput - CurrentPitchInput;
//
//			AddControllerPitchInput(SmoothedPitch * VerticalSensitivity * 0.5);
//		}
//	}
//}

//BEGIN Input setup
void ASTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action
	PlayerInputComponent->BindAction(FName(TEXT("Run")), IE_Pressed, this, &ThisClass::OnPressedRun);
	PlayerInputComponent->BindAction(FName(TEXT("Run")), IE_Released, this, &ThisClass::OnReleasedRun);

	PlayerInputComponent->BindAction(FName(TEXT("Jump")), IE_Pressed, this, &ThisClass::OnPressedJump);
	PlayerInputComponent->BindAction(FName(TEXT("Jump")), IE_Released, this, &ThisClass::OnReleasedJump);

	PlayerInputComponent->BindAction(FName(TEXT("Crouch")), IE_Pressed, this, &ThisClass::OnPressedCrouch);
	PlayerInputComponent->BindAction(FName(TEXT("Crouch")), IE_Released, this, &ThisClass::OnReleasedCrouch);

	PlayerInputComponent->BindAction(FName(TEXT("Interact")), IE_Pressed, this, &ThisClass::OnPressedInteract);
	PlayerInputComponent->BindAction(FName(TEXT("Interact")), IE_Released, this, &ThisClass::OnReleasedInteract);

	PlayerInputComponent->BindAction(FName(TEXT("PrimaryFire")), IE_Pressed, this, &ThisClass::OnPressedPrimaryFire);
	PlayerInputComponent->BindAction(FName(TEXT("PrimaryFire")), IE_Released, this, &ThisClass::OnReleasedPrimaryFire);

	PlayerInputComponent->BindAction(FName(TEXT("SecondaryFire")), IE_Pressed, this, &ThisClass::OnPressedSecondaryFire);
	PlayerInputComponent->BindAction(FName(TEXT("SecondaryFire")), IE_Released, this, &ThisClass::OnReleasedSecondaryFire);

	PlayerInputComponent->BindAction(FName(TEXT("Reload")), IE_Pressed, this, &ThisClass::OnPressedReload);
	PlayerInputComponent->BindAction(FName(TEXT("Reload")), IE_Released, this, &ThisClass::OnReleasedReload);

	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayout1st")), IE_Pressed, this, &ThisClass::OnPressedSwapToLayout1st);
	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayout1st")), IE_Released, this, &ThisClass::OnReleasedSwapToLayout1st);

	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayout2nd")), IE_Pressed, this, &ThisClass::OnPressedSwapToLayout2nd);
	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayout2nd")), IE_Released, this, &ThisClass::OnReleasedSwapToLayout2nd);

	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayout3rd")), IE_Pressed, this, &ThisClass::OnPressedSwapToLayout3rd);
	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayout3rd")), IE_Released, this, &ThisClass::OnReleasedSwapToLayout3rd);

	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayout4th")), IE_Pressed, this, &ThisClass::OnPressedSwapToLayout4th);
	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayout4th")), IE_Released, this, &ThisClass::OnReleasedSwapToLayout4th);

	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayout5th")), IE_Pressed, this, &ThisClass::OnPressedSwapToLayout5th);
	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayout5th")), IE_Released, this, &ThisClass::OnReleasedSwapToLayout5th);

	PlayerInputComponent->BindAction(FName(TEXT("SwapToPreviousSlot")), IE_Pressed, this, &ThisClass::OnPressedSwapToPreviousSlot);
	PlayerInputComponent->BindAction(FName(TEXT("SwapToPreviousSlot")), IE_Released, this, &ThisClass::OnReleasedSwapToPreviousSlot);

	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayoutForward")), IE_Pressed, this, &ThisClass::OnPressedSwapToLayoutForward);
	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayoutForward")), IE_Released, this, &ThisClass::OnReleasedSwapToLayoutForward);

	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayoutBackward")), IE_Pressed, this, &ThisClass::OnPressedSwapToLayoutBackward);
	PlayerInputComponent->BindAction(FName(TEXT("SwapToLayoutBackward")), IE_Released, this, &ThisClass::OnReleasedSwapToLayoutBackward);

	PlayerInputComponent->BindAction(FName(TEXT("DropItem")), IE_Pressed, this, &ThisClass::OnPressedDropItem);
	PlayerInputComponent->BindAction(FName(TEXT("DropItem")), IE_Released, this, &ThisClass::OnReleasedDropItem);

	PlayerInputComponent->BindAction(FName(TEXT("Pause")), IE_Pressed, this, &ThisClass::OnPressedPause);
	PlayerInputComponent->BindAction(FName(TEXT("Pause")), IE_Released, this, &ThisClass::OnReleasedPause);

	PlayerInputComponent->BindAction(FName(TEXT("ScoreSheet")), IE_Pressed, this, &ThisClass::OnPressedScoreSheet);
	PlayerInputComponent->BindAction(FName(TEXT("ScoreSheet")), IE_Released, this, &ThisClass::OnReleasedScoreSheet);


	// Axis
	PlayerInputComponent->BindAxis(FName(TEXT("MoveForward")), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(FName(TEXT("MoveRight")), this, &ThisClass::MoveRight);

	PlayerInputComponent->BindAxis(FName(TEXT("TurnRightRate")), this, &ThisClass::HorizontalLook);
	PlayerInputComponent->BindAxis(FName(TEXT("LookUpRate")), this, &ThisClass::VerticalLook);
}


// Actions
void ASTCharacter::OnPressedRun()
{
	if (STCharacterMovementComponent->GetToggleRunEnabled())
	{
		if (STCharacterMovementComponent->GetWantsToRun() == true)
		{
			if (bToggleRunAlwaysRun == false)
			{
				STCharacterMovementComponent->SetWantsToRun(false);
			}
		}
		else
		{
			STCharacterMovementComponent->SetWantsToRun(true);
		}
	}
	else
	{
		STCharacterMovementComponent->SetWantsToRun(true);
	}
}
void ASTCharacter::OnReleasedRun()
{
	if (STCharacterMovementComponent->GetToggleRunEnabled() == false)
	{
		STCharacterMovementComponent->SetWantsToRun(false);
	}
}

void ASTCharacter::OnPressedJump()
{
	Jump();
}
void ASTCharacter::OnReleasedJump()
{
	StopJumping();
}

void ASTCharacter::OnPressedCrouch()
{
	if (STCharacterMovementComponent->GetToggleCrouchEnabled())
	{
		if (STCharacterMovementComponent->bWantsToCrouch == true)
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
void ASTCharacter::OnReleasedCrouch()
{
	if (STCharacterMovementComponent->GetToggleCrouchEnabled() == false)
	{
		UnCrouch();
	}
}

void ASTCharacter::OnPressedInteract()
{

}
void ASTCharacter::OnReleasedInteract()
{
}

void ASTCharacter::OnPressedPrimaryFire()
{

}
void ASTCharacter::OnReleasedPrimaryFire()
{
}

void ASTCharacter::OnPressedSecondaryFire()
{

}
void ASTCharacter::OnReleasedSecondaryFire()
{
}

void ASTCharacter::OnPressedReload()
{

}
void ASTCharacter::OnReleasedReload()
{
}

void ASTCharacter::OnPressedSwapToLayout1st()
{

}
void ASTCharacter::OnReleasedSwapToLayout1st()
{
}

void ASTCharacter::OnPressedSwapToLayout2nd()
{

}
void ASTCharacter::OnReleasedSwapToLayout2nd()
{
}

void ASTCharacter::OnPressedSwapToLayout3rd()
{

}
void ASTCharacter::OnReleasedSwapToLayout3rd()
{
}

void ASTCharacter::OnPressedSwapToLayout4th()
{

}
void ASTCharacter::OnReleasedSwapToLayout4th()
{
}

void ASTCharacter::OnPressedSwapToLayout5th()
{

}
void ASTCharacter::OnReleasedSwapToLayout5th()
{
}

void ASTCharacter::OnPressedSwapToPreviousSlot()
{

}
void ASTCharacter::OnReleasedSwapToPreviousSlot()
{
}

void ASTCharacter::OnPressedSwapToLayoutForward()
{

}
void ASTCharacter::OnReleasedSwapToLayoutForward()
{
}

void ASTCharacter::OnPressedSwapToLayoutBackward()
{

}
void ASTCharacter::OnReleasedSwapToLayoutBackward()
{
}

void ASTCharacter::OnPressedDropItem()
{

}
void ASTCharacter::OnReleasedDropItem()
{
}

void ASTCharacter::OnPressedPause()
{

}
void ASTCharacter::OnReleasedPause()
{
}

void ASTCharacter::OnPressedScoreSheet()
{

}
void ASTCharacter::OnReleasedScoreSheet()
{
}



// Axis
void ASTCharacter::MoveForward(float Value)
{
	ForwardInputAxis = Value;
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
void ASTCharacter::MoveRight(float Value)
{
	RightInputAxis = Value;
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

void ASTCharacter::HorizontalLook(float Rate)
{
	if (Rate != 0)
	{
		AddControllerYawInput(Rate * HorizontalSensitivity * 0.5f);
	}
}
void ASTCharacter::VerticalLook(float Rate)
{
	if (Rate != 0)
	{
		AddControllerPitchInput(Rate * VerticalSensitivity * 0.5f);
	}
}
//END Input setup

void ASTCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CrouchTickFunction.UnRegisterTickFunction();
	CrouchTickFunction.Target = nullptr;

	Super::EndPlay(EndPlayReason);
}