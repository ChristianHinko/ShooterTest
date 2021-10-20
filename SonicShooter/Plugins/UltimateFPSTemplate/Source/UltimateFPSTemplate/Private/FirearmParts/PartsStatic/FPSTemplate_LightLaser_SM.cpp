// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/PartsStatic/FPSTemplate_LightLaser_SM.h"

#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

AFPSTemplate_LightLaser_SM::AFPSTemplate_LightLaser_SM()
{
	PrimaryActorTick.bCanEverTick = true;

	PartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	PartMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PartMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PartMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	PartMesh->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	RootComponent = PartMesh;
	
	SpotLightComponent->SetupAttachment(PartMesh);
	LaserMesh->SetupAttachment(PartMesh);
	LaserDecalComponent->SetupAttachment(RootComponent);
}

void AFPSTemplate_LightLaser_SM::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
    if (bLaserOn && PartMesh)
    {
    	if (PartMesh->DoesSocketExist(LaserSocket))
    	{
    		FVector Start = PartMesh->GetSocketLocation(LaserSocket);
    		FRotator Rot = PartMesh->GetSocketRotation(LaserSocket);
    		FVector End = Start + Rot.Vector() * MaxLaserDistance;
        
    		FHitResult HitResult;
    		FCollisionQueryParams Params;
    		Params.AddIgnoredActor(this);
    
    		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, CollisionChannel, Params))
    		{
    			if (LaserDecalComponent)
    			{
    				LaserDecalComponent->SetVisibility(true);
    				FRotator NormalizedRotator = UKismetMathLibrary::MakeRotFromX(HitResult.Normal);
    				LaserDecalComponent->SetWorldLocationAndRotation(HitResult.Location, NormalizedRotator);
    			}
    			LaserMesh->SetWorldScale3D(FVector(1.0f, HitResult.Distance / 20.0f, 1.0f));
    		}
    		else
    		{
    			if (LaserDecalComponent)
    			{
    				LaserDecalComponent->SetVisibility(false);
    			}
    		}
    	}
	}
}

void AFPSTemplate_LightLaser_SM::PostInitProperties()
{
	Super::PostInitProperties();
	PartMesh->SetCollisionResponseToChannel(PoseCollision, ECR_Ignore);
}

FTransform AFPSTemplate_LightLaser_SM::GetAimSocketTransform() const
{
	return PartMesh->GetSocketTransform(AimSocket);
}
