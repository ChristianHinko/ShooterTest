// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/PartsSkeletal/FPSTemplate_Magnifier_SK.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"

AFPSTemplate_Magnifier_SK::AFPSTemplate_Magnifier_SK()
{
	PartMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	PartMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PartMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PartMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	RootComponent = PartMesh;
	SceneCapture->SetupAttachment(PartMesh);

	bHasRenderTarget = true;
}

void AFPSTemplate_Magnifier_SK::PostInitProperties()
{
	Super::PostInitProperties();
	PartMesh->SetCollisionResponseToChannel(PoseCollision, ECR_Ignore);
}

FTransform AFPSTemplate_Magnifier_SK::GetAimSocketTransform() const
{
	return PartMesh->GetSocketTransform(AimSocket);
}
