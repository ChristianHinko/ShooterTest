// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/SonicAnimInstance.h"
#include "Character/ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"

USonicAnimInstance::USonicAnimInstance()
{
	LookTarget = nullptr;
	lookRot = FRotator::ZeroRotator;

	eyeLookSpeed = 3;
	eyeMaxPitchRot = 85;
	eyeMaxYawRot = 85;


	rEyeLookAtAlpha = 1;
	lEyeLookAtAlpha = 1;
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
		LookTarget = OwningShooterCharacter->GetNearestPawn();
		if (LookTarget)
		{
			lookRot = Look(LookTarget, DeltaTimeX);


			if (REyeDynamicMat && LEyeDynamicMat)
			{
				float uCoordinateOffset = ((lookRot.Yaw / 360) * 1.5);
				float vCoordinateOffset = ((lookRot.Pitch / 360) * 1.5);

				// Now move the eyes by moving their UV coordinates
				// Right Eye
				REyeDynamicMat->SetScalarParameterValue(TEXT("U"), uCoordinateOffset * rEyeLookAtAlpha);
				REyeDynamicMat->SetScalarParameterValue(TEXT("V"), vCoordinateOffset * rEyeLookAtAlpha);
				// Left Eye
				LEyeDynamicMat->SetScalarParameterValue(TEXT("U"), (uCoordinateOffset * -1) * lEyeLookAtAlpha);		// Texture was mirrored on the x axis so negate
				LEyeDynamicMat->SetScalarParameterValue(TEXT("V"), vCoordinateOffset * lEyeLookAtAlpha);
			}
		}


	}
}

FRotator USonicAnimInstance::Look(AActor* lookTarget, float deltaTime)
{
	if (!lookTarget || !OwningShooterCharacter)
	{
		return FRotator::ZeroRotator;
	}



	FVector SelfHeadBoneLocation;
	if (OwningShooterCharacter->GetMesh())
	{
		SelfHeadBoneLocation = OwningShooterCharacter->GetMesh()->GetSocketLocation(TEXT("head"));
	}
	FVector targetLocation;
	if (AShooterCharacter* ShooterCharacterToLookAt = Cast<AShooterCharacter>(lookTarget))
	{
		if (ShooterCharacterToLookAt->GetMesh())
		{
			targetLocation = ShooterCharacterToLookAt->GetMesh()->GetSocketLocation(TEXT("head"));
		}
	}

	FRotator OwningCharacterRotation = OwningShooterCharacter->GetActorRotation();
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(SelfHeadBoneLocation, targetLocation);

	FRotator normalizedDeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(OwningCharacterRotation, LookAtRotation);

	FRotator hardLookRot = LookAtRotation - OwningCharacterRotation;

	// Eyes
	FRotator smoothedLookRot;
	if (UKismetMathLibrary::Abs(normalizedDeltaRotator.Pitch) < eyeMaxPitchRot && UKismetMathLibrary::Abs(normalizedDeltaRotator.Yaw) < eyeMaxYawRot)	// If the eye can rotate this far
	{
		smoothedLookRot = FMath::RInterpTo(lookRot, hardLookRot, deltaTime, eyeLookSpeed);
	}
	else
	{
		smoothedLookRot = FMath::RInterpTo(lookRot, FRotator::ZeroRotator, deltaTime, eyeLookSpeed);
	}

	return smoothedLookRot;
}

