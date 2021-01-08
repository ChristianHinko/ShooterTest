// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSCharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "Character/SSCharacterMovementComponent.h"
#include "Character/AbilitySystemCharacter.h"
#include "Character/AS_Character.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Kismet/KismetMathLibrary.h"

#include "Kismet/KismetSystemLibrary.h"



USSCharacterMovementComponent::USSCharacterMovementComponent()
{
	CVarToggleCrouchChangeDelegate.BindUFunction(this, TEXT("CVarToggleCrouchChanged"));
	UCVarChangeListenerManager::AddBoolCVarCallbackStatic(TEXT("input.ToggleCrouch"), CVarToggleCrouchChangeDelegate, true);
	
	CVarToggleRunChangeDelegate.BindUFunction(this, TEXT("CVarToggleRunChanged"));
	UCVarChangeListenerManager::AddBoolCVarCallbackStatic(TEXT("input.ToggleRun"), CVarToggleRunChangeDelegate, true);

	bCrouchCancelsDesireToRun = true;
	bRunCancelsDesireToCrouch = true;
	bJumpCancelsDesireToCrouch = true;
	bJumpCancelsDesireToRun = false;


	bCanCrouchJump = false;
	bCanWalkOffLedgesWhenCrouching = true;
}

void USSCharacterMovementComponent::CVarToggleCrouchChanged(bool newToggleCrouch)
{
	bToggleCrouchEnabled = newToggleCrouch;
}
void USSCharacterMovementComponent::CVarToggleRunChanged(bool newToggleRun)
{
	bToggleRunEnabled = newToggleRun;
}

void USSCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();


	// Get reference to our SSCharacter
	OwnerSSCharacter = Cast<ASSCharacter>(PawnOwner);

	// Get reference to our AbilitySystemCharacter
	OwnerAbilitySystemCharacter = Cast<AAbilitySystemCharacter>(OwnerSSCharacter);

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

	if (OwnerSSASC)
	{
		OwnerSSASC->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag("Character.Movement.RunDisabled"), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &USSCharacterMovementComponent::OnRunDisabledTagChanged);
	}

	if (CharacterAttributeSet)
	{
		CharacterAttributeSet->OnStaminaFullyDrained.AddUObject(this, &USSCharacterMovementComponent::OnStaminaFullyDrained);
	}
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
	if (bWantsToRun != newWantsToRun)
	{
		bWantsToRun = newWantsToRun;

		if (bWantsToRun == true)
		{
			timestampWantsToRun = GetWorld()->GetTimeSeconds();
		}
		else
		{
			timestampWantsToRun = -1 * GetWorld()->GetTimeSeconds();
		}
	}
}
#pragma endregion

