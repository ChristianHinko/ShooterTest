// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTags.h"
#include "ArcInventoryDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig)
class ARCINVENTORY_API UArcInventoryDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UArcInventoryDeveloperSettings(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items", config)
	TSubclassOf<class UArcItemStack> DefaultItemStackClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items", config)
	TSubclassOf<class AArcItemStackWorldObject> ItemStackWorldObjectClass;

};
