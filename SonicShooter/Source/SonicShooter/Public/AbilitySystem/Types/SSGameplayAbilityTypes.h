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

    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSCharacter> SSCharacter;

    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSPlayerController> SSPlayerController;

    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<ASSPlayerState> SSPlayerState;

    UPROPERTY(BlueprintReadOnly, Category = "SSActorInfo")
        TWeakObjectPtr<USSCharacterMovementComponent> SSCharacterMovementComponent;


    virtual void InitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void ClearActorInfo() override;
};



////////////////////////////////////////////////////////////////
/// FSSGameplayAbilityActorInfo_Shooter
////////////////////////////////////////////////////////////////


class USSAbilitySystemComponent_Shooter;
class ASSCharacter_Shooter;
class UArcInventoryComponent;


/**
 * Our custom GameplayAbilityActorInfo
 */
USTRUCT()
struct SONICSHOOTER_API FSSGameplayAbilityActorInfo_Shooter : public FSSGameplayAbilityActorInfo
{
    GENERATED_BODY()

    // Our Shooter specific ASC
    UPROPERTY(BlueprintReadOnly, Category = "ShooterActorInfo")
        TWeakObjectPtr<USSAbilitySystemComponent_Shooter> ShooterAbilitySystemComponent;

    // Our ShooterCharacter
    UPROPERTY(BlueprintReadOnly, Category = "ShooterActorInfo")
        TWeakObjectPtr<ASSCharacter_Shooter> ShooterCharacter;

    // Our Inventory Component
    UPROPERTY(BlueprintReadOnly, Category = "ShooterActorInfo")
        TWeakObjectPtr<UArcInventoryComponent> InventoryComponent;


    virtual void InitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void ClearActorInfo() override;
};
