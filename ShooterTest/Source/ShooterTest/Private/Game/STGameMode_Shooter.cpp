// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/STGameMode_Shooter.h"

#include "Player/STPlayerState_Shooter.h"
#include "UI/STHUD_Shooter.h"
#include "Character/STCharacter_Shooter.h"
#include "Generators/ArcItemGenerator.h"
#include "Inventory/AIEInventoryProcessor_Active.h"
#include "Modular/ArcInventoryComponent_Modular.h"
#include "Subobjects/ASSActorComponent_AvatarActorExtension.h"
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
    const UArcInventoryComponent_Modular* AIEInventoryComponentModular = Cast<UArcInventoryComponent_Modular>(UArcItemBPFunctionLibrary::GetInventoryComponent(PlayerPawn, true));
    if (IsValid(AIEInventoryComponentModular))
    {
        UAIEInventoryProcessor_Active* AIEInventoryProcessorActive = AIEInventoryComponentModular->FindFirstProcessor<UAIEInventoryProcessor_Active>();
        if (IsValid(AIEInventoryProcessorActive))
        {
            UASSActorComponent_AvatarActorExtension* AvatarActorExtensionComponent = PlayerPawn->FindComponentByClass<UASSActorComponent_AvatarActorExtension>();
            if (IsValid(AvatarActorExtensionComponent))
            {
                if (AvatarActorExtensionComponent->IsInitializedWithASC())
                {
                    // The Pawn is ready to recieve the startup items
                    AIEInventoryProcessorActive->GiveInventoryStartupItems();
                }
                else
                {
                    UE_LOG(LogSTShooterGameMode, Error, TEXT("%s() failed to call GiveInventoryStartupItems() because the pawn's avatar actor extension component hasn't yet been initialized"), ANSI_TO_TCHAR(__FUNCTION__));
                }
            }
            else
            {
                // Edge case: No avatar actor extension component - just assume he is ready to recieve the startup items
                AIEInventoryProcessorActive->GiveInventoryStartupItems();
            }
        }
    }
}
