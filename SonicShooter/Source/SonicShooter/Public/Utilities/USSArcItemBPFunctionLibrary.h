// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ArcInventoryItemTypes.h"

#include "USSArcItemBPFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSArcItemBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Arc|Inventory|Debug", meta = (WorldContext = "WorldContextObject"))
		static class ASSArcItemStackWorldObject* SpawnWorldItem(UObject* WorldContextObject, UArcItemStack* ItemStack, const FTransform& Transform, TSubclassOf<AArcItemStackWorldObject> StackWorldObject);
};
