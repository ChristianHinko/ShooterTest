// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/PartsStatic/FPSTemplate_ThermalSight_SM.h"
#include "FPSTemplateCharacter.h"

#include "Components/SceneCaptureComponent2D.h"

AFPSTemplate_ThermalSight_SM::AFPSTemplate_ThermalSight_SM()
{
	SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;

	ScopeRefreshRate = 15.0f;
}