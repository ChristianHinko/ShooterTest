// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"
#include "UI\UMG\Widgets\UW_ActiveItem.h"

#include "SSArcItemDefinition_Active.generated.h"





UCLASS(Blueprintable, BlueprintType)
class SONICSHOOTER_API USSUArcUIData_ActiveItemDefinition : public UArcUIData_ItemDefinition
{
	GENERATED_BODY()

public:
	USSUArcUIData_ActiveItemDefinition();


	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUW_ActiveItem> ActiveItemWidgetTSub;
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

	/* Effect that initializes the item's attributes. Attributes that need complex formulas for initialization can be done in an GameplayEffectExecutionCalculation class. For non-attribute properties (ie. raw floats, strings, pointers, etc) you can use UASSAttributeSet::OnDefaultStatsEffectApplied() to manually set those. */
	UPROPERTY(EditDefaultsOnly, Category = "Initialization")
		TSubclassOf<UGameplayEffect> InitializationEffectTSub;

};
