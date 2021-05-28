// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"

#include "SSGameplayAbilityTypes.generated.h"


class USSAbilitySystemComponent;
class ASSPlayerController;
class ASSPlayerState;
class AAbilitySystemCharacter;
class USSCharacterMovementComponent;



DECLARE_MULTICAST_DELEGATE(FAbilityActorInfoState)


/**
 * Our base GameplayAbilityActorInfo.
 * Put non-game-specific data in here - like base classes and stuff
 */
USTRUCT()
struct SONICSHOOTER_API FSSGameplayAbilityActorInfo : public FGameplayAbilityActorInfo
{
	GENERATED_BODY()


    FSSGameplayAbilityActorInfo();
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

    // Our AbilitySystemCharacter. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<AAbilitySystemCharacter> AbilitySystemCharacter;

    // Our CMC. Often nullptr.
    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<USSCharacterMovementComponent> SSCharacterMovementComponent;


    /**
     * Broadcast this at the end of your InitFromActor().
     * The reason this base class can't is because it would be done in the Super call and wouldn't be done after the subclass initialization.
     */
    FAbilityActorInfoState OnInited;

    virtual void InitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void SetAvatarActor(AActor* AvatarActor) override;
    virtual void ClearActorInfo() override;

    // Gets the PC. This is often nullptr.
    ASSPlayerController* GetSSPlayerController() const { return SSPlayerController.IsValid() ? SSPlayerController.Get() : nullptr; }

    // Gets the PS. This is often nullptr.
    ASSPlayerState* GetSSPlayerState() const { return SSPlayerState.IsValid() ? SSPlayerState.Get() : nullptr; }

    // Gets the AbilitySystemCharacter. This is often nullptr.
    AAbilitySystemCharacter* GetAbilitySystemCharacter() const { return AbilitySystemCharacter.IsValid() ? AbilitySystemCharacter.Get() : nullptr; }

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


    virtual void InitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void SetAvatarActor(AActor* AvatarActor) override;
    virtual void ClearActorInfo() override;

    // Gets the ShooterAbilitySystemComponent.
    UASC_Shooter* GetShooterAbilitySystemComponent() const { return ShooterAbilitySystemComponent.IsValid() ? ShooterAbilitySystemComponent.Get() : nullptr; }

    // Gets the ShooterCharacter. This is often nullptr.
    AShooterCharacter* GetShooterCharacter() const { return ShooterCharacter.IsValid() ? ShooterCharacter.Get() : nullptr; }

    // Gets the Inventory Component. This is often nullptr.
    USSArcInventoryComponent_Active* GetInventoryComponent() const { return InventoryComponent.IsValid() ? InventoryComponent.Get() : nullptr; }
};
