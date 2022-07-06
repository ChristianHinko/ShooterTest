// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STCharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "Character/STCharacter.h"
#include "Character/AttributeSets/STAttributeSet_CharacterMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"
#include "Subobjects/ASSActorComponent_AbilitySystemSetup.h"
#include "AbilitySystem/ASSAbilitySystemBlueprintLibrary.h"

#include "Kismet/KismetSystemLibrary.h"



USTCharacterMovementComponent::USTCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
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
FNetworkPredictionData_Client* USTCharacterMovementComponent::GetPredictionData_Client() const
{
	if (ClientPredictionData == nullptr)
	{
		// Return our custom client prediction struct instead
		USTCharacterMovementComponent* MutableThis = const_cast<USTCharacterMovementComponent*>(this);
		MutableThis->ClientPredictionData = new FSTNetworkPredictionData_Client_Character(*this);
	}

	return ClientPredictionData;
}

FSTNetworkPredictionData_Client_Character::FSTNetworkPredictionData_Client_Character(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{

}
FSavedMovePtr FSTNetworkPredictionData_Client_Character::AllocateNewMove()
{
	// Return our custom move struct instead
	return FSavedMovePtr(new FSTSavedMove_Character());
}
#pragma endregion

void USTCharacterMovementComponent::CVarToggleCrouchChanged(bool newToggleCrouch)
{
	bToggleCrouchEnabled = newToggleCrouch;
}
void USTCharacterMovementComponent::CVarToggleRunChanged(bool newToggleRun)
{
	bToggleRunEnabled = newToggleRun;
}

void USTCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// Setup listening for input CVar changes
	CVarToggleCrouchChangeDelegate.BindUFunction(this, TEXT("CVarToggleCrouchChanged"));
	UCVarChangeListenerManager::AddBoolCVarCallbackStatic(TEXT("input.ToggleCrouch"), CVarToggleCrouchChangeDelegate, true);
	CVarToggleRunChangeDelegate.BindUFunction(this, TEXT("CVarToggleRunChanged"));
	UCVarChangeListenerManager::AddBoolCVarCallbackStatic(TEXT("input.ToggleRun"), CVarToggleRunChangeDelegate, true);


	// Get reference to our STCharacter
	STCharacterOwner = Cast<ASTCharacter>(PawnOwner);

	UASSActorComponent_AbilitySystemSetup* AbilitySystemSetupComponent = GetOwner()->FindComponentByClass<UASSActorComponent_AbilitySystemSetup>();
	if (IsValid(AbilitySystemSetupComponent))
	{
		AbilitySystemSetupComponent->OnInitializeAbilitySystemComponentDelegate.AddUObject(this, &USTCharacterMovementComponent::OnInitializeAbilitySystemComponent);
	}
}

#pragma region Ability System
void USTCharacterMovementComponent::OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC)
{
	OwnerASC = ASC;


	CharacterMovementAttributeSet = UASSAbilitySystemBlueprintLibrary::GetAttributeSetCasted<USTAttributeSet_CharacterMovement>(ASC);

	
	// Bind to Tag change delegates
	ASC->RegisterGameplayTagEvent(STNativeGameplayTags::Character_RunDisabled, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &USTCharacterMovementComponent::OnRunDisabledTagChanged);
	ASC->RegisterGameplayTagEvent(STNativeGameplayTags::Character_JumpDisabled, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &USTCharacterMovementComponent::OnJumpDisabledTagChanged);
	ASC->RegisterGameplayTagEvent(STNativeGameplayTags::Character_CrouchDisabled, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &USTCharacterMovementComponent::OnCrouchDisabledTagChanged);

	// Get initial values
	OnRunDisabledTagChanged(STNativeGameplayTags::Character_RunDisabled, ASC->GetTagCount(STNativeGameplayTags::Character_RunDisabled));
	OnJumpDisabledTagChanged(STNativeGameplayTags::Character_JumpDisabled, ASC->GetTagCount(STNativeGameplayTags::Character_JumpDisabled));
	OnCrouchDisabledTagChanged(STNativeGameplayTags::Character_CrouchDisabled, ASC->GetTagCount(STNativeGameplayTags::Character_CrouchDisabled));
}

