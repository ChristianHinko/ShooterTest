// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/PartsSkeletal/FPSTemplate_Sight_SK.h"

#include "Components/SkeletalMeshComponent.h"

AFPSTemplate_Sight_SK::AFPSTemplate_Sight_SK()
{
	PartMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	PartMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PartMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PartMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	RootComponent = PartMesh;

}

void AFPSTemplate_Sight_SK::BeginPlay()
{
	Super::BeginPlay();
	
	ReticleBrightnessIndex = ReticleDefaultBrightnessIndex;

	for (FReticleMaterial& Reticle : Reticles)
	{
		if (Reticle.ReticleMaterial)
		{
			Reticle.DynamicReticleMaterial = UMaterialInstanceDynamic::Create(Reticle.ReticleMaterial, this);
		}
	}

	SetReticle(ReticleIndex);	
	SetReticleBrightness(ReticleDefaultBrightnessIndex);
}

void AFPSTemplate_Sight_SK::PostInitProperties()
{
	Super::PostInitProperties();
	PartMesh->SetCollisionResponseToChannel(PoseCollision, ECR_Ignore);
}

FTransform AFPSTemplate_Sight_SK::GetAimSocketTransform() const
{
	return PartMesh->GetSocketTransform(AimSocket);
}

void AFPSTemplate_Sight_SK::CycleReticle()
{
	if (Reticles.Num())
	{
		if (++ReticleIndex >= Reticles.Num())
		{
			ReticleIndex = 0;
		}
		SetReticle(ReticleIndex);
	}
}

void AFPSTemplate_Sight_SK::SetReticle(uint8 Index)
{
	if (Index < Reticles.Num() && Reticles[Index].DynamicReticleMaterial)
	{
		ReticleIndex = Index;
		PartMesh->SetMaterial(ReticleMaterialIndex, Reticles[ReticleIndex].DynamicReticleMaterial);
	}
}