// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/BaseClasses/FPSTemplate_PartBase.h"
#include "FPSTemplate_PartStatic.generated.h"


UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_PartStatic : public AFPSTemplate_PartBase
{
	GENERATED_BODY()
public:
	AFPSTemplate_PartStatic();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FPSTemplate")
	class UStaticMeshComponent* PartMesh;

	virtual void PostInitProperties() override;
};
