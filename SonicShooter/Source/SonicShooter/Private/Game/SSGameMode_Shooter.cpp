// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SSGameMode_Shooter.h"

#include "Player/SSPlayerState_Shooter.h"
#include "UI/SSHUD_Shooter.h"
#include "Character/SSCharacter_Shooter.h"
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
	UAIEInventoryComponent_Active* AIEInventoryComponentActive = Cast<UAIEInventoryComponent_Active>(UArcItemBPFunctionLibrary::GetInventoryComponent(PlayerPawn, true));
	if (IsValid(AIEInventoryComponentActive))
	{
		UASSActorComponent_AbilitySystemSetup* AbilitySystemSetupComponent = PlayerPawn->FindComponentByClass<UASSActorComponent_AbilitySystemSetup>();
		if (IsValid(AbilitySystemSetupComponent))
		{
			if (AbilitySystemSetupComponent->IsInitializedWithASC())
			{
				// The Pawn is ready to recieve the startup items
				AIEInventoryComponentActive->GiveInventoryStartupItems();
			}
			else
			{
				UE_LOG(LogSSShooterGameMode, Error, TEXT("%s() failed to call GiveInventoryStartupItems() because Pawn's ability system setup component hasn't yet been initialized"), ANSI_TO_TCHAR(__FUNCTION__));
			}
		}
		else
		{
			// Edge case: No setup component - just assume he is ready to recieve the startup items
			AIEInventoryComponentActive->GiveInventoryStartupItems();
		}
	}
}
