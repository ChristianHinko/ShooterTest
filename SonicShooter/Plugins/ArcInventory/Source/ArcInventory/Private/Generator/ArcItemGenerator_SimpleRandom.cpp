// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "Generators/ArcItemGenerator_SimpleRandom.h"
#include "Engine/AssetManager.h"

#include "ArcInventory.h"
#include "Perks/ArcItemStack_Perk.h"

template <typename WeightedStructType>
void SelectWeightedItems(const TArray<WeightedStructType>& WeightedRarities, int32 NumberToSelect, bool bSelectUnique, TArray< WeightedStructType>& OutSelections);

template <typename WeightedStructType>
WeightedStructType SelectSingleWeightedItem(const TArray<WeightedStructType>& WeightedRarities);


UArcItemGenerator_SimpleRandom::UArcItemGenerator_SimpleRandom(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bRequireUniqueModifiers = true;
	bRequireUniquePerks = true;	
}

UArcItemStack* UArcItemGenerator_SimpleRandom::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	if (ItemTagQuery.IsEmpty())
	{
		return nullptr;
	}

	if (RarityTable.Num() == 0)
	{
		return nullptr;
	}

	//Query some item definitions to use, we'll just select one
	
	TArray<TSubclassOf<UArcItemDefinition_New>> ItemDefs;
	if (!UArcItemBPFunctionLibrary::QueryMatchingItemDefinitions(ItemTagQuery, ItemDefs))
	{
		return nullptr;
	}

	//Ensure that we have item defs.  If we don't catch this (but return nullptr, because that is "safe")
	if (!ensure(ItemDefs.Num() > 0))
	{		
		return nullptr;
	}
	
	TSubclassOf<UArcItemDefinition_New> ItemDef = ItemDefs[FMath::RandRange(0, ItemDefs.Num() - 1)];

	if (!IsValid(ItemDef))
	{
		return nullptr;
	}

	//Select the Rarity	
	FArcItemGenerator_RaritySelector RarityEntry = SelectSingleWeightedItem(RarityTable);


	TArray<UArcItemRarity*> Rarieties;
	if (!UArcItemBPFunctionLibrary::QueryMatchingItemRarities(RarityEntry.RarityTagQuery, Rarieties))
	{
		UE_LOG(LogInventory, Warning, TEXT("UArcItemGenerator_SimpleRandom::GenerateItemStack Tried to query for item rarities but found none"));
		//return nullptr;
	}

	UArcItemRarity* Rarity = nullptr;
	if (Rarieties.Num() > 0)
	{
		Rarity = Rarieties[FMath::RandRange(0, Rarieties.Num() - 1)];
	}
		

	UArcItemStack* ItemStack = CreateNewItemStack(ItemDef, Rarity);

	//Create the Dynamic Modifier Perk, and apply dynamic modifiers to this
	if (RarityEntry.NumberOfModifiers > 0 && IsValid(DynamicPerkItemGenerator))
	{
		TArray< FArcItemGenerator_DynamicModifier> SelectedMods;
		SelectWeightedItems(WeightedPossibleModifiers, RarityEntry.NumberOfModifiers, bRequireUniqueModifiers, SelectedMods);

		if (UArcItemStack_Perk* Perk = Cast<UArcItemStack_Perk>(DynamicPerkItemGenerator->GenerateItemStack(Context)))
		{
			for (FArcItemGenerator_DynamicModifier& DynamicMod : SelectedMods)
			{
				FArcPerkModifierData ModifierData;
					ModifierData.Attribute = DynamicMod.Attribute;
					ModifierData.SlotApplicationRequirement = DynamicMod.SlotApplicationRequirement;
					ModifierData.ModifierOp = DynamicMod.ModifierOp;
					ModifierData.Value = FMath::RandRange(DynamicMod.MinValue, DynamicMod.MaxValue);

					Perk->Modifiers.Add(ModifierData);
			}

			//TODO: 
			//Perk->OnGenerated(Context);

			ItemStack->AddSubItemStack(Perk);
		}
	}

	if (RarityEntry.NumberOfPerks > 0)
	{
		TArray< FArcItemGenerator_PerkSelector> SelectedPerks;
		SelectWeightedItems(WeightedPossiblePerks, RarityEntry.NumberOfPerks, bRequireUniquePerks, SelectedPerks);
		for (FArcItemGenerator_PerkSelector& SelectedPerk : SelectedPerks)
		{
			TArray<UArcItemGenerator*> PerkGenerators;
			if (!UArcItemBPFunctionLibrary::QueryMatchingItemGenerators(SelectedPerk.PerkTagQuery, PerkGenerators))
			{
				continue;
			}

			UArcItemGenerator* PerkGenerator = PerkGenerators[FMath::RandRange(0, PerkGenerators.Num() - 1)];
			if (!IsValid(PerkGenerator))
			{
				continue;
			}

			UArcItemStack* PerkInstance = PerkGenerator->GenerateItemStack(Context);
			//TODO:
			//PerkInstance->OnGenerated(Context);
			ItemStack->AddSubItemStack(PerkInstance);
		}
	}
				 	
	return ItemStack;
}


