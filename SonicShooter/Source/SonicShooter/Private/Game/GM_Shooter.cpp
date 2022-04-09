// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GM_Shooter.h"

#include "Player/PS_Shooter.h"
#include "UI/HUD_Shooter.h"
#include "Character/C_Shooter.h"
#include "ArcInventoryComponent.h"
#include "Generators/ArcItemGenerator.h"
#include "Utilities/LogCategories.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "Subobjects/AbilitySystemSetupComponent.h"
#include "ArcItemBPFunctionLibrary.h"



AGM_Shooter::AGM_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerStateClass = APS_Shooter::StaticClass();
	HUDClass = AHUD_Shooter::StaticClass();
	DefaultPawnClass = AC_Shooter::StaticClass();
}


APawn* AGM_Shooter::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	APawn* Pawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);


	// Does this new Pawn have an Inventory Component?
	UArcInventoryComponent* Inventory = Cast<UArcInventoryComponent>(UArcItemBPFunctionLibrary::GetInventoryComponent(Pawn, true));
	if (IsValid(Inventory))
	{
		UAbilitySystemSetupComponent* AbilitySystemSetupComponent = Pawn->FindComponentByClass<UAbilitySystemSetupComponent>();
		if (IsValid(AbilitySystemSetupComponent))
		{
			// Wait until they have they ability system set up
			AbilitySystemSetupComponent->OnInitializeAbilitySystemComponentDelegate.AddUObject(this, &AGM_Shooter::OnInitializeAbilitySystemComponent, Inventory);
		}
		else
		{
			// Unlikely that it would reach here
			GiveInventoryStartupItems(Inventory);
		}
	}


	return Pawn;
}

void AGM_Shooter::GiveInventoryStartupItems(UArcInventoryComponent* Inventory)
{
	USSArcInventoryComponent_Active* SSArcInventoryCompActive = Cast<USSArcInventoryComponent_Active>(Inventory);
	if (IsValid(SSArcInventoryCompActive))
	{
		// Loop through our Starting Items
		for (const FArcStartingItemEntry& StartingItem : SSArcInventoryCompActive->StartingItems)
		{
			const FArcInventoryItemSlotReference& SlotToPutItemIn = SSArcInventoryCompActive->Query_GetFirstSlot(FArcInventoryQuery::QueryForSlot(StartingItem.SlotQuery));
			if (SSArcInventoryCompActive->IsValidItemSlot(SlotToPutItemIn))
			{
				// Try to generate Item
				if (IsValid(StartingItem.ItemGenerator))
				{
					UArcItemStack* GeneratedItemStack = StartingItem.ItemGenerator->GenerateItemStack(FArcItemGeneratorContext());
					
					// Try to equip Item
					const bool bSuccess = SSArcInventoryCompActive->PlaceItemIntoSlot(GeneratedItemStack, SlotToPutItemIn);
					if (!bSuccess)
					{
						UE_LOG(LogArcInventorySetup, Warning, TEXT("Failed to place a starting Item into specified slot. We will just call LootItem() to give the Item instead (may be put in wrong slot)"));
						SSArcInventoryCompActive->LootItem(GeneratedItemStack);
					}
				}
			}
		}
	}

}

void AGM_Shooter::OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const PreviousASC, UAbilitySystemComponent* const NewASC, UArcInventoryComponent* Inventory)
{
	GiveInventoryStartupItems(Inventory);
}
