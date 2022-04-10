// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSCharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "Character/SSCharacter.h"
#include "Character/AttributeSets/AS_CharacterMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"
#include "Subobjects/AbilitySystemSetupComponent.h"
#include "AbilitySystem/ASSAbilitySystemBlueprintLibrary.h"

#include "Kismet/KismetSystemLibrary.h"



USSCharacterMovementComponent::USSCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCrouchCancelsDesireToRun = true;
	bRunCancelsDesireToCrouch = true;
	bJumpCancelsDesireToCrouch = true;
	bJumpCancelsDesireToRun = false;


	bCanCrouchJump = false;
	bCanWalkOffLedgesWhenCrouching = true;
}

#pragma region Prediciton Data Client
FNetworkPredictionData_Client* USSCharacterMovementComponent::GetPredictionData_Client() const
{
	if (ClientPredictionData == nullptr)
	{
		// Return our custom client prediction struct instead
		USSCharacterMovementComponent* MutableThis = const_cast<USSCharacterMovementComponent*>(this);
		MutableThis->ClientPredictionData = new FSSNetworkPredictionData_Client_Character(*this);
	}

	return ClientPredictionData;
}

FSSNetworkPredictionData_Client_Character::FSSNetworkPredictionData_Client_Character(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{

}
FSavedMovePtr FSSNetworkPredictionData_Client_Character::AllocateNewMove()
{
	// Return our custom move struct instead
	return FSavedMovePtr(new FSSSavedMove_Character());
}
#pragma endregion

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

	// Setup listening for input CVar changes
	CVarToggleCrouchChangeDelegate.BindUFunction(this, TEXT("CVarToggleCrouchChanged"));
	UCVarChangeListenerManager::AddBoolCVarCallbackStatic(TEXT("input.ToggleCrouch"), CVarToggleCrouchChangeDelegate, true);
	CVarToggleRunChangeDelegate.BindUFunction(this, TEXT("CVarToggleRunChanged"));
	UCVarChangeListenerManager::AddBoolCVarCallbackStatic(TEXT("input.ToggleRun"), CVarToggleRunChangeDelegate, true);


	// Get reference to our SSCharacter
	SSCharacterOwner = Cast<ASSCharacter>(PawnOwner);

	UAbilitySystemSetupComponent* AbilitySystemSetupComponent = GetOwner()->FindComponentByClass<UAbilitySystemSetupComponent>();
	if (IsValid(AbilitySystemSetupComponent))
	{
		AbilitySystemSetupComponent->OnInitializeAbilitySystemComponentDelegate.AddUObject(this, &USSCharacterMovementComponent::OnInitializeAbilitySystemComponent);
	}
}

#pragma region Ability System
void USSCharacterMovementComponent::OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC)
{
	OwnerASC = ASC;


	CharacterMovementAttributeSet = UASSAbilitySystemBlueprintLibrary::GetAttributeSetCasted<UAS_CharacterMovement>(OwnerASC.Get());

	
	// Bind to Tag change delegates
	ASC->RegisterGameplayTagEvent(NativeGameplayTags::Character_RunDisabled, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &USSCharacterMovementComponent::OnRunDisabledTagChanged);
	ASC->RegisterGameplayTagEvent(NativeGameplayTags::Character_JumpDisabled, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &USSCharacterMovementComponent::OnJumpDisabledTagChanged);
	ASC->RegisterGameplayTagEvent(NativeGameplayTags::Character_CrouchDisabled, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &USSCharacterMovementComponent::OnCrouchDisabledTagChanged);

	// Get initial values
	OnRunDisabledTagChanged(NativeGameplayTags::Character_RunDisabled, ASC->GetTagCount(NativeGameplayTags::Character_RunDisabled));
	OnJumpDisabledTagChanged(NativeGameplayTags::Character_JumpDisabled, ASC->GetTagCount(NativeGameplayTags::Character_JumpDisabled));
	OnCrouchDisabledTagChanged(NativeGameplayTags::Character_CrouchDisabled, ASC->GetTagCount(NativeGameplayTags::Character_CrouchDisabled));
}

