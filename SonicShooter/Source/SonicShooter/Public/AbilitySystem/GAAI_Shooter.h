// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSGameplayAbilityTypes.h"

#include "GAAI_Shooter.generated.h"


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
    typedef Super FSSGameplayAbilityActorInfo;


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
