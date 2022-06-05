// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSCharacterMovementComponent.h"
#include "GameplayEffectTypes.h"

#include "CMC_Shooter.generated.h"


class UO_Stamina;



/**
 * Shooter custom movement mode that "inherits" from ECustomMovementMode
 */
UENUM()
enum class ECustomMovementMode_Shooter : uint8
{
	/** Shooter custom move */
	MOVE_Example = static_cast<uint8>(ECustomMovementMode::MOVE_MAX) + 1		UMETA(DisplayName = "Example"),


	MOVE_MAX																	UMETA(Hidden)
};


/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UCMC_Shooter : public USSCharacterMovementComponent
{
	GENERATED_BODY()

	friend class FSavedMove_Shooter;

public:
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

protected:
	UPROPERTY()
		TObjectPtr<UO_Stamina> StaminaSubobject;

public:
	UCMC_Shooter(const FObjectInitializer& ObjectInitializer);


	UO_Stamina* GetStaminaSubobject() const { return StaminaSubobject; }


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


class FSavedMove_Shooter : public FSSSavedMove_Character
{
	typedef FSSSavedMove_Character Super;
public:


protected:

};

class FNetworkPredictionData_Client_Shooter : public FSSNetworkPredictionData_Client_Character
{
	typedef FSSNetworkPredictionData_Client_Character Super;
public:
	FNetworkPredictionData_Client_Shooter(const UCharacterMovementComponent& ClientMovement);


	virtual FSavedMovePtr AllocateNewMove() override;

};
