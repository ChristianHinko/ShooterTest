// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/BaseClasses/FPSTemplate_PartStatic.h"

#include "Components/StaticMeshComponent.h"

AFPSTemplate_PartStatic::AFPSTemplate_PartStatic()
{
	PartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	PartMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PartMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PartMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	RootComponent = PartMesh;

	
}

void AFPSTemplate_PartStatic::PostInitProperties()
{
	Super::PostInitProperties();
	PartMesh->SetCollisionResponseToChannel(PoseCollision, ECR_Ignore);
}
