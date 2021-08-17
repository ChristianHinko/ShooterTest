// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbilityTypes.h"

#include "SSGameplayAbilityTypes.generated.h"


class ASSCharacter;
class ASSPlayerController;
class ASSPlayerState;
class USSCharacterMovementComponent;



/**
 * Our custom GameplayAbilityActorInfo.
 * Put non-game-specific data in here - like base classes and stuff
 */
USTRUCT()
struct SONICSHOOTER_API FSSGameplayAbilityActorInfo : public FASSGameplayAbilityActorInfo
{
    GENERATED_BODY()


    FSSGameplayAbilityActorInfo();
    virtual ~FSSGameplayAbilityActorInfo()
    {

    }

    // Our Character. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSCharacter> SSCharacter;

    // Our PC. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSPlayerController> SSPlayerController;

    // Our PS. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSPlayerState> SSPlayerState;

    // Our CMC. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<USSCharacterMovementComponent> SSCharacterMovementComponent;


    virtual void ASSInitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void SetAvatarActor(AActor* AvatarActor) override;
    virtual void ClearActorInfo() override;

    // Gets the Character. This is often nullptr.
    ASSCharacter* GetSSCharacter() const { return SSCharacter.IsValid() ? SSCharacter.Get() : nullptr; }

    // Gets the PC. This is often nullptr.
    ASSPlayerController* GetSSPlayerController() const { return SSPlayerController.IsValid() ? SSPlayerController.Get() : nullptr; }

    // Gets the PS. This is often nullptr.
    ASSPlayerState* GetSSPlayerState() const { return SSPlayerState.IsValid() ? SSPlayerState.Get() : nullptr; }

    // Gets the CMC. This is often nullptr.
    USSCharacterMovementComponent* GetSSCharacterMovementComponent() const { return SSCharacterMovementComponent.IsValid() ? SSCharacterMovementComponent.Get() : nullptr; }
};



////////////////////////////////////////////////////////////////
/// FGAAI_Shooter
////////////////////////////////////////////////////////////////


class UASC_Shooter;
class AShooterCharacter;
class USSArcInventoryComponent_Active;


/**
 * Our custom GameplayAbilityActorInfo
 */
USTRUCT()
struct SONICSHOOTER_API FGAAI_Shooter : public FSSGameplayAbilityActorInfo
{
    GENERATED_BODY()


    FGAAI_Shooter();
    virtual ~FGAAI_Shooter()
    {

    }

    // Our Shooter specific ASC.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<UASC_Shooter> ShooterAbilitySystemComponent;

    // Our ShooterCharacter. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<AShooterCharacter> ShooterCharacter;

    // Our Inventory Component. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<USSArcInventoryComponent_Active> InventoryComponent;


    virtual void ASSInitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void SetAvatarActor(AActor* AvatarActor) override;
    virtual void ClearActorInfo() override;

    // Gets the ShooterAbilitySystemComponent.
    UASC_Shooter* GetShooterAbilitySystemComponent() const { return ShooterAbilitySystemComponent.IsValid() ? ShooterAbilitySystemComponent.Get() : nullptr; }

    // Gets the ShooterCharacter. This is often nullptr.
    AShooterCharacter* GetShooterCharacter() const { return ShooterCharacter.IsValid() ? ShooterCharacter.Get() : nullptr; }

    // Gets the Inventory Component. This is often nullptr.
    USSArcInventoryComponent_Active* GetInventoryComponent() const { return InventoryComponent.IsValid() ? InventoryComponent.Get() : nullptr; }
};
