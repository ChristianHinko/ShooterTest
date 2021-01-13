// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcItemGenerator.h"
#include "ArcItemGenerator_Unique.generated.h"

class UArcItemPerkDefinition;

/**
 * 
 */
UCLASS(NotEditInlineNew)
class ARCINVENTORY_API UArcItemGenerator_Unique : public UArcItemGenerator
{
	GENERATED_BODY()
public:
	UArcItemGenerator_Unique(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Definition")
	TSubclassOf<UArcItemDefinition_New> ItemDefinition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Definition")
	UArcItemRarity* ItemRarity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Definition")
	FText ItemDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Definition")
	TArray<UArcItemGenerator*> SubItemGenerators;

	virtual UArcItemStack* GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context) override;
};
