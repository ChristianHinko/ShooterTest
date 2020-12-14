// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/SonicAnimInstance.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"

USonicAnimInstance::USonicAnimInstance()
{
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

void USonicAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();


	REyeDynamicMat = UMaterialInstanceDynamic::Create(REyeMatRef, this);
	LEyeDynamicMat = UMaterialInstanceDynamic::Create(LEyeMatRef, this);
}

void USonicAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (OwningShooterCharacter)
	{
		rEyeLookAtRot = GetREyeLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
		REyeDynamicMat->SetScalarParameterValue("U", rEyeLookAtRot.Pitch);
		REyeDynamicMat->SetScalarParameterValue("V", rEyeLookAtRot.Yaw);

		lEyeLookAtRot = GetLEyeLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
		LEyeDynamicMat->SetScalarParameterValue("U", rEyeLookAtRot.Pitch);
		LEyeDynamicMat->SetScalarParameterValue("V", rEyeLookAtRot.Yaw);


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
		if (UKismetMathLibrary::Abs(DeltaRotator.Roll) < rEyeMaxRollRot && UKismetMathLibrary::Abs(DeltaRotator.Yaw) < rEyeMaxYawRot)	// If the rEye can rotate this far
		{
			FRotator hardLookAtRot;
			hardLookAtRot.Roll = LookAtRotation.Roll - OwningCharacterRotation.Roll;
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
FRotator USonicAnimInstance::GetLEyeLookAtTargetRot(AActor* Target, float deltaTime)
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
		if (UKismetMathLibrary::Abs(DeltaRotator.Roll) < lEyeMaxRollRot && UKismetMathLibrary::Abs(DeltaRotator.Yaw) < lEyeMaxYawRot)	// If the lEye can rotate this far
		{
			FRotator hardLookAtRot;
			hardLookAtRot.Roll = LookAtRotation.Roll - OwningCharacterRotation.Roll;
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

