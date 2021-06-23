// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AbilitySystemSetupCharacter.h"

#include "SSCharacter.generated.h"


class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class USSCharacterMovementComponent;
class ASSGameState;
class UAS_CharacterMovement;
class UAS_Stamina;



/**
 * Handles physical animation while crouching/uncrouching
 */
USTRUCT()
struct FCrouchTickFunction : public FTickFunction
{
	GENERATED_BODY()


		FCrouchTickFunction()
	{
		// This bool doesn't actually do anything for some reason so we have to call SetTickFunctionEnable after
		bStartWithTickEnabled = false;
		SetTickFunctionEnable(bStartWithTickEnabled);

		TickGroup = ETickingGroup::TG_PostPhysics; // the latest tick that occurs before rendering


		// Optimizations:

		bAllowTickOnDedicatedServer = false; // dedicated server shouldn't care about this visual effect
		//bRunOnAnyThread = true; // i want to do this but we set component locations in the tick so we can't
	}

	ASSCharacter* Target;

	virtual void ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;

	virtual FString DiagnosticMessage() override
	{
		return FString(TEXT("FCrouchTickFunction"));
	}

	virtual FName DiagnosticContext(bool bDetailed) override
	{
		return FName(TEXT("ASSCharacter"));
	}
};

template<>
struct TStructOpsTypeTraits<FCrouchTickFunction> : public TStructOpsTypeTraitsBase2<FCrouchTickFunction>
{
	enum
	{
		WithCopy = false
	};
};

/**
 * Base character class
 */
UCLASS()
class ASSCharacter : public AAbilitySystemSetupCharacter
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere, Category = "Character")
		USkeletalMeshComponent* POVMesh; // should this exist on every character (including AI)?
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* CameraBoom;

public:
	ASSCharacter(const FObjectInitializer& ObjectInitializer);

	// Components
	USkeletalMeshComponent* GetPOVMesh() const { return POVMesh; }
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	UAS_CharacterMovement* GetCharacterAttributeSet() const { return CharacterMovementAttributeSet; }
	UAS_Stamina* GetStaminaAttributeSet() const { return StaminaAttributeSet; }

#pragma region Abilities
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Abilities")
		TSubclassOf<UASSGameplayAbility> CharacterJumpAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle CharacterJumpAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Abilities")
		TSubclassOf<UASSGameplayAbility> CharacterCrouchAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle CharacterCrouchAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Abilities")
		TSubclassOf<UASSGameplayAbility> CharacterRunAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle CharacterRunAbilitySpecHandle;
#pragma endregion


	USSCharacterMovementComponent* GetSSCharacterMovementComponent() const { return SSCharacterMovementComponent; }

	/** Whether we are actually running. Replicated to simulated proxies so that they can simulate server movement */
	UPROPERTY(ReplicatedUsing = OnRep_IsRunning)
		uint8 bIsRunning : 1;

	/** If true, after toggling run, you can't untoggle run. You can only stop running by stopping moving forward for example. */
	uint8 bToggleRunAlwaysRun : 1;

	/**
	 * Whether we are actually jumping (only while the player is actively jumping or holding down jump).
	 * Should this be replicated to simulated proxies like bIsRunning is? Maybe if you are using a button hold dependent jump you may have to do this  =@REVIEW MARKER@=.
	 *
	 * If you are looking for a variable that represents whether we are in the air because of a jump, look in the CMC: bJumpedInAir.
	 */
	uint8 bIsJumping : 1;


	bool GetFirstPerson() const { return bFirstPerson; }

	/** Sets bFirstPerson and changes all of the necessary properties to switch to TP/FP. */
	UFUNCTION(Exec)
		void SetFirstPerson(bool newFirstPerson);

	UPROPERTY(EditAnywhere, Category = "First Person")
		float ThirdPersonCameraArmLength;

	float GetForwardInputAxis() const { return forwardInputAxis; }
	float GetRightInputAxis() const { return rightInputAxis; }

	virtual void Jump() override;
	virtual void StopJumping() override;

	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;

	virtual bool CanCrouch() const override; // this function isn't being used but we're overriding it anyways
	virtual void OnStartCrouch(float HeightAdjust, float ScaledHeightAdjust) override;
	virtual void OnEndCrouch(float HeightAdjust, float ScaledHeightAdjust) override;

	virtual void RecalculateBaseEyeHeight() override;


	void CrouchTick(float DeltaTime);


	APawn* GetNearestPawn();

protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	virtual void PostInitProperties() override;
	virtual void PostInitializeComponents() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CreateAttributeSets() override;
	virtual void RegisterAttributeSets() override;
	virtual void GrantStartingAbilities() override;

	UPROPERTY()
		USSCharacterMovementComponent* SSCharacterMovementComponent;

	/** Whether we are currently in first person. NOTE: ONLY DIRECTLY SET THIS IN THE CONSTRUCTOR OR IN BP otherwise use the setter. */
	UPROPERTY(EditAnywhere, Category = "First Person")
		uint8 bFirstPerson : 1;

	virtual bool CanJumpInternal_Implementation() const override;
	virtual void CheckJumpInput(float DeltaTime) override;
	virtual void ClearJumpInput(float DeltaTime) override;

	UFUNCTION()
		virtual void OnRep_IsRunning();

	float CrouchSpeed;

	FCrouchTickFunction CrouchTickFunction;
	//FCrouchTickFunction& GetCrouchTickFunction() const { return CrouchTickFunction; }

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


#pragma region Input Events
	//Actions
	virtual void OnRunPressed();
	virtual void OnRunReleased();

	virtual void OnJumpPressed();
	virtual void OnJumpReleased();

	virtual void OnCrouchPressed();
	virtual void OnCrouchReleased();

	virtual void OnInteractPressed();
	virtual void OnInteractReleased();

	virtual void OnPrimaryFirePressed();
	virtual void OnPrimaryFireReleased();

	virtual void OnSecondaryFirePressed();
	virtual void OnSecondaryFireReleased();

	virtual void OnReloadPressed();
	virtual void OnReloadReleased();

	virtual void OnItem0Pressed();
	virtual void OnItem0Released();

	virtual void OnItem1Pressed();
	virtual void OnItem1Released();

	virtual void OnItem2Pressed();
	virtual void OnItem2Released();

	virtual void OnItem3Pressed();
	virtual void OnItem3Released();

	virtual void OnItem4Pressed();
	virtual void OnItem4Released();

	virtual void OnSwitchWeaponPressed();
	virtual void OnSwitchWeaponReleased();

	virtual void OnNextItemPressed();
	virtual void OnNextItemReleased();

	virtual void OnPreviousItemPressed();
	virtual void OnPreviousItemReleased();

	virtual void OnDropItemPressed();
	virtual void OnDropItemReleased();

	virtual void OnPausePressed();
	virtual void OnPauseReleased();

	virtual void OnScoreSheetPressed();
	virtual void OnScoreSheetReleased();


	//Axis
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);

	virtual void HorizontalLook(float Rate);
	virtual void VerticalLook(float Rate);
#pragma endregion

	float forwardInputAxis;
	float rightInputAxis;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	float HorizontalSensitivity;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	float VerticalSensitivity;


private:
	UPROPERTY(Replicated)
		UAS_CharacterMovement* CharacterMovementAttributeSet;
	UPROPERTY(Replicated)
		UAS_Stamina* StaminaAttributeSet;


	float crouchToHeight;
};
