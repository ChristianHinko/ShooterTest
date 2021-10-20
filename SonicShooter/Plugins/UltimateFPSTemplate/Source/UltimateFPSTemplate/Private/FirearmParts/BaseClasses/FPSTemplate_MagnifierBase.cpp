// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/BaseClasses/FPSTemplate_MagnifierBase.h"
#include "FPSTemplateFirearm.h"
#include "FPSTemplateCharacter.h"

#include "Components/SceneCaptureComponent2D.h"

AFPSTemplate_MagnifierBase::AFPSTemplate_MagnifierBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCapture->bHiddenInGame = true;
	SceneCapture->bCaptureEveryFrame = false;
	SceneCapture->bCaptureOnMovement = false;
	SceneCapture->bAlwaysPersistRenderingState = true;
	SceneCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_RenderScenePrimitives;
	
	PartType = EPartType::Magnifier;
	MagnifierRefreshRate = 60.0f;
	Magnification = 3.0f;
	bHasRenderTarget = true;
	bDisableWhenUnflipped = true;
}

void AFPSTemplate_MagnifierBase::BeginPlay()
{
	Super::BeginPlay();
	HandleRenderTargetSetup();
}

void AFPSTemplate_MagnifierBase::PostInitProperties()
{
	Super::PostInitProperties();

	SceneCapture->FOVAngle = 15.0f / Magnification;
}

void AFPSTemplate_MagnifierBase::OnRep_Owner()
{
	HandleRenderTargetSetup();
}

void AFPSTemplate_MagnifierBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SceneCapture->CaptureScene();
}

void AFPSTemplate_MagnifierBase::HandleRenderTargetSetup()
{
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

void AFPSTemplate_MagnifierBase::SetFOVAngle()
{
	SceneCapture->FOVAngle = 15.0f / Magnification;
}

void AFPSTemplate_MagnifierBase::DisableRenderTarget(bool Disable)
{
	if (Disable && !bDisableWhenUnflipped)
	{
		return;
	}
	SetActorTickEnabled(!Disable);
	SceneCapture->SetHiddenInGame(Disable);
}
