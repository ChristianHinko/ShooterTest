// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "Console/CVarChangeListenerManager.h"

#include "SSCharacterMovementComponent.generated.h"


class ASSCharacter;
class UAbilitySystemComponent;
class UAS_CharacterMovement;



DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterMovementWantsToChanged, bool);
DECLARE_MULTICAST_DELEGATE(FCharacterMovementStateNotify);


/**
 * Custom movement modes. Used when MovementMode == MOVE_Custom
 */
UENUM()
enum class ECustomMovementMode : uint8
{
	/** None (custom movement is disabled). */
	MOVE_None						UMETA(DisplayName = "None"),
	/** Walking on a surface with the ability to walk up any slope angle */
	MOVE_InfiniteAngleWalking		UMETA(DisplayName = "Infinite Angle Walking"),

	MOVE_MAX						UMETA(Hidden)
};

/**
 * Our custom base implementation of the CMC
 *
 *																An overview:
 *													--- not everything is documented ---
 *
 *
 * Movement restrictions:
 *		- Movement restrictions is a way to expose the CMC for gameplay related code.
 *			- Ex: if a stun grenade hits a character, you would set bRunDisabled to true (or add the Gameplay Tag RunDisabled) for the duration of the stun and
 *			this would work flawlessly over the network
 *
 *
 *
 * Integration with GAS:
 *		- Do not try to make your movement abilities set compressed flags
 *			- This would be predictively predicting (ability prediction predicting a movement prediction all in one) a move which gets really weird
 *		- Make your movement ability just directly call the move function in the CMC
 *			- So instead of making your run ability synced with the bWantsToRun, make it synced with bIsRunning. Make it call Run() rather than SetWantsToRun(true).
 *			- Whenever you want to perform a move, activate the movement ability instead. And whenever you are no longer able to be doing
 *				that move, cancel the ability and have the EndAbility() unperform the move.
 *		- Now to ensure your movement abilities are not client authoritative
 *			- In CanActivateAbility(), check whether you can perform the move or not using the Can___InCurrentState() functions so
 *				that the client and server determine whether they can move or not independently
 *			- Make sure your movement abilities (though all of your abilities should have this) have NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ServerOnlyTermination and bServerRespectsRemoteAbilityCancellation = false.
 *			- When you want to stop a movement (maybe in UpdateCharacterStateBeforeMovement()), cancel the movement ability so that the server ends the client.
 *
 *
 *
 *
 * Custom client adjustment:
 *		- Client adjustment occurs when the difference between the client and server's position exceed an allowable threshold or when the client and
 *			server's movement modes do not match up.
 *		- Variables to consider puting in a custom client adjustment should be ones that the server only needs to send when a client correction occurs.
 *			- Therefore you should only consider making a variable a client adjustment variable if it is position related or physics related.
 *			- It is rare to need a custom client adjustment.
 *				- One of the few cases I can think of is that you may want to make your custom movement mode enum an adjustable variable.
 *
 *		1) To have custom client adjustment variables, make your own ClientAdjustPosition unreliable client RPC.
 *			- Add a parameter for each variable you want the server to correct (a good prefix is "adjusted" for example: AdjustedCustomMovementMode).
 *			- In your _Implementation, set your adjustable CMC variables to their corresponding "adjusted" variables.
 *				---------------------------------------------------------------------------------------------------
 *				| Example:
 *				---------------------------------------------------------------------------------------------------
 *				|	MyClientAdjustPosition_Implementation(uint8 AdjustedCustomMovementMode, FVector AdjustedMyPositionRelatedVariable)
 *				|	{
 *  			|		CustomMovementMode = AdjustedCustomMovementMode;
 *				|		MyPositionRelatedVariable = AdjustedMyPositionRelatedVariable;
 *				|	}
 *				---------------------------------------------------------------------------------------------------
 *
 *		2) Override the ClientAdjustPosition() function as an event to call your custom RPCs
 *			- NOT THE _IMPLEMENTATION! We want the server to call the RPC not the client.
 *			- Call the Super, and make it call your client adjust RPC.
 *			- This is a perfect event to call your custom client adjust RPCs.
 *
 *		- If you have children CMCs and they also want custom client adjustment, they can repeat this process.
 *			- You may say all of these RPCs are bad and you are correct but the CMC in general is bad, this is the best and most clean solution.
 *				- Ex: if you are 3 levels deep of inheritance witht the CMC, thats 3 client RPCs at once when the client is corrected.
 *
 *
 *
 *
 *
 *
 *										I realized documenting this is probably a waste of time but its here if you want to finish it:
 *
 * Steps to make a custom move:
 *		1) Make a function for activating it (ex: SetWantsToRun)
 *		2) Make a corresponding compressed movement flag for the move
 *			- Its good to define a macro representing that flag
 *		3)
 */
