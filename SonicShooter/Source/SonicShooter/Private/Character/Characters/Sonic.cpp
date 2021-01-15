// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/Sonic.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

//#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Actor/AS_Health.h"
#include "Character/AS_Character.h"
#include "Character/SSCharacterMovementComponent.h"



ASonic::ASonic(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(65.0f);
	
	//Bump up all meshes so it gets within the capsule
	GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y, GetMesh()->GetRelativeLocation().Z + 44.f-13.f));
	GetPOVMesh()->SetRelativeLocation(FVector(GetPOVMesh()->GetRelativeLocation().X, GetPOVMesh()->GetRelativeLocation().Y, GetPOVMesh()->GetRelativeLocation().Z + 44.f - 13.f));

	GetCameraBoom()->SetRelativeLocation(FVector(GetCameraBoom()->GetRelativeLocation().X, GetCameraBoom()->GetRelativeLocation().Y, 39.f));
	

	//// Don't rotate when the controller rotates. Let that just affect the camera.
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;
	//// Rotate the character in the movement direction
	//GetCharacterMovement()->bOrientRotationToMovement = true;


	//// Third person, so let player see mesh
	//GetMesh()->SetOwnerNoSee(false);

	//// Configure CameraBoom arm length for third person
	//GetCameraBoom()->TargetArmLength = 300.f;
}


void ASonic::BeginPlay()
{
	Super::BeginPlay();


}

void ASonic::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	//if (USSCharacterMovementComponent* CMC = GetSSCharacterMovementComponent())
	//{
	//	UKismetSystemLibrary::PrintString(this, CMC->IsCrouching() ? "CROUCHING" : "not crouching", true, false);
	//	UKismetSystemLibrary::PrintString(this, CMC->bWantsToCrouch ? "WANTS TO CROUCH" : "no want crouching", true, false);

	//	UKismetSystemLibrary::PrintString(this, CMC->IsRunning() ? "RUNNING" : "not running", true, false);
	//	UKismetSystemLibrary::PrintString(this, CMC->GetWantsToRun() ? "WANTS TO RUN" : "no want running", true, false);
	//}


	//if (GetHealthAttributeSet())
	//{
	//	UKismetSystemLibrary::PrintString(this, GetName() + ": " + FString::SanitizeFloat(GetHealthAttributeSet()->GetHealth()), true, false);
	//}
	//if (IsLocallyControlled())
	//{
		//if (GetCharacterAttributeSet())
		//{
		//	UKismetSystemLibrary::PrintString(this, GetCharacterAttributeSet()->GetStaminaAttribute().AttributeName + ": " + FString::SanitizeFloat(GetCharacterAttributeSet()->GetStamina()), true, false);
		//}
	//}
}

//void ASonic::OnJumpPressed()
//{
//	Jump();
//}
//void ASonic::OnJumpReleased()
//{
//	StopJumping();
//}
//
//void ASonic::OnCrouchPressed()
//{
//	Crouch();
//}
//void ASonic::OnCrouchReleased()
//{
//	UnCrouch();
//}
//
//void ASonic::OnRunPressed()
//{
//	SSCharacterMovementComponent->SetWantsToRun(true);
//}
//void ASonic::OnRunReleased()
//{
//	SSCharacterMovementComponent->SetWantsToRun(false);
//}