void USSCharacterMovementComponent::OnRunDisabledTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount > 0) // if RunDisabled tag present
	{
		bRunDisabled = true;
	}
	else // if RunDisabled tag not present
	{
		bRunDisabled = false;
	}
}
void USSCharacterMovementComponent::OnJumpDisabledTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount > 0)
	{
		bJumpDisabled = true;
	}
	else
	{
		bJumpDisabled = false;
	}
}
void USSCharacterMovementComponent::OnCrouchDisabledTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount > 0)
	{
		bCrouchDisabled = true;
	}
	else
	{
		bCrouchDisabled = false;
	}
}
#pragma endregion

#pragma region Move Requests
void USSCharacterMovementComponent::SetWantsToRun(bool newWantsToRun)
{
	if (bWantsToRun != newWantsToRun)
	{
		bWantsToRun = newWantsToRun;

		if (bWantsToRun == true)
		{
			TimestampWantsToRun = GetWorld()->GetTimeSeconds();
		}
		else
		{
			TimestampWantsToRun = -1 * GetWorld()->GetTimeSeconds();
		}
	}
}
#pragma endregion

#pragma region WantsTo Configuration
void USSCharacterMovementComponent::TweakCompressedFlagsBeforeTick()
{
	// Call SetWantsToRun() using our tweaked value
	bool bTweakedWantsToRun = bWantsToRun;
	TweakWantsToRunBeforeTick(bTweakedWantsToRun);
	SetWantsToRun(bTweakedWantsToRun);


	////////////////////////////////////////////////////////////////////////////// Desire Cancellations (for Toggle Modes) //////////


	if (CurrentTimeSeconds == TimestampWantsToJump)
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

	if (CurrentTimeSeconds == TimestampWantsToCrouch)
	{
		if (bCrouchCancelsDesireToRun)
		{
			if (bToggleRunEnabled && GetWantsToRun())
			{
				SetWantsToRun(false);
			}
		}
	}

	if (CurrentTimeSeconds == TimestampWantsToRun)
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

void USSCharacterMovementComponent::TweakWantsToRunBeforeTick(bool& outTweakedWantsToRun) const
{
	const bool bIsMovingForward = IsMovingForward();

	if (!bIsMovingForward && Acceleration.SizeSquared() > 0)
	{
		outTweakedWantsToRun = false; // a client-only check to ensure we are moving forward (i know this is bad, it's not server verified but it's temporary so i guess hackers can run backwards if they want)
	}

	if (bToggleRunEnabled && Acceleration.SizeSquared() == 0)
	{
		// If we are staying still while toggle run is on, we don't want to run
		outTweakedWantsToRun = false;
	}

	if (CurrentTimeSeconds == -TimestampWantsToRun) // if we just stopped running
	{
		if (!IsMovingOnGround() && bToggleRunEnabled && bIsMovingForward)
		{
			// If you're in the air moving forward (only if in toggle mode) you probably still want to run, whether you are
			// trying to stop or not
			outTweakedWantsToRun = true;
		}
	}
}

void USSCharacterMovementComponent::BroadcastMovementDelegates()
{
	if (CurrentTimeSeconds == TimestampWantsToJump)
	{
		OnWantsToJumpChanged.Broadcast(true);
	}
	else if (CurrentTimeSeconds == -1 * TimestampWantsToJump)
	{
		OnWantsToJumpChanged.Broadcast(false);
	}

	if (CurrentTimeSeconds == TimestampWantsToCrouch)
	{
		OnWantsToCrouchChanged.Broadcast(true);
	}
	else if (CurrentTimeSeconds == -1 * TimestampWantsToCrouch)
	{
		OnWantsToCrouchChanged.Broadcast(false);
	}

	if (CurrentTimeSeconds == TimestampWantsToRun)
	{
		OnWantsToRunChanged.Broadcast(true);
	}
	else if (CurrentTimeSeconds == -1 * TimestampWantsToRun)
	{
		OnWantsToRunChanged.Broadcast(false);
	}
}
#pragma endregion

#pragma region Saved Move
void FSSSavedMove_Character::Clear()
{
	Super::Clear();

	// Clear all fsavedmove values
	bSavedWantsToRun = 0;
}

void FSSSavedMove_Character::PrepMoveFor(ACharacter* Character) // Client only
{
	Super::PrepMoveFor(Character);


	USSCharacterMovementComponent* CMC = Cast<USSCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CMC)
	{
		// WE ARE CORRECTING A CLIENT PREDICTIVE ERROR
		// Copy the values out of this move to the CMC so we can replay it, approaching our correct position
		CMC->SetWantsToRun(CMC->bWantsToRun);

		if (CMC->IsMovingOnGround())
		{
			// Kind of a hack. Sometimes on jump corrections, bIsJumping is incorrect
			CMC->SSCharacterOwner->bIsJumping = false;
		}
	}
}

