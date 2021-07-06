// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\AI_ShooterCharacter.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/SSCharacter.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"

#include "Kismet/KismetSystemLibrary.h"



UAI_ShooterCharacter::UAI_ShooterCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	headLookAtRot = FRotator::ZeroRotator;
	headLookSpeed = 3;
	headLookAtAlpha = 1;
	headMaxRollRot = 85;
	headMaxPitchRot = 85;
	headMaxYawRot = 85;



	bTurnInPlaceEnabled = true;
}

void UAI_ShooterCharacter::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();


	OwningShooterCharacter = Cast<AShooterCharacter>(GetOwningActor());
}
void UAI_ShooterCharacter::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);


	if (OwningShooterCharacter)
	{
#pragma region Owning Actor work
		ActorRotation = OwningShooterCharacter->GetActorRotation();

		Velocity = OwningShooterCharacter->GetVelocity();
		Speed = Velocity.Size();

		ForwardSpeed = Velocity.ProjectOnTo(OwningShooterCharacter->GetActorForwardVector()).Size();
		RightSpeed = Velocity.ProjectOnTo(OwningShooterCharacter->GetActorRightVector()).Size();
		UpSpeed = Velocity.ProjectOnTo(OwningShooterCharacter->GetActorUpVector()).Size();

		// TODO: make this more optimized ( "Velocity.ProjectOnToNormal(UpVector).Size()" isn't working some reason )
		HorizontalSpeed = FMath::Sqrt(FMath::Square(ForwardSpeed) + FMath::Square(RightSpeed));

		Direction = CalculateDirection(Velocity, OwningShooterCharacter->GetActorRotation()); // TODO: make sure this is relative to the actor's rotation
#pragma endregion





#pragma region Owning Pawn work
		AimRotation = OwningShooterCharacter->GetBaseAimRotation();	// this will be choppy when replicated but we won't automatically smooth it here

		TurnInPlace(DeltaTimeX);
		MeshRotation = ActorRotation + FRotator(0.f, TurnInPlaceYawOffset, 0.f);

		const FRotator AimOffset = UKismetMathLibrary::NormalizedDeltaRotator(AimRotation, MeshRotation); // the normalized direction from ActorRotation to ControlRotation
		AimOffsetPitch = AimOffset.Pitch;
		AimOffsetYaw = AimOffset.Yaw;
#pragma endregion






#pragma region Owning Charcter work
		// Update movement variables
		if (UCharacterMovementComponent* CMC = OwningShooterCharacter->GetCharacterMovement())
		{
			bGrounded = CMC->IsMovingOnGround();
			bInAir = CMC->IsFalling();
			bIsFlying = CMC->IsFlying();
			bIsSwimming = CMC->IsSwimming();

			bIsCrouching = CMC->IsCrouching();
		}


#pragma endregion





#pragma region Owning ShooterChractor work
		headLookAtRot = GetHeadLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
#pragma endregion
	}



	PreviousActorRotation = ActorRotation;
}

void UAI_ShooterCharacter::TurnInPlace(float DeltaTimeX)
{
	const bool previousTurnInPlaceAvailable = bTurnInPlaceAvailable;
	bTurnInPlaceAvailable = FMath::IsNearlyZero(Speed);
	if (bTurnInPlaceAvailable == true && previousTurnInPlaceAvailable == false)
	{
		// TIP just became available
		TurnInPlaceStartingYaw = ActorRotation.Yaw;
	}


	if (OwningShooterCharacter->bUseControllerRotationYaw == false)
	{
		bTurnInPlaceEnabled = false;
	}

	if (bTurnInPlaceEnabled)
	{
		if (bTurnInPlaceAvailable == false)
		{
			// Start turning back to normal
			bIsTurningInPlace = true;
		}


		const FRotator RotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(ActorRotation, PreviousActorRotation);
		TurnInPlaceYawOffset -= RotationDelta.Yaw; // negate with our Actor's increase/decrease in yaw
		TurnInPlaceYawOffset = FRotator::NormalizeAxis(TurnInPlaceYawOffset);

		if (bIsTurningInPlace == false)
		{
			if (FMath::Abs(TurnInPlaceYawOffset) >= 90.f)
			{
				bIsTurningInPlace = true;
			}
		}

		if (bIsTurningInPlace)
		{
			TurnInPlaceYawOffset = FMath::FInterpConstantTo(TurnInPlaceYawOffset, 0.f, DeltaTimeX, 100.f);
			if (FMath::IsNearlyZero(TurnInPlaceYawOffset))
			{
				TurnInPlaceYawOffset = 0.f;
				bIsTurningInPlace = false;
				TurnInPlaceStartingYaw = ActorRotation.Yaw;
			}
		}

		//UKismetSystemLibrary::PrintString(this, "TurnInPlaceYawOffset: " + FString::SanitizeFloat(TurnInPlaceYawOffset), true, false);
	}
	else
	{
		TurnInPlaceYawOffset = 0.f;
		bIsTurningInPlace = false;
		TurnInPlaceStartingYaw = ActorRotation.Yaw;
	}
}













FRotator UAI_ShooterCharacter::GetHeadLookAtTargetRot(AActor* Target, float deltaTime)
{
	FRotator retVal = FRotator::ZeroRotator;
	if (OwningShooterCharacter && Target)
	{
		FVector SelfHeadLocation;
		if (OwningShooterCharacter->GetMesh())
		{
			SelfHeadLocation = OwningShooterCharacter->GetMesh()->GetSocketLocation(TEXT("head"));
		}
		FVector locationToLookAt;
		if (AShooterCharacter* ShooterCharacterToLookAt = Cast<AShooterCharacter>(Target))
		{
			if (ShooterCharacterToLookAt->GetMesh())
			{
				locationToLookAt = ShooterCharacterToLookAt->GetMesh()->GetSocketLocation(TEXT("head"));
			}
		}

		FRotator OwningShooterCharacterRotation = OwningShooterCharacter->GetActorRotation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(SelfHeadLocation, locationToLookAt);

		FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(OwningShooterCharacterRotation, LookAtRotation);
		if (UKismetMathLibrary::Abs(DeltaRotator.Roll) < headMaxRollRot && UKismetMathLibrary::Abs(DeltaRotator.Pitch) < headMaxPitchRot && UKismetMathLibrary::Abs(DeltaRotator.Yaw) < headMaxYawRot)	// If the head can rotate this far
		{
			FRotator hardLookAtRot;
			hardLookAtRot.Roll = LookAtRotation.Roll - OwningShooterCharacterRotation.Roll;
			hardLookAtRot.Pitch = (LookAtRotation.Pitch - OwningShooterCharacterRotation.Pitch) * -1;
			hardLookAtRot.Yaw = LookAtRotation.Yaw - OwningShooterCharacterRotation.Yaw;

			FRotator softLookAtRot = FMath::RInterpTo(headLookAtRot, hardLookAtRot, deltaTime, headLookSpeed);

			retVal = softLookAtRot;
		}
		else
		{
			FRotator softLookAtRot = FMath::RInterpTo(headLookAtRot, FRotator::ZeroRotator, deltaTime, headLookSpeed);

			retVal = softLookAtRot;
		}
	}

	return retVal;
}
