// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSCharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "Character/SSCharacterMovementComponent.h"
#include "Character/AbilitySystemCharacter.h"
#include "Character/AS_Character.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"

//#include "Kismet/KismetSystemLibrary.h"



USSCharacterMovementComponent::USSCharacterMovementComponent()
{

}
void USSCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerAbilitySystemCharacter = Cast<AAbilitySystemCharacter>(GetPawnOwner());
	if (OwnerAbilitySystemCharacter)
	{
		OwnerAbilitySystemCharacter->PreApplyStartupEffects.AddUObject(this, &USSCharacterMovementComponent::OnOwningCharacterAbilitySystemReady);
	}
}

void USSCharacterMovementComponent::OnOwningCharacterAbilitySystemReady()
{
	if (OwnerAbilitySystemCharacter)
	{
		OwnerSSASC = Cast<USSAbilitySystemComponent>(OwnerAbilitySystemCharacter->GetAbilitySystemComponent());
		CharacterAttributeSet = OwnerAbilitySystemCharacter->GetCharacterAttributeSet();
	}
	
	OwnerSSASC->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag("Character.Movement.RunDisabled"), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &USSCharacterMovementComponent::OnRunDisabledTagChanged);
}

void USSCharacterMovementComponent::OnRunDisabledTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount > 0)	// If RunDisabled tag present
	{
		bRunDisabled = true;
	}
	else 			    // If RunDisabled tag not present
	{
		bRunDisabled = false;
	}
}


#pragma region Move Requests
void USSCharacterMovementComponent::SetWantsToRun(bool newWantsToRun)
{
	bWantsToRun = newWantsToRun;
}
#pragma endregion

#pragma region Saved Move
void FSavedMove_SSCharacter::Clear()
{
	Super::Clear();

	// Clear all fsavedmove values
	bSavedWantsToRun = 0;
}

void FSavedMove_SSCharacter::PrepMoveFor(ACharacter* Character) // Client only
{
	Super::PrepMoveFor(Character);


	USSCharacterMovementComponent* CMC = Cast<USSCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CMC)
	{
		//																							TODO: document, fix this comment \/ \/ \/
		// WE ARE GETTING READY TO CORRECT A CLIENT PREDICTIVE ERROR
		// Copy values out of the saved move to use for a client correction
		CMC->bWantsToRun = bSavedWantsToRun;
	}
}

void FSavedMove_SSCharacter::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	USSCharacterMovementComponent* CMC = static_cast<USSCharacterMovementComponent*>(Character->GetCharacterMovement());
	if (CMC)
	{
		// Copy client values into the saved move to use for our next movement and to send to the server for the server to copy our movement
		bSavedWantsToRun = CMC->bWantsToRun;

		// DO NOT SET THE MOVEMENT RESTRICTIONS IN SET MOVE FOR WE DONT WANT THE SERVER TO LISTEN TO THE CLIENTS RESTRICTIONS					TODO: document
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
		retVal |= FLAG_WantsToRun;
	}

	// return the compressed flags that represent our desired moves for this saved move
	return retVal;
}

void USSCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	// Update this CMC with the info stored in the compressed flags
	bWantsToRun = (Flags & FLAG_WantsToRun) != 0;
}
#pragma endregion


#pragma region Client Adjust
void USSCharacterMovementComponent::ClientAdjustPosition(float TimeStamp, FVector NewLoc, FVector NewVel, UPrimitiveComponent* NewBase, FName NewBaseBoneName, bool bHasBase, bool bBaseRelativePosition, uint8 ServerMovementMode)
{
	Super::ClientAdjustPosition(TimeStamp, NewLoc, NewVel, NewBase, NewBaseBoneName, bHasBase, bBaseRelativePosition, ServerMovementMode);


	//SSClientAdjustPosition();
}

//void USSCharacterMovementComponent::SSClientAdjustPosition_Implementation()
//{
//	
//}
#pragma endregion

void USSCharacterMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);


	if (CharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		if (bIsRunning && (!bWantsToRun || !CanRunInCurrentState()))
		{
			bIsRunning = false;
		}
		else if (!bIsRunning && bWantsToRun && CanRunInCurrentState())
		{
			bIsRunning = true;
		}
	}
}

bool USSCharacterMovementComponent::CanCrouchInCurrentState() const
{
	if (!IsMovingOnGround())
	{
		return false;
	}

	return Super::CanCrouchInCurrentState();
}

bool USSCharacterMovementComponent::CanRunInCurrentState() const
{
	if (!IsMovingOnGround())
	{
		return false;
	}

	return true;
}


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
			if (!CharacterAttributeSet)
			{
				UE_LOG(LogCharacterMovement, Error, TEXT("CharacterAttributeSet was NULL when trying to return a speed value"));
				return 0;
			}

			if (bIsRunning && bRunDisabled == false)
			{
				return CharacterAttributeSet->GetRunSpeed();
			}
			return CharacterAttributeSet->GetWalkSpeed();
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
		if (!CharacterAttributeSet)
		{
			UE_LOG(LogCharacterMovement, Error, TEXT("CharacterAttributeSet was NULL when trying to return a acceleration value"));
			return 0;
		}

		if (bIsRunning && bRunDisabled == false)
		{
			return CharacterAttributeSet->GetRunAccelaration();
		}
		return CharacterAttributeSet->GetWalkAcceleration();;
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


	CustomMovementMode = static_cast<TEnumAsByte<ECustomMovementMode>>(NewCustomMode);
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

#pragma region Prediciton Data Client
FNetworkPredictionData_Client* USSCharacterMovementComponent::GetPredictionData_Client() const
{
	if (ClientPredictionData == nullptr)
	{
		// Return our custom client prediction struct instead
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


#pragma region MovementHelpers
bool USSCharacterMovementComponent::IsMovingForward(/*float degreeTolerance*/)
{
	/**
	 * At dot product 0.7 you are looking at a 45 degrees angle
	 * For 25 degrees tolerance use > 0.9
	 * 0.99 gives you 8 degrees of tolerance
	 * 
	 * ACOS(dot product) is the formula. Incidentally, it's the formula to find the angle between two vectors
	 */
	FVector CharacterNormalizedVel = CharacterOwner->GetVelocity();
	CharacterNormalizedVel.Normalize();
	FVector CharacterFwd = CharacterOwner->GetActorForwardVector();
	float dotProd = FVector::DotProduct(CharacterNormalizedVel, CharacterFwd);

	

	//float cmpVal = acosf(dotProd);	// we need to find the cmpVal

	if (dotProd > .99f/*cmpVal should go here but don't know how to calculate it yet*/)
	{
		return true;
	}


	return false;
}
#pragma endregion
