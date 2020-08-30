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
class IInteractable;


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

	/*UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector CameraSwayAmount;
	UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector AddedCameraSwayDuringADS;*/


public:
	ASSCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	// Components
	USkeletalMeshComponent* GetPOVMesh() const { return POVMesh; }
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	USSCharacterMovementComponent* GetSSCharacterMovementComponent() const { return SSCharacterMovementComponent; }

	// Uses this specific character's parameters and camera orientation to do a sphere sweep to give a possible interactable. If no interactable detected, returns nullptr
	void ScanForInteractables(IInteractable*& OutInteractable, FHitResult& OutHit);



	IInteractable* CurrentInteract;
	IInteractable* LastInteract;

protected:
		// Try ustilizing our custom trace channel before resorting to this
	UPROPERTY(EditAnywhere)
		TArray<AActor*> ActorsToNotInteractWith;
	ETraceTypeQuery InteractChannel;
	UPROPERTY(EditAnywhere)
		float InteractSweepDistance;
	UPROPERTY(EditAnywhere)
		float InteractSweepRadius;
	FHitResult InteractSweepHitResult;

	

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
