// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"

#include "Character/SSCharacter.h"
#include "Player/SSPlayerController.h"
#include "Player/SSPlayerState.h"
#include "Character/SSCharacterMovementComponent.h"
#include "ArcItemBPFunctionLibrary.h"



void FSSGameplayAbilityActorInfo::InitFromActor(AActor* InOwnerActor, AActor* InAvatarActor, UAbilitySystemComponent* InAbilitySystemComponent)
{
	Super::InitFromActor(InOwnerActor, InAvatarActor, InAbilitySystemComponent);

	// Get our SSCharacter
	SSCharacter = Cast<ASSCharacter>(InAvatarActor);

	// Get our PC and PS
	if (PlayerController.IsValid())
	{
		SSPlayerController = Cast<ASSPlayerController>(PlayerController.Get());
		SSPlayerState = PlayerController->GetPlayerState<ASSPlayerState>();
	}
	else
	{
		SSPlayerController = nullptr;
		SSPlayerState = nullptr;
	}

	// Get our CMC
	if (SSCharacter.IsValid())
	{
		SSCharacterMovementComponent = SSCharacter->GetSSCharacterMovementComponent();
	}
	else
	{
		SSCharacterMovementComponent = nullptr;
	}
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
/// FSSGameplayAbilityActorInfo_Shooter
////////////////////////////////////////////////////////////////


#include "AbilitySystem/AbilitySystemComponents/SSAbilitySystemComponent_Shooter.h"
#include "Character/SSCharacter_Shooter.h"
#include "Inventory/SSInventoryComponent_Active.h"



void FSSGameplayAbilityActorInfo_Shooter::InitFromActor(AActor* InOwnerActor, AActor* InAvatarActor, UAbilitySystemComponent* InAbilitySystemComponent)
{
	Super::InitFromActor(InOwnerActor, InAvatarActor, InAbilitySystemComponent);

	// Get our Shooter ASC
	ShooterAbilitySystemComponent = Cast<USSAbilitySystemComponent_Shooter>(ASSAbilitySystemComponent);

	// Get our Shooter Character
	ShooterCharacter = Cast<ASSCharacter_Shooter>(InAvatarActor);

	// Get our Inventory
	if (IsValid(InAvatarActor))
	{
		InventoryComponent = Cast<USSInventoryComponent_Active>(UArcItemBPFunctionLibrary::GetInventoryComponent(InAvatarActor, true));
	}
	else
	{
		InventoryComponent = nullptr;
	}
}

void FSSGameplayAbilityActorInfo_Shooter::ClearActorInfo()
{
	Super::ClearActorInfo();

	ShooterAbilitySystemComponent = nullptr;
	ShooterCharacter = nullptr;
	InventoryComponent = nullptr;
}
