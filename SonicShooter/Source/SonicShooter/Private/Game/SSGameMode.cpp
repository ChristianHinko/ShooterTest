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
#include "Inventory/SSArcinventoryComponent_Active.h"

APawn* ASSGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	APawn* Pawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);

	if (AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(Pawn))
	{
		if (UArcInventoryComponent* Inventory = ShooterCharacter->GetInventoryComponent())
		{
			// For each item generator
			for (int32 i = ShooterCharacter->ItemsToLootOnStartup.Num()-1; i >= 0; i--)
			{
				TSubclassOf<UArcItemGenerator_Unique> ItemGeneratorTSub = ShooterCharacter->ItemsToLootOnStartup[i];
				// Get this generator
				UArcItemGenerator_Unique* ItemGenerator = ItemGeneratorTSub.GetDefaultObject();
				FArcItemGeneratorContext GeneratorContext;

				// Generate the item
				UArcItemStack* ItemStack = ItemGenerator->GenerateItemStack(GeneratorContext);

				// Loot the newly generated item
				FArcInventoryItemSlotReference SlotRefToPlaceIn = FArcInventoryItemSlotReference(i, Inventory);		// Currently we are handling making Arc Inventory not make active the items we populate the inventory with by using the contructor that doesn't pass in the FArcInventoryItemSlot. Not having the FArcInventoryItemSlot passed through makes the system not able to tell if the item you "equiped" is an active item or not, since the slot tags from FArcInventoryItemSlot isn't stored. Because of this it doesn't bother setting it active (which is what we want, but this is not the right way to do it). By default Arc Inventory just sets the active item active when you loot it if you don't currently have an active item active. And by default, if you unequip a curently active item, it will move you to the next available active item instead of leaving you with nothing active. These things aren't configurable and it's annoying, however the method that does these things is overidable UArcInventoryComponent_Active::OnItemEquipped()
				Inventory->PlaceItemIntoSlot(ItemStack, SlotRefToPlaceIn);
			}

		}
	}

	return Pawn;
}