void FSSSavedMove_Character::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	USSCharacterMovementComponent* CMC = static_cast<USSCharacterMovementComponent*>(Character->GetCharacterMovement());
	if (CMC)
	{
		// Copy client values into the saved move to use for our next movement and to send to the server for the server to copy our movement
		bSavedWantsToRun = CMC->bWantsToRun;
	}
}

bool FSSSavedMove_Character::CanCombineWith(const FSavedMovePtr& NewMovePtr, ACharacter* Character, float MaxDelta) const
{
	const FSSSavedMove_Character* NewMove = static_cast<const FSSSavedMove_Character*>(NewMovePtr.Get());

	// As an optimization, check if the we can combine saved moves.
	if (bSavedWantsToRun != NewMove->bSavedWantsToRun)
	{
		return false;
	}

	return Super::CanCombineWith(NewMovePtr, Character, MaxDelta);
}

uint8 FSSSavedMove_Character::GetCompressedFlags() const
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

void USSCharacterMovementComponent::ServerMove_PerformMovement(const FCharacterNetworkMoveData& MoveData)
{
	const float previousAccelerationSize = Acceleration.SizeSquared();
	Super::ServerMove_PerformMovement(MoveData);


	const float currentAccelerationSize = Acceleration.SizeSquared();

	if (previousAccelerationSize <= KINDA_SMALL_NUMBER && currentAccelerationSize > KINDA_SMALL_NUMBER)
	{
		// We started acceleration
		OnAccelerationStart.Broadcast();
	}
	if (previousAccelerationSize > KINDA_SMALL_NUMBER && currentAccelerationSize <= KINDA_SMALL_NUMBER)
	{
		// We stopped acceleration
		OnAccelerationStop.Broadcast();
	}
}

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

#pragma region Moves
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
			if (!SSCharacterOwner->bIsJumping)
			{
				if (CharacterOwner->bClientUpdating == false)
				{
					bDidJump = SSCharacterOwner->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Movement_Jump.GetTag().GetSingleTagContainer());
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
			if (SSCharacterOwner->bIsJumping)
			{
				SSCharacterOwner->GetAbilitySystemComponent()->CancelAbilities(&NativeGameplayTags::Ability_Movement_Jump.GetTag().GetSingleTagContainer());
			}
		}
	}
	else
	{
		CharacterOwner->JumpForceTimeRemaining = 0.0f;
		CharacterOwner->bWasJumping = false;
		if (SSCharacterOwner->bIsJumping)
		{
			SSCharacterOwner->GetAbilitySystemComponent()->CancelAbilities(&NativeGameplayTags::Ability_Movement_Jump.GetTag().GetSingleTagContainer());
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
			OwnerASC->CancelAbilities(&NativeGameplayTags::Ability_Movement_Crouch.GetTag().GetSingleTagContainer());
		}
		else if (!IsCrouching() && willCrouch)
		{
			if (TimestampWantsToCrouch > TimestampWantsToRun)
			{
				OwnerASC->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Movement_Crouch.GetTag().GetSingleTagContainer());
			}
		}


		const bool willRun = bWantsToRun && CanRunInCurrentState() && Acceleration.SizeSquared() > 0;
		if (IsRunning() && !willRun)
		{
			OwnerASC->CancelAbilities(&NativeGameplayTags::Ability_Movement_Run.GetTag().GetSingleTagContainer());
		}
		else if (!IsRunning() && willRun)
		{
			if (TimestampWantsToRun > TimestampWantsToCrouch)
			{
				OwnerASC->TryActivateAbilitiesByTag(NativeGameplayTags::Ability_Movement_Run.GetTag().GetSingleTagContainer());
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
			OwnerASC->CancelAbilities(&NativeGameplayTags::Ability_Movement_Crouch.GetTag().GetSingleTagContainer());
		}


		if (IsRunning() && !CanRunInCurrentState())
		{
			OwnerASC->CancelAbilities(&NativeGameplayTags::Ability_Movement_Run.GetTag().GetSingleTagContainer());
		}
	}
}

