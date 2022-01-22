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
#include "Utilities/LogCategories.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SSGameState.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Pawn.h"
#include "Character/AS_CharacterMovement.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "Kismet/KismetSystemLibrary.h"



DEFINE_LOG_CATEGORY_STATIC(LogCharacter, Log, All); // for some overriden ACharacter functions


void ASSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME_CONDITION(ASSCharacter, bIsRunning, COND_SimulatedOnly);
	DOREPLIFETIME_CONDITION(ASSCharacter, RemoteViewYaw, COND_SkipOwner); // we also do a custom condition for this in PreReplication() (but we aren't using COND_Custom because we still want to COND_SkipOwner)

	DOREPLIFETIME(ASSCharacter, CharacterMovementAttributeSet);
	DOREPLIFETIME(ASSCharacter, StaminaAttributeSet);
	DOREPLIFETIME_CONDITION(ASSCharacter, CharacterJumpAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ASSCharacter, CharacterCrouchAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ASSCharacter, CharacterRunAbilitySpecHandle, COND_OwnerOnly);
}


const FName ASSCharacter::POVMeshComponentName = TEXT("POVMesh");

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


	if (GetCharacterMovement())
	{
		GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}

	CrouchSpeed = 100.f;

	bToggleRunAlwaysRun = false;
}
void ASSCharacter::PostInitProperties()
{
	Super::PostInitProperties();

	// Set our configuration for this first/third person mode
	SetFirstPerson(bFirstPerson);
}
#if WITH_EDITOR
void ASSCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);


	if (GetMesh())
	{
		GetMesh()->SetRelativeLocation(FVector(0, 0, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * -1));
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

void ASSCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	CrouchTickFunction.Target = this;
	CrouchTickFunction.RegisterTickFunction(GetLevel());
}

void ASSCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);


	if (GetLocalRole() == ROLE_Authority && GetController())
	{
		SetRemoteViewYaw(GetController()->GetControlRotation().Yaw);
	}

	// Custom RemoteViewYaw replication condition - only replicate if we aren't using bUseControllerRotationYaw
	DOREPLIFETIME_ACTIVE_OVERRIDE(ASSCharacter, RemoteViewYaw, (bUseControllerRotationYaw == false));

}


void ASSCharacter::CreateAttributeSets()
{
	Super::CreateAttributeSets();


	if (!CharacterMovementAttributeSet)
	{
		CharacterMovementAttributeSet = NewObject<UAS_CharacterMovement>(this, UAS_CharacterMovement::StaticClass(), TEXT("CharacterMovementAttributeSet"));
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogSSAbilitySystemSetup, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), *FString(__FUNCTION__), *CharacterMovementAttributeSet->GetName());
	}

	if (!StaminaAttributeSet)
	{
		StaminaAttributeSet = NewObject<UAS_Stamina>(this, UAS_Stamina::StaticClass(), TEXT("StaminaAttributeSet"));
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogSSAbilitySystemSetup, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), *FString(__FUNCTION__), *StaminaAttributeSet->GetName());
	}
}
void ASSCharacter::RegisterAttributeSets()
{
	Super::RegisterAttributeSets();


	if (CharacterMovementAttributeSet && !GetAbilitySystemComponent()->GetSpawnedAttributes().Contains(CharacterMovementAttributeSet))	// If CharacterMovementAttributeSet is valid and it's not yet registered with the Character's ASC
	{
		GetAbilitySystemComponent()->AddAttributeSetSubobject(CharacterMovementAttributeSet);
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogSSAbilitySystemSetup, Warning, TEXT("%s() CharacterMovementAttributeSet was either NULL or already added to the character's ASC. Character: %s"), *FString(__FUNCTION__), *GetName());
	}

	if (StaminaAttributeSet && !GetAbilitySystemComponent()->GetSpawnedAttributes().Contains(StaminaAttributeSet))	// If StaminaAttributeSet is valid and it's not yet registered with the Character's ASC
	{
		GetAbilitySystemComponent()->AddAttributeSetSubobject(StaminaAttributeSet);
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogSSAbilitySystemSetup, Warning, TEXT("%s() StaminaAttributeSet was either NULL or already added to the character's ASC. Character: %s"), *FString(__FUNCTION__), *GetName());
	}
}

