// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Types/ASSGameplayAbilityTypes.h"

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
    virtual ~FSSGameplayAbilityActorInfo() override
    {

    }


    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSCharacter> SSCharacter;

    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSPlayerController> SSPlayerController;

    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSPlayerState> SSPlayerState;

    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<USSCharacterMovementComponent> SSCharacterMovementComponent;


    virtual void ASSInitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void SetAvatarActor(AActor* AvatarActor) override;
    virtual void ClearActorInfo() override;


    ASSCharacter* GetSSCharacter() const { return SSCharacter.Get(); }
    ASSPlayerController* GetSSPlayerController() const { return SSPlayerController.Get(); }
    ASSPlayerState* GetSSPlayerState() const { return SSPlayerState.Get(); }
    USSCharacterMovementComponent* GetSSCharacterMovementComponent() const { return SSCharacterMovementComponent.Get(); }
};



////////////////////////////////////////////////////////////////
/// FSSGameplayAbilityActorInfo_Shooter
////////////////////////////////////////////////////////////////


class USSAbilitySystemComponent_Shooter;
class ASSCharacter_Shooter;
class USSInventoryComponent_Active;


/**
 * Our custom GameplayAbilityActorInfo
 */
USTRUCT()
struct SONICSHOOTER_API FSSGameplayAbilityActorInfo_Shooter : public FSSGameplayAbilityActorInfo
{
    GENERATED_BODY()


    FSSGameplayAbilityActorInfo_Shooter();
    virtual ~FSSGameplayAbilityActorInfo_Shooter() override
    {

    }

    // Our Shooter specific ASC
    UPROPERTY(BlueprintReadOnly, Category = "Shooter")
        TWeakObjectPtr<USSAbilitySystemComponent_Shooter> ShooterAbilitySystemComponent;

    // Our ShooterCharacter
    UPROPERTY(BlueprintReadOnly, Category = "Shooter")
        TWeakObjectPtr<ASSCharacter_Shooter> ShooterCharacter;

    // Our Inventory Component
    UPROPERTY(BlueprintReadOnly, Category = "Shooter")
        TWeakObjectPtr<USSInventoryComponent_Active> InventoryComponent;


    virtual void ASSInitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void SetAvatarActor(AActor* AvatarActor) override;
    virtual void ClearActorInfo() override;


    USSAbilitySystemComponent_Shooter* GetShooterAbilitySystemComponent() const { return ShooterAbilitySystemComponent.Get(); }
    ASSCharacter_Shooter* GetShooterCharacter() const { return ShooterCharacter.Get(); }
    USSInventoryComponent_Active* GetInventoryComponent() const { return InventoryComponent.Get(); }
};
