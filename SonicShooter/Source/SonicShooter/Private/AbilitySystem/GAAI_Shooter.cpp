// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GAAI_Shooter.h"

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
