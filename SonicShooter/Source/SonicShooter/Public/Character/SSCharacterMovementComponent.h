// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "SSCharacterMovementComponent.generated.h"

class USSAbilitySystemComponent;
class UAS_Character;
class AAbilitySystemCharacter;

DECLARE_MULTICAST_DELEGATE(FCharacterMovementState);


/**
 * Custom movement modes. used when MovementMode == MOVE_Custom
 */
UENUM()
enum ECustomMovementMode																		// should we make this an enum class?
{
	/** None (custom movement is disabled). */
	CMOVE_None						UMETA(DisplayName="None"),
	/** Walking on a surface with the ability to walk up any slope angle */
	CMOVE_InfiniteAngleWalking		UMETA(DisplayName="InfiniteAngleWalking"),

	CMOVE_MAX						UMETA(Hidden)
};

/**
 * Our custom base implementation of the CMC
 * 
 *																An overview:
 * 
 * 
 * 
 * 
 * 
 * Movement restrictions:
 *		- Movement restrictions is a way to expose the CMC for gameplay related code. This is mainly for integration with the Gameplay Ability System.
 *			- Ex: if a stun grenade hits a character, you would set bCanRun to false for the duration of the stun and
 *			this would work flawlessly over the network
 * 
 *		- All movement restrictions should be correctable by the server (SEE: Custom client adjustment section below).
 *		
 * 
 * 
 * 
 * 
 * Custom client adjustment:
 *		1) To have custom CMC variables corrected by the server, make your own ClientAdjustPosition unreliable client RPC.
 *			- Add a parameter for each variable you want the server to correct (a good prefix is "adjusted" for example: bAdjustedCanRun).
 *			- In your _Implementation, set your correctable CMC variables to their corresponding "adjusted" variables.
 *				---------------------------------------------------------------------------------------------------
 *				| Example:
 *				---------------------------------------------------------------------------------------------------
 *				|	MyClientAdjustPosition_Implementation(bool bAdjustedCanRun, bool bAdjustedCanJump, float adjustedJumpHeight)
 *				|	{
 *  			|		bCanRun = bAdjustedCanRun;
 *  			|		bCanJump = bAdjustedCanJump;
 *  			|		jumpHeight = adjustedJumpHeight;
 *				|	}
 *				---------------------------------------------------------------------------------------------------
 * 
 *		2) Override the ClientAdjustPosition() function
 *			- NOT THE _IMPLEMENTATION! We want the server to call our RPC not the client.
 *			- Call the Super, and make it call your client adjust RPC.
 *			- This is a perfect event to call you custom client adjust RPCs.
 * 
 *		- If you have children CMCs and they also want custom client adjustment, they can repeat this process.
 *			- You may say all of these RPCs are bad and you are correct but the CMC in general is bad, this is the best solution.
 *				- Ex: if you are 3 levels deep of inheritance witht the CMC, thats 3 client RPCs at once when the client is corrected.
 * 
 * 
 * 
 * 
 * 
 * Integration with GAS:
 *		- Make heavy use of movement restrictions
 *			- You probably want a corresponding Gameplay Tag for each movement restriction
 *			- I would avoid setting the movement restrictions directly
 *			- Use RegisterGameplayTagEvent with EGameplayTagEventType::NewOrRemoved to have your movement restrictions synced with their gameplay tags
 * 
 *		- For movement abilities such as GA_CharacterRun
 *			- If something goes wrong set the abilities corresponding movement restriction to disable the movement (ex: set bCanRun to false)
 *				- In CanActivateAbility() whenever you return false, disable the movement
 *				- In ActivteAbility() anywhere you have CancelAbility(), disable the movement
 *			- This is an exception to not setting movement restrictions directly		]\]\]][		actually its not maybe use a GE for this
 *			-				talk about movement restrictions working as rollback			\-\-=\-\-\]-\]-\]\-\-]-\]-\-]\-=]\-=\]-]\-=\]
 * 
 * 
 * 
 * 
 *										I realized documenting this is probably a waste of time but its here if you want to finish it:
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
	

	friend class FSavedMove_SSCharacter;

public:
	USSCharacterMovementComponent();
	
	
	void SetWantsToRun(bool newWantsToRun);

#pragma region Movement Delegates
	FCharacterMovementState OnWantsToRun;
#pragma endregion

protected:
	//	Don't know for sure if this is the best event to use but works for now
	virtual void InitializeComponent() override;

	UPROPERTY()
		AAbilitySystemCharacter* OwnerAbilitySystemCharacter;
	UPROPERTY()
		USSAbilitySystemComponent* OwnerSSASC;
	UPROPERTY()
		UAS_Character* CharacterAttributeSet;

	UFUNCTION()
		virtual void OnOwningCharacterAbilitySystemReady();

	//BEGIN CMC Interface
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void OnMovementUpdated(float deltaTime, const FVector& OldLocation, const FVector& OldVelocity) override;
	virtual float GetMaxAcceleration() const override;
	virtual FString GetMovementName() const override;
	virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	//END CMC Interface

	//BEGIN UMovementComponent Interface
	virtual float GetMaxSpeed() const override;
	//END UMovementComponent Interface

#pragma region Compressed Flags
	uint8 bWantsToRun : 1;
#pragma endregion

	// This is a good event for calling your custom client adjustment RPCs
	virtual void ClientAdjustPosition(float TimeStamp, FVector NewLoc, FVector NewVel, UPrimitiveComponent* NewBase, FName NewBaseBoneName, bool bHasBase, bool bBaseRelativePosition, uint8 ServerMovementMode) override;
	//UFUNCTION(Unreliable, Client)
	//	virtual void SSClientAdjustPosition();
	//virtual void SSClientAdjustPosition_Implementation();

#pragma region Movement Restrictions
	void OnRunDisabledTagChanged(const FGameplayTag Tag, int32 NewCount);
	/** This bool is only and optimization thing. We dont want to be checking HasMatchingTag every frame in GetMaxSpeed() */
	uint8 bRunDisabled : 1;
#pragma endregion


	TEnumAsByte<ECustomMovementMode> CustomMovementMode;

#pragma region Custom Movement Physics
	virtual void PhysInfiniteAngleWalking(float deltaTime, int32 Iterations);
#pragma endregion
};


#define FLAG_WantsToRun FSavedMove_SSCharacter::FLAG_Custom_0

class FSavedMove_SSCharacter : public FSavedMove_Character
{
public:
	typedef FSavedMove_Character Super;


	virtual void Clear() override;
	virtual void PrepMoveFor(ACharacter* Character) override;
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;
	virtual uint8 GetCompressedFlags() const override;

protected:
	uint8 bSavedWantsToRun : 1;
};

class FNetworkPredictionData_Client_SSCharacter : public FNetworkPredictionData_Client_Character
{
public:
	typedef FNetworkPredictionData_Client_Character Super;


	FNetworkPredictionData_Client_SSCharacter(const UCharacterMovementComponent& ClientMovement);

	virtual FSavedMovePtr AllocateNewMove() override;
};
