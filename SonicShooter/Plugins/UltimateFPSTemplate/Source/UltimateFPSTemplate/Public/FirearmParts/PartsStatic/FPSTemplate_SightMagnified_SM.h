// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"

#include "FirearmParts/PartsStatic/FPSTemplate_Sight_SM.h"
#include "FPSTemplate_SightMagnified_SM.generated.h"


UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_SightMagnified_SM : public AFPSTemplate_Sight_SM
{
	GENERATED_BODY()

public:
	AFPSTemplate_SightMagnified_SM();
	
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
	
	void SetFOVAngle();

	UFUNCTION(BlueprintImplementableEvent, Category = "FPSTemplate | Events")
	void OpticZoomedIn(float OldMagnification);

	void HandleFirstFocalPlaneZoom(float MagnificationDifference);
	void HandleRenderTarget();

public:
	virtual float GetMagnification() const override { return CurrentMagnification; };
	virtual void ZoomIn() override;
	virtual void ZoomOut() override;
	virtual void IncreaseVerticalZero() override;
	virtual void DecreaseVerticalZero() override;

	virtual void DisableRenderTarget(bool Disable) override;
};
