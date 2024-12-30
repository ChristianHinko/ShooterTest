// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Types/STGameplayAbilityTypes.h"

#include "Character/STCharacter.h"
#include "Player/STPlayerController.h"
#include "Player/STPlayerState.h"
#include "Character/STCharacterMovementComponent.h"

void FSTGameplayAbilityActorInfo::InitFromActor(
    AActor* inOwnerActor,
    AActor* inAvatarActor,
    UAbilitySystemComponent* inAbilitySystemComponent)
{
    Super::InitFromActor(inOwnerActor, inAvatarActor, inAbilitySystemComponent);

    STCharacter = Cast<ASTCharacter>(inAvatarActor);

    if (APlayerController* playerController = PlayerController.Get())
    {
        STPlayerController = Cast<ASTPlayerController>(playerController);
        STPlayerState = playerController->GetPlayerState<ASTPlayerState>();
    }
    else
    {
        STPlayerController = nullptr;
        STPlayerState = nullptr;
    }

    if (inAvatarActor)
    {
        STCharacterMovementComponent = inAvatarActor->FindComponentByClass<USTCharacterMovementComponent>();
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

void FSTGameplayAbilityActorInfo_Shooter::InitFromActor(
    AActor* inOwnerActor,
    AActor* inAvatarActor,
    UAbilitySystemComponent* inAbilitySystemComponent)
{
    Super::InitFromActor(inOwnerActor, inAvatarActor, inAbilitySystemComponent);

    // Get our Shooter ASC
    ShooterAbilitySystemComponent = Cast<USTAbilitySystemComponent_Shooter>(inAbilitySystemComponent);

    // Get our Shooter Character
    ShooterCharacter = Cast<ASTCharacter_Shooter>(inAvatarActor);

    // Get our Inventory
    if (inAvatarActor)
    {
        constexpr bool shouldAllowSearchComponents = true;
        InventoryComponent =
            Cast<UArcInventoryComponent_Modular>(
                UArcItemBPFunctionLibrary::GetInventoryComponent(inAvatarActor, shouldAllowSearchComponents));
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
