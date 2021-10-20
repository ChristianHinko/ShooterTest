// Copyright 2021, Dakota Dawe, All rights reserved


#include "FirearmParts/PartsStatic/FPSTemplate_SightMagnified_SM.h"
#include "FPSTemplateFirearm.h"
#include "FPSTemplateCharacter.h"
#include "FPSTemplateStatics.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"

AFPSTemplate_SightMagnified_SM::AFPSTemplate_SightMagnified_SM()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCapture->SetupAttachment(PartMesh);
	SceneCapture->bHiddenInGame = true;
	SceneCapture->bCaptureEveryFrame = false;
	SceneCapture->bCaptureOnMovement = false;
	SceneCapture->bAlwaysPersistRenderingState = true;
	SceneCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_RenderScenePrimitives;

	ScopeRefreshRate = 60.0f;
	bIsFirstFocalPlane = false;

	Magnifications = {1.0f};
	MagnificationIndex = 0;

	bHasRenderTarget = true;
	bDisableWhenNotAiming = true;
}

void AFPSTemplate_SightMagnified_SM::BeginPlay()
{
	Super::BeginPlay();

	DisableRenderTarget(true);
	//HandleRenderTarget();
}

void AFPSTemplate_SightMagnified_SM::PostInitProperties()
{
	Super::PostInitProperties();
	if (Magnifications.Num())
	{
		CurrentMagnification = Magnifications[MagnificationIndex];
	}
	else
	{
		CurrentMagnification = 1.0f;
	}
	SetFOVAngle();
	
	SetActorTickInterval(1 / ScopeRefreshRate);

	PartMesh->SetCollisionResponseToChannel(PoseCollision, ECR_Ignore);
}

void AFPSTemplate_SightMagnified_SM::OnRep_Owner()
{
	
	//HandleRenderTarget();
}

void AFPSTemplate_SightMagnified_SM::HandleRenderTarget()
{
	if (PartType == EPartType::Magnifier)
	{
		if (AFPSTemplateCharacter* Character = GetOwningCharacter())
		{
			if (Character->IsLocallyControlled())
			{
				DisableRenderTarget(false);
			}
		}
	}
	else
	{
		DisableRenderTarget(true);
	}
}

void AFPSTemplate_SightMagnified_SM::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SceneCapture->CaptureScene();
}

void AFPSTemplate_SightMagnified_SM::SetFOVAngle()
{
	SceneCapture->FOVAngle = 15.0f / CurrentMagnification;
}

void AFPSTemplate_SightMagnified_SM::HandleFirstFocalPlaneZoom(float MagnificationDifference)
{
	for (FReticleMaterial& Reticle : Reticles)
	{
		if (Reticle.DynamicReticleMaterial)
		{
			float CurrentReticleSize;
			Reticle.DynamicReticleMaterial->GetScalarParameterValue(FName("ReticleSize"), CurrentReticleSize);
			if (CurrentReticleSize)
			{
				float NewReticleSize = CurrentReticleSize + (MagnificationDifference * 0.1f / 2.0f);
				Reticle.DynamicReticleMaterial->SetScalarParameterValue(FName("ReticleSize"), NewReticleSize);
			}
		}
	}
}

void AFPSTemplate_SightMagnified_SM::ZoomIn()
{
	if (++MagnificationIndex < Magnifications.Num())
	{
		float OldMagnification = CurrentMagnification;
		CurrentMagnification = Magnifications[MagnificationIndex];

		if (bIsFirstFocalPlane)
		{
			HandleFirstFocalPlaneZoom(CurrentMagnification - OldMagnification);
		}
		
		for (FReticleMaterial& Reticle : Reticles)
		{
			if (Reticle.DynamicReticleMaterial)
			{
				float EyeboxRange;
				Reticle.DynamicReticleMaterial->GetScalarParameterValue(FName("EyeboxRange"), EyeboxRange);
				if (EyeboxRange)
				{
					EyeboxRange -= 150.0f;
					Reticle.DynamicReticleMaterial->SetScalarParameterValue(FName("EyeboxRange"), EyeboxRange);
				}
			}
		}
		
		OpticZoomedIn(OldMagnification);
		SetFOVAngle();
	}
	else
	{
		MagnificationIndex = Magnifications.Num() - 1;
	}
}

void AFPSTemplate_SightMagnified_SM::ZoomOut()
{
	if (MagnificationIndex - 1 >= 0)
	{
		float OldMagnification = CurrentMagnification;
		--MagnificationIndex;
		CurrentMagnification = Magnifications[MagnificationIndex];

		if (bIsFirstFocalPlane)
		{
			HandleFirstFocalPlaneZoom(CurrentMagnification - OldMagnification);
		}
		
		for (FReticleMaterial& Reticle : Reticles)
		{
			if (Reticle.DynamicReticleMaterial)
			{
				float EyeboxRange;
				Reticle.DynamicReticleMaterial->GetScalarParameterValue(FName("EyeboxRange"), EyeboxRange);
				if (EyeboxRange)
				{
					EyeboxRange += 150.0f;
					Reticle.DynamicReticleMaterial->SetScalarParameterValue(FName("EyeboxRange"), EyeboxRange);
				}
			}
		}
		
		OpticZoomedIn(OldMagnification);
		SetFOVAngle();
	}
	else
	{
		MagnificationIndex = 0;
	}
}

void AFPSTemplate_SightMagnified_SM::IncreaseVerticalZero()
{
	FRotator CurrentRot = SceneCapture->GetRelativeRotation();
	CurrentRot.Pitch -= 0.006f;
	SceneCapture->SetRelativeRotation(CurrentRot);
}

void AFPSTemplate_SightMagnified_SM::DecreaseVerticalZero()
{
	FRotator CurrentRot = SceneCapture->GetRelativeRotation();
	CurrentRot.Pitch += 0.006f;
	SceneCapture->SetRelativeRotation(CurrentRot);
}

void AFPSTemplate_SightMagnified_SM::DisableRenderTarget(bool Disable)
{
	/*if (Disable && !bDisableWhenNotAiming)
	{
		return;
	}*/
	SetActorTickEnabled(!Disable);
	SceneCapture->SetHiddenInGame(Disable);
}