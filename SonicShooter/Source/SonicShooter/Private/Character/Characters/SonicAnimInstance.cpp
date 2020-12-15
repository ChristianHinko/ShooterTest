// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/SonicAnimInstance.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"

USonicAnimInstance::USonicAnimInstance()
{
	lookAtTargetRot = FRotator::ZeroRotator;
	rEyeLookSpeed = 3;
	rEyeLookAtAlpha = 1;
	rEyeMaxRollRot = 185;
	rEyeMaxPitchRot = 185;
	rEyeMaxYawRot = 185;


	lEyeLookSpeed = 3;
	lEyeLookAtAlpha = 1;
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
		lookAtTargetRot = GetHeadLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
		float uCoordinateOffset = ((lookAtTargetRot.Yaw / 360) * 1.5);
		float vCoordinateOffset = ((lookAtTargetRot.Pitch / 360) * 1.5);
		if (REyeDynamicMat && LEyeDynamicMat)
		{
			// Move the eyes by moving their UV coordinates

			// Right Eye
			REyeDynamicMat->SetScalarParameterValue(TEXT("U"), uCoordinateOffset * rEyeLookAtAlpha);
			REyeDynamicMat->SetScalarParameterValue(TEXT("V"), vCoordinateOffset * rEyeLookAtAlpha);

			// Left Eye
			LEyeDynamicMat->SetScalarParameterValue(TEXT("U"), (uCoordinateOffset * -1) * lEyeLookAtAlpha);		// Texture was mirrored on the x axis so negate
			LEyeDynamicMat->SetScalarParameterValue(TEXT("V"), vCoordinateOffset * lEyeLookAtAlpha);
		}


	}
}

FRotator USonicAnimInstance::GetHeadLookAtTargetRot(AActor* Target, float deltaTime)
{
	FRotator retVal = FRotator::ZeroRotator;
	if (OwningShooterCharacter && Target)
	{
		FVector SelfHeadBoneLocation;
		if (OwningShooterCharacter->GetMesh())
		{
			SelfHeadBoneLocation = OwningShooterCharacter->GetMesh()->GetSocketLocation(TEXT("head"));
		}
		FVector targetLocation;
		if (AShooterCharacter* ShooterCharacterToLookAt = Cast<AShooterCharacter>(Target))
		{
			if (ShooterCharacterToLookAt->GetMesh())
			{
				targetLocation = ShooterCharacterToLookAt->GetMesh()->GetSocketLocation(TEXT("head"));
			}
		}

		FRotator OwningCharacterRotation = OwningShooterCharacter->GetActorRotation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(SelfHeadBoneLocation, targetLocation);

		FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(OwningCharacterRotation, LookAtRotation);
		if (UKismetMathLibrary::Abs(DeltaRotator.Roll) < rEyeMaxRollRot && UKismetMathLibrary::Abs(DeltaRotator.Yaw) < rEyeMaxYawRot)	// If the rEye can rotate this far
		{
			FRotator hardLookAtRot = LookAtRotation - OwningCharacterRotation;

			FRotator softLookAtRot = FMath::RInterpTo(lookAtTargetRot, hardLookAtRot, deltaTime, rEyeLookSpeed);

			retVal = softLookAtRot;
		}
		else
		{
			FRotator softLookAtRot = FMath::RInterpTo(lookAtTargetRot, FRotator::ZeroRotator, deltaTime, rEyeLookSpeed);

			retVal = softLookAtRot;
		}
	}

	return retVal;
}

