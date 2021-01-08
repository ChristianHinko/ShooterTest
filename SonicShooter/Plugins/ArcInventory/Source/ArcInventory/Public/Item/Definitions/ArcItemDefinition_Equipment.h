// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item/ArcItemDefinition_New.h"
#include "ArcInventoryItemTypes.h"
#include "ArcItemDefinition_Equipment.generated.h"

/**
 * 
 */
UCLASS(abstract)
class ARCINVENTORY_API UArcItemDefinition_Equipment : public UArcItemDefinition_New
{
	GENERATED_BODY()
public:
	UArcItemDefinition_Equipment();
		
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Equipped Item")
	FArcItemDefinition_AbilityInfo EquippedItemAbilityInfo;


};
