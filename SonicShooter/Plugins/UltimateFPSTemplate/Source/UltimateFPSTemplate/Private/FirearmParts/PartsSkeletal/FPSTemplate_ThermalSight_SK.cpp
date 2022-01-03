// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/PartsSkeletal/FPSTemplate_ThermalSight_SK.h"
#include "FPSTemplateCharacter.h"

#include "Components/SceneCaptureComponent2D.h"

AFPSTemplate_ThermalSight_SK::AFPSTemplate_ThermalSight_SK()
{
	PrimaryActorTick.bCanEverTick = true;

	ScopeRefreshRate = 15.0f;
}