UCLASS()
class SONICSHOOTER_API USSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	friend class FSSSavedMove_Character;
public:
	USSCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);


	bool GetToggleCrouchEnabled() const { return bToggleCrouchEnabled; }
	bool GetToggleRunEnabled() const { return bToggleRunEnabled; }

	/**
	 * Desire cancellations.
	 *
	 * If a movements's toggle mode is enabled, then another movement can cancel the player's desire to do it.
	 * Ex: If bRunCancelsDesireToRun is true and bToggleRunEnabled is true, then when you crouch, that means
	 * that you don't want to run. So if you are running and you crouch and uncrouch, you will no longer be running (even though you may be able to).
	 */
	uint8 bCrouchCancelsDesireToRun : 1;
	uint8 bRunCancelsDesireToCrouch : 1;
	uint8 bJumpCancelsDesireToCrouch : 1;
	uint8 bJumpCancelsDesireToRun : 1;


	/**
	 * Set WantsTos.
	 *
	 * Is replicated to the server but doesn't actually make the character run. Whether you run or not is also depenent on CanRunInCurrentState which
	 * is calculated on the local machine (the server and client independently determine whether you actually run or not)
	 */
	void SetWantsToRun(bool newWantsToRun);
	bool GetWantsToRun() const { return bWantsToRun; }

	/**
	 * Can In Current State.
	 *
	 * Checks on whether you actually can perform moves or not. This gives security to the client->server replicated compressed flags (or WantsTo bools)
	 */
	virtual bool CanAttemptJump() const override;
	uint8 bCanCrouchJump : 1;
	virtual bool CanCrouchInCurrentState() const override;
	virtual bool CanRunInCurrentState() const;


	/** Basically a UpdateCharacterStateBeforeMovement() for the jump */
	virtual void CheckJumpInput(float DeltaTime);
	virtual void ClearJumpInput(float DeltaTime);

	/**
	 * Boolean Timestamps.
	 *
	 * Represent the timestamp the moment wanted to do something.
	 * If negative, represents the timestamp the moment you stopped wanting to do something.
	 * And, I guess, if zero, null which is kind of cool.
	 */
	float TimestampWantsToJump;
	FCharacterMovementWantsToChanged OnWantsToJumpChanged;
	float TimestampWantsToCrouch;
	FCharacterMovementWantsToChanged OnWantsToCrouchChanged;
	float TimestampWantsToRun;
	FCharacterMovementWantsToChanged OnWantsToRunChanged;


	float CurrentTimeSeconds;
	void BroadcastMovementDelegates();


	/** Whether we are actually running or not */
	bool IsRunning() const;

	/** Actually makes the character run, should not be called directly and is only public so that replicated character bIsRunning state can call this */
	virtual void Run();
	/** Actually makes the character stop running, should not be called directly */
	virtual void UnRun();


	virtual bool DoJump(bool bReplayingMoves) override;
	virtual void UnJump();

	/** If true, we are in the air because of a jump */
	uint8 bJumpedInAir : 1;


	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;



	FRotator CurrentRotationRate;

	FCharacterMovementStateNotify OnAccelerationStart;
	FCharacterMovementStateNotify OnAccelerationStop;

	FCharacterMovementStateNotify OnStartedFalling;
	FCharacterMovementStateNotify OnStoppedFalling;


	//BEGIN UCharacterMovementComponent Interface
	virtual FString GetMovementName() const override;
	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;
	virtual float GetMaxBrakingDeceleration() const override;
	//END UCharacterMovementComponent Interface