void USSCharacterMovementComponent::TweakCompressedFlagsBeforeTick()
{
	////////////////////////////////////////////////////////////////////////////// WantsTo Calculations //////////
	
	// When calculation whether we want to run or not, modify this. We will
	// set bWantsToRun to this using SetWantsToRun() at the end of our calculations.
	// The reason we do this is to avoid messing up timestamps or
	// calling it multiple times for no reason.
	bool newWantsToRun = bWantsToRun;


	if (CharacterAttributeSet && CharacterAttributeSet->GetStamina() <= 0.f)
	{
		if (IsMovingOnGround()) // only if we are on the ground. if we are in the air, the player will be expecting to run anyways
		{
			// We don't want to run if we are fully out of stamina or else when stamina starts regening we would run right away and be back at zero stamina
			newWantsToRun = false;
		}
	}

	bool isMovingForward = IsMovingForward();

	if (!isMovingForward)
	{
		newWantsToRun = false; // a client-only check to ensure we are moving forward (i know this is bad, it's not server verified but it's temporary so i guess hackers can run backwards if they want)
	}
	if (currentTimeSeconds == -timestampWantsToRun)
	{
		if (!IsMovingOnGround() && bToggleRunEnabled && isMovingForward)
		{
			// If you're in the air moving forward (only if in toggle mode) you probably still want to run, whether you are
			// trying to stop or not
			newWantsToRun = true;
		}
	}

	// Call SetWantsToRun() using our calculated value of newWantsToRun
	SetWantsToRun(newWantsToRun);




	////////////////////////////////////////////////////////////////////////////// Desire Cancellations (for Toggle Modes) //////////


	if (currentTimeSeconds == timestampWantsToJump)
	{
		if (bJumpCancelsDesireToCrouch)
		{
			if (bToggleCrouchEnabled && bWantsToCrouch)
			{
				CharacterOwner->UnCrouch();
			}
		}
		if (bJumpCancelsDesireToRun)
		{
			if (GetToggleRunEnabled() && bWantsToRun)
			{
				SetWantsToRun(false);
			}
		}
	}

	if (currentTimeSeconds == timestampWantsToCrouch)
	{
		if (bCrouchCancelsDesireToRun)
		{
			if (bToggleRunEnabled && GetWantsToRun())
			{
				SetWantsToRun(false);
			}
		}
	}

	if (currentTimeSeconds == timestampWantsToRun)
	{
		if (bRunCancelsDesireToCrouch)
		{
			if (bToggleCrouchEnabled && bWantsToCrouch)
			{
				CharacterOwner->UnCrouch();
			}
		}
	}
}

void USSCharacterMovementComponent::BroadcastMovementDelegates()
{
	if (currentTimeSeconds == timestampWantsToJump)
	{
		OnWantsToJumpChanged.Broadcast(true);
	}
	else if (currentTimeSeconds == -1 * timestampWantsToJump)
	{
		OnWantsToJumpChanged.Broadcast(false);
	}

	if (currentTimeSeconds == timestampWantsToCrouch)
	{
		OnWantsToCrouchChanged.Broadcast(true);
	}
	else if (currentTimeSeconds == -1 * timestampWantsToCrouch)
	{
		OnWantsToCrouchChanged.Broadcast(false);
	}

	if (currentTimeSeconds == timestampWantsToRun)
	{
		OnWantsToRunChanged.Broadcast(true);
	}
	else if (currentTimeSeconds == -1 * timestampWantsToRun)
	{
		OnWantsToRunChanged.Broadcast(false);
	}
}

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
		CMC->SetWantsToRun(CMC->bWantsToRun);

		if (CMC->IsMovingOnGround())
		{
			// Kind of a hack. Sometimes on jump corrections, bIsJumping is incorrect
			CMC->OwnerSSCharacter->bIsJumping = false;
		}
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
	//Super::UpdateFromCompressedFlags(Flags);

	if (!CharacterOwner)
	{
		return;
	}

	//const bool bWasPressingJump = CharacterOwner->bPressedJump;

	//CharacterOwner->bPressedJump = ((Flags & FSavedMove_Character::FLAG_JumpPressed) != 0);
	//const bool bIsPressingJump = ((Flags & FSavedMove_Character::FLAG_JumpPressed) != 0);
	if ((Flags & FSavedMove_Character::FLAG_JumpPressed) != 0)
	{
		CharacterOwner->Jump();
	}
	else
	{
		CharacterOwner->StopJumping();
	}
	if ((Flags & FSavedMove_Character::FLAG_WantsToCrouch) != 0)
	{
		CharacterOwner->Crouch();
	}
	else
	{
		CharacterOwner->UnCrouch();
	}

	// Detect change in jump press on the server
	//if (CharacterOwner->GetLocalRole() == ROLE_Authority)
	//{
	//	if (bIsPressingJump && !bWasPressingJump)
	//	{
	//		CharacterOwner->Jump();
	//	}
	//	else if (!bIsPressingJump)
	//	{
	//		CharacterOwner->StopJumping();
	//	}
	//}
	////////////////////////////////////    /\/\/\ Modified Super /\/\/\





	// Update this CMC with the info stored in the compressed flags
	SetWantsToRun((Flags & FLAG_WantsToRun) != 0);




	if (PawnOwner->IsLocallyControlled() == false)
	{
		BroadcastMovementDelegates();
	}
}
#pragma endregion


