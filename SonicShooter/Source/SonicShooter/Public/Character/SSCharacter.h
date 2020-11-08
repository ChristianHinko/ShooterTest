// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "SSCharacter.generated.h"


class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class USSCharacterMovementComponent;

/**
 * Base character class (without GAS implementation)
 */
UCLASS()
class ASSCharacter : public ACharacter
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere, Category = "Character")
		USkeletalMeshComponent* POVMesh; // should this exist on every character (including AI)?
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* CameraBoom;

public:
	ASSCharacter(const FObjectInitializer& ObjectInitializer);
	
	
	float fowardInputAxis;
	float rightInputAxis;
	// Components
	USkeletalMeshComponent* GetPOVMesh() const { return POVMesh; }
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	USSCharacterMovementComponent* GetSSCharacterMovementComponent() const { return SSCharacterMovementComponent; }


	

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		USSCharacterMovementComponent* SSCharacterMovementComponent;

	
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
