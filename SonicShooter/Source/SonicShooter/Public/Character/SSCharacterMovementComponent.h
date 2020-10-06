// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "SSCharacterMovementComponent.generated.h"

class USSAbilitySystemComponent;
class UAS_Character;
class AAbilitySystemCharacter;

DECLARE_MULTICAST_DELEGATE(FCharacterMovementState);


/**
 * Custom movement modes. used when MovementMode == MOVE_Custom
 */
UENUM()
enum ECustomMovementMode																		// should we make this an enum class?
{
	/** None (custom movement is disabled). */
	CMOVE_None						UMETA(DisplayName="None"),
	/** Walking on a surface with the ability to walk up any slope angle */
	CMOVE_InfiniteAngleWalking		UMETA(DisplayName="InfiniteAngleWalking"),

	CMOVE_MAX						UMETA(Hidden)
};

/**
 * Our custom base implementation of the CMC
 */
UCLASS()
class SONICSHOOTER_API USSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	

	friend class FSavedMove_SSCharacter;

public:
	USSCharacterMovementComponent();

	//	Don't know for sure if this is the best event to use but works for now
	virtual void InitializeComponent() override;
	
	
	void SetWantsToRun(bool newWantsToRun);

#pragma region Movement Delegates
	FCharacterMovementState OnWantsToRun;
#pragma endregion


protected:
	UPROPERTY()
		AAbilitySystemCharacter* OwnerAbilitySystemCharacter;
	UPROPERTY()
		USSAbilitySystemComponent* OwnerSSASC;
	UPROPERTY()
		UAS_Character* CharacterAttributeSet;

	UFUNCTION()
		virtual void OnOwningCharacterSetupWithAbilitySystemFinished();

	//BEGIN CMC Interface
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void OnMovementUpdated(float deltaTime, const FVector& OldLocation, const FVector& OldVelocity) override;
	virtual float GetMaxAcceleration() const override;
	virtual FString GetMovementName() const override;
	virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	//END CMC Interface

	//BEGIN UMovementComponent Interface
	virtual float GetMaxSpeed() const override;
	//END UMovementComponent Interface

#pragma region Compressed Flags
	uint8 bWantsToRun : 1;
#pragma endregion


	TEnumAsByte<ECustomMovementMode> CustomMovementMode;

#pragma region Custom Movement Physics
	virtual void PhysInfiniteAngleWalking(float deltaTime, int32 Iterations);
#pragma endregion
};

class FSavedMove_SSCharacter : public FSavedMove_Character
{
public:
	typedef FSavedMove_Character Super;


	virtual void Clear() override;
	virtual void PrepMoveFor(class ACharacter* Character) override;
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;
	virtual uint8 GetCompressedFlags() const override;

protected:
	uint8 bSavedWantsToRun : 1;
};

class FNetworkPredictionData_Client_SSCharacter : public FNetworkPredictionData_Client_Character
{
public:
	typedef FNetworkPredictionData_Client_Character Super;


	FNetworkPredictionData_Client_SSCharacter(const UCharacterMovementComponent& ClientMovement);

	virtual FSavedMovePtr AllocateNewMove() override;
};
