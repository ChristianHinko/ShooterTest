//Copyright 2021, Dakota Dawe, All rights reserved

#include "FPSTemplateCharacter.h"

#include "DrawDebugHelpers.h"
#include "FPSTemplateFirearm.h"
#include "FPSTemplateAnimInstance.h"
#include "FPSTemplateStatics.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

AFPSTemplateCharacter::AFPSTemplateCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	GetMesh()->bCastHiddenShadow = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadMeshComponent"));
	HeadMesh->SetupAttachment(GetMesh());
	HeadMesh->bCastHiddenShadow = true;
	
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(GetCapsuleComponent());
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	GetCharacterMovement()->MaxAcceleration = 1365.0f;
	GetCharacterMovement()->BrakingFriction = 1.0f;
	GetCharacterMovement()->MaxWalkSpeed = 250.0f;

	SprintSpeed = 600.0f;
	MaxLookUpAngle = 90.0f;
	MaxLookDownAngle = 80.0f;
	
	bIsTrueFirstPerson = false;
	CameraSocket = FName("CameraSocket");
	CameraSocketParentBone = FName("cc_Camera");
	WeaponGripSocket = FName("cc_WeaponGrip");
	bIsAiming = false;

	PortPose = EPortPose::None;

	MaxLeanAngle = 35.0f;

	bUseAutoPort = false;
	bAutoPortIsHitting = false;
	PortDistanceChecking = 50.0f;
	PoseCollision = ECC_GameTraceChannel2;

	bLeanLeftDown = false;
	bLeanRightDown = false;
}

void AFPSTemplateCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (HeadMesh && GetMesh())
	{
		HeadMesh->SetMasterPoseComponent(GetMesh());
	}

	if (GetInUseMesh())
	{
		AnimationInstance = Cast<UFPSTemplateAnimInstance>(GetInUseMesh()->GetAnimInstance());
		if (IsLocallyControlled())
		{
			FirstPersonCameraComponent->AttachToComponent(GetInUseMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, CameraSocket);
			GetInUseMesh()->SetOwnerNoSee(false);
			if (HeadMesh)
			{
				HeadMesh->SetHiddenInGame(true);
			}
			
			if (bIsTrueFirstPerson)
			{
				if (GetMesh1P())
				{
					GetMesh1P()->SetHiddenInGame(true);
				}
			}
			SetMinMaxPitch();
		}
	}
}

void AFPSTemplateCharacter::PostInitProperties()
{
	Super::PostInitProperties();
	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void AFPSTemplateCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSTemplateCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSTemplateCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFPSTemplateCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPSTemplateCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSTemplateCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPSTemplateCharacter::LookUpAtRate);
}

void AFPSTemplateCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bUseAutoPort && CurrentFirearm && AnimationInstance && PortPose == EPortPose::None)
	{
		FVector Start = FirstPersonCameraComponent->GetComponentLocation();
		FVector Muzzle = CurrentFirearm->GetMuzzleSocketTransform().GetLocation();
		FRotator Rotation = FirstPersonCameraComponent->GetComponentRotation();
		if (!bIsAiming)
		{
			Rotation.Yaw += 8.0f;
			Rotation.Pitch -= 2.0f;
		}
		FVector End = Start + Rotation.Vector() * 150.0f;
		float DistanceToMuzzle = FVector::Distance(Start, Muzzle);

		FHitResult HitResult;
		/*TArray<AActor*> ActorsToIgnore = {this, CurrentFirearm};
		if (AActor* MuzzleDevice = CurrentFirearm->GetMuzzleDeviceActor())
		{
			ActorsToIgnore.Add(MuzzleDevice);
		}*/
		
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.0f, 0, 1.0f);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, PoseCollision, Params))
		{
			float HitDistance = HitResult.Distance - DistanceToMuzzle;

			EPortPose Pose = EPortPose::High;
			float Normalized = 0.0f;
			float NeededCollisionDistance = 15.0f;
			if (HitDistance < NeededCollisionDistance)
			{
				HitDistance *= -1.0f;
				Normalized = UKismetMathLibrary::NormalizeToRange(HitDistance, NeededCollisionDistance * -1.0f, -5.0f);
				Normalized = FMath::Clamp(Normalized,0.0f, 1.0f);

				float Pitch = GetBaseAimRotation().Pitch;
				if (IsLocallyControlled())
				{
					if (Pitch < 0.0f)
					{
						Pose = EPortPose::Low;
					}
				}
				else
				{
					if (Pitch > 89.0f)
					{
						Pose = EPortPose::Low;
					}
				}
				bAutoPortIsHitting = AnimationInstance->HandleFirearmCollision(Pose, Normalized);
			}
			else if (HitDistance > NeededCollisionDistance + 10.0f)
			{
				Normalized = 0.0f;
				Pose = EPortPose::None;
				bAutoPortIsHitting = AnimationInstance->HandleFirearmCollision(Pose, Normalized);
				if (GetIsAiming())
				{
					AnimationInstance->SetIsAiming(true);
				}
			}
		}
		else
		{
			bAutoPortIsHitting = AnimationInstance->HandleFirearmCollision(EPortPose::None, 0.0f);
			/*if (GetIsAiming())
			{
				AnimationInstance->SetIsAiming(true);
			}*/
		}
	}
}

void AFPSTemplateCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AFPSTemplateCharacter, bIsAiming, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AFPSTemplateCharacter, CurrentLean, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AFPSTemplateCharacter, bIsSprinting, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AFPSTemplateCharacter, PortPose, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AFPSTemplateCharacter, bFreeLook, COND_SkipOwner);
	DOREPLIFETIME(AFPSTemplateCharacter, CurrentFirearm);
}

void AFPSTemplateCharacter::SetCurrentFirearm(AFPSTemplateFirearm* Firearm)
{
	if (Firearm)
	{
		CurrentFirearm = Firearm;
	}
}

void AFPSTemplateCharacter::OnRep_FreeLook()
{
	if (AnimationInstance)
	{
		AnimationInstance->SetFreeLook(bFreeLook);
	}
}

void AFPSTemplateCharacter::SetFreeLook(bool FreeLook)
{
	bFreeLook = FreeLook;
	if (bFreeLook)
	{
		bUseControllerRotationYaw = false;
	}
	else
	{
		bUseControllerRotationYaw = true;
	}
	if (!HasAuthority())
	{
		Server_SetFreeLook(bFreeLook);
	}
	OnRep_FreeLook();
}

bool AFPSTemplateCharacter::Server_SetFreeLook_Validate(bool FreeLook)
{
	return true;
}

void AFPSTemplateCharacter::Server_SetFreeLook_Implementation(bool FreeLook)
{
	SetFreeLook(FreeLook);
}

void AFPSTemplateCharacter::OnRep_PortPose()
{
	if (AnimationInstance)
	{
		AnimationInstance->SetPortPose(PortPose);
	}
}

bool AFPSTemplateCharacter::Server_SetPortPose_Validate(EPortPose NewPortPose)
{
	return true;
}

void AFPSTemplateCharacter::Server_SetPortPose_Implementation(EPortPose NewPortPose)
{
	PortPose = NewPortPose;
	OnRep_PortPose();
}

void AFPSTemplateCharacter::SetHighPortPose()
{
	if (!bAutoPortIsHitting)
	{
		bHighPort = true;
		if (PortPose == EPortPose::Low)
		{
			PortPose = EPortPose::None;
		}
		else
		{
			PortPose = EPortPose::High;
		}
		
		OnRep_PortPose();
		if (!HasAuthority())
		{
			Server_SetPortPose(PortPose);
		}
	}
}

void AFPSTemplateCharacter::SetLowPortPose()
{
	if (!bAutoPortIsHitting)
	{
		bLowPort = true;
		if (PortPose == EPortPose::High)
		{
			PortPose = EPortPose::None;
		}
		else
		{
			PortPose = EPortPose::Low;
		}
		
		OnRep_PortPose();
		if (!HasAuthority())
		{
			Server_SetPortPose(PortPose);
		}
	}
}

void AFPSTemplateCharacter::StopLowPortPose()
{
	if (!bAutoPortIsHitting)
	{
		bLowPort = false;
		if (bHighPort)
		{
			PortPose = EPortPose::High;
		}
		else
		{
			PortPose = EPortPose::None;
		}
		
		OnRep_PortPose();
		if (!HasAuthority())
		{
			Server_SetPortPose(PortPose);
		}
	}
}

