// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SSGameplayAbilityTypes.h"

#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "Character/AbilitySystemCharacter.h"
#include "Player/SSPlayerController.h"
#include "Player/SSPlayerState.h"
#include "Character/SSCharacterMovementComponent.h"



FSSGameplayAbilityActorInfo::FSSGameplayAbilityActorInfo()
{

}


void FSSGameplayAbilityActorInfo::InitFromActor(AActor* InOwnerActor, AActor* InAvatarActor, UAbilitySystemComponent* InAbilitySystemComponent)
{
	Super::InitFromActor(InOwnerActor, InAvatarActor, InAbilitySystemComponent);

    // Get our ASC
    SSAbilitySystemComponent = Cast<USSAbilitySystemComponent>(InAbilitySystemComponent);

    // Get our AbilitySystemCharacter
    AbilitySystemCharacter = Cast<AAbilitySystemCharacter>(InAvatarActor);

    // Get our PC and PS
    if (PlayerController.IsValid())
    {
        SSPlayerController = Cast<ASSPlayerController>(PlayerController.Get());
        SSPlayerState = PlayerController->GetPlayerState<ASSPlayerState>();
    }

    // Get our CMC
    if (ASSCharacter* SSCharacter = Cast<ASSCharacter>(InAvatarActor))
    {
        SSCharacterMovementComponent = SSCharacter->GetSSCharacterMovementComponent();
    }


    //OnInited.Broadcast();
}

void FSSGameplayAbilityActorInfo::SetAvatarActor(AActor* InAvatarActor)
{
    Super::SetAvatarActor(InAvatarActor);


}

void FSSGameplayAbilityActorInfo::ClearActorInfo()
{
    Super::ClearActorInfo();


    SSAbilitySystemComponent = nullptr;
    SSPlayerController = nullptr;
    SSPlayerState = nullptr;
    AbilitySystemCharacter = nullptr;
    SSCharacterMovementComponent = nullptr;
}



////////////////////////////////////////////////////////////////
/// FGAAI_Shooter
////////////////////////////////////////////////////////////////


#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"
#include "Character/ShooterCharacter.h"
#include "Inventory/SSArcInventoryComponent_Active.h"



FGAAI_Shooter::FGAAI_Shooter()
{

}


void FGAAI_Shooter::InitFromActor(AActor* InOwnerActor, AActor* InAvatarActor, UAbilitySystemComponent* InAbilitySystemComponent)
{
    Super::InitFromActor(InOwnerActor, InAvatarActor, InAbilitySystemComponent);


    // Get our Shooter ASC
    ShooterAbilitySystemComponent = Cast<UASC_Shooter>(SSAbilitySystemComponent);

    // Get our Shooter Character
    ShooterCharacter = Cast<AShooterCharacter>(InAvatarActor);

    // Get our Inventory

    //if (ShooterCharacter.IsValid())
    //{
    //    InventoryComponent = ShooterCharacter->GetInventoryComponent();
    //}
    InventoryComponent = Cast<USSArcInventoryComponent_Active>(InAvatarActor->GetComponentByClass(USSArcInventoryComponent_Active::StaticClass()));


    OnInited.Broadcast();
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
