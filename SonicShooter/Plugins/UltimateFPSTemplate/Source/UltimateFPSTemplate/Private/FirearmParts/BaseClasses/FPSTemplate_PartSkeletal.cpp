// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/BaseClasses/FPSTemplate_PartSkeletal.h"

#include "Components/SkeletalMeshComponent.h"

AFPSTemplate_PartSkeletal::AFPSTemplate_PartSkeletal()
{
	PartMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMeshComponent"));
	PartMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PartMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PartMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	RootComponent = PartMesh;
}

void AFPSTemplate_PartSkeletal::PostInitProperties()
{
	Super::PostInitProperties();
	PartMesh->SetCollisionResponseToChannel(PoseCollision, ECR_Ignore);
}