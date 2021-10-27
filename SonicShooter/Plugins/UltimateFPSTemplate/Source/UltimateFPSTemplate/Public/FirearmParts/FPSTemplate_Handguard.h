// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/BaseClasses/FPSTemplate_PartStatic.h"
#include "FPSTemplate_Handguard.generated.h"

class AFPSTemplate_ForwardGrip;
class AFPSTemplateFirearm;
class AFPSTemplateFirearm_Sight;

UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_Handguard : public AFPSTemplate_PartStatic
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSTemplate_Handguard();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Sockets")
	FName ForwardGripSocket;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Sockets")
	FName HandGripSocket;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Sockets")
	FString SightSocket;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Attachments")
	AFPSTemplate_ForwardGrip* GetForwardGrip() const { return nullptr; }

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Animation")
	FTransform GetGripTransform() const;

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Animation")
	EFirearmGripType GetGripType() const;

	virtual FTransform GetAimSocketTransform() const override;
};