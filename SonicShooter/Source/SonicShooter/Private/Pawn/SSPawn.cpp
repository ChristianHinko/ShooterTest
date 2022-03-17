// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/SSPawn.h"

#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"



ASSPawn::ASSPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Action
	PlayerInputComponent->BindAction(FName(TEXT("Run")), IE_Pressed, this, &ThisClass::OnRunPressed);
	PlayerInputComponent->BindAction(FName(TEXT("Run")), IE_Released, this, &ThisClass::OnRunReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Jump")), IE_Pressed, this, &ThisClass::OnJumpPressed);
	PlayerInputComponent->BindAction(FName(TEXT("Jump")), IE_Released, this, &ThisClass::OnJumpReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Crouch")), IE_Pressed, this, &ThisClass::OnCrouchPressed);
	PlayerInputComponent->BindAction(FName(TEXT("Crouch")), IE_Released, this, &ThisClass::OnCrouchReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Interact")), IE_Pressed, this, &ThisClass::OnInteractPressed);
	PlayerInputComponent->BindAction(FName(TEXT("Interact")), IE_Released, this, &ThisClass::OnInteractReleased);

	PlayerInputComponent->BindAction(FName(TEXT("PrimaryFire")), IE_Pressed, this, &ThisClass::OnPrimaryFirePressed);
	PlayerInputComponent->BindAction(FName(TEXT("PrimaryFire")), IE_Released, this, &ThisClass::OnPrimaryFireReleased);

	PlayerInputComponent->BindAction(FName(TEXT("SecondaryFire")), IE_Pressed, this, &ThisClass::OnSecondaryFirePressed);
	PlayerInputComponent->BindAction(FName(TEXT("SecondaryFire")), IE_Released, this, &ThisClass::OnSecondaryFireReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Reload")), IE_Pressed, this, &ThisClass::OnReloadPressed);
	PlayerInputComponent->BindAction(FName(TEXT("Reload")), IE_Released, this, &ThisClass::OnReloadReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Item0")), IE_Pressed, this, &ThisClass::OnItem0Pressed);
	PlayerInputComponent->BindAction(FName(TEXT("Item0")), IE_Released, this, &ThisClass::OnItem0Released);

	PlayerInputComponent->BindAction(FName(TEXT("Item1")), IE_Pressed, this, &ThisClass::OnItem1Pressed);
	PlayerInputComponent->BindAction(FName(TEXT("Item1")), IE_Released, this, &ThisClass::OnItem1Released);

	PlayerInputComponent->BindAction(FName(TEXT("Item2")), IE_Pressed, this, &ThisClass::OnItem2Pressed);
	PlayerInputComponent->BindAction(FName(TEXT("Item2")), IE_Released, this, &ThisClass::OnItem2Released);

	PlayerInputComponent->BindAction(FName(TEXT("Item3")), IE_Pressed, this, &ThisClass::OnItem3Pressed);
	PlayerInputComponent->BindAction(FName(TEXT("Item3")), IE_Released, this, &ThisClass::OnItem3Released);

	PlayerInputComponent->BindAction(FName(TEXT("Item4")), IE_Pressed, this, &ThisClass::OnItem4Pressed);
	PlayerInputComponent->BindAction(FName(TEXT("Item4")), IE_Released, this, &ThisClass::OnItem4Released);

	PlayerInputComponent->BindAction(FName(TEXT("SwitchWeapon")), IE_Pressed, this, &ThisClass::OnSwitchWeaponPressed);
	PlayerInputComponent->BindAction(FName(TEXT("SwitchWeapon")), IE_Released, this, &ThisClass::OnSwitchWeaponReleased);

	PlayerInputComponent->BindAction(FName(TEXT("NextItem")), IE_Pressed, this, &ThisClass::OnNextItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("NextItem")), IE_Released, this, &ThisClass::OnNextItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("PreviousItem")), IE_Pressed, this, &ThisClass::OnPreviousItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("PreviousItem")), IE_Released, this, &ThisClass::OnPreviousItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("DropItem")), IE_Pressed, this, &ThisClass::OnDropItemPressed);
	PlayerInputComponent->BindAction(FName(TEXT("DropItem")), IE_Released, this, &ThisClass::OnDropItemReleased);

	PlayerInputComponent->BindAction(FName(TEXT("Pause")), IE_Pressed, this, &ThisClass::OnPausePressed);
	PlayerInputComponent->BindAction(FName(TEXT("Pause")), IE_Released, this, &ThisClass::OnPauseReleased);

	PlayerInputComponent->BindAction(FName(TEXT("ScoreSheet")), IE_Pressed, this, &ThisClass::OnScoreSheetPressed);
	PlayerInputComponent->BindAction(FName(TEXT("ScoreSheet")), IE_Released, this, &ThisClass::OnScoreSheetReleased);



	//Axis
	PlayerInputComponent->BindAxis(FName(TEXT("MoveForward")), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(FName(TEXT("MoveRight")), this, &ThisClass::MoveRight);

	PlayerInputComponent->BindAxis(FName(TEXT("TurnRightRate")), this, &ThisClass::HorizontalLook);
	PlayerInputComponent->BindAxis(FName(TEXT("LookUpRate")), this, &ThisClass::VerticalLook);
}


//Actions
void ASSPawn::OnRunPressed()
{

}
void ASSPawn::OnRunReleased()
{
}

void ASSPawn::OnJumpPressed()
{

}
void ASSPawn::OnJumpReleased()
{
}

void ASSPawn::OnCrouchPressed()
{

}
void ASSPawn::OnCrouchReleased()
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

void ASSPawn::OnItem0Pressed()
{

}
void ASSPawn::OnItem0Released()
{
}

void ASSPawn::OnItem1Pressed()
{

}
void ASSPawn::OnItem1Released()
{
}

void ASSPawn::OnItem2Pressed()
{

}
void ASSPawn::OnItem2Released()
{
}

void ASSPawn::OnItem3Pressed()
{

}
void ASSPawn::OnItem3Released()
{
}

void ASSPawn::OnItem4Pressed()
{

}
void ASSPawn::OnItem4Released()
{
}

void ASSPawn::OnSwitchWeaponPressed()
{

}
void ASSPawn::OnSwitchWeaponReleased()
{
}

void ASSPawn::OnNextItemPressed()
{

}
void ASSPawn::OnNextItemReleased()
{
}

void ASSPawn::OnPreviousItemPressed()
{

}
void ASSPawn::OnPreviousItemReleased()
{
}

void ASSPawn::OnDropItemPressed()
{

}
void ASSPawn::OnDropItemReleased()
{
}

void ASSPawn::OnPausePressed()
{

}
void ASSPawn::OnPauseReleased()
{
}

void ASSPawn::OnScoreSheetPressed()
{

}
void ASSPawn::OnScoreSheetReleased()
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

void ASSPawn::HorizontalLook(float Rate) // TODO: add slight smoothing in courtesy of players with low polling rates on high refresh rate displays
{
	if (Rate != 0)
	{
		AddControllerYawInput(Rate * HorizontalSensitivity * 0.5/* * GetWorld()->GetDeltaSeconds()*/); // delta seconds is not needed here for some reason. Idk why but it does the opposite of the expected effect
	}
}
void ASSPawn::VerticalLook(float Rate) // TODO: add slight smoothing in courtesy of players with low polling rates on high refresh rate displays
{
	if (Rate != 0)
	{
		AddControllerPitchInput(Rate * VerticalSensitivity * 0.5/* * GetWorld()->GetDeltaSeconds()*/); // delta seconds is not needed here for some reason. Idk why but it does the opposite of the expected effect
	}
}
#pragma endregion
