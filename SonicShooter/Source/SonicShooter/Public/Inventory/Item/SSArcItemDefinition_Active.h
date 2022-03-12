// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"

#include "SSArcItemDefinition_Active.generated.h"


class UUW_ActiveItem;



/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SONICSHOOTER_API USSArcUIData_ItemDefinition : public UArcUIData_ItemDefinition
{
	GENERATED_BODY()

public:
	USSArcUIData_ItemDefinition();


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


	/**
	 * Display name of the Item for UI.
	 * May be overriden by the Item Generator (e.g. TF2 name tags and description tags).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		FText DefaultItemName;

	/**
	 * Effect that initializes the Item's Attributes.
	 * Attributes that need complex formulas for initialization can be done in an GameplayEffectExecutionCalculation class.
	 * For non-Attribute properties (e.g. raw floats, pointers, classes, etc.) you should use a GEEC to handle those in the Effect.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Initialization")
		TSubclassOf<UGameplayEffect> InitializationEffectTSub;

};
