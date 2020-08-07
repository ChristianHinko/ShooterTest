// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/Sonic.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

ASonic::ASonic(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetMesh()->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(78.0f);

	// Create FaceMesh
	FaceMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FaceMesh"));
	FaceMesh->SetupAttachment(GetMesh());
	FaceMesh->SetRelativeLocation(FVector(0.f, 0.f, -96.f));
	FaceMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	FaceMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	//Bump up all meshes so it gets within the capsule
	GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y, GetMesh()->GetRelativeLocation().Z + 20));
	GetPOVMesh()->SetRelativeLocation(FVector(GetPOVMesh()->GetRelativeLocation().X, GetPOVMesh()->GetRelativeLocation().Y, GetPOVMesh()->GetRelativeLocation().Z + 20));
}

