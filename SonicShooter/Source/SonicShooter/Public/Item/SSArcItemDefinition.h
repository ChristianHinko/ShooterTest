// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"
#include "UI\UMG\Widgets\UW_ActiveItem.h"

#include "SSArcItemDefinition.generated.h"





UCLASS(Blueprintable, BlueprintType)
class SONICSHOOTER_API USSUArcUIData_ItemDefinition : public UArcUIData_ItemDefinition
{
	GENERATED_BODY()

public:
	USSUArcUIData_ItemDefinition();


	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUW_ActiveItem> ActiveItemWidgetTSub;
};

/**
 * 
 */
UCLASS(Abstract)
class SONICSHOOTER_API USSArcItemDefinition : public UArcItemDefinition_Active
{
	GENERATED_BODY()

public:
	USSArcItemDefinition();


};
