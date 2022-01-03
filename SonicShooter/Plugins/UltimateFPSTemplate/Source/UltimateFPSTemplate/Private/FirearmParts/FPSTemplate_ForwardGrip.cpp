// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/FPSTemplate_ForwardGrip.h"
#include "FirearmParts/FPSTemplate_Handguard.h"
#include "FPSTemplateFirearm.h"

AFPSTemplate_ForwardGrip::AFPSTemplate_ForwardGrip()
{

	PartStats.Weight = 0.06f;
	PartStats.ErgonomicsChangePercentage = 10.0f;
	PartStats.RecoilChangePercentage = -8.0f;

	HandGripSocket = FName("S_LeftHandIK");

	PartType = EPartType::ForwardGrip;
}

void AFPSTemplate_ForwardGrip::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (AFPSTemplate_Handguard* Handguard = Cast<AFPSTemplate_Handguard>(GetOwner()))
		{
			if (AFPSTemplateFirearm* Firearm = Cast<AFPSTemplateFirearm>(Handguard->GetOwner()))
			{
				//Firearm->UpdateFirearmStats();
				//UE_LOG(LogTemp, Warning, TEXT("UPDATING STATS FORWARDGRIP"));
			}
		}
	}
}

FTransform AFPSTemplate_ForwardGrip::GetGripTransform() const
{
	return PartMesh->GetSocketTransform(HandGripSocket);
}

EFirearmGripType AFPSTemplate_ForwardGrip::GetGripType() const
{
	return GripType;
}
