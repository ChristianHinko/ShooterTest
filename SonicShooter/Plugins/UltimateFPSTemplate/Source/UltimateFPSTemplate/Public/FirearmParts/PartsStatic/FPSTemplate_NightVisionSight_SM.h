// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/PartsStatic/FPSTemplate_SightMagnified_SM.h"
#include "FPSTemplate_NightVisionSight_SM.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_NightVisionSight_SM : public AFPSTemplate_SightMagnified_SM
{
	GENERATED_BODY()
public:
	AFPSTemplate_NightVisionSight_SM();

protected:
	virtual void PostInitProperties() override;
};
