// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"

#include "STGameplayAbilityTypes.generated.h"

class UAbilitySystemComponent;
class ASTCharacter;
class ASTPlayerController;
class ASTPlayerState;
class USTCharacterMovementComponent;

/**
 * @brief Game's gameplay ability actor info class.
 */
USTRUCT()
struct SHOOTERTEST_API FSTGameplayAbilityActorInfo : public FGameplayAbilityActorInfo
{
    GENERATED_BODY()

public:

    // ~ FGameplayAbilityActorInfo overrides.
    virtual void InitFromActor(
        AActor* inOwnerActor,
        AActor* inAvatarActor,
        UAbilitySystemComponent* inAbilitySystemComponent) override;
    virtual void ClearActorInfo() override;
    // ~ FGameplayAbilityActorInfo overrides.

public:

    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
    TWeakObjectPtr<ASTCharacter> STCharacter;

    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
    TWeakObjectPtr<ASTPlayerController> STPlayerController;

    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
    TWeakObjectPtr<ASTPlayerState> STPlayerState;

    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
    TWeakObjectPtr<USTCharacterMovementComponent> STCharacterMovementComponent;
};

////////////////////////////////////////////////////////////////
/// FSTGameplayAbilityActorInfo_Shooter
////////////////////////////////////////////////////////////////

class USTAbilitySystemComponent_Shooter;
class ASTCharacter_Shooter;
class UArcInventoryComponent_Modular;

/**
 *
 */
USTRUCT()
struct SHOOTERTEST_API FSTGameplayAbilityActorInfo_Shooter : public FSTGameplayAbilityActorInfo
{
    GENERATED_BODY()

public:

    // ~ FGameplayAbilityActorInfo overrides.
    virtual void InitFromActor(
        AActor* inOwnerActor,
        AActor* inAvatarActor,
        UAbilitySystemComponent* inAbilitySystemComponent) override;
    virtual void ClearActorInfo() override;
    // ~ FGameplayAbilityActorInfo overrides.

public:

    // Our shooter-specific ASC.
    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
    TWeakObjectPtr<USTAbilitySystemComponent_Shooter> ShooterAbilitySystemComponent;

    // Our shooter-specific character.
    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
    TWeakObjectPtr<ASTCharacter_Shooter> ShooterCharacter;

    // Our inventory component.
    UPROPERTY(BlueprintReadOnly, Category = "STActorInfo")
    TWeakObjectPtr<UArcInventoryComponent_Modular> InventoryComponent;
};
