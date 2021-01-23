// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SSGameMode.h"

#include "Character/ShooterCharacter.h"
#include "ArcInventoryComponent.h"
#include "Generators/ArcItemGenerator_Unique.h"



ASSGameMode::ASSGameMode()
{
	bUseSeamlessTravel = true;
}


#include "Components/ArcInventoryComponent_Active.h"
APawn* ASSGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	APawn* Pawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);

	if (AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(Pawn))
	{
		if (UArcInventoryComponent* Inventory = ShooterCharacter->GetInventoryComponent())
		{
			// For each item generator
			for (int i = 0; i < ShooterCharacter->ItemsToLootOnStartup.Num(); i++)
			{
				TSubclassOf<UArcItemGenerator_Unique> ItemGeneratorTSub = ShooterCharacter->ItemsToLootOnStartup[i];
				// Get this generator
				UArcItemGenerator_Unique* ItemGenerator = ItemGeneratorTSub.GetDefaultObject();
				FArcItemGeneratorContext GeneratorContext;

				// Generate the item
				UArcItemStack* ItemStack = ItemGenerator->GenerateItemStack(GeneratorContext);

				// Loot the newly generated item
				FArcInventoryItemSlotReference SlotAddedTo;
				Inventory->LootItemAndOutSlotRef(ItemStack, SlotAddedTo);
				//if (UArcInventoryComponent_Active* a = Cast<UArcInventoryComponent_Active>(ShooterCharacter->GetInventoryComponent()))
				//{
				//	a->SwapActiveItems(SlotAddedTo.SlotId);
				//}
			}

		}
	}

	return Pawn;
}
