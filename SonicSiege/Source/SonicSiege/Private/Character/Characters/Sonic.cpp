// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/Sonic.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Character/AS_Character.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "GameFramework/SpringArmComponent.h"

ASonic::ASonic(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(78.0f);

	//Bump up all meshes so it gets within the capsule
	GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y, GetMesh()->GetRelativeLocation().Z + 20));
	GetPOVMesh()->SetRelativeLocation(FVector(GetPOVMesh()->GetRelativeLocation().X, GetPOVMesh()->GetRelativeLocation().Y, GetPOVMesh()->GetRelativeLocation().Z + 20));


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



