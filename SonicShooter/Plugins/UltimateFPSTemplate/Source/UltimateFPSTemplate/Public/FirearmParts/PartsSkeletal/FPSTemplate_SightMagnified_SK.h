// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/PartsSkeletal/FPSTemplate_Sight_SK.h"
#include "FPSTemplate_SightMagnified_SK.generated.h"


UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_SightMagnified_SK : public AFPSTemplate_Sight_SK
{
	GENERATED_BODY()

public:
	AFPSTemplate_SightMagnified_SK();
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Default")
	class USceneCaptureComponent2D* SceneCapture;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	float ScopeRefreshRate;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	TArray<float> Magnifications;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	bool bIsFirstFocalPlane;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	bool bDisableWhenNotAiming;

	uint8 MagnificationIndex;
	float CurrentMagnification;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
	virtual void OnRep_Owner() override;
	virtual void Tick(float DeltaSeconds) override;
	void HandleRenderTarget();
		
	void SetFOVAngle();

	UFUNCTION(BlueprintImplementableEvent, Category = "FPSTemplate | Events")
	void OpticZoomedIn(float OldMagnification);

	void HandleFirstFocalPlaneZoom(float MagnificationDifference);

public:
	virtual float GetMagnification() const override { return CurrentMagnification; };
	virtual void ZoomIn() override;
	virtual void ZoomOut() override;
	virtual void IncreaseVerticalZero() override;
	virtual void DecreaseVerticalZero() override;

	virtual void DisableRenderTarget(bool Disable) override;
};
