// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSCharacterMovementComponent.h"
#include "GameplayEffectTypes.h"

#include "SSCharacterMovementComponent_Shooter.generated.h"


class USSObject_Stamina;



/**
 * Shooter custom movement mode that "inherits" from ESSCustomMovementMode
 */
UENUM()
enum class ESSCustomMovementMode_Shooter : uint8
{
	/** Shooter custom move */
	MOVE_Rappelling = static_cast<uint8>(ESSCustomMovementMode::MOVE_MAX)		UMETA(DisplayName = "Rappelling"),


	MOVE_MAX																	UMETA(Hidden)
};


/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSCharacterMovementComponent_Shooter : public USSCharacterMovementComponent
{
	GENERATED_BODY()

	friend class FSSSavedMove_ShooterCharacter;

public:
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:
	UPROPERTY()
		TObjectPtr<USSObject_Stamina> StaminaSubobject;

public:
	USSCharacterMovementComponent_Shooter(const FObjectInitializer& ObjectInitializer);


	USSObject_Stamina* GetStaminaSubobject() const { return StaminaSubobject; }


	virtual bool CanRunInCurrentState() const override;
	virtual void Run() override;
	virtual void UnRun() override;


	//BEGIN UCharacterMovementComponent Interface
	virtual FString GetMovementName() const override;
	//END UCharacterMovementComponent Interface

protected:
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	virtual void BeginDestroy() override;


	virtual void OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC) override;
	void TweakWantsToRunBeforeTick(bool& outTweakedWantsToRun) const override;

	virtual void OnStaminaFullyDrained();

private:
	//BEGIN Attribute value change
	void OnMaxStaminaAttributeChange(const FOnAttributeChangeData& Data);
	void OnStaminaDrainAttributeChange(const FOnAttributeChangeData& Data);
	void OnStaminaGainAttributeChange(const FOnAttributeChangeData& Data);
	void OnStaminaRegenPauseAttributeChange(const FOnAttributeChangeData& Data);
	//END Attribute value change
};


class FSSSavedMove_ShooterCharacter : public FSSSavedMove_Character
{
	typedef FSSSavedMove_Character Super;
public:


protected:

};

class FSSNetworkPredictionData_Client_ShooterCharacter : public FSSNetworkPredictionData_Client_Character
{
	typedef FSSNetworkPredictionData_Client_Character Super;
public:
	FSSNetworkPredictionData_Client_ShooterCharacter(const UCharacterMovementComponent& ClientMovement);


	virtual FSavedMovePtr AllocateNewMove() override;

};