#pragma region Client Adjust
//void USSCharacterMovementComponent::ClientAdjustPosition(float TimeStamp, FVector NewLoc, FVector NewVel, UPrimitiveComponent* NewBase, FName NewBaseBoneName, bool bHasBase, bool bBaseRelativePosition, uint8 ServerMovementMode)
//{
//	Super::ClientAdjustPosition(TimeStamp, NewLoc, NewVel, NewBase, NewBaseBoneName, bHasBase, bBaseRelativePosition, ServerMovementMode);
//
//
//	SSClientAdjustPosition();
//}

//void USSCharacterMovementComponent::SSClientAdjustPosition_Implementation()
//{
//	
//}
#pragma endregion

void USSCharacterMovementComponent::CheckJumpInput(float DeltaTime) // basically a UpdateCharacterStateBeforeMovement() for the jump
{
	CharacterOwner->JumpCurrentCountPreJump = CharacterOwner->JumpCurrentCount;

	if (CharacterOwner->bPressedJump)
	{
		// If this is the first jump and we're already falling,
		// then increment the JumpCount to compensate.
		const bool bFirstJump = CharacterOwner->JumpCurrentCount == 0;
		if (bFirstJump && IsFalling())
		{
			CharacterOwner->JumpCurrentCount++;
		}

		//const bool bDidJump = CanJump() && GetCharacterMovement()->DoJump(bClientUpdating);
		bool bDidJump = false;
		if (CharacterOwner->CanJump())
		{
			if (!OwnerSSCharacter->bIsJumping)
			{
				if (CharacterOwner->bClientUpdating == false)
				{
					if (PawnOwner->IsLocallyControlled())
					{
						if (GetOwnerAbilitySystemCharacter() && GetOwnerAbilitySystemCharacter()->GetAbilitySystemComponent())
						{
							bDidJump = GetOwnerAbilitySystemCharacter()->GetAbilitySystemComponent()->TryActivateAbility(GetOwnerAbilitySystemCharacter()->CharacterJumpAbilitySpecHandle);
						}
					}
					else
					{
						bDidJump = DoJump(CharacterOwner->bClientUpdating);
					}
				}
				else
				{
					bDidJump = DoJump(CharacterOwner->bClientUpdating);
				}
			}
		}

		if (bDidJump)
		{
			// Transition from not (actively) jumping to jumping.
			if (!CharacterOwner->bWasJumping)
			{
				CharacterOwner->JumpCurrentCount++;
				CharacterOwner->JumpForceTimeRemaining = CharacterOwner->GetJumpMaxHoldTime();
				CharacterOwner->OnJumped();
			}
		}

		CharacterOwner->bWasJumping = bDidJump;
	}
}

void USSCharacterMovementComponent::ClearJumpInput(float DeltaTime)
{
	if (CharacterOwner->bPressedJump)
	{
		CharacterOwner->JumpKeyHoldTime += DeltaTime;

		// Don't disable bPressedJump right away if it's still held.
		// Don't modify JumpForceTimeRemaining because a frame of update may be remaining.
		if (CharacterOwner->JumpKeyHoldTime >= CharacterOwner->GetJumpMaxHoldTime())
		{
			if (OwnerSSCharacter->bIsJumping)
			{
				OwnerAbilitySystemCharacter->GetAbilitySystemComponent()->CancelAbilityHandle(OwnerAbilitySystemCharacter->CharacterJumpAbilitySpecHandle);
			}
		}
	}
	else
	{
		CharacterOwner->JumpForceTimeRemaining = 0.0f;
		CharacterOwner->bWasJumping = false;
		if (OwnerSSCharacter->bIsJumping)
		{
			OwnerAbilitySystemCharacter->GetAbilitySystemComponent()->CancelAbilityHandle(OwnerAbilitySystemCharacter->CharacterJumpAbilitySpecHandle);
		}
	}
}

void USSCharacterMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	//Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);


	// Proxies get replicated crouch state.
	if (CharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		// Check for a change in crouch state. Players toggle crouch by changing bWantsToCrouch.
		const bool willCrouch = bWantsToCrouch && CanCrouchInCurrentState();
		if (IsCrouching() && !willCrouch)
		{
			OwnerAbilitySystemCharacter->GetAbilitySystemComponent()->CancelAbilityHandle(OwnerAbilitySystemCharacter->CharacterCrouchAbilitySpecHandle);
		}
		else if (!IsCrouching() && willCrouch)
		{
			if (timestampWantsToCrouch > timestampWantsToRun)
			{
				if (CharacterOwner->IsLocallyControlled())
				{
					OwnerAbilitySystemCharacter->GetAbilitySystemComponent()->TryActivateAbility(OwnerAbilitySystemCharacter->CharacterCrouchAbilitySpecHandle);
				}
				else
				{
					Crouch();
				}
			}
		}


		const bool willRun = bWantsToRun && CanRunInCurrentState();
		if (IsRunning() && !willRun)
		{
			OwnerAbilitySystemCharacter->GetAbilitySystemComponent()->CancelAbilityHandle(OwnerAbilitySystemCharacter->CharacterRunAbilitySpecHandle);
		}
		else if (!IsRunning() && willRun)
		{
			if (timestampWantsToRun > timestampWantsToCrouch)
			{
				if (CharacterOwner->IsLocallyControlled())
				{
					OwnerAbilitySystemCharacter->GetAbilitySystemComponent()->TryActivateAbility(OwnerAbilitySystemCharacter->CharacterRunAbilitySpecHandle);
				}
				else
				{
					Run();
				}
			}
		}
	}
}

void USSCharacterMovementComponent::UpdateCharacterStateAfterMovement(float DeltaSeconds)
{
	//Super::UpdateCharacterStateAfterMovement(DeltaSeconds);


	// Proxies get replicated crouch state.
	if (CharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		// Uncrouch if no longer allowed to be crouched
		if (IsCrouching() && !CanCrouchInCurrentState())
		{
			//UnCrouch();
			OwnerAbilitySystemCharacter->GetAbilitySystemComponent()->CancelAbilityHandle(OwnerAbilitySystemCharacter->CharacterCrouchAbilitySpecHandle);
		}


		if (IsRunning() && !CanRunInCurrentState())
		{
			//UnRun();
			OwnerAbilitySystemCharacter->GetAbilitySystemComponent()->CancelAbilityHandle(OwnerAbilitySystemCharacter->CharacterRunAbilitySpecHandle);
		}
	}
}

bool USSCharacterMovementComponent::CanAttemptJump() const
{
	//Super::CanAttemptJump(); // the super makes it return false when crouched - we don't want this

	if (IsJumpAllowed() == false)
	{
		return false;
	}

	if ((IsMovingOnGround() || IsFalling()) == false) // falling included for double-jump and non-zero jump hold time, but validated by character.
	{
		return false;
	}

	// Don't jump if we can't move up/down.
	if (bConstrainToPlane && FMath::Abs(PlaneConstraintNormal.Z) == 1.f)
	{
		return false;
	}
	
	return true;
}

bool USSCharacterMovementComponent::CanCrouchInCurrentState() const
{
	if (!bCanCrouchJump && !IsMovingOnGround())
	{
		return false;
	}

	if (IsRunning())
	{
		return false;
	}


	return Super::CanCrouchInCurrentState();
}

bool USSCharacterMovementComponent::CanRunInCurrentState() const
{
	if (bRunDisabled)
	{
		return false;
	}
	if (!IsMovingOnGround())
	{
		return false;
	}
	// Actually we don't do this check (the client-only version) at all anymore because if it does pass, only the client can't run but that doesn't mean anything (and causes useless corrections)
	//if (PawnOwner->IsLocallyControlled() && IsMovingForward() == false) // we dont perform the IsMovingForward() check on dedicated server because its messed up on there. Yes this is a vulnerability but its temporary
	//{
	//	return false;
	//}
	if (CharacterAttributeSet && CharacterAttributeSet->GetStamina() <= 0)
	{
		return false;
	}

	if (IsCrouching())
	{
		return false;
	}


	return true;
}