bool USSCharacterMovementComponent::CanAttemptJump() const
{
	//Super::CanAttemptJump(); // the super makes it return false when crouched - we don't want this
	if (bJumpDisabled)
	{
		return false;
	}

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
	if (bCrouchDisabled)
	{
		return false;
	}

	if (!bCanCrouchJump && !IsMovingOnGround())
	{
		if (bJumpedInAir) // only false if jumped
		{
			return false;
		}
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

	if (IsCrouching() && bWantsToCrouch == false)
	{
		return false;
	}


	return true;
}

bool USSCharacterMovementComponent::IsRunning() const
{
	return SSCharacterOwner->bIsRunning;
}


bool USSCharacterMovementComponent::DoJump(bool bReplayingMoves)
{
	//return Super::DoJump(bReplayingMoves); // super does CanJump checks we don't want checks, checks are done elsewhere

	SSCharacterOwner->bIsJumping = true;

	Velocity.Z = FMath::Max(Velocity.Z, JumpZVelocity);
	SetMovementMode(MOVE_Falling);

	bJumpedInAir = true;

	return true;
}

void USSCharacterMovementComponent::UnJump()
{
	SSCharacterOwner->bIsJumping = false;
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
	SSCharacterOwner->bIsRunning = true;
}
void USSCharacterMovementComponent::UnRun()
{
	SSCharacterOwner->bIsRunning = false;
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
	// By default, the cases break and proceed to the Super's switch
	switch (MovementMode)
	{
	case MOVE_None:
	{
		break;
	}
	case MOVE_Walking:
	case MOVE_NavWalking:
	{
		if (IsCrouching())
		{
			return MaxWalkSpeedCrouched;
		}
		else
		{
			if (!CharacterMovementAttributeSet.IsValid())
			{
				UE_LOG(LogCharacterMovement, Error, TEXT("CharacterMovementAttributeSet was NULL when trying to return a speed value"));
				return 0;
			}

			if (IsRunning())
			{
				return CharacterMovementAttributeSet->GetRunSpeed();
			}
			return CharacterMovementAttributeSet->GetWalkSpeed();
		}

		break;
	}
	case MOVE_Falling:
	{
		break;
	}
	case MOVE_Swimming:
	{
		break;
	}
	case MOVE_Flying:
	{
		break;
	}
	case MOVE_Custom:
	{
		switch (static_cast<ECustomMovementMode>(CustomMovementMode))
		{
		case ECustomMovementMode::MOVE_None:
		{
			break;
		}
		case ECustomMovementMode::MOVE_InfiniteAngleWalking:
		{
			break;
		}
		default:
		{
			return MaxCustomMovementSpeed;
		}
		}

		break;
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
	{
		break;
	}
	case MOVE_Walking:
	case MOVE_NavWalking:
	{
		if (!CharacterMovementAttributeSet.IsValid())
		{
			UE_LOG(LogCharacterMovement, Error, TEXT("CharacterMovementAttributeSet was NULL when trying to return a acceleration value"));
			return 0;
		}

		if (IsRunning())
		{
			return CharacterMovementAttributeSet->GetRunAccelaration();
		}
		return CharacterMovementAttributeSet->GetWalkAcceleration();;
	}
	case MOVE_Falling:
	{
		break;
	}
	case MOVE_Swimming:
	{
		break;
	}
	case MOVE_Flying:
	{
		break;
	}
	case MOVE_Custom:
	{
		switch (static_cast<ECustomMovementMode>(CustomMovementMode))
		{
		case ECustomMovementMode::MOVE_None:
		{
			break;
		}
		case ECustomMovementMode::MOVE_InfiniteAngleWalking:
		{
			break;
		}
		default:
		{
			break;
		}
		}

		break;
	}

	default:
	{
		break;
	}
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
		const UEnum* CustomMovementModeEnum = FindObject<const UEnum>(ANY_PACKAGE, TEXT("ECustomMovementMode"));
		if (IsValid(CustomMovementModeEnum))
		{
			// If this value is in our custom movement enum
			if (CustomMovementModeEnum->IsValidEnumValue(CustomMovementMode))
			{
				// Return the display name!
				return CustomMovementModeEnum->GetDisplayNameTextByValue(CustomMovementMode).ToString();
			}
		}
	}


	return Super::GetMovementName();
}

void USSCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

	if (MovementMode == MOVE_Walking)
	{
		bJumpedInAir = false;
	}

	if (MovementMode == MOVE_Falling && PreviousMovementMode != MOVE_Falling)
	{
		// We started falling
		OnStartedFalling.Broadcast();
	}
	if (MovementMode != MOVE_Falling && PreviousMovementMode == MOVE_Falling)
	{
		// We stopped falling
		OnStoppedFalling.Broadcast();
	}
}

void USSCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);


	switch (static_cast<ECustomMovementMode>(CustomMovementMode))
	{
	case ECustomMovementMode::MOVE_None:
	{
		break;
	}
	case ECustomMovementMode::MOVE_InfiniteAngleWalking:
	{
		PhysInfiniteAngleWalking(deltaTime, Iterations);
		break;
	}
	default:
	{
		UE_LOG(LogCharacterMovementSetup, Warning, TEXT("%s has unsupported custom movement mode %d"), *CharacterOwner->GetName(), static_cast<uint8>(CustomMovementMode));
		SetMovementMode(EMovementMode::MOVE_Custom, static_cast<uint8>(ECustomMovementMode::MOVE_None));
		break;
	}
	}
}

