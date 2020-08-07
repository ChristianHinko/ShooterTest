// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "SSCharacter.generated.h"


class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class USSCharacterMovementComponent;
class AItem;



/**
 *  This should store the info for an Item so we can avoid casting for no reason.
 */
USTRUCT()
struct FItemInfo
{
	GENERATED_USTRUCT_BODY()

public:
	AItem* Item;

	bool isGun;
	bool isMelee;
	bool isGrenade;
};

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

	UPROPERTY(Replicated)
		TArray<AItem*> Inventory;
	UPROPERTY(Replicated)
		AItem* CurrentItem;
	UPROPERTY(Replicated)
		AItem* PreviousItem;


public:
	ASSCharacter(const FObjectInitializer& ObjectInitializer);

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
