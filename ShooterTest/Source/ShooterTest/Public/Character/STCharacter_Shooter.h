// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/STCharacter.h"
#include "Interfaces/ArcInventoryInterface.h"

#include "STCharacter_Shooter.generated.h"


class ISTInteractableInterface;
class USTActorComponent_Interactor;
class UArcInventoryComponent;
class UArcInventoryComponent_Modular;
class USTInventoryProcessor_Shooter;
class UInputComponent;



/**
 * Base Shooter Character
 */
UCLASS()
class SHOOTERTEST_API ASTCharacter_Shooter : public ASTCharacter, public IArcInventoryInterface
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
        TObjectPtr<UArcInventoryComponent_Modular> InventoryComponent;
    static const FName InventoryComponentName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Interactor")
        TObjectPtr<USTActorComponent_Interactor> Interactor;

public:
    ASTCharacter_Shooter(const FObjectInitializer& ObjectInitializer);


    // Subobject getters
    UArcInventoryComponent* GetInventoryComponent() const override { return static_cast<UArcInventoryComponent*>(InventoryComponent); }
    USTActorComponent_Interactor* GetInteractorComponent() const { return Interactor; }

protected:
    //  BEGIN AActor Interface
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    //  END AActor Interface

    //  BEGIN APawn Interface
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    //  END APawn Interface


    UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
        FVector CameraSwayAmount;
    UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
        FVector AddedCameraSwayDuringADS;


    //  BEGIN Input actions
    virtual void OnPressedInteract();
    //  END Input actions

private:
    // Cached Inventory
    UPROPERTY()
        TWeakObjectPtr<USTInventoryProcessor_Shooter> ShooterInventoryProcessor;

};
