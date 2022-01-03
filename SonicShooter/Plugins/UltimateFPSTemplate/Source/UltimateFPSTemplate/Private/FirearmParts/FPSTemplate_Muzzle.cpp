// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/FPSTemplate_Muzzle.h"
#include "FirearmParts/FPSTemplate_Barrel.h"
#include "FPSTemplate_PartComponent.h"
#include "FPSTemplateFirearm.h"
#include "FPSTemplateStatics.h"

AFPSTemplate_Muzzle::AFPSTemplate_Muzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsSuppressor = false;
	
	MuzzleSocket = FName("S_Muzzle");
	
	PartStats.Weight = 1.6f;
	PartStats.RecoilChangePercentage = -10.0f;

	PartType = EPartType::MuzzleDevice;
}

FTransform AFPSTemplate_Muzzle::GetMuzzleSocketTransform()
{
	if (PartComponents.Num())
	{
		for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
		{
			if (PartComponent)
			{
				AFPSTemplate_Muzzle* Muzzle = PartComponent->GetPart<AFPSTemplate_Muzzle>();
				if (IsValid(Muzzle))
				{
					return Muzzle->GetMuzzleSocketTransform();
				}
			}
		}
	}
	FPSLog(TEXT("Returning Muzzle Device: %s"), *GetName());
	return PartMesh->GetSocketTransform(MuzzleSocket);
}

bool AFPSTemplate_Muzzle::DoesMuzzleSocketExist()
{
	return PartMesh->DoesSocketExist(MuzzleSocket);
}

bool AFPSTemplate_Muzzle::IsSuppressor() const
{
	if (PartComponents.Num())
	{
		for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
		{
			if (PartComponent)
			{
				AFPSTemplate_Muzzle* Muzzle = PartComponent->GetPart<AFPSTemplate_Muzzle>();
				if (IsValid(Muzzle))
				{
					return Muzzle->IsSuppressor();
				}
			}
		}
	}
	return bIsSuppressor;
}