UArcItemGenerator_SelectGenerator::UArcItemGenerator_SelectGenerator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UArcItemStack* UArcItemGenerator_SelectGenerator::GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context)
{
	if (WeightedGenerators.Num() == 0)
	{
		return nullptr;
	}

	FArcItemGenerator_GeneratorSelector Generator = SelectSingleWeightedItem(WeightedGenerators);

	if (!IsValid(Generator.ItemGen))
	{
		return nullptr;
	}
	
	return Generator.ItemGen->GenerateItemStack(Context);
}


template <typename WeightedStructType>
WeightedStructType* PickWeightedItem(const TArray<WeightedStructType>& WeightedRarities, int32 SumOfWeights);

template <typename WeightedStructType>
void SelectWeightedItems(const TArray<WeightedStructType>& WeightedRarities, int32 NumberToSelect, bool bSelectUnique, TArray< WeightedStructType>& OutSelections)
{
	//If we have no weighted rarities, then we can't really do anything here
	if (WeightedRarities.Num() == 0)
	{
		return;
	}

	//Get the sum of all weights. 
	int32 SumOfWeights = 0;
	for (const WeightedStructType& Entry : WeightedRarities)
	{
		SumOfWeights += Entry.Weight;
	}

	 //Try to select a number of items from the weighted list
	TArray<WeightedStructType*> PossibleSelection;

	for (int32 i = 0; i < NumberToSelect; i++)
	{
		int32 Tries = 0;
		WeightedStructType* GrabbedStruct = nullptr;
		do 
		{
			GrabbedStruct = PickWeightedItem(WeightedRarities, SumOfWeights);

			//If we have to pick a unique entry here, check to see if we've already grabbed it.  If we have, null out and use up a try
			if (bSelectUnique && PossibleSelection.Contains(GrabbedStruct))
			{
				GrabbedStruct = nullptr;
			}

		} while (GrabbedStruct == nullptr || ++Tries > 10); //Just give up after 10 tries.  We'll just skip adding this to the array		
		
		if (GrabbedStruct != nullptr)
		{
			PossibleSelection.Add(GrabbedStruct);
		}  		
	}

	for (WeightedStructType* Selection : PossibleSelection)
	{
		OutSelections.Add(*Selection);
	}
}



template <typename WeightedStructType>
WeightedStructType SelectSingleWeightedItem(const TArray<WeightedStructType>& WeightedRarities)
{
	if (!ensure(WeightedRarities.Num() != 0))
	{
		return WeightedStructType();
	}

	int32 SumOfWeights = 0;
	for (const WeightedStructType& Entry : WeightedRarities)
	{
		SumOfWeights += Entry.Weight;
	}

	WeightedStructType* Selected =  PickWeightedItem(WeightedRarities, SumOfWeights);

	if (Selected != nullptr)
	{
		return *Selected;
	}

	//If we don't find a rarity above, just grab the first element of the array
	return WeightedRarities[0];

}

template <typename WeightedStructType>
WeightedStructType* PickWeightedItem(const TArray<WeightedStructType>& WeightedRarities, int32 SumOfWeights)
{
	int32 RandomRoll = FMath::RandRange(0, SumOfWeights);

	for (const WeightedStructType& Struct : WeightedRarities)
	{
		if (RandomRoll < Struct.Weight)
		{
			return const_cast<WeightedStructType*>(&Struct);
		}
		RandomRoll -= Struct.Weight;
	}

	return nullptr;
}

