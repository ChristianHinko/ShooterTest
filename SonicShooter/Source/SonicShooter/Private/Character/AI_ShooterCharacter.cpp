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

		//HorizontalSpeed = Velocity.ProjectOnToNormal(UpVector).Size(); // doesnt work some reason
		//HorizontalSpeed = FMath::Sqrt(FMath::Square(ForwardSpeed) + FMath::Square(RightSpeed)); // is expensive

		Direction = CalculateDirection(Velocity, OwningShooterCharacter->GetActorRotation()); // TODO: make sure this is relative to the actor's rotation
#pragma endregion





#pragma region Owning Pawn work
		AimRotation = OwningShooterCharacter->GetBaseAimRotation();		// This will be choppy when replicated but we won't automatically smooth it here


		// Turn in place
		if (OwningShooterCharacter->bUseControllerRotationYaw == true)
		{
			const float AimYawIncrease = AimRotation.Yaw - PreviousAimRotation.Yaw;
			NegatedRootYawOffset += AimYawIncrease * -1; // negate it so we cancel out with our Actor Rotation
			NegatedRootYawOffset = FRotator::NormalizeAxis(NegatedRootYawOffset);
			if (FMath::Abs(NegatedRootYawOffset) >= 90.f || FMath::IsNearlyZero(Speed) == false)
			{
				bIsTurningInPlace = true;
			}

			if (bIsTurningInPlace)
			{
				NegatedRootYawOffset = FMath::FInterpConstantTo(NegatedRootYawOffset, 0.f, DeltaTimeX, 100.f);
				if (FMath::IsNearlyZero(NegatedRootYawOffset))
				{
					NegatedRootYawOffset = 0.f;
					bIsTurningInPlace = false;
				}
			}

			//UKismetSystemLibrary::PrintString(this, "NegatedRootYawOffset: " + FString::SanitizeFloat(NegatedRootYawOffset), true, false);
		}
		else
		{
			NegatedRootYawOffset = 0.f;
			bIsTurningInPlace = false;
		}

		MeshRotation = ActorRotation + FRotator(0.f, NegatedRootYawOffset, 0.f);


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




	PreviousAimRotation = AimRotation;
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
