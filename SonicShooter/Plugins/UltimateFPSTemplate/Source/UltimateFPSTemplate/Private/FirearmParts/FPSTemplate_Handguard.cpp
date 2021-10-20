// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/FPSTemplate_Handguard.h"
#include "FPSTemplateFirearm.h"
#include "FPSTemplate_PartComponent.h"
#include "FirearmParts/FPSTemplate_ForwardGrip.h"

#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFPSTemplate_Handguard::AFPSTemplate_Handguard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PartStats.Weight = 1.0f;
	PartStats.ErgonomicsChangePercentage = 5.0f;

	PartType = EPartType::Handguard;
	
	ForwardGripSocket = FName("S_ForwardGrip");
	HandGripSocket = FName("S_LeftHandIK");
	SightSocket = FString("S_Sight");
}

// Called when the game starts or when spawned
void AFPSTemplate_Handguard::BeginPlay()
{
	Super::BeginPlay();
}

FTransform AFPSTemplate_Handguard::GetGripTransform() const
{
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent)
		{
			AFPSTemplate_ForwardGrip* ForwardGrip = PartComponent->GetPart<AFPSTemplate_ForwardGrip>();
			if (IsValid(ForwardGrip))
			{
				return ForwardGrip->GetGripTransform();
			}
		}
	}
	return PartMesh->GetSocketTransform(HandGripSocket);
}

EFirearmGripType AFPSTemplate_Handguard::GetGripType() const
{
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent)
		{
			AFPSTemplate_ForwardGrip* ForwardGrip = PartComponent->GetPart<AFPSTemplate_ForwardGrip>();
			if (IsValid(ForwardGrip))
			{
				return ForwardGrip->GetGripType();
			}
		}
	}
	return EFirearmGripType::None;
}

FTransform AFPSTemplate_Handguard::GetAimSocketTransform() const
{
	return PartMesh->GetSocketTransform(AimSocket);
}
