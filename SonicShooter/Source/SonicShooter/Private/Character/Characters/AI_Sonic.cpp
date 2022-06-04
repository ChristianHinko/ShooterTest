// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/AI_Sonic.h"

#include "Character/C_Shooter.h"
#include "Kismet/KismetMathLibrary.h"



UAI_Sonic::UAI_Sonic(const FObjectInitializer& ObjectInitializer)
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

void UAI_Sonic::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (USkeletalMeshComponent* SkelMesh = GetSkelMeshComponent())
	{
		REyeDynamicMat = SkelMesh->CreateDynamicMaterialInstance(5);
		LEyeDynamicMat = SkelMesh->CreateDynamicMaterialInstance(6);
	}
}
void UAI_Sonic::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
	
	if (OwningShooterCharacter.IsValid())
	{
		LookTarget = GetNearestPawn(OwningShooterCharacter.Get());
		if (LookTarget.IsValid())
		{
			RightEyelookRot = Look(TEXT("u_Eye_r"), LookTarget.Get(), DeltaTimeX);
			LeftEyelookRot = Look(TEXT("u_Eye_l"), LookTarget.Get(), DeltaTimeX);


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

FRotator UAI_Sonic::Look(FName boneName, AActor* lookTarget, float deltaTime)
{
	if (!lookTarget || !OwningShooterCharacter.IsValid())
	{
		return FRotator::ZeroRotator;
	}




	FVector boneLocation;
	if (OwningShooterCharacter->GetMesh())
	{
		boneLocation = OwningShooterCharacter->GetMesh()->GetSocketLocation(boneName);
	}


	FVector targetLocation;
	if (AC_Shooter* ShooterCharacterToLookAt = Cast<AC_Shooter>(lookTarget))
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
