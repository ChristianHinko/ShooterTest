// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/BaseClasses/FPSTemplate_SightBase.h"
#include "FPSTemplate_Sight_SM.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_Sight_SM : public AFPSTemplate_SightBase
{
	GENERATED_BODY()
public:
	AFPSTemplate_Sight_SM();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "FPSTemplate")
	class UStaticMeshComponent* PartMesh;
	
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;

public:
	virtual FTransform GetAimSocketTransform() const override;
	virtual void CycleReticle() override;
	virtual void SetReticle(uint8 Index) override;
};
