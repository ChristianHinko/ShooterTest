// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/PartsStatic/FPSTemplate_NightVisionSight_SM.h"

#include "Components/SceneCaptureComponent2D.h"

AFPSTemplate_NightVisionSight_SM::AFPSTemplate_NightVisionSight_SM()
{
	FPostProcessSettings PostProcessSettings;
	PostProcessSettings.WhiteTemp = 4957.0f;
	PostProcessSettings.WhiteTint = 0.43f;
	PostProcessSettings.ColorSaturation = FVector4(0.56f, 0.56f, 0.56f, 1.0f);
	PostProcessSettings.ColorContrast = FVector4(1.34f, 1.34f, 1.34f, 1.0f);
	PostProcessSettings.ColorGamma = FVector4(1.5f, 1.5f, 1.5f, 1.0f);
	PostProcessSettings.VignetteIntensity = 3.0f;
	PostProcessSettings.GrainIntensity = 0.5f;
	PostProcessSettings.SceneColorTint = FLinearColor(0.07f, 0.6f, 0.0f);
	PostProcessSettings.BloomIntensity = 2.0f;
	PostProcessSettings.AutoExposureBias = 8.0f;
	
	SceneCapture->PostProcessSettings = PostProcessSettings;
	SceneCapture->PostProcessBlendWeight = 1.0f;
	SceneCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_RenderScenePrimitives;
	SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	
}

void AFPSTemplate_NightVisionSight_SM::PostInitProperties()
{
	Super::PostInitProperties();
	PartMesh->SetCollisionResponseToChannel(PoseCollision, ECR_Ignore);
}
