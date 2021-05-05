// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"

#include "SSArcItemDefinition_Active.generated.h"


class UUW_Crosshair;
class UUW_Ammo;



UCLASS(Blueprintable, BlueprintType)
class SONICSHOOTER_API USSUArcUIData_ItemDefinition : public UArcUIData_ItemDefinition
{
	GENERATED_BODY()

public:
	USSUArcUIData_ItemDefinition();


	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUW_Crosshair> CrosshairWidgetTSub;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUW_Ammo> AmmoWidgetTSub;
};

/**
 * 
 */
UCLASS(Abstract)
class SONICSHOOTER_API USSArcItemDefinition_Active : public UArcItemDefinition_Active
{
	GENERATED_BODY()

public:
	USSArcItemDefinition_Active();


};
