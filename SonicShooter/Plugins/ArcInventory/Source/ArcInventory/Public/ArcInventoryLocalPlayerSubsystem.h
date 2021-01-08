// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ArcInventoryItemTypes.h"
#include "ArcInventoryLocalPlayerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ARCINVENTORY_API UArcInventoryLocalPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
public:
	UArcInventoryLocalPlayerSubsystem();

	//UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	//FArcInventoryItemSlotReference SwapFromSlot;

	//UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	//FArcInventoryItemSlotReference SwapToSlot;
	
};