bool USSCharacterMovementComponent::IsRunning() const
{
	return OwnerSSCharacter->bIsRunning;
}


bool USSCharacterMovementComponent::DoJump(bool bReplayingMoves)
{
	//return Super::DoJump(bReplayingMoves); // super does CanJump checks we don't want checks, checks are done elsewhere

	OwnerSSCharacter->bIsJumping = true;

	Velocity.Z = FMath::Max(Velocity.Z, JumpZVelocity);
	SetMovementMode(MOVE_Falling);
	return true;
}

void USSCharacterMovementComponent::UnJump()
{
	OwnerSSCharacter->bIsJumping = false;
}

void USSCharacterMovementComponent::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);



}

void USSCharacterMovementComponent::UnCrouch(bool bClientSimulation)
{
	Super::UnCrouch(bClientSimulation);



}

void USSCharacterMovementComponent::Run()
{
	OwnerSSCharacter->bIsRunning = true;
	if (CharacterAttributeSet)
	{
		CharacterAttributeSet->SetStaminaDraining(true);
	}
}
void USSCharacterMovementComponent::UnRun()
{
	OwnerSSCharacter->bIsRunning = false;
	if (CharacterAttributeSet)
	{
		CharacterAttributeSet->SetStaminaDraining(false);
	}
}

void USSCharacterMovementComponent::OnStaminaFullyDrained()
{
	SetWantsToRun(false);
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

			if (IsRunning())
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

		if (IsRunning())
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

float USSCharacterMovementComponent::GetMaxBrakingDeceleration() const
{
	return Super::GetMaxBrakingDeceleration();
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

void USSCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) // DO NOT UTILIZE THIS EVENT FOR MOVEMENT
{
	// DO NOT UTILIZE THIS EVENT FOR MOVEMENT

	currentTimeSeconds = GetWorld()->GetTimeSeconds();

	CurrentRotationRate = (PawnOwner->GetActorRotation() - PreviousRotation) * (DeltaTime * 1000);


	if (PawnOwner->IsLocallyControlled()) // only tweak compressed flags on client/controlled
	{
		TweakCompressedFlagsBeforeTick();
		BroadcastMovementDelegates();
	}

	

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



	PreviousRotation = PawnOwner->GetActorRotation();
}

#pragma region MovementHelpers
bool USSCharacterMovementComponent::IsMovingForward(/*float degreeTolerance*/) const // THIS CHECK DOES NOT WORK ON DEDICATED SERVER
{
	/*
	 * At dot product 0.7 you are looking at a 45 degrees angle
	 * For 25 degrees tolerance use > 0.9
	 * 0.99 gives you 8 degrees of tolerance
	 * 
	 * ACOS(dot product) is the formula. Incidentally, it's the formula to find the angle between two vectors
	 */

	const FVector ForwardDir = PawnOwner->GetActorForwardVector();
	const FVector DesiredDir = Acceleration.GetSafeNormal();

	const float forwardDifference = FVector::DotProduct(DesiredDir, ForwardDir);


	const float degsDiff = UKismetMathLibrary::DegAcos(forwardDifference);
	const float graceDegs = 1 + FMath::Abs(CurrentRotationRate.Yaw) + FMath::Abs(CurrentRotationRate.Pitch) + FMath::Abs(CurrentRotationRate.Roll); // how much extra degrees of grace should be given based on how fast we are rotating. We need this because the dot product isnt perfect for some reason and gets more inaccurate the faster you rotate

	if (degsDiff > 45.f + graceDegs) // if we are moving 45 degs or more away from our forward vector (plus some grace based on how fast we are rotating)
	{
		return false;
	}

	return true;
}
#pragma endregion
