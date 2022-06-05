// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/C_Sonic.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

//#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/AttributeSets/AS_CharacterMovement.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
#include "AttributeSets/ASSEAttributeSet_Health.h"
#include "Character/SSCharacterMovementComponent.h"



AC_Sonic::AC_Sonic(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(65.0f);
	
	////Bump up all meshes so it gets within the capsule
	//GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y, GetMesh()->GetRelativeLocation().Z + 44.f-13.f));
	//GetPOVMesh()->SetRelativeLocation(FVector(GetPOVMesh()->GetRelativeLocation().X, GetPOVMesh()->GetRelativeLocation().Y, GetPOVMesh()->GetRelativeLocation().Z + 44.f - 13.f));

	GetCameraBoom()->SetRelativeLocation(FVector(GetCameraBoom()->GetRelativeLocation().X, GetCameraBoom()->GetRelativeLocation().Y, 39.f));
}


void AC_Sonic::BeginPlay()
{
	Super::BeginPlay();


}

void AC_Sonic::Tick(float DeltaSeconds)
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
	//	if (GetStaminaAttributeSet())
	//	{
	//		UKismetSystemLibrary::PrintString(this, GetStaminaAttributeSet()->GetStaminaAttribute().AttributeName + ": " + FString::SanitizeFloat(GetStaminaAttributeSet()->GetStamina()), true, false);
	//	}
	//}
}

//void AC_Sonic::OnJumpPressed()
//{
//	Jump();
//}
//void AC_Sonic::OnJumpReleased()
//{
//	StopJumping();
//}
//
//void AC_Sonic::OnCrouchPressed()
//{
//	Crouch();
//}
//void AC_Sonic::OnCrouchReleased()
//{
//	UnCrouch();
//}
//
//void AC_Sonic::OnRunPressed()
//{
//	SSCharacterMovementComponent->SetWantsToRun(true);
//}
//void AC_Sonic::OnRunReleased()
//{
//	SSCharacterMovementComponent->SetWantsToRun(false);
//}
