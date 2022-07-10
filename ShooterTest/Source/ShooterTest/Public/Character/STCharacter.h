// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Examples/ASSCharacter_Example.h"

#include "STCharacter.generated.h"


class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UGSActorComponent_PawnExtension;
class USTCharacterMovementComponent;
class UPlayerMappableInputConfig;
class UInputAction;
struct FInputActionValue;



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


	UPROPERTY()
		TWeakObjectPtr<ASTCharacter> Target;

	virtual void ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;


	virtual FString DiagnosticMessage() override
	{
		return TNameOf<FCrouchTickFunction>::GetName();
	}
	virtual FName DiagnosticContext(bool bDetailed) override
	{
		return TNameOf<ASTCharacter>::GetName();
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
 * Game's base Character class
 */
UCLASS()
class ASTCharacter : public AASSCharacter_Example
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere, Category = "Character")
		TObjectPtr<USkeletalMeshComponent> POVMesh;
	static const FName POVMeshComponentName;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "GameSetup")
		TObjectPtr<UGSActorComponent_PawnExtension> GSPawnExtensionComponent;

public:
	ASTCharacter(const FObjectInitializer& ObjectInitializer);

	// Subobject getters
	USkeletalMeshComponent* GetPOVMesh() const { return POVMesh; }
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	USTCharacterMovementComponent* GetSTCharacterMovementComponent() const { return STCharacterMovementComponent.Get(); }


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

	/** Replicated so we can see where remote clients are looking. */
	UPROPERTY(Replicated)
		uint8 RemoteViewYaw;
	/**
	 * Set Pawn ViewYaw, so we can see where remote clients are looking.
	 * Maps 360.0 degrees into a byte
	 * @param	NewRemoteViewYaw	Yaw component to replicate to remote (non owned) clients.
	 */
	void SetRemoteViewYaw(float NewRemoteViewYaw);
	virtual FRotator GetBaseAimRotation() const override;

	virtual void Jump() override;
	virtual void StopJumping() override;

	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;

	virtual bool CanCrouch() const override; // this function isn't being used but we're overriding it anyways
	virtual void OnStartCrouch(float HeightAdjust, float ScaledHeightAdjust) override;
	virtual void OnEndCrouch(float HeightAdjust, float ScaledHeightAdjust) override;

	virtual void RecalculateBaseEyeHeight() override;


	void CrouchTick(float DeltaTime);

protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	virtual void PostInitProperties() override;
	virtual void PostInitializeComponents() override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


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


	//  BEGIN Input setup
	UPROPERTY(EditAnywhere, Category = "Input|Config")
		TArray<TObjectPtr<UPlayerMappableInputConfig>> PlayerMappableInputConfigs;


	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionRun;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionJump;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionCrouch;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionInteract;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionPrimaryFire;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionSecondaryFire;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionReload;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionSwapToLayout1st;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionSwapToLayout2nd;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionSwapToLayout3rd;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionSwapToLayout4th;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionSwapToLayout5th;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionSwapToPreviousSlot;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionSwapToLayoutForward;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionSwapToLayoutBackward;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionDropItem;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionPause;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionScoreSheet;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionMove;
	UPROPERTY(EditDefaultsOnly, Category = "Input|Actions")
		TObjectPtr<const UInputAction> InputActionLook;






	virtual void OnPressedRun();
	virtual void OnReleasedRun();

	virtual void OnPressedJump();
	virtual void OnReleasedJump();

	virtual void OnPressedCrouch();
	virtual void OnReleasedCrouch();

	virtual void OnPressedInteract();
	virtual void OnReleasedInteract();

	virtual void OnPressedPrimaryFire();
	virtual void OnReleasedPrimaryFire();

	virtual void OnPressedSecondaryFire();
	virtual void OnReleasedSecondaryFire();

	virtual void OnPressedReload();
	virtual void OnReleasedReload();

	virtual void OnPressedSwapToLayout1st();
	virtual void OnReleasedSwapToLayout1st();

	virtual void OnPressedSwapToLayout2nd();
	virtual void OnReleasedSwapToLayout2nd();

	virtual void OnPressedSwapToLayout3rd();
	virtual void OnReleasedSwapToLayout3rd();

	virtual void OnPressedSwapToLayout4th();
	virtual void OnReleasedSwapToLayout4th();

	virtual void OnPressedSwapToLayout5th();
	virtual void OnReleasedSwapToLayout5th();

	virtual void OnPressedSwapToPreviousSlot();
	virtual void OnReleasedSwapToPreviousSlot();

	virtual void OnPressedSwapToLayoutForward();
	virtual void OnReleasedSwapToLayoutForward();

	virtual void OnPressedSwapToLayoutBackward();
	virtual void OnReleasedSwapToLayoutBackward();

	virtual void OnPressedDropItem();
	virtual void OnReleasedDropItem();

	virtual void OnPressedPause();
	virtual void OnReleasedPause();

	virtual void OnPressedScoreSheet();
	virtual void OnReleasedScoreSheet();

	virtual void OnMove(const FInputActionValue& InputActionValue);
	virtual void OnLook(const FInputActionValue& InputActionValue);
	//  END Input setup


private:
	// Cached STCharacterMovementComponent
	UPROPERTY()
		TWeakObjectPtr<USTCharacterMovementComponent> STCharacterMovementComponent;


	float CrouchToHeight;
};
