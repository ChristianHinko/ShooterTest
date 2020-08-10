// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/Sonic.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

ASonic::ASonic(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(78.0f);

	//Bump up all meshes so it gets within the capsule
	GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y, GetMesh()->GetRelativeLocation().Z + 20));
	GetPOVMesh()->SetRelativeLocation(FVector(GetPOVMesh()->GetRelativeLocation().X, GetPOVMesh()->GetRelativeLocation().Y, GetPOVMesh()->GetRelativeLocation().Z + 20));
}