void USTCharacterMovementComponent::OnRunDisabledTagChanged(const FGameplayTag Tag, int32 NewCount)
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
void USTCharacterMovementComponent::OnJumpDisabledTagChanged(const FGameplayTag Tag, int32 NewCount)
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
void USTCharacterMovementComponent::OnCrouchDisabledTagChanged(const FGameplayTag Tag, int32 NewCount)
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
void USTCharacterMovementComponent::SetWantsToRun(bool newWantsToRun)
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
void USTCharacterMovementComponent::TweakCompressedFlagsBeforeTick()
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

void USTCharacterMovementComponent::TweakWantsToRunBeforeTick(bool& outTweakedWantsToRun) const
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

void USTCharacterMovementComponent::BroadcastMovementDelegates()
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
void FSTSavedMove_Character::Clear()
{
	Super::Clear();

	// Clear all fsavedmove values
	bSavedWantsToRun = 0;
}

void FSTSavedMove_Character::PrepMoveFor(ACharacter* Character) // Client only
{
	Super::PrepMoveFor(Character);


	USTCharacterMovementComponent* CMC = Cast<USTCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CMC)
	{
		// WE ARE CORRECTING A CLIENT PREDICTIVE ERROR
		// Copy the values out of this move to the CMC so we can replay it, approaching our correct position
		CMC->SetWantsToRun(CMC->bWantsToRun);

		if (CMC->IsMovingOnGround())
		{
			// Kind of a hack. Sometimes on jump corrections, bIsJumping is incorrect
			CMC->STCharacterOwner->bIsJumping = false;
		}
	}
}

void FSTSavedMove_Character::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	USTCharacterMovementComponent* CMC = static_cast<USTCharacterMovementComponent*>(Character->GetCharacterMovement());
	if (CMC)
	{
		// Copy client values into the saved move to use for our next movement and to send to the server for the server to copy our movement
		bSavedWantsToRun = CMC->bWantsToRun;
	}
}

bool FSTSavedMove_Character::CanCombineWith(const FSavedMovePtr& NewMovePtr, ACharacter* Character, float MaxDelta) const
{
	const FSTSavedMove_Character* NewMove = static_cast<const FSTSavedMove_Character*>(NewMovePtr.Get());

	// As an optimization, check if the we can combine saved moves.
	if (bSavedWantsToRun != NewMove->bSavedWantsToRun)
	{
		return false;
	}

	return Super::CanCombineWith(NewMovePtr, Character, MaxDelta);
}

uint8 FSTSavedMove_Character::GetCompressedFlags() const
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

void USTCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
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

void USTCharacterMovementComponent::ServerMove_PerformMovement(const FCharacterNetworkMoveData& MoveData)
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
//void USTCharacterMovementComponent::ClientAdjustPosition(float TimeStamp, FVector NewLoc, FVector NewVel, UPrimitiveComponent* NewBase, FName NewBaseBoneName, bool bHasBase, bool bBaseRelativePosition, uint8 ServerMovementMode)
//{
//	Super::ClientAdjustPosition(TimeStamp, NewLoc, NewVel, NewBase, NewBaseBoneName, bHasBase, bBaseRelativePosition, ServerMovementMode);
//
//
//	STClientAdjustPosition();
//}

//void USTCharacterMovementComponent::STClientAdjustPosition_Implementation()
//{
//	
//}
#pragma endregion

