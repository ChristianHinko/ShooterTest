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




}

void UShooterCharacterAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	OwningShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	
	if (OwningShooterCharacter)
	{
		headLookAtRot = GetHeadLookAtTargetRot(OwningShooterCharacter->GetNearestPawn(), DeltaTimeX);
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