protected:
	virtual void InitializeComponent() override;

	UPROPERTY()
		TWeakObjectPtr<ASSCharacter> SSCharacterOwner;
	UPROPERTY()
		TWeakObjectPtr<UAbilitySystemComponent> OwnerASC;
	UPROPERTY()
		TWeakObjectPtr<UAS_CharacterMovement> CharacterMovementAttributeSet;

	virtual void OnAbilitySystemSetUpPreInitialized(UAbilitySystemComponent* const PreviousASC, UAbilitySystemComponent* const NewASC);
	virtual void OnAbilitySystemSetUp(UAbilitySystemComponent* const PreviousASC, UAbilitySystemComponent* const NewASC);

	//BEGIN UCharacterMovementComponent Interface
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	virtual void OnMovementUpdated(float deltaTime, const FVector& OldLocation, const FVector& OldVelocity) override;
	virtual void UpdateCharacterStateAfterMovement(float DeltaSeconds) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; // DO NOT UTILIZE THIS EVENT FOR MOVEMENT
	//END UCharacterMovementComponent Interface

	// A new thing added to the engine NOTE: look into this and see if we need to fix anything because of this
	virtual void ServerMove_PerformMovement(const FCharacterNetworkMoveData& MoveData) override;


#pragma region Compressed Flags
	uint8 bWantsToRun : 1;
#pragma endregion

	/** WARNING: This check does not work on dedicated server */
	bool IsMovingForward(/*float degreeTolerance = 45.f*/) const;


	/**
	 * Tweak the user's move desires before ticking
	 */
	virtual void TweakCompressedFlagsBeforeTick();

	/** For calculating whether we WANT to run or not */
	virtual void TweakWantsToRunBeforeTick(bool& outTweakedWantsToRun) const;


	//// This is a good event for calling your custom client adjustment RPCs
	//virtual void ClientAdjustPosition(float TimeStamp, FVector NewLoc, FVector NewVel, UPrimitiveComponent* NewBase, FName NewBaseBoneName, bool bHasBase, bool bBaseRelativePosition, uint8 ServerMovementMode) override;
	//UFUNCTION(Unreliable, Client)
	//	virtual void SSClientAdjustPosition();
	//virtual void SSClientAdjustPosition_Implementation();

#pragma region Movement Restrictions
	void OnRunDisabledTagChanged(const FGameplayTag Tag, int32 NewCount);
	/** This bool is only and optimization layer. We dont want to be checking HasMatchingTag all of the time */
	uint8 bRunDisabled : 1;

	void OnJumpDisabledTagChanged(const FGameplayTag Tag, int32 NewCount);
	uint8 bJumpDisabled : 1;

	void OnCrouchDisabledTagChanged(const FGameplayTag Tag, int32 NewCount);
	uint8 bCrouchDisabled : 1;
#pragma endregion

#pragma region Custom Movement Physics
	virtual void PhysInfiniteAngleWalking(float deltaTime, int32 Iterations);
#pragma endregion

#pragma region Input CVars
	FBoolCVarChangedSignature CVarToggleCrouchChangeDelegate;
	UFUNCTION()
		void CVarToggleCrouchChanged(bool newToggleCrouch);
	uint8 bToggleCrouchEnabled : 1;

	FBoolCVarChangedSignature CVarToggleRunChangeDelegate;
	UFUNCTION()
		void CVarToggleRunChanged(bool newToggleRun);
	uint8 bToggleRunEnabled : 1;
#pragma endregion

private:
	FRotator PreviousRotation;
};


#define FLAG_WantsToRun FSavedMove_Character::CompressedFlags::FLAG_Custom_0

class FSSSavedMove_Character : public FSavedMove_Character
{
	typedef FSavedMove_Character Super;
public:
	virtual void Clear() override;
	virtual void PrepMoveFor(ACharacter* Character) override;
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;
	virtual uint8 GetCompressedFlags() const override;

protected:
	uint8 bSavedWantsToRun : 1;

};

class FSSNetworkPredictionData_Client_Character : public FNetworkPredictionData_Client_Character
{
	typedef FNetworkPredictionData_Client_Character Super;
public:
	FSSNetworkPredictionData_Client_Character(const UCharacterMovementComponent& ClientMovement);


	virtual FSavedMovePtr AllocateNewMove() override;

};
