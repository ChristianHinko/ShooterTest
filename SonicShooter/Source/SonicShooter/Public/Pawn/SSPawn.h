// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/P_AbilitySystemSetupPawn.h"

#include "SSPawn.generated.h"



/**
 * Base pawn class for all pawns to inherit from (besides pawns which inherit from the base pawn)
 */
UCLASS()
class SONICSHOOTER_API ASSPawn : public AP_AbilitySystemSetupPawn
{
	GENERATED_BODY()

public:
	ASSPawn(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


#pragma region Input Events
	//Actions
	virtual void OnRunPressed();
	virtual void OnRunReleased();

	virtual void OnJumpPressed();
	virtual void OnJumpReleased();

	virtual void OnCrouchPressed();
	virtual void OnCrouchReleased();

	virtual void OnInteractPressed();
	virtual void OnInteractReleased();

	virtual void OnPrimaryFirePressed();
	virtual void OnPrimaryFireReleased();

	virtual void OnSecondaryFirePressed();
	virtual void OnSecondaryFireReleased();

	virtual void OnReloadPressed();
	virtual void OnReloadReleased();

	virtual void OnItem0Pressed();
	virtual void OnItem0Released();

	virtual void OnItem1Pressed();
	virtual void OnItem1Released();

	virtual void OnItem2Pressed();
	virtual void OnItem2Released();

	virtual void OnItem3Pressed();
	virtual void OnItem3Released();

	virtual void OnItem4Pressed();
	virtual void OnItem4Released();

	virtual void OnSwitchWeaponPressed();
	virtual void OnSwitchWeaponReleased();

	virtual void OnNextItemPressed();
	virtual void OnNextItemReleased();

	virtual void OnPreviousItemPressed();
	virtual void OnPreviousItemReleased();

	virtual void OnDropItemPressed();
	virtual void OnDropItemReleased();

	virtual void OnPausePressed();
	virtual void OnPauseReleased();

	virtual void OnScoreSheetPressed();
	virtual void OnScoreSheetReleased();


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