void ASSCharacter::GrantStartingAbilities()
{
	Super::GrantStartingAbilities();

	CharacterJumpAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(CharacterJumpAbilityTSub, /*GetLevel()*/1, -1, this));
	CharacterCrouchAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(CharacterCrouchAbilityTSub, /*GetLevel()*/1, -1, this));
	CharacterRunAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(CharacterRunAbilityTSub, /*GetLevel()*/1, -1, this));


}


void ASSCharacter::SetFirstPerson(bool newFirstPerson)
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

void ASSCharacter::SetRemoteViewYaw(float NewRemoteViewYaw)
{
	// Compress yaw to 1 byte
	NewRemoteViewYaw = FRotator::ClampAxis(NewRemoteViewYaw);
	RemoteViewYaw = (uint8)(NewRemoteViewYaw * 255.f / 360.f);
}
FRotator ASSCharacter::GetBaseAimRotation() const
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
		interpedHeight = FMath::FInterpConstantTo(crouchFromHeight, crouchToHeight, DeltaTime, CrouchSpeed);

		if (interpedHeight == crouchToHeight)
		{
			// We've reached our goal, make this our last tick
			CrouchTickFunction.SetTickFunctionEnable(false);
		}
	}
	else // hold to crouch feels better with a smooth interp
	{
		interpedHeight = FMath::FInterpTo(crouchFromHeight, crouchToHeight, DeltaTime, CrouchSpeed / 10);

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

//void ASSCharacter::Tick(float DeltaTime)
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

#pragma region Input
void ASSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Action
	PlayerInputComponent->BindAction(FName(TEXT("Run")), IE_Pressed, this, &ASSCharacter::OnRunPressed);
	PlayerInputComponent->BindAction(FName(TEXT("Run")), IE_Released, this, &ASSCharacter::OnRunReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Jump")), IE_Pressed, this, &ASSCharacter::OnJumpPressed);
	PlayerInputComponent->BindAction(FName(TEXT("Jump")), IE_Released, this, &ASSCharacter::OnJumpReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Crouch")), IE_Pressed, this, &ASSCharacter::OnCrouchPressed);
	PlayerInputComponent->BindAction(FName(TEXT("Crouch")), IE_Released, this, &ASSCharacter::OnCrouchReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Interact")), IE_Pressed, this, &ASSCharacter::OnInteractPressed);
	PlayerInputComponent->BindAction(FName(TEXT("Interact")), IE_Released, this, &ASSCharacter::OnInteractReleased);

	PlayerInputComponent->BindAction(FName(TEXT("PrimaryFire")), IE_Pressed, this, &ASSCharacter::OnPrimaryFirePressed);
	PlayerInputComponent->BindAction(FName(TEXT("PrimaryFire")), IE_Released, this, &ASSCharacter::OnPrimaryFireReleased);

	PlayerInputComponent->BindAction(FName(TEXT("SecondaryFire")), IE_Pressed, this, &ASSCharacter::OnSecondaryFirePressed);
	PlayerInputComponent->BindAction(FName(TEXT("SecondaryFire")), IE_Released, this, &ASSCharacter::OnSecondaryFireReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Reload")), IE_Pressed, this, &ASSCharacter::OnReloadPressed);
	PlayerInputComponent->BindAction(FName(TEXT("Reload")), IE_Released, this, &ASSCharacter::OnReloadReleased);

	PlayerInputComponent->BindAction(FName(TEXT("FirstItem")), IE_Pressed, this, &ASSCharacter::OnFirstItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("FirstItem")), IE_Released, this, &ASSCharacter::OnFirstItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("SecondItem")), IE_Pressed, this, &ASSCharacter::OnSecondItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("SecondItem")), IE_Released, this, &ASSCharacter::OnSecondItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("ThirdItem")), IE_Pressed, this, &ASSCharacter::OnThirdItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("ThirdItem")), IE_Released, this, &ASSCharacter::OnThirdItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("FourthItem")), IE_Pressed, this, &ASSCharacter::OnFourthItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("FourthItem")), IE_Released, this, &ASSCharacter::OnFourthItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("FifthItem")), IE_Pressed, this, &ASSCharacter::OnFifthItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("FifthItem")), IE_Released, this, &ASSCharacter::OnFifthItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("SwitchWeapon")), IE_Pressed, this, &ASSCharacter::OnSwitchWeaponPressed);
	PlayerInputComponent->BindAction(FName(TEXT("SwitchWeapon")), IE_Released, this, &ASSCharacter::OnSwitchWeaponReleased);

	PlayerInputComponent->BindAction(FName(TEXT("NextItem")), IE_Pressed, this, &ASSCharacter::OnNextItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("NextItem")), IE_Released, this, &ASSCharacter::OnNextItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("PreviousItem")), IE_Pressed, this, &ASSCharacter::OnPreviousItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("PreviousItem")), IE_Released, this, &ASSCharacter::OnPreviousItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("DropItem")), IE_Pressed, this, &ASSCharacter::OnDropItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("DropItem")), IE_Released, this, &ASSCharacter::OnDropItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Pause")), IE_Pressed, this, &ASSCharacter::OnPausePressed);
	PlayerInputComponent->BindAction(FName(TEXT("Pause")), IE_Released, this, &ASSCharacter::OnPauseReleased);

	PlayerInputComponent->BindAction(FName(TEXT("ScoreSheet")), IE_Pressed, this, &ASSCharacter::OnScoreSheetPressed);
	PlayerInputComponent->BindAction(FName(TEXT("ScoreSheet")), IE_Released, this, &ASSCharacter::OnScoreSheetReleased);



	//Axis
	PlayerInputComponent->BindAxis(FName(TEXT("MoveForward")), this, &ASSCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName(TEXT("MoveRight")), this, &ASSCharacter::MoveRight);

	PlayerInputComponent->BindAxis(FName(TEXT("TurnRightRate")), this, &ASSCharacter::HorizontalLook);
	PlayerInputComponent->BindAxis(FName(TEXT("LookUpRate")), this, &ASSCharacter::VerticalLook);
}


