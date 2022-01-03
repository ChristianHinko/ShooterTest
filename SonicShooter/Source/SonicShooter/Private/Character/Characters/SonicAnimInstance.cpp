// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/SonicAnimInstance.h"

#include "Character/ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"



USonicAnimInstance::USonicAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LookTarget = nullptr;
	LeftEyelookRot = FRotator::ZeroRotator;

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
		REyeDynamicMat = SkelMesh->CreateDynamicMaterialInstance(5);
		LEyeDynamicMat = SkelMesh->CreateDynamicMaterialInstance(6);
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
			RightEyelookRot = Look(TEXT("u_Eye_r"), LookTarget, DeltaTimeX);
			LeftEyelookRot = Look(TEXT("u_Eye_l"), LookTarget, DeltaTimeX);


			if (REyeDynamicMat)
			{
				float uCoordinateOffset = ((RightEyelookRot.Yaw / 360) * 1.3);
				float vCoordinateOffset = ((RightEyelookRot.Pitch / 360) * 1.3);

				// Now move the eyes by moving their UV coordinates
				// Right Eye
				REyeDynamicMat->SetScalarParameterValue(TEXT("U"), uCoordinateOffset * rEyeLookAtAlpha);
				REyeDynamicMat->SetScalarParameterValue(TEXT("V"), vCoordinateOffset * rEyeLookAtAlpha);
			}
			if (LEyeDynamicMat)
			{
				float uCoordinateOffset = ((LeftEyelookRot.Yaw / 360) * 1.3);
				float vCoordinateOffset = ((LeftEyelookRot.Pitch / 360) * 1.3);

				// Now move the eyes by moving their UV coordinates
				// Left Eye
				LEyeDynamicMat->SetScalarParameterValue(TEXT("U"), (uCoordinateOffset * -1) * lEyeLookAtAlpha);		// Texture was mirrored on the x axis so negate
				LEyeDynamicMat->SetScalarParameterValue(TEXT("V"), vCoordinateOffset * lEyeLookAtAlpha);
			}
		}


	}
}

FRotator USonicAnimInstance::Look(FName boneName, AActor* lookTarget, float deltaTime)
{
	if (!lookTarget || !OwningShooterCharacter)
	{
		return FRotator::ZeroRotator;
	}




	FVector boneLocation;
	if (OwningShooterCharacter->GetMesh())
	{
		boneLocation = OwningShooterCharacter->GetMesh()->GetSocketLocation(boneName);
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
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(boneLocation, targetLocation);

	FRotator normalizedDeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(OwningCharacterRotation, LookAtRotation);

	FRotator hardLookRot = LookAtRotation - OwningCharacterRotation;

	// Eyes
	FRotator smoothedLookRot;
	if (UKismetMathLibrary::Abs(normalizedDeltaRotator.Pitch) < eyeMaxPitchRot && UKismetMathLibrary::Abs(normalizedDeltaRotator.Yaw) < eyeMaxYawRot)	// If the eye can rotate this far
	{
		smoothedLookRot = FMath::RInterpTo(LeftEyelookRot, hardLookRot, deltaTime, eyeLookSpeed);
	}
	else
	{
		smoothedLookRot = FMath::RInterpTo(LeftEyelookRot, FRotator::ZeroRotator, deltaTime, eyeLookSpeed);
	}

	return smoothedLookRot;
}
