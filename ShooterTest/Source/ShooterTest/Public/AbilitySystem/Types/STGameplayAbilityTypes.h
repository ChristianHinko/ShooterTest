// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Types/ASSGameplayAbilityTypes.h"

#include "STGameplayAbilityTypes.generated.h"


class ASTCharacter;
class ASTPlayerController;
class ASTPlayerState;
class USTCharacterMovementComponent;



/**
 * Our custom GameplayAbilityActorInfo.
 * Put non-game-specific data in here - like base classes and stuff
 */
USTRUCT()
struct SHOOTERTEST_API FSTGameplayAbilityActorInfo : public FASSGameplayAbilityActorInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
        TWeakObjectPtr<ASTCharacter> STCharacter;

    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
        TWeakObjectPtr<ASTPlayerController> STPlayerController;

    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
        TWeakObjectPtr<ASTPlayerState> STPlayerState;

    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
        TWeakObjectPtr<USTCharacterMovementComponent> STCharacterMovementComponent;


    virtual void InitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void ClearActorInfo() override;
};



////////////////////////////////////////////////////////////////
/// FSTGameplayAbilityActorInfo_Shooter
////////////////////////////////////////////////////////////////


class USTAbilitySystemComponent_Shooter;
class ASTCharacter_Shooter;
class UArcInventoryComponent;


/**
 * Our custom GameplayAbilityActorInfo
 */
USTRUCT()
struct SHOOTERTEST_API FSTGameplayAbilityActorInfo_Shooter : public FSTGameplayAbilityActorInfo
{
    GENERATED_BODY()

    // Our Shooter specific ASC
    UPROPERTY(BlueprintReadOnly, Category = "ShooterActorInfo")
        TWeakObjectPtr<USTAbilitySystemComponent_Shooter> ShooterAbilitySystemComponent;

    // Our ShooterCharacter
    UPROPERTY(BlueprintReadOnly, Category = "ShooterActorInfo")
        TWeakObjectPtr<ASTCharacter_Shooter> ShooterCharacter;

    // Our Inventory Component
    UPROPERTY(BlueprintReadOnly, Category = "ShooterActorInfo")
        TWeakObjectPtr<UArcInventoryComponent> InventoryComponent;


    virtual void InitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
    virtual void ClearActorInfo() override;
};