//Actions
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

void ASSCharacter::OnJumpPressed()
{
	Jump();
}
void ASSCharacter::OnJumpReleased()
{
	StopJumping();
}

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

void ASSCharacter::OnFirstItemPressed()
{

}
void ASSCharacter::OnFirstItemReleased()
{
}

void ASSCharacter::OnSecondItemPressed()
{

}
void ASSCharacter::OnSecondItemReleased()
{
}

void ASSCharacter::OnThirdItemPressed()
{

}
void ASSCharacter::OnThirdItemReleased()
{
}

void ASSCharacter::OnFourthItemPressed()
{

}
void ASSCharacter::OnFourthItemReleased()
{
}

void ASSCharacter::OnFifthItemPressed()
{

}
void ASSCharacter::OnFifthItemReleased()
{
}

void ASSCharacter::OnSwitchWeaponPressed()
{

}
void ASSCharacter::OnSwitchWeaponReleased()
{
}

void ASSCharacter::OnNextItemPressed()
{

}
void ASSCharacter::OnNextItemReleased()
{
}

void ASSCharacter::OnPreviousItemPressed()
{

}
void ASSCharacter::OnPreviousItemReleased()
{
}

void ASSCharacter::OnDropItemPressed()
{

}
void ASSCharacter::OnDropItemReleased()
{
}

void ASSCharacter::OnPausePressed()
{

}
void ASSCharacter::OnPauseReleased()
{
}

void ASSCharacter::OnScoreSheetPressed()
{

}
void ASSCharacter::OnScoreSheetReleased()
{
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
		AddControllerYawInput(Rate * HorizontalSensitivity * 0.5);
	}
}
void ASSCharacter::VerticalLook(float Rate)
{
	if (Rate != 0)
	{
		AddControllerPitchInput(Rate * VerticalSensitivity * 0.5);
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
		for (int32 i = 0; i < PlayerStates.Num(); ++i)
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