#pragma region Moves
void USTCharacterMovementComponent::CheckJumpInput(float DeltaTime) // basically a UpdateCharacterStateBeforeMovement() for the jump
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
			if (!STCharacterOwner->bIsJumping)
			{
				if (CharacterOwner->bClientUpdating == false)
				{
					bDidJump = STCharacterOwner->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(STNativeGameplayTags::Ability_Movement_Jump.GetTag().GetSingleTagContainer());
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

void USTCharacterMovementComponent::ClearJumpInput(float DeltaTime)
{
	if (CharacterOwner->bPressedJump)
	{
		CharacterOwner->JumpKeyHoldTime += DeltaTime;

		// Don't disable bPressedJump right away if it's still held.
		// Don't modify JumpForceTimeRemaining because a frame of update may be remaining.
		if (CharacterOwner->JumpKeyHoldTime >= CharacterOwner->GetJumpMaxHoldTime())
		{
			if (STCharacterOwner->bIsJumping)
			{
				STCharacterOwner->GetAbilitySystemComponent()->CancelAbilities(&STNativeGameplayTags::Ability_Movement_Jump.GetTag().GetSingleTagContainer());
			}
		}
	}
	else
	{
		CharacterOwner->JumpForceTimeRemaining = 0.0f;
		CharacterOwner->bWasJumping = false;
		if (STCharacterOwner->bIsJumping)
		{
			STCharacterOwner->GetAbilitySystemComponent()->CancelAbilities(&STNativeGameplayTags::Ability_Movement_Jump.GetTag().GetSingleTagContainer());
		}
	}
}

void USTCharacterMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	//Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);


	// Proxies get replicated crouch state.
	if (CharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		// Check for a change in crouch state. Players toggle crouch by changing bWantsToCrouch.
		const bool willCrouch = bWantsToCrouch && CanCrouchInCurrentState();
		if (IsCrouching() && !willCrouch)
		{
			OwnerASC->CancelAbilities(&STNativeGameplayTags::Ability_Movement_Crouch.GetTag().GetSingleTagContainer());
		}
		else if (!IsCrouching() && willCrouch)
		{
			if (TimestampWantsToCrouch > TimestampWantsToRun)
			{
				OwnerASC->TryActivateAbilitiesByTag(STNativeGameplayTags::Ability_Movement_Crouch.GetTag().GetSingleTagContainer());
			}
		}


		const bool willRun = bWantsToRun && CanRunInCurrentState() && Acceleration.SizeSquared() > 0;
		if (IsRunning() && !willRun)
		{
			OwnerASC->CancelAbilities(&STNativeGameplayTags::Ability_Movement_Run.GetTag().GetSingleTagContainer());
		}
		else if (!IsRunning() && willRun)
		{
			if (TimestampWantsToRun > TimestampWantsToCrouch)
			{
				OwnerASC->TryActivateAbilitiesByTag(STNativeGameplayTags::Ability_Movement_Run.GetTag().GetSingleTagContainer());
			}
		}
	}
}

void USTCharacterMovementComponent::UpdateCharacterStateAfterMovement(float DeltaSeconds)
{
	//Super::UpdateCharacterStateAfterMovement(DeltaSeconds);


	// Proxies get replicated crouch state.
	if (CharacterOwner->GetLocalRole() != ROLE_SimulatedProxy)
	{
		// Uncrouch if no longer allowed to be crouched
		if (IsCrouching() && !CanCrouchInCurrentState())
		{
			OwnerASC->CancelAbilities(&STNativeGameplayTags::Ability_Movement_Crouch.GetTag().GetSingleTagContainer());
		}


		if (IsRunning() && !CanRunInCurrentState())
		{
			OwnerASC->CancelAbilities(&STNativeGameplayTags::Ability_Movement_Run.GetTag().GetSingleTagContainer());
		}
	}
}

bool USTCharacterMovementComponent::CanAttemptJump() const
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

bool USTCharacterMovementComponent::CanCrouchInCurrentState() const
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

bool USTCharacterMovementComponent::CanRunInCurrentState() const
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

bool USTCharacterMovementComponent::IsRunning() const
{
	return STCharacterOwner->bIsRunning;
}


bool USTCharacterMovementComponent::DoJump(bool bReplayingMoves)
{
	//return Super::DoJump(bReplayingMoves); // super does CanJump checks we don't want checks, checks are done elsewhere

	STCharacterOwner->bIsJumping = true;

	Velocity.Z = FMath::Max(Velocity.Z, JumpZVelocity);
	SetMovementMode(MOVE_Falling);

	bJumpedInAir = true;

	return true;
}

void USTCharacterMovementComponent::UnJump()
{
	STCharacterOwner->bIsJumping = false;
}

void USTCharacterMovementComponent::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);



}

