// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/BaseClasses/FPSTemplate_PartBase.h"
#include "FPSTemplate_MagnifierBase.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_MagnifierBase : public AFPSTemplate_PartBase
{
	GENERATED_BODY()
public:
	AFPSTemplate_MagnifierBase();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Default")
	class USceneCaptureComponent2D* SceneCapture;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	float MagnifierRefreshRate;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	float Magnification;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	bool bDisableWhenUnflipped;

	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
	virtual void OnRep_Owner() override;
	virtual void Tick(float DeltaSeconds) override;

	void HandleRenderTargetSetup();
	void SetFOVAngle();

public:
	virtual void DisableRenderTarget(bool Disable) override;

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Default")
	bool DisableWhenFlipped() const { return bDisableWhenUnflipped; }
};