void AFPSTemplateCharacter::StopHighPortPose()
{
	if (!bAutoPortIsHitting)
	{
		bHighPort = false;
		if (bLowPort)
		{
			PortPose = EPortPose::Low;
		}
		else
		{
			PortPose = EPortPose::None;
		}
		
		OnRep_PortPose();
		if (!HasAuthority())
		{
			Server_SetPortPose(PortPose);
		}
	}
}

USkeletalMeshComponent* AFPSTemplateCharacter::GetInUseMesh() const
{
	if (bIsTrueFirstPerson)
	{
		return GetMesh();
	}
	if (IsLocallyControlled())
	{
		return GetMesh1P();
	}
	return GetMesh();
}

void AFPSTemplateCharacter::PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake, float Scale)
{
	if (CameraShake)
	{
		if (APlayerController* PC = GetController<APlayerController>())
		{
			PC->ClientStartCameraShake(CameraShake, Scale);
		}
	}
}

FName AFPSTemplateCharacter::GetCameraSocket() const
{
	if (bUseParentSocketForAiming)
	{
		return CameraSocketParentBone;
	}
	return CameraSocket;
}

bool AFPSTemplateCharacter::Server_AddFirearm_Validate(TSubclassOf<AFPSTemplateFirearm> FirearmClass,
	bool SetAsCurrent)
{
	return true;
}

void AFPSTemplateCharacter::Server_AddFirearm_Implementation(TSubclassOf<AFPSTemplateFirearm> FirearmClass,
	bool SetAsCurrent)
{
	AddFirearm(FirearmClass, SetAsCurrent);
}

void AFPSTemplateCharacter::AddFirearm(TSubclassOf<AFPSTemplateFirearm> FirearmClass, bool SetAsCurrent)
{
	if (FirearmClass && HasAuthority())
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		if (AFPSTemplateFirearm* Firearm = GetWorld()->SpawnActor<AFPSTemplateFirearm>(FirearmClass, Params))
		{
			if (SetAsCurrent)
			{
				CurrentFirearm = Firearm;
				if (CurrentFirearm)
				{
					OnRep_CurrentFirearm();
				}
			}
			else // ADD TO ARRAY
			{
			
			}
		}
	}
}

bool AFPSTemplateCharacter::UseThirdPersonFirearmMontage() const
{
	if (bIsTrueFirstPerson || !IsLocallyControlled())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AFPSTemplateCharacter::RagdollWithImpact(FVector ImpactLocation, float ImpactForce)
{
	UFPSTemplateStatics::RagdollWithImpact(GetInUseMesh(), ImpactLocation, ImpactForce);
}

void AFPSTemplateCharacter::OnRep_CurrentFirearm()
{
	if (CurrentFirearm)
	{
		CurrentFirearm->AttachToComponent(GetInUseMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponGripSocket);
	}
}

void AFPSTemplateCharacter::OnRep_IsAiming()
{
	if (AnimationInstance)
	{
		AnimationInstance->SetIsAiming(bIsAiming);
	}
}

void AFPSTemplateCharacter::StartAiming()
{
	bIsAiming = true;
	if (bAutoPortIsHitting)
	{
		return;
	}
	if (CurrentFirearm)
	{
		CurrentFirearm->DisableAllRenderTargets(false);
	}
	if (AnimationInstance)
	{
		AnimationInstance->SetIsAiming(bIsAiming);
	}
	if (!HasAuthority())
	{
		Server_SetAiming(bIsAiming);
	}
}

void AFPSTemplateCharacter::StopAiming()
{
	bIsAiming = false;
	if (CurrentFirearm)
	{
		CurrentFirearm->DisableAllRenderTargets(true);
	}
	if (AnimationInstance)
	{
		AnimationInstance->SetIsAiming(bIsAiming);
	}
	if (!HasAuthority())
	{
		Server_SetAiming(bIsAiming);
	}
}

void AFPSTemplateCharacter::StartSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	bIsSprinting = true;

	if (!HasAuthority())
	{
		Server_SetSprinting(bIsSprinting);
	}
}

void AFPSTemplateCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	bIsSprinting = false;
	if (!HasAuthority())
	{
		Server_SetSprinting(bIsSprinting);
	}
}

void AFPSTemplateCharacter::OnRep_IsSprinting()
{
	if (bIsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}
}

bool AFPSTemplateCharacter::Server_SetSprinting_Validate(bool IsSprinting)
{
	return true;
}

void AFPSTemplateCharacter::Server_SetSprinting_Implementation(bool IsSprinting)
{
	bIsSprinting = IsSprinting;
	OnRep_IsSprinting();
}

void AFPSTemplateCharacter::OnRep_Lean()
{
	if (AnimationInstance)
	{
		AnimationInstance->SetLeaning(CurrentLean);
	}
}

void AFPSTemplateCharacter::LeanLeft()
{
	bLeanLeftDown = true;
	if (CurrentLean == ELeaning::Right)
	{
		CurrentLean = ELeaning::None;
	}
	else
	{
		CurrentLean = ELeaning::Left;
	}
	
	if (AnimationInstance)
	{
		AnimationInstance->SetLeaning(CurrentLean);
	}
	if (!HasAuthority())
	{
		Server_SetLean(CurrentLean);
	}
}

void AFPSTemplateCharacter::LeanRight()
{
	bLeanRightDown = true;
	if (CurrentLean == ELeaning::Left)
	{
		CurrentLean = ELeaning::None;
	}
	else
	{
		CurrentLean = ELeaning::Right;
	}

	if (AnimationInstance)
	{
		AnimationInstance->SetLeaning(CurrentLean);
	}
	if (!HasAuthority())
	{
		Server_SetLean(CurrentLean);
	}
}

void AFPSTemplateCharacter::StopLeanLeft()
{
	bLeanLeftDown = false;
	if (bLeanRightDown)
	{
		CurrentLean = ELeaning::Right;
	}
	else
	{
		CurrentLean = ELeaning::None;
	}
	
	if (AnimationInstance)
	{
		AnimationInstance->SetLeaning(CurrentLean);
	}
	if (!HasAuthority())
	{
		Server_SetLean(CurrentLean);
	}
}

void AFPSTemplateCharacter::StopLeanRight()
{
	bLeanRightDown = false;
	if (bLeanLeftDown)
	{
		CurrentLean = ELeaning::Left;
	}
	else
	{
		CurrentLean = ELeaning::None;
	}
	
	if (AnimationInstance)
	{
		AnimationInstance->SetLeaning(CurrentLean);
	}
	if (!HasAuthority())
	{
		Server_SetLean(CurrentLean);
	}
}

bool AFPSTemplateCharacter::Server_SetLean_Validate(ELeaning Lean)
{
	return true;
}

void AFPSTemplateCharacter::Server_SetLean_Implementation(ELeaning Lean)
{
	CurrentLean = Lean;
	OnRep_Lean();
}

bool AFPSTemplateCharacter::Server_SetAiming_Validate(bool IsAiming)
{
	return true;
}

void AFPSTemplateCharacter::Server_SetAiming_Implementation(bool IsAiming)
{
	bIsAiming = IsAiming;
	OnRep_IsAiming();
}

void AFPSTemplateCharacter::CycleSights()
{
	if (CurrentFirearm)
	{
		CurrentFirearm->CycleSights();
	}
}

void AFPSTemplateCharacter::SetMinMaxPitch()
{
	if (APlayerController* PC = GetController<APlayerController>())
	{
		if (APlayerCameraManager* CameraManager = PC->PlayerCameraManager)
		{
			CameraManager->ViewPitchMax = MaxLookUpAngle;
			CameraManager->ViewPitchMin = MaxLookDownAngle * -1.0f;
		}
	}	
}

void AFPSTemplateCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPSTemplateCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPSTemplateCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (Rate != 0.0f)
	{
		if (CurrentFirearm && bIsAiming)
		{
			Rate *= 1.0f / CurrentFirearm->GetOpticMagnification();
		}
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AFPSTemplateCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (Rate != 0.0f)
	{
		if (CurrentFirearm && bIsAiming)
		{
			Rate *= 1.0f / CurrentFirearm->GetOpticMagnification();
		}
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}