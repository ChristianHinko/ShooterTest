// Copyright 2021, Dakota Dawe, All rights reserved

#include "FirearmParts/BaseClasses/FPSTemplate_SightBase.h"
#include "FPSTemplateFirearm.h"
#include "FPSTemplateCharacter.h"

#include "Materials/MaterialInstanceDynamic.h"

AFPSTemplate_SightBase::AFPSTemplate_SightBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PartStats.Weight = 0.1f;
	PartStats.ErgonomicsChangePercentage = -2.0f;
	CameraFOVZoom = 10.0f;
	CameraFOVZoomSpeed = 10.0f;

	bIsAimable = true;

	PartType = EPartType::Sight;

	ReticleIndex = 0;
	ReticleBrightnessSettings = {1.0f};
	ReticleDefaultBrightnessIndex = 0;
	ReticleBrightnessIndex = 0;
	ReticleMaterialIndex = 1;
}

// Called when the game starts or when spawned
void AFPSTemplate_SightBase::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSTemplate_SightBase::SetReticleBrightness(uint8 Index)
{
	if (Index < ReticleBrightnessSettings.Num())
	{
		for (FReticleMaterial& Reticle : Reticles)
		{
			if (Reticle.DynamicReticleMaterial)
			{
				Reticle.DynamicReticleMaterial->SetScalarParameterValue(FName("ReticleBrightness"), ReticleBrightnessSettings[Index]);
			}
		}
	}
}

void AFPSTemplate_SightBase::IncreaseBrightness()
{
	if (++ReticleBrightnessIndex < ReticleBrightnessSettings.Num())
	{
		SetReticleBrightness(ReticleBrightnessIndex);
	}
	else
	{
		ReticleBrightnessIndex = ReticleBrightnessSettings.Num() - 1;
	}
}

void AFPSTemplate_SightBase::DecreaseBrightness()
{
	if (ReticleBrightnessIndex - 1 >= 0)
	{
		--ReticleBrightnessIndex;
		SetReticleBrightness(ReticleBrightnessIndex);
	}
	else
	{
		ReticleBrightnessIndex = 0;
	}
}