void USTCharacterMovementComponent::UnCrouch(bool bClientSimulation)
{
	Super::UnCrouch(bClientSimulation);



}

void USTCharacterMovementComponent::Run()
{
	STCharacterOwner->bIsRunning = true;
}
void USTCharacterMovementComponent::UnRun()
{
	STCharacterOwner->bIsRunning = false;
}
#pragma endregion

void USTCharacterMovementComponent::OnMovementUpdated(float deltaTime, const FVector& OldLocation, const FVector& OldVelocity)
{
	//Super::OnMovementUpdated(deltaTime, OldLocation, OldVelocity);	// empty super


}

#pragma region Custom Getters
float USTCharacterMovementComponent::GetMaxSpeed() const
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
		switch (static_cast<ESTCustomMovementMode>(CustomMovementMode))
		{
		case ESTCustomMovementMode::MOVE_None:
		{
			break;
		}
		case ESTCustomMovementMode::MOVE_InfiniteAngleWalking:
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

float USTCharacterMovementComponent::GetMaxAcceleration() const
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
		switch (static_cast<ESTCustomMovementMode>(CustomMovementMode))
		{
		case ESTCustomMovementMode::MOVE_None:
		{
			break;
		}
		case ESTCustomMovementMode::MOVE_InfiniteAngleWalking:
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

float USTCharacterMovementComponent::GetMaxBrakingDeceleration() const
{
	return Super::GetMaxBrakingDeceleration();
}
#pragma endregion

#pragma region Movement Mode and Physics
FString USTCharacterMovementComponent::GetMovementName() const
{
	if (MovementMode == MOVE_Custom)
	{
		// If this value is in our custom movement enum
		if (StaticEnum<ESTCustomMovementMode>()->IsValidEnumValue(CustomMovementMode))
		{
			// Return the display name
			return StaticEnum<ESTCustomMovementMode>()->GetDisplayNameTextByValue(CustomMovementMode).ToString();
		}
	}

	return Super::GetMovementName();
}

void USTCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
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

void USTCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);


	switch (static_cast<ESTCustomMovementMode>(CustomMovementMode))
	{
	case ESTCustomMovementMode::MOVE_None:
	{
		break;
	}
	case ESTCustomMovementMode::MOVE_InfiniteAngleWalking:
	{
		PhysInfiniteAngleWalking(deltaTime, Iterations);
		break;
	}
	default:
	{
		UE_LOG(LogSTCharacterMovementSetup, Warning, TEXT("%s has unsupported custom movement mode %d"), *CharacterOwner->GetName(), static_cast<uint8>(CustomMovementMode));
		SetMovementMode(EMovementMode::MOVE_Custom, static_cast<uint8>(ESTCustomMovementMode::MOVE_None));
		break;
	}
	}
}

#pragma region Custom Physics
void USTCharacterMovementComponent::PhysInfiniteAngleWalking(float deltaTime, int32 Iterations)
{

}
#pragma endregion
#pragma endregion


void USTCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) // DO NOT UTILIZE THIS EVENT FOR MOVEMENT
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
bool USTCharacterMovementComponent::IsMovingForward(/*float degreeTolerance*/) const // THIS CHECK DOES NOT WORK ON DEDICATED SERVER
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
