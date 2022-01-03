// Copyright 2021, Dakota Dawe, All rights reserved

#include "FirearmParts/PartsStatic/FPSTemplate_Magnifier_SM.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"

AFPSTemplate_Magnifier_SM::AFPSTemplate_Magnifier_SM()
{
	PartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	PartMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PartMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PartMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	RootComponent = PartMesh;
	SceneCapture->SetupAttachment(PartMesh);
}

void AFPSTemplate_Magnifier_SM::PostInitProperties()
{
	Super::PostInitProperties();
	PartMesh->SetCollisionResponseToChannel(PoseCollision, ECR_Ignore);
}

FTransform AFPSTemplate_Magnifier_SM::GetAimSocketTransform() const
{
	return PartMesh->GetSocketTransform(AimSocket);
}
