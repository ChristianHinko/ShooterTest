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
 *						OUTDATED DOCUMENTATION
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
 * 
 * 
 * 
 * Integration with GAS:
 *		- The Ability System is heavily gameplay related so we need a way for gameplay to affect movement
 *			- You cannot simply have a run ability that checks stamina like this:
 *						 															if (has stamina)
 *						 																CMC->SetWantsToRun(true)
 * 
 *				because SetWantsToRun is client authoritative and tells the server to run through the fsavedmove.
 *					- If the client passes the stamina check on his activation but the server doesn't, then the client will run while the server doesn't causing a
 *						client correction right?
 *					- And if the client predictively activates the ability but the server rolls it back, then the rollback will make the client stop running right?
 *					- Wrong, it doensn't matter, the character is going to run on the server too because the client's SetWantsToRun told the server to do so.
 *						- SetWantsToRun is client authoritative, once its called it will in turn set the server's WantsToRun as well.
 * 
 *			- To fix this we will need a Gameplay Tag that determines whether you can run or not.
 *				- This tag, when added, will disable running for the CMC (ex: "Character.Movement.RunDisabled").
 *				- We will have to implement what this tag does deep in the CMC level rather than the ability level.
 *				- Now whenever you check if bWantsToRun in the CMC, also make sure the owning ASC does not have the RunDisabled tag.
 *				- Checking if the player has the tag every time is annoying and not efficient.
 *					- To simplify this, make a corresponding bool for that tag (ex: bRunDisabled)
 *					- Use the RegisterGameplayTagEvent with EGameplayTagEventType::NewOrRemoved and if the tag count is > 0, that means the tag was added so
 *						set bRunDisabled = true, else the tag was removed to set bRunDisabled = false.
 *					- Never touch the bRunDisabled bool, only read from it. And do not make it a client adjustment variable, the Gameplay Tag will replicate so the client will
 *						always have the correct value.
 *																								\][\][\]\']'\]\[]\[			TODO: document
 * 
 * 
 * 
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
 * 
 * 
 * Custom client adjustment:
 *		- Client adjustment occurs when the difference between the client and server's position exceed an allowable threshold or when the client and 
 *			server's movement modes do not match up.
 *		- Variables to consider puting in a custom client adjustment should be ones that the server only needs to send when a client correction occurs.
 *			- Therefore you should only consider making a variable a client adjustment variable if it is position related or movement mode related.
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
	

	friend class FSavedMove_SSCharacter;

public:
	USSCharacterMovementComponent();
	
	/** This is client authoritative. So calling this will always make the character run (on both client and server). Very insecure */
	void SetWantsToRun(bool newWantsToRun);

	bool IsMovingForward(/*float degreeTolerance = 99.f*/);

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
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	virtual void OnMovementUpdated(float deltaTime, const FVector& OldLocation, const FVector& OldVelocity) override;
	virtual float GetMaxAcceleration() const override;
	virtual FString GetMovementName() const override;
	virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	//END CMC Interface

	virtual bool CanAttemptJump() const override;

	virtual bool CanCrouchInCurrentState() const override;
	virtual bool CanRunInCurrentState() const;

	//BEGIN UMovementComponent Interface
	virtual float GetMaxSpeed() const override;
	//END UMovementComponent Interface

#pragma region Compressed Flags
	uint8 bWantsToRun : 1;
#pragma endregion

	/** Whether we are actually running */
	uint8 bIsRunning : 1;

	// This is a good event for calling your custom client adjustment RPCs
	virtual void ClientAdjustPosition(float TimeStamp, FVector NewLoc, FVector NewVel, UPrimitiveComponent* NewBase, FName NewBaseBoneName, bool bHasBase, bool bBaseRelativePosition, uint8 ServerMovementMode) override;
	//UFUNCTION(Unreliable, Client)
	//	virtual void SSClientAdjustPosition();
	//virtual void SSClientAdjustPosition_Implementation();

#pragma region Movement Restrictions
	void OnRunDisabledTagChanged(const FGameplayTag Tag, int32 NewCount);
	/** This bool is only and optimization layer. We dont want to be checking HasMatchingTag every frame in GetMaxSpeed() */
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
