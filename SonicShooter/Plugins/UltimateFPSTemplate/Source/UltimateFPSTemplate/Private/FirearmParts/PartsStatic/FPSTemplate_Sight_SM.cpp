// Copyright 2021, Dakota Dawe, All rights reserved

#include "FirearmParts/PartsStatic/FPSTemplate_Sight_SM.h"

#include "Components/StaticMeshComponent.h"

AFPSTemplate_Sight_SM::AFPSTemplate_Sight_SM()
{
	PartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	PartMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PartMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PartMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	RootComponent = PartMesh;

}

void AFPSTemplate_Sight_SM::BeginPlay()
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

void AFPSTemplate_Sight_SM::PostInitProperties()
{
	Super::PostInitProperties();
	PartMesh->SetCollisionResponseToChannel(PoseCollision, ECR_Ignore);
}

FTransform AFPSTemplate_Sight_SM::GetAimSocketTransform() const
{
	return PartMesh->GetSocketTransform(AimSocket);
}

void AFPSTemplate_Sight_SM::CycleReticle()
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

void AFPSTemplate_Sight_SM::SetReticle(uint8 Index)
{
	if (Index < Reticles.Num() && Reticles[Index].DynamicReticleMaterial)
	{
		ReticleIndex = Index;
		PartMesh->SetMaterial(ReticleMaterialIndex, Reticles[ReticleIndex].DynamicReticleMaterial);
	}
}