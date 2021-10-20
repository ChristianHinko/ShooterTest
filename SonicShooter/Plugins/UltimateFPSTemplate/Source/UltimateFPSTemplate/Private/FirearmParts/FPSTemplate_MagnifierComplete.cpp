// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/FPSTemplate_MagnifierComplete.h"
#include "FPSTemplateFirearm.h"
#include "FPSTemplateCharacter.h"

#include "Components/SceneCaptureComponent2D.h"

AFPSTemplate_MagnifierComplete::AFPSTemplate_MagnifierComplete()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCapture->SetupAttachment(PartMesh);
	SceneCapture->bHiddenInGame = true;
	SceneCapture->bCaptureEveryFrame = false;
	SceneCapture->bCaptureOnMovement = false;
	SceneCapture->bAlwaysPersistRenderingState = true;
	SceneCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_RenderScenePrimitives;

	MagnifierRefreshRate = 60.0f;
	Magnification = 3.0f;

	bHasRenderTarget = true;
}

void AFPSTemplate_MagnifierComplete::BeginPlay()
{
	Super::BeginPlay();

	if (AFPSTemplateCharacter* Character = GetOwningCharacter())
	{
		if (Character->IsLocallyControlled())
		{
			DisableRenderTarget(false);
			SetActorTickInterval(1 / MagnifierRefreshRate);
		}
		else
		{
			SetActorTickEnabled(false);
		}
	}
}

void AFPSTemplate_MagnifierComplete::PostInitProperties()
{
	Super::PostInitProperties();
	
	SceneCapture->FOVAngle = 15.0f / Magnification;
}

void AFPSTemplate_MagnifierComplete::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SceneCapture->CaptureScene();
}

void AFPSTemplate_MagnifierComplete::DisableRenderTarget(bool Disable)
{
	SetActorTickEnabled(!Disable);

	SceneCapture->SetHiddenInGame(Disable);
}
