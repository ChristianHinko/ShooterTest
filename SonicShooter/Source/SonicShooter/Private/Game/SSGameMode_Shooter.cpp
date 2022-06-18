// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SSGameMode_Shooter.h"

#include "Player/SSPlayerState_Shooter.h"
#include "UI/SSHUD_Shooter.h"
#include "Character/SSCharacter_Shooter.h"
#include "ArcInventoryComponent.h"
#include "Generators/ArcItemGenerator.h"
#include "Inventory/AIEInventoryComponent_Active.h"
#include "Subobjects/ASSActorComponent_AbilitySystemSetup.h"
#include "ArcItemBPFunctionLibrary.h"



ASSGameMode_Shooter::ASSGameMode_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerStateClass = ASSPlayerState_Shooter::StaticClass();
	HUDClass = ASSHUD_Shooter::StaticClass();
	DefaultPawnClass = ASSCharacter_Shooter::StaticClass();
}


void ASSGameMode_Shooter::SetPlayerDefaults(APawn* PlayerPawn)
{
	Super::SetPlayerDefaults(PlayerPawn);

	// Try to give startup items
	UArcInventoryComponent* Inventory = UArcItemBPFunctionLibrary::GetInventoryComponent(PlayerPawn, true);
	if (IsValid(Inventory))
	{
		UASSActorComponent_AbilitySystemSetup* AbilitySystemSetupComponent = PlayerPawn->FindComponentByClass<UASSActorComponent_AbilitySystemSetup>();
		if (IsValid(AbilitySystemSetupComponent))
		{
			if (AbilitySystemSetupComponent->IsInitializedWithASC())
			{
				// The Pawn is ready to recieve the startup items
				GiveInventoryStartupItems(Inventory);
			}
			else
			{
				// Wait for his ASC to be initialized
				AbilitySystemSetupComponent->OnInitializeAbilitySystemComponentDelegate.AddUObject(this, &ASSGameMode_Shooter::OnInitializeAbilitySystemComponent, Inventory);
			}
		}
		else
		{
			// Edge case: No setup component - just assume he is ready to recieve the startup items
			GiveInventoryStartupItems(Inventory);
		}
	}
}

void ASSGameMode_Shooter::OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC, UArcInventoryComponent* Inventory)
{
	GiveInventoryStartupItems(Inventory);
}

void ASSGameMode_Shooter::GiveInventoryStartupItems(UArcInventoryComponent* Inventory)
{
	UAIEInventoryComponent_Active* AIEInventoryComponentActive = Cast<UAIEInventoryComponent_Active>(Inventory);
	if (IsValid(AIEInventoryComponentActive))
	{
		// Loop through our Starting Items
		for (const FArcStartingItemEntry& StartingItem : AIEInventoryComponentActive->StartingItems)
		{
			const FArcInventoryItemSlotReference& SlotToPutItemIn = AIEInventoryComponentActive->Query_GetFirstSlot(FArcInventoryQuery::QueryForSlot(StartingItem.SlotQuery));
			if (AIEInventoryComponentActive->IsValidItemSlot(SlotToPutItemIn))
			{
				// Try to generate Item
				if (IsValid(StartingItem.ItemGenerator))
				{
					UArcItemStack* GeneratedItemStack = StartingItem.ItemGenerator->GenerateItemStack(FArcItemGeneratorContext());

					// Try to equip Item
					const bool bSuccess = AIEInventoryComponentActive->PlaceItemIntoSlot(GeneratedItemStack, SlotToPutItemIn);
					if (!bSuccess)
					{
						UE_LOG(LogSSInventoryComponent, Warning, TEXT("Failed to place a starting Item into specified slot. We will just call LootItem() to give the Item instead (may be put in wrong slot)"));
						AIEInventoryComponentActive->LootItem(GeneratedItemStack);
					}
				}
			}
		}
	}
}
