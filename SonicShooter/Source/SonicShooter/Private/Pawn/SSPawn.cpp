// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/SSPawn.h"

#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"



ASSPawn::ASSPawn()
{
	//PrimaryActorTick.bCanEverTick = false;

	// Set our turn rates for input
	HorizontalSensitivity = 45.f;
	VerticalSensitivity = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}


#pragma region Input
void ASSPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//Action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASSPawn::OnJumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASSPawn::OnJumpReleased);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASSPawn::OnInteractPressed);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ASSPawn::OnInteractReleased);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASSPawn::OnRunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASSPawn::OnRunReleased);

	PlayerInputComponent->BindAction("PrimaryFire", IE_Pressed, this, &ASSPawn::OnPrimaryFirePressed);
	PlayerInputComponent->BindAction("PrimaryFire", IE_Released, this, &ASSPawn::OnPrimaryFireReleased);

	PlayerInputComponent->BindAction("SecondaryFire", IE_Pressed, this, &ASSPawn::OnSecondaryFirePressed);
	PlayerInputComponent->BindAction("SecondaryFire", IE_Released, this, &ASSPawn::OnSecondaryFireReleased);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ASSPawn::OnReloadPressed);
	PlayerInputComponent->BindAction("Reload", IE_Released, this, &ASSPawn::OnReloadReleased);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASSPawn::OnCrouchPressed);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASSPawn::OnCrouchReleased);

	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ASSPawn::OnSwitchWeaponPressed);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Released, this, &ASSPawn::OnSwitchWeaponReleased);

	//Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &ASSPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASSPawn::MoveRight);

	PlayerInputComponent->BindAxis("TurnRightRate", this, &ASSPawn::HorizontalLook);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASSPawn::VerticalLook);
}

//Actions
void ASSPawn::OnJumpPressed()
{

}
void ASSPawn::OnJumpReleased()
{

}

void ASSPawn::OnInteractPressed()
{

}
void ASSPawn::OnInteractReleased()
{

}

void ASSPawn::OnPrimaryFirePressed()
{

}
void ASSPawn::OnPrimaryFireReleased()
{

}

void ASSPawn::OnSecondaryFirePressed()
{

}
void ASSPawn::OnSecondaryFireReleased()
{

}

void ASSPawn::OnReloadPressed()
{

}
void ASSPawn::OnReloadReleased()
{

}

void ASSPawn::OnCrouchPressed()
{

}
void ASSPawn::OnCrouchReleased()
{

}

void ASSPawn::OnSwitchWeaponPressed()
{

}
void ASSPawn::OnSwitchWeaponReleased()
{

}

void ASSPawn::OnRunPressed()
{

}
void ASSPawn::OnRunReleased()
{

}


//Axis
void ASSPawn::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void ASSPawn::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASSPawn::HorizontalLook(float Rate)
{
	if (Rate != 0)
	{
		AddControllerYawInput(Rate * HorizontalSensitivity * GetWorld()->GetDeltaSeconds());
	}
}
void ASSPawn::VerticalLook(float Rate)
{
	if (Rate != 0)
	{
		AddControllerPitchInput(Rate * VerticalSensitivity * GetWorld()->GetDeltaSeconds());
	}
}
#pragma endregion
