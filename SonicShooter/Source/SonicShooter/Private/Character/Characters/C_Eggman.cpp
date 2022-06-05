// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/C_Eggman.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

//#include "GameFramework/CharacterMovementComponent.h"
//#include "Kismet/KismetSystemLibrary.h"
//#include "Actor/ASSEAttributeSet_Health.h"



AC_Eggman::AC_Eggman(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(85.0f + 7.f);

	////Bump up all meshes so it gets within the capsule
	//GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y, GetMesh()->GetRelativeLocation().Z + 44.f - 13.f - 20.f - 7.f));
	//GetPOVMesh()->SetRelativeLocation(FVector(GetPOVMesh()->GetRelativeLocation().X, GetPOVMesh()->GetRelativeLocation().Y, GetPOVMesh()->GetRelativeLocation().Z + 44.f - 13.f - 20.f - 7.f));

	GetCameraBoom()->SetRelativeLocation(FVector(GetCameraBoom()->GetRelativeLocation().X, GetCameraBoom()->GetRelativeLocation().Y, 73.0f));
}
