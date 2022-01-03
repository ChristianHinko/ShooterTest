// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/BaseClasses/FPSTemplate_LightLaserBase.h"
#include "FPSTemplate_LightLaser_SM.generated.h"

UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_LightLaser_SM : public AFPSTemplate_LightLaserBase
{
	GENERATED_BODY()
	
public:
	AFPSTemplate_LightLaser_SM();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "FPSTemplate")
	class UStaticMeshComponent* PartMesh;

	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitProperties() override;
	
public:
	virtual FTransform GetAimSocketTransform() const override;
};
