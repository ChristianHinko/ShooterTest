// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/STGameMode_Shooter.h"

#include "Player/STPlayerState_Shooter.h"
#include "UI/STHUD_Shooter.h"
#include "Character/STCharacter_Shooter.h"
#include "Generators/ArcItemGenerator.h"
#include "Inventory/AIEInventoryComponent_Active.h"
#include "Subobjects/ASSActorComponent_AbilitySystemSetup.h"
#include "ArcItemBPFunctionLibrary.h"



ASTGameMode_Shooter::ASTGameMode_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerStateClass = ASTPlayerState_Shooter::StaticClass();
	HUDClass = ASTHUD_Shooter::StaticClass();
	DefaultPawnClass = ASTCharacter_Shooter::StaticClass();
}


void ASTGameMode_Shooter::SetPlayerDefaults(APawn* PlayerPawn)
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
				UE_LOG(LogSTShooterGameMode, Error, TEXT("%s() failed to call GiveInventoryStartupItems() because Pawn's ability system setup component hasn't yet been initialized"), ANSI_TO_TCHAR(__FUNCTION__));
			}
		}
		else
		{
			// Edge case: No setup component - just assume he is ready to recieve the startup items
			AIEInventoryComponentActive->GiveInventoryStartupItems();
		}
	}
}