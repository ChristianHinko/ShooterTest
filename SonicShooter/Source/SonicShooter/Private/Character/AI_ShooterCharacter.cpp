// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\AI_ShooterCharacter.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/SSCharacter.h"
#include "Character/C_Shooter.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

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


	OwningShooterCharacter = Cast<AC_Shooter>(GetOwningActor());
}
void UAI_ShooterCharacter::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);


	if (const AC_Shooter* ShooterCharacter = OwningShooterCharacter.Get())
	{
#pragma region Owning Actor work
		ActorRotation = ShooterCharacter->GetActorRotation();

		Velocity = ShooterCharacter->GetVelocity();
		Speed = Velocity.Size();

		ForwardSpeed = Velocity.ProjectOnTo(ShooterCharacter->GetActorForwardVector()).Size();
		RightSpeed = Velocity.ProjectOnTo(ShooterCharacter->GetActorRightVector()).Size();
		UpSpeed = Velocity.ProjectOnTo(ShooterCharacter->GetActorUpVector()).Size();

		// TODO: make this more optimized ( "Velocity.ProjectOnToNormal(UpVector).Size()" isn't working some reason )
		HorizontalSpeed = FMath::Sqrt(FMath::Square(ForwardSpeed) + FMath::Square(RightSpeed));

		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, ShooterCharacter->GetActorRotation()); // TODO: make sure this is relative to the actor's rotation
#pragma endregion





#pragma region Owning Pawn work
		AimRotation = ShooterCharacter->GetBaseAimRotation();	// this will be choppy when replicated but we won't automatically smooth it here

		TurnInPlace(DeltaTimeX);
		MeshRotation = ActorRotation + FRotator(0.f, TurnInPlaceYawOffset, 0.f);

		const FRotator AimOffset = UKismetMathLibrary::NormalizedDeltaRotator(AimRotation, MeshRotation); // the normalized direction from ActorRotation to ControlRotation
		AimOffsetPitch = AimOffset.Pitch;
		AimOffsetYaw = AimOffset.Yaw;
#pragma endregion






#pragma region Owning Charcter work
		// Update movement variables
		if (UCharacterMovementComponent* CMC = ShooterCharacter->GetCharacterMovement())
		{
			bGrounded = CMC->IsMovingOnGround();
			bInAir = CMC->IsFalling();
			bIsFlying = CMC->IsFlying();
			bIsSwimming = CMC->IsSwimming();

			bIsCrouching = CMC->IsCrouching();
		}


#pragma endregion





#pragma region Owning ShooterChractor work
		headLookAtRot = GetHeadLookAtTargetRot(GetNearestPawn(ShooterCharacter), DeltaTimeX);
#pragma endregion
	}



	PreviousActorRotation = ActorRotation;
}

bool UAI_ShooterCharacter::IsTurnInPlaceEnabled() const
{
	// Right now our TIP system is only meant for bUseControllerRotationYaw
	if (OwningShooterCharacter->bUseControllerRotationYaw == false)
	{
		return false;
	}

	return true;
}
bool UAI_ShooterCharacter::IsTurnInPlaceAvailable() const
{
	// Only do TIP offsetting if we are staying still
	if (FMath::IsNearlyZero(Speed) == false)
	{
		return false;
	}

	return true;
}
void UAI_ShooterCharacter::TurnInPlace(float DeltaTimeX)
{
	bTurnInPlaceEnabled = IsTurnInPlaceEnabled();
	if (bTurnInPlaceEnabled)
	{
		// Store previous states
		const bool previousTurnInPlaceAvailable = bTurnInPlaceAvailable;
		const bool previousIsTurningInPlace = bIsTurningInPlace;

		// Check TIP availability
		bTurnInPlaceAvailable = IsTurnInPlaceAvailable();
		if (bTurnInPlaceAvailable == true && previousTurnInPlaceAvailable == false)
		{
			// TIP just became available this tick
			TurnInPlaceStartingYaw = ActorRotation.Yaw;
		}



		// Start turning back to normal if TIP isn't available anymore
		if (bTurnInPlaceAvailable == false)
		{
			bIsTurningInPlace = true;
		}

		// Update TurnInPlaceYawOffset
		const FRotator RotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(ActorRotation, PreviousActorRotation);
		TurnInPlaceYawOffset -= RotationDelta.Yaw; // negate with our Actor's increase/decrease in yaw
		TurnInPlaceYawOffset = FRotator::NormalizeAxis(TurnInPlaceYawOffset);

		// Check if we passed our TIP degree thresholds
		if (bIsTurningInPlace == false)
		{
			if (FMath::Abs(TurnInPlaceYawOffset) >= 90.f)
			{
				bIsTurningInPlace = true;
			}
		}


		// If we are turning back to normal
		if (bIsTurningInPlace)
		{
			//if (previousIsTurningInPlace == false)
			//{
			//	// We just began a TIP
			//	UKismetSystemLibrary::PrintString(this, "We just began a TIP", true, false, FLinearColor::Yellow);
			//}

			//UKismetSystemLibrary::PrintString(this, "TurnInPlaceYawOffset: " + FString::SanitizeFloat(TurnInPlaceYawOffset), true, false, FLinearColor::White);

			TurnInPlaceYawOffset = FMath::FInterpConstantTo(TurnInPlaceYawOffset, 0.f, DeltaTimeX, 100.f);
			if (FMath::IsNearlyZero(TurnInPlaceYawOffset))
			{
				//UKismetSystemLibrary::PrintString(this, "TIP goal reached", true, false, FLinearColor::Green);
				TurnInPlaceYawOffset = 0.f;
				bIsTurningInPlace = false;
				TurnInPlaceStartingYaw = ActorRotation.Yaw;
			}

		}
	}
	else
	{
		bTurnInPlaceAvailable = false;

		TurnInPlaceYawOffset = 0.f;
		bIsTurningInPlace = false;
		TurnInPlaceStartingYaw = ActorRotation.Yaw;
	}
}













FRotator UAI_ShooterCharacter::GetHeadLookAtTargetRot(AActor* Target, float deltaTime)
{
	FRotator retVal = FRotator::ZeroRotator;
	if (OwningShooterCharacter.IsValid() && Target)
	{
		FVector SelfHeadLocation;
		if (OwningShooterCharacter->GetMesh())
		{
			SelfHeadLocation = OwningShooterCharacter->GetMesh()->GetSocketLocation(TEXT("head"));
		}
		FVector locationToLookAt;
		if (AC_Shooter* ShooterCharacterToLookAt = Cast<AC_Shooter>(Target))
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

APawn* UAI_ShooterCharacter::GetNearestPawn(const AActor* InActor)
{
	APawn* RetVal = nullptr;
	if (UGameplayStatics::GetGameState(InActor))
	{
		float closestPawnDistance = MAX_FLT;
		TArray<APlayerState*> PlayerStates = UGameplayStatics::GetGameState(InActor)->PlayerArray;
		for (int32 i = 0; i < PlayerStates.Num(); ++i)
		{
			if (PlayerStates.IsValidIndex(i) && PlayerStates[i])
			{
				APawn* CurrentPawn = PlayerStates[i]->GetPawn();
				if (CurrentPawn != InActor)
				{
					float distanceToCurrentPlayer = InActor->GetDistanceTo(CurrentPawn);
					if (distanceToCurrentPlayer < closestPawnDistance)
					{
						RetVal = CurrentPawn;
						closestPawnDistance = distanceToCurrentPlayer;
					}
				}
			}
		}
	}

	return RetVal;
}
