// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/STCharacterMovementComponent.h"
#include "GameplayEffectTypes.h"

#include "STCharacterMovementComponent_Shooter.generated.h"


class USTObject_Stamina;



/**
 * Shooter custom movement mode that "inherits" from ESTCustomMovementMode
 */
UENUM()
enum class ESTCustomMovementMode_Shooter : uint8
{
    /** Shooter custom move */
    MOVE_Rappelling = static_cast<uint8>(ESTCustomMovementMode::MOVE_MAX)        UMETA(DisplayName = "Rappelling"),


    MOVE_MAX                                                                    UMETA(Hidden)
};


/**
 *
 */
UCLASS()
class SHOOTERTEST_API USTCharacterMovementComponent_Shooter : public USTCharacterMovementComponent
{
    GENERATED_BODY()

    friend class FSTSavedMove_ShooterCharacter;

public:
    virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:
    UPROPERTY()
        TObjectPtr<USTObject_Stamina> StaminaSubobject;

public:
    USTCharacterMovementComponent_Shooter(const FObjectInitializer& ObjectInitializer);


    USTObject_Stamina* GetStaminaSubobject() const { return StaminaSubobject; }


    virtual bool CanRunInCurrentState() const override;
    virtual void Run() override;
    virtual void UnRun() override;


    //  BEGIN UCharacterMovementComponent Interface
    virtual FString GetMovementName() const override;
    //  END UCharacterMovementComponent Interface

protected:
    virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
    virtual void BeginDestroy() override;


    virtual void OnInitializeAbilitySystemComponent(UAbilitySystemComponent& asc) override;
    void TweakWantsToRunBeforeTick(bool& outTweakedWantsToRun) const override;

    virtual void OnStaminaFullyDrained();

private:
    //  BEGIN Attribute value change
    void OnMaxStaminaAttributeChange(const FOnAttributeChangeData& Data);
    void OnStaminaDrainAttributeChange(const FOnAttributeChangeData& Data);
    void OnStaminaGainAttributeChange(const FOnAttributeChangeData& Data);
    void OnStaminaRegenPauseAttributeChange(const FOnAttributeChangeData& Data);
    //  END Attribute value change
};


class FSTSavedMove_ShooterCharacter : public FSTSavedMove_Character
{
    typedef FSTSavedMove_Character Super;
public:


protected:

};

class FSTNetworkPredictionData_Client_ShooterCharacter : public FSTNetworkPredictionData_Client_Character
{
    typedef FSTNetworkPredictionData_Client_Character Super;
public:
    FSTNetworkPredictionData_Client_ShooterCharacter(const UCharacterMovementComponent& ClientMovement);


    virtual FSavedMovePtr AllocateNewMove() override;

};
