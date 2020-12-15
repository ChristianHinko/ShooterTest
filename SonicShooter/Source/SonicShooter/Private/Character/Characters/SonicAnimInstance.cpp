// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/SonicAnimInstance.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"

USonicAnimInstance::USonicAnimInstance()
{
	rEyeLookAtRot = FRotator::ZeroRotator;
	rEyeLookSpeed = 3;
	rEyeMaxRollRot = 185;
	rEyeMaxPitchRot = 185;
	rEyeMaxYawRot = 185;


	lEyeLookAtRot = FRotator::ZeroRotator;
	lEyeLookSpeed = 3;
	lEyeMaxRollRot = 185;
	lEyeMaxPitchRot = 185;
	lEyeMaxYawRot = 185;
}

void USonicAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (USkeletalMeshComponent* SkelMesh = GetSkelMeshComponent())
	{
		REyeDynamicMat = SkelMesh->CreateDynamicMaterialInstance(3);
		LEyeDynamicMat = SkelMesh->CreateDynamicMaterialInstance(4);
	}
}

void USonicAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
	
	if (OwningShooterCharacter)
	{
		rEyeLookAtRot = GetREyeLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
		float lookAmt = 1.5;
		float uCoordinateOffset = (rEyeLookAtRot.Yaw / 360) * lookAmt;
		float vCoordinateOffset = (rEyeLookAtRot.Pitch / 360) * lookAmt;
		if (REyeDynamicMat)
		{
			REyeDynamicMat->SetScalarParameterValue(TEXT("U"), uCoordinateOffset);
			REyeDynamicMat->SetScalarParameterValue(TEXT("V"), vCoordinateOffset);

		}

		lEyeLookAtRot = GetLEyeLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
		if (LEyeDynamicMat)
		{
			LEyeDynamicMat->SetScalarParameterValue(TEXT("U"), (uCoordinateOffset) * -1);	// Texture was mirrored on the x so negate
			LEyeDynamicMat->SetScalarParameterValue(TEXT("V"), vCoordinateOffset);
		}


	}
}

FRotator USonicAnimInstance::GetREyeLookAtTargetRot(AActor* Target, float deltaTime)
{
	FRotator retVal = FRotator::ZeroRotator;
	if (OwningShooterCharacter && Target)
	{
		FVector SelfREyeLocation;
		if (OwningShooterCharacter->GetMesh())
		{
			SelfREyeLocation = OwningShooterCharacter->GetMesh()->GetSocketLocation(TEXT("head"));
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
		if (UKismetMathLibrary::Abs(DeltaRotator.Roll) < rEyeMaxRollRot && UKismetMathLibrary::Abs(DeltaRotator.Yaw) < rEyeMaxYawRot)	// If the rEye can rotate this far
		{
			FRotator hardLookAtRot = LookAtRotation - OwningCharacterRotation;

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
FRotator USonicAnimInstance::GetLEyeLookAtTargetRot(AActor* Target, float deltaTime)
{
	FRotator retVal = FRotator::ZeroRotator;
	if (OwningShooterCharacter && Target)
	{
		FVector SelfLEyeLocation;
		if (OwningShooterCharacter->GetMesh())
		{
			SelfLEyeLocation = OwningShooterCharacter->GetMesh()->GetSocketLocation(TEXT("head"));
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
		if (UKismetMathLibrary::Abs(DeltaRotator.Roll) < lEyeMaxRollRot && UKismetMathLibrary::Abs(DeltaRotator.Yaw) < lEyeMaxYawRot)	// If the lEye can rotate this far
		{
			FRotator hardLookAtRot = LookAtRotation - OwningCharacterRotation;


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

