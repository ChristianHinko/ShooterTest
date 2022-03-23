// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"

#include "Character/SSCharacter.h"
#include "Player/SSPlayerController.h"
#include "Player/SSPlayerState.h"
#include "Character/SSCharacterMovementComponent.h"
#include "ArcItemBPFunctionLibrary.h"



FSSGameplayAbilityActorInfo::FSSGameplayAbilityActorInfo()
{

}


void FSSGameplayAbilityActorInfo::ASSInitFromActor(AActor* InOwnerActor, AActor* InAvatarActor, UAbilitySystemComponent* InAbilitySystemComponent)
{
    Super::ASSInitFromActor(InOwnerActor, InAvatarActor, InAbilitySystemComponent);

    // Get our SSCharacter
    SSCharacter = Cast<ASSCharacter>(InAvatarActor);

    // Get our PC and PS
    if (PlayerController.IsValid())
    {
        SSPlayerController = Cast<ASSPlayerController>(PlayerController.Get());
        SSPlayerState = PlayerController->GetPlayerState<ASSPlayerState>();
    }

    // Get our CMC
    if (SSCharacter.IsValid())
    {
        SSCharacterMovementComponent = SSCharacter->GetSSCharacterMovementComponent();
    }
}

void FSSGameplayAbilityActorInfo::SetAvatarActor(AActor* InAvatarActor)
{
    Super::SetAvatarActor(InAvatarActor);


}

void FSSGameplayAbilityActorInfo::ClearActorInfo()
{
    Super::ClearActorInfo();

    SSCharacter = nullptr;
    SSPlayerController = nullptr;
    SSPlayerState = nullptr;
    SSCharacterMovementComponent = nullptr;
}



////////////////////////////////////////////////////////////////
/// FGAAI_Shooter
////////////////////////////////////////////////////////////////


#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"
#include "Character/C_Shooter.h"
#include "Inventory/SSArcInventoryComponent_Active.h"



FGAAI_Shooter::FGAAI_Shooter()
{

}


void FGAAI_Shooter::ASSInitFromActor(AActor* InOwnerActor, AActor* InAvatarActor, UAbilitySystemComponent* InAbilitySystemComponent)
{
    Super::ASSInitFromActor(InOwnerActor, InAvatarActor, InAbilitySystemComponent);

    // Get our Shooter ASC
    ShooterAbilitySystemComponent = Cast<UASC_Shooter>(ASSAbilitySystemComponent);

    // Get our Shooter Character
    ShooterCharacter = Cast<AC_Shooter>(InAvatarActor);

    // Get our Inventory
    InventoryComponent = Cast<USSArcInventoryComponent_Active>(UArcItemBPFunctionLibrary::GetInventoryComponent(InAvatarActor, true));
}

void FGAAI_Shooter::SetAvatarActor(AActor* InAvatarActor)
{
    Super::SetAvatarActor(InAvatarActor);


}

void FGAAI_Shooter::ClearActorInfo()
{
    Super::ClearActorInfo();


    ShooterAbilitySystemComponent = nullptr;
    ShooterCharacter = nullptr;
    InventoryComponent = nullptr;
}
