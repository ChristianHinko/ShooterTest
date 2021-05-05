// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"

#include "SSGameplayAbilityTypes.generated.h"


class USSAbilitySystemComponent;
class ASSPlayerController;
class ASSPlayerState;
class AShooterCharacter;
class UASC_Shooter;
class USSCharacterMovementComponent;
class USSArcInventoryComponent_Active;



DECLARE_MULTICAST_DELEGATE(FAbilityActorInfoState)


/**
 * Our custom FGameplayAbilityActorInfo
 */
USTRUCT()
struct SONICSHOOTER_API FSSGameplayAbilityActorInfo : public FGameplayAbilityActorInfo
{
	GENERATED_BODY()
    typedef Super FGameplayAbilityActorInfo;


    virtual ~FSSGameplayAbilityActorInfo()
    {

    }

    // Our ASC. Should NEVER be null.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<USSAbilitySystemComponent> SSAbilitySystemComponent;

    // Our PC. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSPlayerController> SSPlayerController;

    // Our PS. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSPlayerState> SSPlayerState;

    // Our ShooterCharacter. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<AShooterCharacter> ShooterCharacter;

    // Our Shooter specific ASC.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<UASC_Shooter> ShooterAbilitySystemComponent;

    // Our CMC. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<USSCharacterMovementComponent> SSCharacterMovementComponent;

    // Our Inventory Component. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<USSArcInventoryComponent_Active> InventoryComponent;


    FAbilityActorInfoState OnInited;

    virtual void InitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void SetAvatarActor(AActor* AvatarActor) override;
    virtual void ClearActorInfo() override;

    // Gets the PC. This is often nullptr.
    ASSPlayerController* GetSSPlayerController() const { return SSPlayerController.IsValid() ? SSPlayerController.Get() : nullptr; }

    // Gets the PS. This is often nullptr.
    ASSPlayerState* GetSSPlayerState() const { return SSPlayerState.IsValid() ? SSPlayerState.Get() : nullptr; }

    // Gets the ShooterCharacter. This is often nullptr.
    AShooterCharacter* GetShooterCharacter() const { return ShooterCharacter.IsValid() ? ShooterCharacter.Get() : nullptr; }

    // Gets the ShooterAbilitySystemComponent.
    UASC_Shooter* GetShooterAbilitySystemComponent() const { return ShooterAbilitySystemComponent.IsValid() ? ShooterAbilitySystemComponent.Get() : nullptr; }

    // Gets the CMC. This is often nullptr.
    USSCharacterMovementComponent* GetSSCharacterMovementComponent() const { return SSCharacterMovementComponent.IsValid() ? SSCharacterMovementComponent.Get() : nullptr; }

    // Gets the Inventory Component. This is often nullptr.
    USSArcInventoryComponent_Active* GetInventoryComponent() const { return InventoryComponent.IsValid() ? InventoryComponent.Get() : nullptr; }
};
