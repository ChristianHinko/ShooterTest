// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/FPSTemplate_FlipMount.h"
#include "FPSTemplate_MagnifierComplete.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_MagnifierComplete : public AFPSTemplate_FlipMount
{
	GENERATED_BODY()
public:
	AFPSTemplate_MagnifierComplete();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Default")
	class USceneCaptureComponent2D* SceneCapture;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	float MagnifierRefreshRate;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	float Magnification;

	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
	virtual void Tick(float DeltaSeconds) override;
	
public:
	virtual void DisableRenderTarget(bool Disable) override;
};
