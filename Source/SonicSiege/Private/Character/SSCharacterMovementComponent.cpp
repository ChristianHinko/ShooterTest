// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSCharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"



USSCharacterMovementComponent::USSCharacterMovementComponent()
{
	walkSpeed = 600.0f;
	runSpeed = 1600.0f;
	walkAcceleration = 4000.0f;
	runAccelaration = 16000.0f;
}


#pragma region Move Requests
void USSCharacterMovementComponent::SetWantsToRun(bool newWantsToRun)
{
	bWantsToRun = newWantsToRun;
	OnWantsToRun.Broadcast();
}
#pragma endregion

#pragma region Saved Move
void FSavedMove_SSCharacter::Clear()
{
	Super::Clear();

	// Clear all values
	bSavedWantsToRun = 0;
}

void FSavedMove_SSCharacter::PrepMoveFor(class ACharacter* Character) // Client only
{
	Super::PrepMoveFor(Character);


	USSCharacterMovementComponent* CMC = Cast<USSCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CMC)
	{
		// WE ARE GETTING READY TO CORRECT A CLIENT PREDICTIVE ERROR
		// Copy values out of the saved move to use for a client correction
		CMC->bWantsToRun = bSavedWantsToRun;
	}
}

void FSavedMove_SSCharacter::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	USSCharacterMovementComponent* CMC = static_cast<USSCharacterMovementComponent*>(Character->GetCharacterMovement());
	if (CMC)
	{
		// Copy values into the saved move to send to the server
		bSavedWantsToRun = CMC->bWantsToRun;
	}
}

bool FSavedMove_SSCharacter::CanCombineWith(const FSavedMovePtr& NewMovePtr, ACharacter* Character, float MaxDelta) const
{
	const FSavedMove_SSCharacter* NewMove = static_cast<const FSavedMove_SSCharacter*>(NewMovePtr.Get());

	// As an optimization, check if the we can combine saved moves.
	if (bSavedWantsToRun != NewMove->bSavedWantsToRun)
	{
		return false;
	}

	return Super::CanCombineWith(NewMovePtr, Character, MaxDelta);
}

uint8 FSavedMove_SSCharacter::GetCompressedFlags() const
{
	uint8 retVal = Super::GetCompressedFlags();

	// Write to the return value's flags to match our current move state
	if (bSavedWantsToRun)
	{
		retVal |= FLAG_Custom_0;
	}

	// return the compressed flags that represent our desired moves
	return retVal;
}

void USSCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	// Update this CMC with the info stored in the compressed flags
	bWantsToRun = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}
#pragma endregion

void USSCharacterMovementComponent::OnMovementUpdated(float deltaTime, const FVector& OldLocation, const FVector& OldVelocity)
{
	//Super::OnMovementUpdated(deltaTime, OldLocation, OldVelocity);	// empty super



}

#pragma region Custom Getters
float USSCharacterMovementComponent::GetMaxSpeed() const
{
	// The super already switches through MovementMode. We do it before they do to implement our custom values for specific movement modes.
	// By default, the cases break and proceed to the super's switch
	switch (MovementMode)
	{
	case MOVE_None:
		break;
	case MOVE_Walking:
	case MOVE_NavWalking:
	{
		if (IsCrouching())
		{
			return MaxWalkSpeedCrouched;
		}
		else
		{
			if (bWantsToRun)
			{
				return runSpeed;
			}

			return walkSpeed;
		}
	}
	case MOVE_Falling:
		break;
	case MOVE_Swimming:
		break;
	case MOVE_Flying:
		break;
	case MOVE_Custom:
	{
		switch (CustomMovementMode)
		{
		case CMOVE_None:
			break;
		case CMOVE_InfiniteAngleWalking:
			break;
		default:
			return MaxCustomMovementSpeed;
		}
	}
	default:
		break;
	}


	return Super::GetMaxSpeed();
}

float USSCharacterMovementComponent::GetMaxAcceleration() const
{
	// By default, the cases break and proceed to the super's MaxAcceleration
	switch (MovementMode)
	{
	case MOVE_None:
		break;
	case MOVE_Walking:
	case MOVE_NavWalking:
	{
		if (bWantsToRun)
		{
			return runAccelaration;
		}

		return walkAcceleration;
	}
	case MOVE_Falling:
		break;
	case MOVE_Swimming:
		break;
	case MOVE_Flying:
		break;
	case MOVE_Custom:
		switch (CustomMovementMode)
		{
		case CMOVE_None:
			break;
		case CMOVE_InfiniteAngleWalking:
			break;
		default:
			break;
		}
	default:
		break;
	}


	return Super::GetMaxAcceleration();
}
#pragma endregion

#pragma region Movement Mode and Physics
FString USSCharacterMovementComponent::GetMovementName() const
{
	if (MovementMode == MOVE_Custom)
	{
		switch (CustomMovementMode)
		{
		case CMOVE_None:						return TEXT("Custom_None"); break;
		case CMOVE_InfiniteAngleWalking:		return TEXT("Custom_InfiniteAngleWalking"); break;
		default:								break;
		}
	}


	return Super::GetMovementName();
}

void USSCharacterMovementComponent::SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
	Super::SetMovementMode(NewMovementMode, NewCustomMode);


	CustomMovementMode = static_cast<TEnumAsByte<ECustomMovementMode>>(NewCustomMode);	//legacy? (this oculd be causing the TEnumAsByte warnings)
}

void USSCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
}

void USSCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);


	switch (CustomMovementMode)
	{
	case CMOVE_None:
		break;
	case CMOVE_InfiniteAngleWalking:
		PhysInfiniteAngleWalking(deltaTime, Iterations);
		break;
	default:
		UE_LOG(LogCharacterMovementSetup, Warning, TEXT("%s has unsupported custom movement mode %d"), *CharacterOwner->GetName(), int32(CustomMovementMode));
		SetMovementMode(EMovementMode::MOVE_Custom, ECustomMovementMode::CMOVE_None);
		break;
	}
}

#pragma region Custom Physics
void USSCharacterMovementComponent::PhysInfiniteAngleWalking(float deltaTime, int32 Iterations)
{

}
#pragma endregion
#pragma endregion

#pragma region Prediciton Data
FNetworkPredictionData_Client* USSCharacterMovementComponent::GetPredictionData_Client() const
{
	if (ClientPredictionData == nullptr)
	{
		// Return our custom client prediction class instead
		USSCharacterMovementComponent* MutableThis = const_cast<USSCharacterMovementComponent*>(this);
		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_SSCharacter(*this);
	}

	return ClientPredictionData;
}


FNetworkPredictionData_Client_SSCharacter::FNetworkPredictionData_Client_SSCharacter(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{

}

FSavedMovePtr FNetworkPredictionData_Client_SSCharacter::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_SSCharacter());
}
#pragma endregion
