// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/BaseClasses/FPSTemplate_PartStatic.h"
#include "FPSTemplate_ForwardGrip.generated.h"

UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_ForwardGrip : public AFPSTemplate_PartStatic
{
	GENERATED_BODY()
public:
	AFPSTemplate_ForwardGrip();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Sockets")
	FName HandGripSocket;

	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	EFirearmGripType GripType;

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Animation")
	FTransform GetGripTransform() const;
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Animation")
	EFirearmGripType GetGripType() const;
};