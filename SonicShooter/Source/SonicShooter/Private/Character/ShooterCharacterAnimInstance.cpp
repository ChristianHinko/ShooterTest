// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\ShooterCharacterAnimInstance.h"

#include "Kismet/KismetMathLibrary.h"
#include "Character/ShooterCharacter.h"

UShooterCharacterAnimInstance::UShooterCharacterAnimInstance()
{
	headLookAtRot = FRotator::ZeroRotator;
	headLookSpeed = 3;
	headLookAtAlpha = 0;
	headMaxRollRot = 85;
	headMaxPitchRot = 85;
	headMaxYawRot = 85;


	rEyeLookAtRot = FRotator::ZeroRotator;
	rEyeLookSpeed = 3;
	rEyeLookAtAlpha = .35f;
	rEyeMaxRollRot = 85;
	rEyeMaxPitchRot = 85;
	rEyeMaxYawRot = 85;


	lEyeLookAtRot = FRotator::ZeroRotator;
	lEyeLookSpeed = 3;
	lEyeLookAtAlpha = .35f;
	lEyeMaxRollRot = 85;
	lEyeMaxPitchRot = 85;
	lEyeMaxYawRot = 85;


}

void UShooterCharacterAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	OwningShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	
	if (OwningShooterCharacter)
	{
		headLookAtRot = GetHeadLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
		rEyeLookAtRot = GetREyeLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
		lEyeLookAtRot = GetLEyeLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
	}
}

FRotator UShooterCharacterAnimInstance::GetHeadLookAtTargetRot(AActor* Target, float deltaTime)
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
FRotator UShooterCharacterAnimInstance::GetREyeLookAtTargetRot(AActor* Target, float deltaTime)
{
	FRotator retVal = FRotator::ZeroRotator;
	if (OwningShooterCharacter && Target)
	{
		FVector SelfREyeLocation;
		if (OwningShooterCharacter->GetMesh())
		{
			SelfREyeLocation = OwningShooterCharacter->GetMesh()->GetSocketLocation(TEXT("u_EyeRot_R"));
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
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(SelfREyeLocation, locationToLookAt);

		FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(OwningCharacterRotation, LookAtRotation);
		if (UKismetMathLibrary::Abs(DeltaRotator.Roll) < rEyeMaxRollRot && UKismetMathLibrary::Abs(DeltaRotator.Pitch) < rEyeMaxPitchRot && UKismetMathLibrary::Abs(DeltaRotator.Yaw) < rEyeMaxYawRot)	// If the rEye can rotate this far
		{
			FRotator hardLookAtRot;
			hardLookAtRot.Roll = LookAtRotation.Roll - OwningCharacterRotation.Roll;
			hardLookAtRot.Pitch = (LookAtRotation.Pitch - OwningCharacterRotation.Pitch) * -1;
			hardLookAtRot.Yaw = LookAtRotation.Yaw - OwningCharacterRotation.Yaw;


			FRotator softLookAtRot = FMath::RInterpTo(rEyeLookAtRot, hardLookAtRot, deltaTime, rEyeLookSpeed);

			retVal = softLookAtRot;
		}
		else
		{
			FRotator softLookAtRot = FMath::RInterpTo(rEyeLookAtRot, FRotator::ZeroRotator, deltaTime, rEyeLookSpeed);

			retVal = softLookAtRot;
		}
	}

	return retVal;
}
FRotator UShooterCharacterAnimInstance::GetLEyeLookAtTargetRot(AActor* Target, float deltaTime)
{
	FRotator retVal = FRotator::ZeroRotator;
	if (OwningShooterCharacter && Target)
	{
		FVector SelfLEyeLocation;
		if (OwningShooterCharacter->GetMesh())
		{
			SelfLEyeLocation = OwningShooterCharacter->GetMesh()->GetSocketLocation(TEXT("u_EyeRot_L"));
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
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(SelfLEyeLocation, locationToLookAt);

		FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(OwningCharacterRotation, LookAtRotation);
		if (UKismetMathLibrary::Abs(DeltaRotator.Roll) < lEyeMaxRollRot && UKismetMathLibrary::Abs(DeltaRotator.Pitch) < lEyeMaxPitchRot && UKismetMathLibrary::Abs(DeltaRotator.Yaw) < lEyeMaxYawRot)	// If the lEye can rotate this far
		{
			FRotator hardLookAtRot;
			hardLookAtRot.Roll = LookAtRotation.Roll - OwningCharacterRotation.Roll;
			hardLookAtRot.Pitch = (LookAtRotation.Pitch - OwningCharacterRotation.Pitch) * -1;
			hardLookAtRot.Yaw = LookAtRotation.Yaw - OwningCharacterRotation.Yaw;


			FRotator softLookAtRot = FMath::RInterpTo(lEyeLookAtRot, hardLookAtRot, deltaTime, lEyeLookSpeed);

			retVal = softLookAtRot;
		}
		else
		{
			FRotator softLookAtRot = FMath::RInterpTo(lEyeLookAtRot, FRotator::ZeroRotator, deltaTime, lEyeLookSpeed);

			retVal = softLookAtRot;
		}
	}

	return retVal;
}
