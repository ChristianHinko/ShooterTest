// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Types/STGameplayAbilityTypes.h"

#include "Character/STCharacter.h"
#include "Player/STPlayerController.h"
#include "Player/STPlayerState.h"
#include "Character/STCharacterMovementComponent.h"



void FSTGameplayAbilityActorInfo::InitFromActor(AActor* InOwnerActor, AActor* InAvatarActor, UAbilitySystemComponent* InAbilitySystemComponent)
{
    Super::InitFromActor(InOwnerActor, InAvatarActor, InAbilitySystemComponent);

    // Get our STCharacter
    STCharacter = Cast<ASTCharacter>(InAvatarActor);

    // Get our PC and PS
    if (PlayerController.IsValid())
    {
        STPlayerController = Cast<ASTPlayerController>(PlayerController.Get());
        STPlayerState = PlayerController->GetPlayerState<ASTPlayerState>();
    }
    else
    {
        STPlayerController = nullptr;
        STPlayerState = nullptr;
    }

    // Get our CMC
    if (STCharacter.IsValid())
    {
        STCharacterMovementComponent = STCharacter->GetSTCharacterMovementComponent();
    }
    else
    {
        STCharacterMovementComponent = nullptr;
    }
}

void FSTGameplayAbilityActorInfo::ClearActorInfo()
{
    Super::ClearActorInfo();

    STCharacter = nullptr;
    STPlayerController = nullptr;
    STPlayerState = nullptr;
    STCharacterMovementComponent = nullptr;
}



////////////////////////////////////////////////////////////////
/// FSTGameplayAbilityActorInfo_Shooter
////////////////////////////////////////////////////////////////


#include "AbilitySystem/AbilitySystemComponents/STAbilitySystemComponent_Shooter.h"
#include "Character/STCharacter_Shooter.h"
#include "ArcInventoryComponent.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Modular/ArcInventoryComponent_Modular.h"



void FSTGameplayAbilityActorInfo_Shooter::InitFromActor(AActor* InOwnerActor, AActor* InAvatarActor, UAbilitySystemComponent* InAbilitySystemComponent)
{
    Super::InitFromActor(InOwnerActor, InAvatarActor, InAbilitySystemComponent);

    // Get our Shooter ASC
    ShooterAbilitySystemComponent = Cast<USTAbilitySystemComponent_Shooter>(ASSAbilitySystemComponent);

    // Get our Shooter Character
    ShooterCharacter = Cast<ASTCharacter_Shooter>(InAvatarActor);

    // Get our Inventory
    if (IsValid(InAvatarActor))
    {
        InventoryComponent = Cast<UArcInventoryComponent_Modular>(UArcItemBPFunctionLibrary::GetInventoryComponent(InAvatarActor, true));
    }
    else
    {
        InventoryComponent = nullptr;
    }
}

void FSTGameplayAbilityActorInfo_Shooter::ClearActorInfo()
{
    Super::ClearActorInfo();

    ShooterAbilitySystemComponent = nullptr;
    ShooterCharacter = nullptr;
    InventoryComponent = nullptr;
}
