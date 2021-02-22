// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SSGameMode.h"

#include "Character/ShooterCharacter.h"
#include "ArcInventory\Public\ArcInventoryComponent.h"
#include "Generators/ArcItemGenerator_Unique.h"
#include "Utilities/LogCategories.h"


ASSGameMode::ASSGameMode()
{
	bUseSeamlessTravel = true;
}




APawn* ASSGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	APawn* Pawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);

	// Does this new pawn have an inventory component?
	if (UActorComponent* FoundActorComponent = Pawn->GetComponentByClass(UArcInventoryComponent::StaticClass()))
	{
		if (UArcInventoryComponent* Inventory = Cast<UArcInventoryComponent>(FoundActorComponent))
		{
			GiveInventoryStartupLoadout(Inventory);
		}
	}







	return Pawn;
}

void ASSGameMode::GiveInventoryStartupLoadout(UArcInventoryComponent* NewInventory)
{
	// Loop through the SlotDefinitions we filled out in the inventory component's BP for this pawn so we can access the information of what item we should put in each slot
	for (int i = 0; i < NewInventory->CustomInventorySlots.Num(); i++)
	{
		//	Get the item generator the SlotDefinition specifies
		if (UArcItemGenerator_Unique* CurrentItemGenerator = NewInventory->CustomInventorySlots[i].SlotStartupItem.GetDefaultObject())
		{
			//	Generate the item
			UArcItemStack* GeneratedItem = CurrentItemGenerator->GenerateItemStack(FArcItemGeneratorContext());

			// Equip the generated item
			if (GeneratedItem)
			{
				FArcInventoryItemSlotReference SlotToAddItemTo;
				if (NewInventory->GetSlotReferenceByIndex(i, SlotToAddItemTo))
				{
					NewInventory->PlaceItemIntoSlot(GeneratedItem, SlotToAddItemTo);
				}
				else
				{
					UE_LOG(LogArcInventorySetup, Error, TEXT("%s() Could not place starting item into slot because CustomInventorySlots[i] did not match to an actual slot reference. (This should like never happen since the inventory slots are generated from this CustomInventorySlots array)"), *FString(__FUNCTION__), *GetName());
				}
			}
			else
			{
				UE_LOG(LogArcInventorySetup, Error, TEXT("%s() GeneratedItem was NULL. We tried to give the new newly spawned pawn a starting item for a certain slot, but did not generate corectly."), *FString(__FUNCTION__), *GetName());
			}
		}
	}
}