#pragma region Custom Physics
void USSCharacterMovementComponent::PhysInfiniteAngleWalking(float deltaTime, int32 Iterations)
{

}
#pragma endregion
#pragma endregion


void USSCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) // DO NOT UTILIZE THIS EVENT FOR MOVEMENT
{
	// DO NOT UTILIZE THIS EVENT FOR MOVEMENT

	CurrentTimeSeconds = GetWorld()->GetTimeSeconds();

	CurrentRotationRate = (PawnOwner->GetActorRotation() - PreviousRotation) * (DeltaTime * 1000);


	if (PawnOwner->IsLocallyControlled()) // only tweak compressed flags on client/controlled
	{
		TweakCompressedFlagsBeforeTick();
		BroadcastMovementDelegates(); // the server's movement delegates are broadcasted on UpdateFromCompressedFlags()
	}

	const float previousAccelerationSize = Acceleration.SizeSquared();

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float currentAccelerationSize = Acceleration.SizeSquared();

	if (PawnOwner->IsLocallyControlled())
	{
		if (previousAccelerationSize <= KINDA_SMALL_NUMBER && currentAccelerationSize > KINDA_SMALL_NUMBER)
		{
			// We started acceleration
			OnAccelerationStart.Broadcast();
		}
		if (previousAccelerationSize > KINDA_SMALL_NUMBER && currentAccelerationSize <= KINDA_SMALL_NUMBER)
		{
			// We stopped acceleration
			OnAccelerationStop.Broadcast();
		}
	}


	PreviousRotation = PawnOwner->GetActorRotation();
}

#pragma region MovementHelpers
bool USSCharacterMovementComponent::IsMovingForward(/*float degreeTolerance*/) const // THIS CHECK DOES NOT WORK ON DEDICATED SERVER
{
	// At dot product 0.7 you are looking at a 45 degrees angle
	// For 25 degrees tolerance use > 0.9
	// 0.99 gives you 8 degrees of tolerance
	// 
	// ACOS(dot product) is the formula. Incidentally, it's the formula to find the angle between two vectors

	const FVector ForwardDir = PawnOwner->GetActorForwardVector();
	const FVector DesiredDir = Acceleration.GetSafeNormal();

	const float ForwardDifference = FVector::DotProduct(DesiredDir, ForwardDir);


	const float DegsDiff = UKismetMathLibrary::DegAcos(ForwardDifference);
	const float GraceDegs = 1 + FMath::Abs(CurrentRotationRate.Yaw) + FMath::Abs(CurrentRotationRate.Pitch) + FMath::Abs(CurrentRotationRate.Roll); // how much extra degrees of grace should be given based on how fast we are rotating. We need this because the dot product isnt perfect for some reason and gets more inaccurate the faster you rotate

	if (DegsDiff > 45.f + GraceDegs) // if we are moving 45 degs or more away from our forward vector (plus some grace based on how fast we are rotating)
	{
		return false;
	}

	return true;
}
#pragma endregion
