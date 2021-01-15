// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcItemGenerator.h"
#include "ArcItemGenerator_SimpleRandom.generated.h"

class UArcItemRarity;
class UArcItemStack;
class UArcItemStack_Perk;

USTRUCT(BlueprintType)
struct FArcItemGenerator_RaritySelector
{
	GENERATED_USTRUCT_BODY()
public:
	FArcItemGenerator_RaritySelector()
	{
		NumberOfPerks = 1;
		NumberOfModifiers = 1;
		Weight = 1;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	FGameplayTagQuery RarityTagQuery;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	int32 NumberOfPerks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		int32 NumberOfModifiers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	int32 Weight; 
};

USTRUCT(BlueprintType)
struct FArcItemGenerator_DynamicModifier
{
	GENERATED_USTRUCT_BODY()
public:

	FArcItemGenerator_DynamicModifier()
	{
		MinValue = 0;
		MaxValue = 1;
		ModifierOp = EGameplayModOp::Multiplicitive;
		Weight = 1;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		FGameplayAttribute Attribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		TEnumAsByte<EGameplayModOp::Type> ModifierOp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	float MinValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	float MaxValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameplayModifier)
	FGameplayTagQuery SlotApplicationRequirement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	int32 Weight;
};

USTRUCT(BlueprintType)
struct FArcItemGenerator_PerkSelector
{
	GENERATED_USTRUCT_BODY()
public:

	FArcItemGenerator_PerkSelector()
	{
		Weight = 1;
	}
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	FGameplayTagQuery PerkTagQuery;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	int32 Weight;
};

/**
 * 
 */
UCLASS(NotEditInlineNew, Abstract)
class ARCINVENTORY_API UArcItemGenerator_SimpleRandom : public UArcItemGenerator
{
	GENERATED_BODY()
public:

	UArcItemGenerator_SimpleRandom(const FObjectInitializer& ObjectInitializer);
	

	//Tag Query for picking up any item definition and generating this item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	FGameplayTagQuery ItemTagQuery;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	TArray< FArcItemGenerator_RaritySelector> RarityTable;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
		bool bRequireUniqueModifiers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	TArray<FArcItemGenerator_DynamicModifier> WeightedPossibleModifiers;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Perks")
		bool bRequireUniquePerks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Perks")
	TArray<FArcItemGenerator_PerkSelector> WeightedPossiblePerks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced, Category = "Perks")
	UArcItemGenerator* DynamicPerkItemGenerator;
																   	
		
	virtual UArcItemStack* GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context) override;

protected:
	
		  
};


USTRUCT(BlueprintType)
struct FArcItemGenerator_GeneratorSelector
{
	GENERATED_USTRUCT_BODY()
public:
	FArcItemGenerator_GeneratorSelector()
	{
		ItemGen = nullptr;
		Weight = 1;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", Instanced)
	UArcItemGenerator* ItemGen;
		   			 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int32 Weight;
};

UCLASS(EditInlineNew)
class ARCINVENTORY_API UArcItemGenerator_SelectGenerator : public UArcItemGenerator
{
	GENERATED_BODY()
public:
	UArcItemGenerator_SelectGenerator(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TArray<FArcItemGenerator_GeneratorSelector> WeightedGenerators;


	virtual UArcItemStack* GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context) override;

};