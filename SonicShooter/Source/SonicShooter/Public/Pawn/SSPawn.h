// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "SSPawn.generated.h"


class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class USSCharacterMovementComponent;



/**
 * Base pawn class for all pawns to inherit from (besides pawns which inherit from the base pawn)
 */
UCLASS()
class SONICSHOOTER_API ASSPawn : public APawn
{
	GENERATED_BODY()

public:
	ASSPawn();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


#pragma region Input Events
	//Actions
	virtual void OnJumpPressed();
	virtual void OnJumpReleased();

	virtual void OnInteractPressed();
	virtual void OnInteractReleased();

	virtual void OnRunPressed();
	virtual void OnRunReleased();

	virtual void OnPrimaryFirePressed();
	virtual void OnPrimaryFireReleased();

	virtual void OnSecondaryFirePressed();
	virtual void OnSecondaryFireReleased();

	virtual void OnReloadPressed();
	virtual void OnReloadReleased();

	virtual void OnCrouchPressed();
	virtual void OnCrouchReleased();

	virtual void OnSwitchWeaponPressed();
	virtual void OnSwitchWeaponReleased();



	//Axis
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);

	virtual void HorizontalLook(float Rate);
	virtual void VerticalLook(float Rate);
#pragma endregion

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	float HorizontalSensitivity;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	float VerticalSensitivity;
};
