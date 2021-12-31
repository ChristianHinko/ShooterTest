// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/BaseClasses/FPSTemplate_PartBase.h"
#include "FPSTemplate_PartSkeletal.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_PartSkeletal : public AFPSTemplate_PartBase
{
	GENERATED_BODY()
public:
	AFPSTemplate_PartSkeletal();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FPSTemplate")
	class USkeletalMeshComponent* PartMesh;

	virtual void PostInitProperties() override;
};
