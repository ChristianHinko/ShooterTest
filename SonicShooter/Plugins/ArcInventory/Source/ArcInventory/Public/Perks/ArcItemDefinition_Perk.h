// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item/ArcItemDefinition_New.h"
#include "ArcItemDefinition_Perk.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class ARCINVENTORY_API UArcItemDefinition_Perk : public UArcItemDefinition_New
{
	GENERATED_BODY()
public:
	UArcItemDefinition_Perk();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perk Settings")
		TArray<TSubclassOf<class UGameplayEffect>> GameplayEffects;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = "Perk Settings")
		TArray<UAttributeSet*> AttributeSets;

};
