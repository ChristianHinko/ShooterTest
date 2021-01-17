// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArcInventoryComponent_Active.h"

#include "SSArcInventoryComponent_Active.generated.h"

class UArkItemStack;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSArcInventoryComponent_Active : public UArcInventoryComponent_Active
{
	GENERATED_BODY()
	
public:
	USSArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer);


	TArray<UArcItemStack*> ItemHistory;

protected:
	UFUNCTION()
		void OnNewActiveItem(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* NewlyActiveItemStack);
};
