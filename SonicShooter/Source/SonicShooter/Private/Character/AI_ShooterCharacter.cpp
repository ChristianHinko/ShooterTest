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


	OwningActor = GetOwningActor();
	OwningPawn = Cast<APawn>(OwningActor);
	OwningCharacter = Cast<ACharacter>(OwningPawn);
	OwningSSCharacter = Cast<ASSCharacter>(OwningCharacter);
	OwningShooterCharacter = Cast<AShooterCharacter>(OwningCharacter);
}
void UAI_ShooterCharacter::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);


	if (OwningActor)
	{
		Velocity = OwningActor->GetVelocity();
		Speed = Velocity.Size();

		ForwardSpeed = Velocity.ProjectOnTo(OwningActor->GetActorForwardVector()).Size();
		RightSpeed = Velocity.ProjectOnTo(OwningActor->GetActorRightVector()).Size();
		UpSpeed = Velocity.ProjectOnTo(OwningActor->GetActorUpVector()).Size();

		//HorizontalSpeed = Velocity.ProjectOnToNormal(UpVector).Size(); // doesnt work some reason
		//HorizontalSpeed = FMath::Sqrt(FMath::Square(ForwardSpeed) + FMath::Square(RightSpeed)); // is expensive

		Direction = CalculateDirection(Velocity, OwningActor->GetActorRotation()); // TODO: make sure this is relative to the actor's rotation
	}

	if (OwningPawn)
	{
		const FRotator ActorRotation = OwningActor->GetActorRotation();
		const FRotator ControlRotation = OwningPawn->GetBaseAimRotation();
		const FRotator AimDelta = UKismetMathLibrary::NormalizedDeltaRotator(ControlRotation, ActorRotation); // the normalized direction from ActorRotation to ControlRotation

		// These will be choppy when replicated but we won't automatically smooth it here
		AimPitch = AimDelta.Pitch;
		AimYaw = AimDelta.Yaw;
	}

	if (OwningCharacter)
	{
		// Update movement variables
		if (UCharacterMovementComponent* CMC = OwningCharacter->GetCharacterMovement())
		{
			bGrounded = CMC->IsMovingOnGround();
			bInAir = CMC->IsFalling();
			bIsFlying = CMC->IsFlying();
			bIsSwimming = CMC->IsSwimming();

			bIsCrouching = CMC->IsCrouching();
		}
	}

	if (OwningSSCharacter)
	{

	}


	if (OwningShooterCharacter)
	{
		headLookAtRot = GetHeadLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
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

		FRotator OwningCharacterRotation = OwningShooterCharacter->GetActorRotation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(SelfHeadLocation, locationToLookAt);

		FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(OwningCharacterRotation, LookAtRotation);
		if (UKismetMathLibrary::Abs(DeltaRotator.Roll) < headMaxRollRot && UKismetMathLibrary::Abs(DeltaRotator.Pitch) < headMaxPitchRot && UKismetMathLibrary::Abs(DeltaRotator.Yaw) < headMaxYawRot)	// If the head can rotate this far
		{
			FRotator hardLookAtRot;
			hardLookAtRot.Roll = LookAtRotation.Roll - OwningCharacterRotation.Roll;
			hardLookAtRot.Pitch = (LookAtRotation.Pitch - OwningCharacterRotation.Pitch) * -1;
			hardLookAtRot.Yaw = LookAtRotation.Yaw - OwningCharacterRotation.Yaw;

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
