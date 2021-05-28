// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GM_Shooter.h"

#include "Character/ShooterCharacter.h"
#include "ArcInventory\Public\ArcInventoryComponent.h"
#include "Generators/ArcItemGenerator_Unique.h"
#include "Utilities/LogCategories.h"
#include "Inventory\SSArcInventoryComponent_Active.h"



AGM_Shooter::AGM_Shooter()
{

}


APawn* AGM_Shooter::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	APawn* Pawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);

	// Does this new pawn have an inventory component?
	if (UActorComponent* InventoryComponentFound = Pawn->GetComponentByClass(UArcInventoryComponent::StaticClass()))
	{
		if (UArcInventoryComponent* Inventory = Cast<UArcInventoryComponent>(InventoryComponentFound))
		{
			if (AAbilitySystemCharacter* AbilitySystemCharacter = Cast<AAbilitySystemCharacter>(Pawn))
			{
				// Wait until they have they ability system set up
				AbilitySystemCharacter->SetupWithAbilitySystemCompleted.AddUObject(this, &AGM_Shooter::GiveInventoryStartupItems, Inventory);
			}
			else
			{
				// Unlikely that it would reach here
				GiveInventoryStartupItems(Inventory);
			}
		}
	}





	return Pawn;
}

void AGM_Shooter::GiveInventoryStartupItems(UArcInventoryComponent* Inventory)
{
	USSArcInventoryComponent_Active* SSArcInventoryCompActive = Cast<USSArcInventoryComponent_Active>(Inventory);	// See if we are a USSArcInventoryComponent_Active so we can do extra logic on that specific type

	// Loop through the SlotDefinitions we filled out in the inventory component's BP for this pawn so we can access the information of what item we should put in each slot
	// We loop through them backwards since we call USSArcInventoryComponent_Active::AddToActiveItemHistory every iteration
	for (int32 i = Inventory->CustomInventorySlots.Num() - 1; i >= 0; --i)
	{
		//	Get the item generator the SlotDefinition specifies
		if (UArcItemGenerator_Unique* CurrentItemGenerator = Inventory->CustomInventorySlots[i].SlotStartupItem.GetDefaultObject())
		{
			//	Generate the item
			UArcItemStack* GeneratedItem = CurrentItemGenerator->GenerateItemStack(FArcItemGeneratorContext());

			// Equip the generated item
			if (GeneratedItem)
			{
				FArcInventoryItemSlotReference SlotToAddItemTo;
				if (Inventory->GetSlotReferenceByIndex(i, SlotToAddItemTo))
				{
					Inventory->PlaceItemIntoSlot(GeneratedItem, SlotToAddItemTo);

					// Now we want to fill our active item history array if we have it
					if (SSArcInventoryCompActive)
					{
						SSArcInventoryCompActive->AddToActiveItemHistory(SlotToAddItemTo);

						if (i == 0)
						{
							// This is a good time to sync the client's history array with the server's for the first time
							MARK_PROPERTY_DIRTY_FROM_NAME(USSArcInventoryComponent_Active, ActiveItemHistory, SSArcInventoryCompActive);
						}
					}
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
