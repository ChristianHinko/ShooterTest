// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/BaseClasses/FPSTemplate_MagnifierBase.h"
#include "FPSTemplate_Magnifier_SM.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_Magnifier_SM : public AFPSTemplate_MagnifierBase
{
	GENERATED_BODY()
public:
	AFPSTemplate_Magnifier_SM();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "FPSTemplate")
	class UStaticMeshComponent* PartMesh;

	virtual void PostInitProperties() override;
	
public:
	virtual FTransform GetAimSocketTransform() const override;
};
