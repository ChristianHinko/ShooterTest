// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SSGameMode.h"

#include "Character/ShooterCharacter.h"
#include "Inventory/SSArcinventoryComponent_Active.h"
#include "Generators/ArcItemGenerator_Unique.h"



ASSGameMode::ASSGameMode()
{
	bUseSeamlessTravel = true;
}



APawn* ASSGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	APawn* Pawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);

	if (AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(Pawn))
	{
		if (USSArcInventoryComponent_Active* SSInventory = ShooterCharacter->SSInventoryComponentActive)
		{
			TArray<FArcInventoryItemSlotReference> CharacterInventoryActiveItemSlotRefs;
			if (SSInventory->Query_GetAllSlots(FArcInventoryQuery::QuerySlotMatchingTag(GetDefault<UArcInventoryDeveloperSettings>()->ActiveItemSlotTag), CharacterInventoryActiveItemSlotRefs))
			{
				// Iterating down the list equips our primary item last, which is what we want
				for (int32 i = CharacterInventoryActiveItemSlotRefs.Num() - 1; i >= 0; i--)
				{
					if (ShooterCharacter->ItemsToEquipOnStartup.IsValidIndex(i))
					{
						// Get the generator
						TSubclassOf<UArcItemGenerator_Unique> ItemGeneratorTSub = ShooterCharacter->ItemsToEquipOnStartup[i];
						UArcItemGenerator_Unique* ItemGenerator = ItemGeneratorTSub.GetDefaultObject();

						// Generate the item
						FArcItemGeneratorContext GeneratorContext;
						UArcItemStack* GeneratedItem = ItemGenerator->GenerateItemStack(GeneratorContext);

						// Equip the generated item
						SSInventory->PlaceItemIntoSlot(GeneratedItem, CharacterInventoryActiveItemSlotRefs[i]);
						if (i != 0)	// Only manually add to item history if we aren't equiping the last item. ArcInventoryComponent_Active::BeginPlay() will set active the last item which will in turn add it to the item history by function USSArcInventoryComponent_Active::MakeItemActive_Internal
						{
							SSInventory->AddToItemHistory(CharacterInventoryActiveItemSlotRefs[i]);
						}
					}

				}
			}
		}
	}

	return Pawn;
}
