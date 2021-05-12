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
    typedef Super FGameplayAbilityActorInfo;


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
